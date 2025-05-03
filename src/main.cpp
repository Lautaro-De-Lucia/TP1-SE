#include "mbed.h"
#include "InputHandler.h"
#include "PedalFSM.h"
#include "StatusController.h"
#include "DisplayController.h"
#include "AudioController.h"

#define SAMPLING_FREQ_HZ    8000
#define SAMPLING_PERIOD_US  (1000000 / SAMPLING_FREQ_HZ)

Ticker samplingTicker;
volatile bool samplingFlag = false;
void samplingISR() { samplingFlag = true; }

Ticker debounceTicker;
InputHandler* inputH;
void debounceISR() { inputH->sampleButtons(); }

int main()
{
    // Inicialización por medio de los Constructores 
    PedalFSM          fsm;
    StatusController  statusCtrl;
    DisplayController displayCtrl;
    AudioController   audioCtrl;        

    samplingTicker.attach_us(&samplingISR, SAMPLING_PERIOD_US);
    inputH = new InputHandler(BUTTON1, PC_8, PC_6);
    debounceTicker.attach(&debounceISR, 0.01f);       

    while (true) {
        // 1. Obtener estado de los botones
        fsm.update(inputH->isPowerPressed(),
                   inputH->isRecordPressed(),
                   inputH->isDistortPressed());
        // 2. Actualizar FSM 
        FSMState st = fsm.getCurrentState();
        // 3. Usar el nuevo estado para actualizar los controladores
        statusCtrl .update(st);
        displayCtrl.update(st);
        audioCtrl  .update(st);
        // 4. Procesar muestra de Audio 
        if (samplingFlag) {
            audioCtrl.handleSampling();
            samplingFlag = false;
        }
    }
}

