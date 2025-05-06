#ifndef SERIAL_CONTROLLER_H
#define SERIAL_CONTROLLER_H

#include "mbed.h"
#include "PedalFSM.h"

class SerialController {
public:
    SerialController(PinName tx = USBTX, PinName rx = USBRX,
                     int baud = 230400);
    void config(int baud);
    void update(FSMState state);
    void sendSample(uint16_t sample);
    bool isActive() const { return _active; }

private:
    BufferedSerial _serial;
    bool           _active;
};
#endif
