#include "WiFiReceiver.h"
#include <cstring>
#include <cstdio>

WiFiReceiver::WiFiReceiver(PinName tx, PinName rx, int baud)
    : _esp(tx, rx, baud),
      _idx(0),
      _newCfg(false),
      _gain(0.0f),
      _tone(0.0f)
{
    _model[0] = '\0';
    _esp.set_blocking(false);           
}

bool WiFiReceiver::hasNewConfig() const
{
    return _newCfg;
}

void WiFiReceiver::getConfig(char* modelOut, float& gainOut, float& toneOut)
{
    if (!_newCfg) return;               
    std::strncpy(modelOut, _model, 32);
    modelOut[31] = '\0';                
    gainOut = _gain;
    toneOut = _tone;
    _newCfg = false;                    
}

void WiFiReceiver::update()
{
    while (_esp.readable()) {
        char c;
        if (_esp.read(&c, 1) != 1) break;

        printf("%c", c);                

        if (c == '\r' || c == '\n') {
            if (_idx == 0) continue;    

            _line[_idx] = '\0';
            if (char* p = std::strchr(_line, '\r')) *p = '\0';

            if (std::sscanf(_line,
                            "{\"model\":\"%31[^\"]\",\"gain\":%f,\"tone\":%f}",
                            _model, &_gain, &_tone) == 3) {
                printf("\r\nParsed: model=%s gain=%.2f tone=%.2f\r\n",
                       _model, _gain, _tone);
                _newCfg = true;        
            } else {
                printf("\r\nMalformed: %s\r\n", _line);
            }
            _idx = 0;                   
        }
        else if (_idx < sizeof(_line) - 1) {
            _line[_idx++] = c;         
        }
    }
}
