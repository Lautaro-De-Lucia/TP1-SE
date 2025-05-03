#include "mbed.h"
#include "I2CDisplay.h"

I2CDisplay::I2CDisplay() { }

void I2CDisplay::init() {
    displayInit(DISPLAY_CONNECTION_I2C_PCF8574_IO_EXPANDER);
}

void I2CDisplay::setCursor(uint8_t col, uint8_t row) {
    displayCharPositionWrite(col, row);
}

void I2CDisplay::print(const char* str) {
    displayStringWrite(str);
}

void I2CDisplay::clear() {
    for (uint8_t row = 0; row < 2; ++row) {
        setCursor( 0, row );
        for (uint8_t col = 0; col < 16; ++col) {
            print(" ");
        }
    }
    setCursor( 0, 0 );
}