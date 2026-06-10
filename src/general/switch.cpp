#include "switch.h"
#include <cstdint>
#define DEBOUNCE_DELAY_US 10000ULL // Debounce delay in microseconds (50 ms)
extern void prepareISR();
extern void IRAM_ATTR switchGet(void *arg);

playbackControl::playbackControl() {
    _stopPin = -1;
    _runPin = -1;
    _revPin = -1;
    _rewindPin = -1;
    _type = none;
    _internalDirection = N_A;
}

playbackControl::playbackControl(playbackControlType type, uint8_t runPin, uint8_t stopPin, uint8_t revPin, uint8_t rewindPin) {
    init(type, runPin, stopPin, revPin, rewindPin);
}
int playbackControl::checkPin(uint8_t pin) {
return gpio_get_level((gpio_num_t)pin);
}
direction playbackControl::readDirection(direction dir)
{
    if (_type == toggle)
    {
        if (dir == N_A)
        {
            if (checkPin(_runPin) == 0)
            {
            _internalDirection = _stop;
            } else if (checkPin(_runPin) == 1)
            {
                if (checkPin(_revPin) != 1)
                {
                    _internalDirection = forward;

                } else if (checkPin(_revPin) == 1)
                {
                    _internalDirection = reverse;
                }
            }
        }
    } 
    
    else if (_type == dial)
    {
        if (dir == N_A)
        {
            if (checkPin(_runPin) == 0 && checkPin(_revPin) == 0)
            {
            _internalDirection = _stop;
            } else
            {
                if (checkPin(_runPin) == 1)
                {
                    _internalDirection = forward;
                } else if (checkPin(_revPin) == 1)
                {
                    _internalDirection = reverse;
                }
            }

        }
    }

    xQueueSend(runMsg, &_internalDirection, 2);


    return _internalDirection;

}

void playbackControl::init(playbackControlType type, uint8_t runPin, uint8_t stopPin, uint8_t revPin, uint8_t rewindPin) {
    _stopPin = stopPin;
    _runPin = runPin;
    _revPin = revPin;
    _rewindPin = rewindPin;
    _type = type;

        gpio_config_t fwd_conf = {
        .pin_bit_mask = (1ULL << (gpio_num_t)_runPin),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE};
        gpio_config(&fwd_conf);

        if(_revPin != 99)
        {
        gpio_config_t rev_conf = {
        .pin_bit_mask = (1ULL << (gpio_num_t)_revPin),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE};
        gpio_config(&rev_conf);
        }

        if(_stopPin != 99)
        {
        gpio_config_t stop_conf = {
        .pin_bit_mask = (1ULL << (gpio_num_t)_stopPin),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE};
        gpio_config(&stop_conf);
        }

        if(_rewindPin != 99)
        {
        gpio_config_t rewind_conf = {
        .pin_bit_mask = (1ULL << (gpio_num_t)_rewindPin),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE};
        gpio_config(&rewind_conf);
        }

        readDirection();
}








Button::Button() : control() 
 {
    _pinMsg = xQueueCreate(1, sizeof(bool));
    _lastPress = 0;
    _currentPress = 0;
    _lastPresstime = 0;
    _timenow = 0;
}

Button::Button(uint8_t attachTo, switchmode buttonMode, bool debounce)
{
    init(attachTo, buttonMode, debounce);
}

void Button::parseIO()
{
    for(;;){
        _timenow = esp_timer_get_time();
        _lastPress = _currentPress;
        _currentPress = gpio_get_level((gpio_num_t)_pin);
        if (_timenow - _lastPresstime > DEBOUNCE_DELAY_US)
        {
            xQueueSend(_pinMsg, &_currentPress, 1);
            _lastPresstime = _timenow;
        }
    vTaskDelay(10);}
}

void Button::startTaskImpl(void* _this){((Button*)_this)->parseIO();}


void Button::init(uint8_t attachTo, switchmode buttonMode, bool debounce)
{
        _pin = attachTo;
        _debounce = debounce;
        _buttonMode = buttonMode;

        gpio_config_t switch_conf = {
        .pin_bit_mask = (1ULL << (gpio_num_t)_pin),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE};

        gpio_config(&switch_conf);

        xTaskCreatePinnedToCore(
            this->startTaskImpl,
            "Parse IO",
            1000,
            this,
            configMAX_PRIORITIES - 7,
            &stackHandle,
            1);
}


uint8_t Button::getPin()
{
    return _pin;
}

bool Button::isPressed()
{
    xQueueReceive(_pinMsg, &_queueReceive, 1);
    return _queueReceive;
}


