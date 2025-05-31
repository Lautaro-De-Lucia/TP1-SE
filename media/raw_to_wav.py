import wave

# Define the input and output file names
input_file = 'testaudio.raw'
output_file = 'testaudio.wav'

# Audio parameters
num_channels = 1        # Mono audio
sample_width = 2        # 2 bytes per sample (16-bit audio)
frame_rate = 8000       # 8 kHz sample rate

# Read the raw audio data
with open(input_file, 'rb') as raw_file:
    raw_data = raw_file.read()

# Write the data to a WAV file
with wave.open(output_file, 'wb') as wav_file:
    wav_file.setnchannels(num_channels)
    wav_file.setsampwidth(sample_width)
    wav_file.setframerate(frame_rate)
    wav_file.writeframes(raw_data)

print(f"Conversion complete: '{output_file}' created.")
