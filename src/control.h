#pragma once

#ifndef control_h
#define control_h

#include <cstdint>
#include <functional>


#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"


#include "esp_log.h"
#include "driver/gptimer.h"
#include "driver/GPIO.h"
#include "esp_timer.h"
#include "freertos/semphr.h"


enum direction {
    forward,
    reverse,
    stop,
    N_A
};


class control{
    public:
    control();
    private:
};

#endif