#include "InputHandler.h"

InputHandler::InputHandler(PinName powerPin, PinName recordPin, PinName distortPin, int debounceSamples)
    : powerBtn(powerPin, debounceSamples),
      recordBtn(recordPin, debounceSamples),
      distortBtn(distortPin, debounceSamples)
{}

void InputHandler::sampleButtons() {
    powerBtn.sample();
    recordBtn.sample();
    distortBtn.sample();
}

bool InputHandler::isPowerPressed() const {
    return powerBtn.read();
}

bool InputHandler::isRecordPressed() const {
    return recordBtn.read();
}

bool InputHandler::isDistortPressed() const {
    return distortBtn.read();
}
