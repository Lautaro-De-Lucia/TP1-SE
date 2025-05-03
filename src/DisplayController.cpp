// DisplayController.cpp
#include "DisplayController.h"

DisplayController::DisplayController()
    : _lastPower(false), _lastDist(false), _lastRec(false)
{
    _disp.init();
    _disp.clear();
}

void DisplayController::_refresh(bool powered,
                                 bool distorted,
                                 bool recording)
{
    if (!powered) {
        _disp.clear();
        return;
    }
    _disp.clear();
    _disp.setCursor(0,0);
    _disp.print(distorted ? "DIST: ON " : "DIST: OFF");
    _disp.setCursor(0,1);
    _disp.print(recording ? "UART: ON " : "UART: OFF");
}

void DisplayController::update(FSMState state)
{
    bool powered   = (state != FSMState::OFF);
    bool distorted = (state == FSMState::ON_DAC_DISTORT ||
                      state == FSMState::ON_UART_DISTORT);
    bool recording = (state == FSMState::ON_UART_CLEAN ||
                      state == FSMState::ON_UART_DISTORT);

    if (powered != _lastPower ||
        (powered && (distorted != _lastDist || recording != _lastRec)))
    {
        _refresh(powered, distorted, recording);
        _lastPower = powered;
        _lastDist  = distorted;
        _lastRec   = recording;
    }
}
