#ifndef STATUS_CONTROLLER_H
#define STATUS_CONTROLLER_H

#include "mbed.h"
#include "PedalFSM.h"

class StatusController {
public:
    explicit StatusController(PinName ledPin = LED1);
    void config(PinName ledPin);              
    void update(FSMState state);

private:
    DigitalOut _led;
    bool       _lastPowered;
};
#endif
