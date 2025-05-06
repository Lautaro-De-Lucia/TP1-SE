// DisplayController.h
#ifndef DISPLAY_CONTROLLER_H
#define DISPLAY_CONTROLLER_H

#include "I2CDisplay.h"
#include "PedalFSM.h"

class DisplayController {
public:
    DisplayController();                     
    void update(FSMState state);

private:
    I2CDisplay _disp;
    bool       _lastPower, _lastDist, _lastRec;
    void       _refresh(bool pwr, bool dist, bool rec);
};
#endif
