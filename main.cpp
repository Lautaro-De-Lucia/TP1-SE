#include "mbed.h"
#include "arm_book_lib.h"

#define SAMPLING_PERIOD_US 125

DigitalIn   recordButton(BUTTON1);
DigitalOut  recorderLed(LED1);
AnalogIn    micInput(A0);

BufferedSerial uartUsb(USBTX, USBRX, 230400);

bool recordingState = OFF;

void inputsInit();
void outputsInit();
void recordingControlUpdate();
void recordingSendingUpdate();

int main()
{
    inputsInit();
    outputsInit();

    while (true) {
        recordingControlUpdate();

        if (recordingState) {
            recordingSendingUpdate();
        }

        wait_us(SAMPLING_PERIOD_US);
    }
}

void inputsInit()
{

}

void outputsInit()
{
    recorderLed = OFF;
}

void recordingControlUpdate()
{
    static bool buttonPreviouslyPressed = false;
    bool buttonIsPressed = recordButton.read();

    if (buttonIsPressed && !buttonPreviouslyPressed) {
        recordingState = !recordingState;
    }
    buttonPreviouslyPressed = buttonIsPressed;

    recorderLed = recordingState ? ON : OFF;
}

void recordingSendingUpdate()
{
    uint16_t rawAdcValue = micInput.read_u16() >> 4;

    char data[2];
    data[0] = rawAdcValue & 0xFF;
    data[1] = (rawAdcValue >> 8) & 0xFF;

    uartUsb.write(data, 2);
}
