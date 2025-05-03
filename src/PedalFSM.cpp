#include "PedalFSM.h"

PedalFSM::PedalFSM() 
    : currentState(FSMState::OFF),
      lastPowerBtn(false),
      lastRecordBtn(false),
      lastDistortBtn(false) {}

void PedalFSM::update(bool powerBtn, bool recordBtn, bool distortBtn) {
    if (powerBtn && !lastPowerBtn) {
        currentState = (currentState == FSMState::OFF) 
                     ? FSMState::ON_DAC_CLEAN 
                     : FSMState::OFF;
    }

    if (currentState != FSMState::OFF) {
        if (recordBtn && !lastRecordBtn) {
            switch (currentState) {
                case FSMState::ON_UART_CLEAN:
                    currentState = FSMState::ON_DAC_CLEAN;
                    break;
                case FSMState::ON_DAC_CLEAN:
                    currentState = FSMState::ON_UART_CLEAN;
                    break;
                case FSMState::ON_UART_DISTORT:
                    currentState = FSMState::ON_DAC_DISTORT;
                    break;
                case FSMState::ON_DAC_DISTORT:
                    currentState = FSMState::ON_UART_DISTORT;
                    break;
                default: break;
            }
        }

        if (distortBtn && !lastDistortBtn) {
            switch (currentState) {
                case FSMState::ON_UART_CLEAN:
                    currentState = FSMState::ON_UART_DISTORT;
                    break;
                case FSMState::ON_UART_DISTORT:
                    currentState = FSMState::ON_UART_CLEAN;
                    break;
                case FSMState::ON_DAC_CLEAN:
                    currentState = FSMState::ON_DAC_DISTORT;
                    break;
                case FSMState::ON_DAC_DISTORT:
                    currentState = FSMState::ON_DAC_CLEAN;
                    break;
                default: break;
            }
        }
    }

    lastPowerBtn = powerBtn;
    lastRecordBtn = recordBtn;
    lastDistortBtn = distortBtn;
}

bool PedalFSM::isPowered() const {
    return currentState != FSMState::OFF;
}

bool PedalFSM::isDistorted() const {
    return currentState == FSMState::ON_UART_DISTORT ||
           currentState == FSMState::ON_DAC_DISTORT;
}

bool PedalFSM::isUARTOutput() const {
    return currentState == FSMState::ON_UART_CLEAN ||
           currentState == FSMState::ON_UART_DISTORT;
}

FSMState PedalFSM::getCurrentState() const {
    return currentState;
}
