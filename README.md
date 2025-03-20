## TP1 - Grabador de Audio

#### Alumno : Lautaro De Lucia
#### Materia : Sistemas Embebidos 

## Objetivo 

Capturar audio con la **NUCLEO-F103RB**.

## Descripción

Al iniciar, el programa queda en espera hasta que el usuario presione un botón. Al presionarlo, inicia la grabación del audio, el cual proveniene de un módulo KY-037 conectado al ADC del microcontrolador. Las lecturas de la señal de audio se transmiten a la PC mediante UART. La grabación puede detenerse manualmente volviendo a pulsar el botón. Los estados del sistema se indican visualmente mediante un LED y a en forma de texto en el serial monitor.

#### Especificaciones

- **Microcontrolador**: STM32F103RB (ARM Cortex-M3).
- **Entrada Analógica:** Sensor de audio KY-037 conectado al canal analógico A0, alimentado con 3.3V de la placa.
- **Frecuencia de muestreo:** Por simplicidad, se utilizará una frecuencia de muestreo de 8 kHz (definida por el timer del ADC).
- **Baudrate UART:** 230400 bps.
 

| Periférico           | Uso en el sistema                           | Pin utilizado    |
|----------------------|--------------------------------------------|------------------|
| KY-037 Analog Out    | Captura de audio analógico                  | PA0            |
| REC_BUTTON          | Inicia/detiene la grabación                 | GPIO (ej. PC13)  |
| LED (grabando)       | Encendido indica grabación activa           | GPIO (ej. PB0)   |

#### Flujo

1. Al iniciar, el sistema informa por el monitor serial que debe presionarse el botón para comenzar a grabar.
2. Al pulsar el botón:
    - Comienza a grabar audio desde el módulo KY-037.
    - El LED de grabación se enciende.
    - Los valores de audio se transmiten por UART a la PC.
3. Al pulsar nuevamente el botón 
    - Finaliza la grabación.
    - El LED se apaga.
    - Dejan de transmitirse los datos por UART. 
4. Al finalizar la transmisión, el sistema vuelve al paso 1.

#### Diagrama de Bloques

<center>

![alt text](/imgs/ddb.png)

</center>
