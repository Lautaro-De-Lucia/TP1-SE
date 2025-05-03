#include "AudioController.h"

#ifdef HAS_DAC
AudioController::AudioController(PinName mic, PinName dac,
                                 PinName tx,  PinName rx, int baud)
    : _mic(mic), _dac(dac), _uart(tx, rx, baud) {}
#else
AudioController::AudioController(PinName mic,
                                 PinName tx,  PinName rx, int baud)
    : _mic(mic), _uart(tx, rx, baud) {}
#endif

void AudioController::update(FSMState st)
{
    _powered = (st != FSMState::OFF);
    _distort = (st == FSMState::ON_DAC_DISTORT ||
                st == FSMState::ON_UART_DISTORT);
    _useUart = (st == FSMState::ON_UART_CLEAN  ||
                st == FSMState::ON_UART_DISTORT);
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

    if (amplified >  400) amplified =  400;
    if (amplified < -400) amplified = -400;

    _lpFiltered      = 0.9f * amplified + 0.1f * _lpFiltered;
    float hpFiltered = amplified - _lpFiltered;
    float tone       = 0.5f * (_lpFiltered + hpFiltered);

    return static_cast<uint16_t>(tone + 2048);
}

void AudioController::_send(uint16_t s)
{
    if (_useUart) {
        char d[2] = { static_cast<char>(s & 0xFF),
                      static_cast<char>(s >> 8) };
        _uart.write(d, 2);
    }
#ifdef HAS_DAC
    else {                     
        _dac.write(static_cast<float>(s) / 4095.0f);
    }
#else
    (void)s;                      
#endif
}
