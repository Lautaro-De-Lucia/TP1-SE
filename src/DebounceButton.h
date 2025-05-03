#pragma once
#include "mbed.h"


class DebounceButton {

public:

    DebounceButton(PinName pin, int threshold = 5);
    void sample();
    bool read() const;

private:
    DigitalIn _pin;   
    bool      _state;
    bool      _lastRaw;
    int       _count;
    int       _threshold;
};
