import serial
import time
import struct

SERIAL_PORT = 'COM6'     
BAUD_RATE = 230400        
OUTPUT_FILE = 'samples.txt'

def main():
    with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:
        time.sleep(2)

        print("Recording data from microcontroller. Press Ctrl+C to stop.")
        
        with open(OUTPUT_FILE, 'w') as f:
            try:
                while True:
                    # Leemos 2 bytes
                    raw = ser.read(2)
                    if len(raw) == 2:
                        # Guardamos como little-endian 16-bit 
                        # El valor queda en el rango [0..4095]
                        rawAdcValue = struct.unpack('<H', raw)[0]
                        # Guardamos en el archivo
                        f.write(str(rawAdcValue) + '\n')
            except KeyboardInterrupt:
                print("\nStopped recording. Data saved to", OUTPUT_FILE)

if __name__ == '__main__':
    main()
