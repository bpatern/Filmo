#include "dial.h"


Dial::Dial() : control()
{
    _potQueue = xQueueCreate(1, sizeof(uint16_t));

    _potRead = 0;
    _potReadOld = 0;
   _potReadUnscaled = 0;
   _pin = ADC_CHANNEL_0;
   _resolution = 0;
   _min = 0;
   _max = 0;
   _potSampleCounter = 0;

       init_config = {
        .unit_id = ADC_UNIT_1,
        .clk_src = ADC_RTC_CLK_SRC_DEFAULT,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };
    adc_oneshot_new_unit(&init_config, &_adc_handle);
        channel_config = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_12,
    };


}

inline float Dial::_map(float x, float in_min, float in_max, float out_min, float out_max)
{
   const float run = in_max - in_min;
  if (run == 0) {
    // log_e("map(): Invalid input range, min == max");
    return -1;  // AVR returns -1, SAM returns 0
  }
  const float rise = out_max - out_min;
  const float delta = x - in_min;
  return (delta * rise) / run + out_min;
}

Dial::Dial(uint8_t attachTo, uint8_t resolution, uint16_t min, uint16_t max)
{
    
    init(attachTo, resolution, min, max);
}

float Dial::kalmanUpdateEstimate(float mea)
{
  _kalman_gain = _err_estimate / (_err_estimate + _err_measure);
  _current_estimate = _last_estimate + _kalman_gain * (mea - _last_estimate);
  _err_estimate = (1.0f - _kalman_gain) * _err_estimate + (float)(_last_estimate - _current_estimate) * _q;
  _last_estimate = _current_estimate;

  return _current_estimate;
}

void Dial::readPot()
{
    for(;;)
    {
    adc_oneshot_read(_adc_handle, _pin, &_potReadRaw);

    // _potSampleStorage[_potSampleCounter] = _potReadRaw;
    // _potSampleCounter++;

    // if (_potSampleCounter > 1)
    // {
    //     _potReadOld = _potRead;
    //   _potReadUnscaled = 0;
    //   if (_potReadOld != 0)
    //   {
    //   for(int i = 0; i < _potSampleCounter; i++)
    //   {

    //       _potReadUnscaled = _potReadUnscaled + _potSampleStorage[i];
    //   }
    //   _potReadUnscaled = _potReadUnscaled / _potSampleCounter;
    // } else
    // {
    // }

      _potRead = (uint32_t)kalmanUpdateEstimate((float)_potReadRaw);

    //   if (_min != 0 && _max != 4096)
    //   {
    //   _potRead = _map(_potRead, 10, 4096, _min, _max);
    //   }





    //   _potSampleCounter = 0;


    // }



        xQueueSend(_potQueue, &_potRead, 5); // send motor pot value to motor task via queue

        vTaskDelay(30 / portTICK_PERIOD_MS);
    }
}

void Dial::startTaskImpl(void* _this){((Dial*)_this)->readPot();}


void Dial::init(uint8_t attachTo, uint8_t resolution, uint16_t min, uint16_t max)
{

       _pin = (adc_channel_t)attachTo;
    _resolution = resolution;
    _min = min;
    _max = max;



    
    adc_oneshot_config_channel(_adc_handle, _pin, &channel_config);


    xTaskCreatePinnedToCore(
            this->startTaskImpl,
            "Parse POT",
            8000,
            this,
            configMAX_PRIORITIES - 6,
            &_stackHandle,
            1);
    vTaskSuspend(_stackHandle);

    // #ifdef CONFIG_IDF_TARGET_ESP32

    // _pin = attachTo;

    // #endif
}

void Dial::begin()
{
    vTaskResume(_stackHandle);
}

uint16_t Dial::readValue()
{
    xQueueReceive(_potQueue, &res, 5);
    return res;
}