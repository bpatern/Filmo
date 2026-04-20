#pragma once

#ifndef switch_h
#define switch_h

#include "control.h"




enum switchmode {
  INPUT_PULLUP,
  INPUT_PULLDOWN,
  INPUT,
  empty
}; //esp vs arduino vs picosdk handled different, use arduino syntax for clarity


class playbackControl : public control {
    public:
        enum playbackControlType {
    toggle, //when fwd is pressed it is on, when released it is off, etc etc. Classic american home projector style
    dial, //relies on pressed and held pins on a dial, usually part of a cam system. Eiki style
    none
};
        playbackControl();
        playbackControl(playbackControlType type, uint8_t runPin, uint8_t stopPin = 99, uint8_t revPin = 99, uint8_t rewindPin = 99);
        void init(playbackControlType type, uint8_t runPin, uint8_t stopPin = 99, uint8_t revPin = 99, uint8_t rewindPin = 99);
        direction readDirection(direction dir = N_A);
        int checkPin(uint8_t pin);
        QueueHandle_t runMsg;
    private:

    uint8_t _stopPin;
    uint8_t _runPin;
    uint8_t _revPin;
    uint8_t _rewindPin;
    playbackControlType _type;
    direction _internalDirection;
};

class Button : public control {

protected:

    static char fb;
    switchmode _buttonMode;
    bool _debounce;
    uint16_t _pin;


public:
    // SemaphoreHandle_t switchinput;
    TaskHandle_t stackHandle;
    const char *ioTH = "io task handle";
    Button();
    bool isPressed();
    Button(uint8_t attachTo, switchmode buttonMode = INPUT_PULLUP, bool debounce = true);
    uint8_t getPin();
    uint16_t getISR();
    uint8_t ignoreControlSwitch;
    void init(uint8_t attachTo, switchmode buttonMode = INPUT_PULLUP, bool debounce = true);
    uint16_t isrcount;


private:
    bool _queueReceive;
    QueueHandle_t _pinMsg;
    void parseIO();
    static void startTaskImpl(void*);
    uint8_t _lastPress = 0;
    uint8_t _currentPress = 0;
    uint64_t _lastPresstime = 0;
    uint64_t _timenow = 0;

};


#endif