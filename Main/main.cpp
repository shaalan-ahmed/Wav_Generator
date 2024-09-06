#include "../Declarations/declarations.h"

/*--------------------------WAV HEADER-------------------------*/
string ChunkID = "RIFF";
string ChunkSize = "----";
string Format = "WAVE";
string SubChunk1Id = "fmt ";
string SubChunk2Id = "data";
string SubChunk2Size = "----";

int SubChunk1Size = 16;
int AudioFormat = 1;
int NumChannels = 1;
int SampleRate = 44100;
int ByteRate = SampleRate * NumChannels * (SubChunk1Size / 8);
int BlockAlign = NumChannels * (SubChunk1Size / 8);
int BitsPerSample = 16;
/*-------------------------------------------------------------*/

/*--------------------------VARIABLES--------------------------*/
int duration; 
double frequency;
double amplitude;
/*-------------------------------------------------------------*/

int main () {
    FILE* wav = fopen("../Audio/output.wav", "wb");

    cout << "Duration in seconds: ";
    cin >> duration;

    cout << "Frequency in hz: ";
    cin >> frequency;

    cout << "Amplitude (< 32760): ";
    cin >> amplitude;

    if (wav) {
        wavWrite(wav, ChunkID);
        wavWrite(wav, ChunkSize);
        wavWrite(wav, Format);
        wavWrite(wav, SubChunk1Id);
        
        writeBytes(wav, SubChunk1Size, 4);
        writeBytes(wav, AudioFormat, 2);
        writeBytes(wav, NumChannels, 2);
        writeBytes(wav, SampleRate, 4);
        writeBytes(wav, ByteRate, 4);
        writeBytes(wav, BlockAlign, 2);
        writeBytes(wav, BitsPerSample, 2);

        wavWrite(wav, SubChunk2Id);
        wavWrite(wav, SubChunk2Size);

        int start_audio = ftell(wav);

        for (int t = 0; t < SampleRate * duration; t++) {
            double value = sin (2 * M_PI * t * frequency / SampleRate);

            double ch1 = amplitude * value;

            writeBytes(wav, ch1, 2);
        }

        int end_audio = ftell(wav);

        fseek(wav, start_audio - 4, SEEK_SET);

        writeBytes(wav, end_audio - start_audio, 4);

        fseek(wav, 4, SEEK_SET);

        writeBytes(wav, end_audio - 8, 4);
    }

    fclose(wav);
    
    return 0;
}
