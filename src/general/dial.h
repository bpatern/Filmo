#pragma once

#ifndef dial_h
#define dial_h

#ifndef control_h
#include "control.h"
#endif
#include "esp_adc/adc_oneshot.h"

#include <cstdint>
#include <functional>

enum dialmode {
  notched,
  smooth,
  empty
}; //esp vs arduino vs picosdk handled different, use arduino syntax for clarity


             static adc_oneshot_chan_cfg_t channel_config;
             static adc_oneshot_unit_handle_t _adc_handle;
static adc_oneshot_unit_init_cfg_t init_config;


class Dial : public control {
protected:
  adc_channel_t _pin;

public:
    Dial();
    void begin();
    Dial(uint8_t attachTo, uint8_t resolution, uint16_t min, uint16_t max);
    void init(uint8_t attachTo, uint8_t resolution, uint16_t min, uint16_t max);
     uint16_t readValue();
     uint8_t getPin() const;
     uint16_t readValueRaw() const;
     float kalmanUpdateEstimate(float mea);
     float _map(float x, float in_min, float in_max, float out_min, float out_max);
              




private:
     void readPot();
         static void startTaskImpl(void*);


  float _kalman_gain = 0;
  float _err_measure = 1;
  float _err_estimate = 1;
  float _q = 0.05;
  float _current_estimate = 0;
  float _last_estimate = 0;
  float _potEstimate = 0;
  QueueHandle_t _potQueue;
      int _potReadRaw;
    uint16_t res;

  int _potRead;
  int _potReadOld;
  uint16_t _potReadUnscaled;
  uint16_t _resolution;
  uint32_t _min;
  uint32_t _max;
  uint8_t _potSampleCounter;
   uint32_t _potSampleStorage[32];
       TaskHandle_t _stackHandle;







};

#endif
