#ifndef PEDALFSM_H
#define PEDALFSM_H

enum class FSMState {
    OFF,
    ON_UART_CLEAN,
    ON_UART_DISTORT,
    ON_DAC_CLEAN,
    ON_DAC_DISTORT
};

class PedalFSM {
public:
    PedalFSM();

    void update(bool powerBtn, bool recordBtn, bool distortBtn);

    bool isPowered() const;
    bool isDistorted() const;
    bool isUARTOutput() const;

    FSMState getCurrentState() const;

private:
    FSMState currentState;

    bool lastPowerBtn;
    bool lastRecordBtn;
    bool lastDistortBtn;
};

#endif
