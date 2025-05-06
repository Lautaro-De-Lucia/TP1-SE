#include "SerialController.h"

SerialController::SerialController(PinName tx, PinName rx, int baud)
    : _serial(tx, rx, baud), _active(false) {}

void SerialController::config(int baud) { _serial.set_baud(baud); }

void SerialController::update(FSMState state)
{
    _active = (state == FSMState::ON_UART_CLEAN ||
               state == FSMState::ON_UART_DISTORT);
}

void SerialController::sendSample(uint16_t sample)
{
    if (_active) {
        char d[2] = { static_cast<char>(sample & 0xFF),
                      static_cast<char>((sample >> 8) & 0xFF) };
        _serial.write(d, 2);
    }
}
