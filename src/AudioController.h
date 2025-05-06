#ifndef AUDIO_CONTROLLER_H
#define AUDIO_CONTROLLER_H

#include "mbed.h"
#include "PedalFSM.h"

class AudioController {
public:

#ifdef HAS_DAC
    explicit AudioController(PinName mic = A2, PinName dac = A3,
                             PinName tx = USBTX, PinName rx = USBRX,
                             int baud = 230400);
#else
    explicit AudioController(PinName mic = A2,
                             PinName tx  = USBTX, PinName rx = USBRX,
                             int baud = 230400);
#endif

    void update(FSMState st);

    void handleSampling();

    void configSampleRate(int sr_hz);

private:
    AnalogIn        _mic;
#ifdef HAS_DAC
    AnalogOut       _dac;
#endif
    BufferedSerial  _uart;

    bool _powered{false};
    bool _distort{false};
    bool _useUart{false};

    float _lpFiltered{0.0f};

    uint16_t _readMic();
    uint16_t _applyDistortion(uint16_t raw);
    void     _send(uint16_t s);
};

#endif 