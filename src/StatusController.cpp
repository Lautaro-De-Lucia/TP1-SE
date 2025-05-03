#include "StatusController.h"

StatusController::StatusController(PinName ledPin)
    : _led(ledPin), _lastPowered(false)
{
    _led = 0;                  
}

void StatusController::config(PinName ledPin) { _led = DigitalOut(ledPin); }

void StatusController::update(FSMState state)
{
    bool powered = (state != FSMState::OFF);
    if (powered != _lastPowered) {
        _led = powered;
        _lastPowered = powered;
    }
}
