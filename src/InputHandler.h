#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "mbed.h"
#include "DebounceButton.h"

class InputHandler {
public:
    InputHandler(PinName powerPin, PinName recordPin, PinName distortPin, int debounceSamples = 5);

    void sampleButtons();

    bool isPowerPressed() const;
    bool isRecordPressed() const;
    bool isDistortPressed() const;

private:
    DebounceButton powerBtn;
    DebounceButton recordBtn;
    DebounceButton distortBtn;
};

#endif
