import wave
import struct


INPUT_FILE = 'samples.txt'
OUTPUT_WAV = 'output.wav'
SAMPLE_RATE = 6000

def main():

    with open(INPUT_FILE, 'r') as f:
        lines = f.readlines()
    
    with wave.open(OUTPUT_WAV, 'wb') as wf:
        wf.setnchannels(1)         # mono
        wf.setsampwidth(2)         # 16-bit 
        wf.setframerate(SAMPLE_RATE)
        
        for line in lines:
            line = line.strip()
            if not line:
                continue
            
            try:
                raw_value = int(line)
            except ValueError:
                continue  

            # Transformación de 0..4095 a señal centrada en 0
            # Restamos 2048 
            # Escalamos (<<4) para tener 16-bit (-2048,...,2047) => (-32768,...,32752)
            centered_value = raw_value - 2048
            sample_16bit = centered_value << 4
            
            # Empaquetamos como little-endian 16-bit
            data = struct.pack('<h', sample_16bit)

            wf.writeframesraw(data)

    print(f"WAV file '{OUTPUT_WAV}' created with {len(lines)} samples at {SAMPLE_RATE} Hz.")

if __name__ == '__main__':
    main()
