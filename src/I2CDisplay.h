#ifndef I2CDISPLAY_H
#define I2CDISPLAY_H

#include "display.h"
#include "mbed.h"

class I2CDisplay {
public:

    I2CDisplay();

    void init();

    void setCursor(uint8_t col, uint8_t row);

    void print(const char* str);

    void clear();
};

#endif 