#include "AudioController.h"

#ifdef HAS_DAC
AudioController::AudioController(PinName mic, PinName dac)
    : _mic(mic), _dac(dac) {}
#else
AudioController::AudioController(PinName mic)
    : _mic(mic) {}
#endif

void AudioController::update(FSMState st)
{
    bool shouldPower = (st != FSMState::OFF);
    bool shouldDistort = (st == FSMState::ON_DAC_DISTORT ||
                          st == FSMState::ON_UART_DISTORT);  
    bool shouldUseDac = (st == FSMState::ON_DAC_CLEAN ||
                         st == FSMState::ON_DAC_DISTORT);

    if (!_powered && shouldPower) {
        _sdStreamOpen = _sd.openBinaryStream("testaudio.raw", true);  
        if (_sdStreamOpen) {
            printf("AudioController: Started recording to SD.\n");
        } else {
            printf("AudioController: Failed to open SD stream.\n");
        }
    } else if (_powered && !shouldPower) {
        if (_sdStreamOpen) {
            _sd.closeBinaryStream();
            _sdStreamOpen = false;
            printf("AudioController: Stopped recording to SD.\n");
        }
    }

    _powered = shouldPower;
    _distort = shouldDistort;
    _useDac  = shouldUseDac;
}

void AudioController::handleSampling()
{
    if (!_powered) return;

    uint16_t raw = _readMic();
    uint16_t out = _distort ? _applyDistortion(raw) : raw;
    _send(out);
}

void AudioController::configSampleRate(int) { }

uint16_t AudioController::_readMic()
{
    return _mic.read_u16() >> 4;
}

uint16_t AudioController::_applyDistortion(uint16_t raw)
{
    int16_t s = static_cast<int16_t>(raw) - 2048;
    float amplified = 4.0f * s;

    if (amplified > 400) amplified = 400;
    if (amplified < -400) amplified = -400;

    _lpFiltered      = 0.9f * amplified + 0.1f * _lpFiltered;
    float hpFiltered = amplified - _lpFiltered;
    float tone       = 0.5f * (_lpFiltered + hpFiltered);

    return static_cast<uint16_t>(tone + 2048);
}

void AudioController::_send(uint16_t s)
{
    if (_useDac) {
#ifdef HAS_DAC
        _dac.write(static_cast<float>(s) / 4095.0f);
#endif
    }

    if (_sdStreamOpen) {
        if (!_sd.writeBinaryStream(&s, 1)) {
            printf("AudioController: SD write error.\n");
        }
    }
}
