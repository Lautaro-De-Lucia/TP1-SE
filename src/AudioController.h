#ifndef AUDIO_CONTROLLER_H
#define AUDIO_CONTROLLER_H

#include "mbed.h"
#include "PedalFSM.h"
#include "SDCard.h"

class AudioController {
public:
#ifdef HAS_DAC
    explicit AudioController(PinName mic = A3, PinName dac = A4);
#else
    explicit AudioController(PinName mic = A3);
#endif
    void setGain(float g);     
    void setTone(float t);     
    void update(FSMState st);
    void handleSampling();
    void configSampleRate(int sr_hz);

private:
    AnalogIn _mic;
#ifdef HAS_DAC
    AnalogOut _dac;
#endif

    SDCard _sd;

    float _gain {4.0f};       
    float _tone {0.5f};       
    bool _powered{false};
    bool _distort{false};
    bool _useDac{false};
    bool _sdStreamOpen{false};

    float _lpFiltered{0.0f};

    uint16_t _readMic();
    uint16_t _applyDistortion(uint16_t raw);
    void     _send(uint16_t s);
};

#endif
