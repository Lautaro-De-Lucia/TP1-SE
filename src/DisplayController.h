// DisplayController.h
#ifndef DISPLAY_CONTROLLER_H
#define DISPLAY_CONTROLLER_H

#include "I2CDisplay.h"
#include "PedalFSM.h"

class DisplayController {
public:
    DisplayController();                     
    void update(FSMState state);
    void setModelName(const char* name);

private:
    I2CDisplay _disp;
    char  _model[32];
    bool       _lastPower, _lastDist, _lastRec;
    char  _lastModel[32];
    void       _refresh(bool pwr, bool dist, bool rec);
};
#endif
