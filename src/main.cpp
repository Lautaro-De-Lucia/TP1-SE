#include "mbed.h"
#include "InputHandler.h"
#include "PedalFSM.h"
#include "StatusController.h"
#include "DisplayController.h"
#include "AudioController.h"
#include "WiFiReceiver.h"   

#define SAMPLING_FREQ_HZ    8000
#define SAMPLING_PERIOD_US  (1000000 / SAMPLING_FREQ_HZ)

Ticker samplingTicker;
volatile bool samplingFlag = false;
void samplingISR() { samplingFlag = true; }

Ticker debounceTicker;
InputHandler* inputH;
void debounceISR() { inputH->sampleButtons(); }

WiFiReceiver wifi(D8,D2);

int main()
{
    printf("\r\n=== Pedal + WiFi test ===\r\n");

    PedalFSM          fsm;
    StatusController  statusCtrl;
    DisplayController displayCtrl;
    AudioController   audioCtrl;  

    samplingTicker.attach_us(&samplingISR, SAMPLING_PERIOD_US);
    inputH = new InputHandler(BUTTON1, PC_8, PC_6);
    debounceTicker.attach(&debounceISR, 0.01f);       

    while (true) {
        // 1. Recepción Wi-Fi 
        wifi.update();
        if (wifi.hasNewConfig()) {
            char  model[32];
            float gain, tone;
            wifi.getConfig(model, gain, tone);            
            displayCtrl.setModelName(model);
            audioCtrl.setGain(gain);
            audioCtrl.setTone(tone);
        }

        // 2. Lectura de Estados 
        fsm.update(inputH->isPowerPressed(),
                   inputH->isRecordPressed(),
                   inputH->isDistortPressed());

        // 3. Actualizamos estado en los controladores
        FSMState st = fsm.getCurrentState();
        statusCtrl .update(st);
        displayCtrl.update(st);
        audioCtrl  .update(st);

        // 4. Captura de Sample del ADC
        if (samplingFlag) {
            audioCtrl.handleSampling();
            samplingFlag = false;
        }
    }
}
