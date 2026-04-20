#pragma once

#ifndef dial_h
#define dial_h

#include <cstdint>
#include <functional>






class Dial {
protected:
enum dialmode {
  notched,
  smooth,
  empty
}; //esp vs arduino vs picosdk handled different, use arduino syntax for clarity
public:
    Dial();
    Dial(uint8_t attachTo, uint8_t resolution, uint16_t min, uint16_t max, bool useFilter);
    void init(uint8_t attachTo, uint8_t resolution, uint16_t min, uint16_t max, bool useFilter);
     uint16_t readValue() const;
     uint8_t getPin() const;
     uint16_t readValueRaw() const;

private:

};

#endif
