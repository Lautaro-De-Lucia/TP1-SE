#ifndef WIFI_RECEIVER_H
#define WIFI_RECEIVER_H

#include "mbed.h"

class WiFiReceiver {
public:
    WiFiReceiver(PinName tx, PinName rx, int baud = 115200);
    void update();
    bool hasNewConfig() const;
    void getConfig(char* modelOut, float& gainOut, float& toneOut);

private:
    BufferedSerial _esp;
    char   _line[256];
    size_t _idx;
    bool   _newCfg;

    char   _model[32];
    float  _gain, _tone;
};

#endif  // WIFI_RECEIVER_H
