#include "Synth_Oscillators.h"

Synth_Oscillators::Synth_Oscillators()
{
    waveTableSineWave.clear();
    waveTableSquareWave.clear();
    waveTableTriangleWave.clear();
    
    increment = 440 * 1024 / 480000;
}

Synth_Oscillators::~Synth_Oscillators()
{
    
}

void Synth_Oscillators::wavetable(float inSampleRate)
{
    phase = 0;
    amplitude = 1;
    frequency = 300;
    wtSize = 1024;
    mySampleRate = inSampleRate;
    
    for(int i=0; i < wtSize; i++)
    {
        //SINEWAVE
        waveTableSineWave.insert(i, sin(2.0 * VALOR_PI * i/wtSize));
        
        //SQUARE WAVE
        if(i<=(wtSize/2))
            waveTableSquareWave.insert(i, 1);
        else
            waveTableSquareWave.insert(i, 0);
        
        //TRIANGLE WAVE
        waveTableTriangleWave.insert(i, ((2/VALOR_PI)*asin(sin((2*VALOR_PI*i)/wtSize))));
    }
}

void Synth_Oscillators::process(float* inAudio,
                                float* outAudio,
                                float inSampleToRender,
                                float inSineWave,
                                float inSquareWave,
                                float inTriangleWave,
                                float inWhiteNoise)
{
    /*increment = frequency * wtSize / mySampleRate;
    
    for(int i=0; i < inSampleToRender; i++)
    {
        outAudio[i] = inAudio[i] + (waveTableSineWave[(int)phase] * inSineWave);
        outAudio[i] = inAudio[i] + (waveTableSquareWave[(int)phase] * inSquareWave);
        outAudio[i] = inAudio[i] + (waveTableTriangleWave[(int)phase] * inTriangleWave);
        outAudio[i] = inAudio[i] + ((random.nextFloat() * 0.25f - 0.125f) * inWhiteNoise);
        
        phase = fmod(phase+increment, wtSize);
    }*/
}

double Synth_Oscillators::oscillatorOne(double frequency, int inType)
{
    increment = frequency * wtSize / mySampleRate;
    
    switch(inType)
    {
        case 0:
            output = waveTableSineWave[(int)phase];
            break;
        case 1:
            output = waveTableSquareWave[(int)phase];
            break;
        case 2:
            output = waveTableTriangleWave[(int)phase];
            break;
    }

    phase = fmod(phase+increment, wtSize);
    
    return output;
}

double Synth_Oscillators::oscillatorTwo(double frequency, int inType)
{
    increment = frequency * wtSize / mySampleRate;
    
    switch(inType)
    {
        case 0:
            output = waveTableSineWave[(int)phase];
            break;
        case 1:
            output = waveTableSquareWave[(int)phase];
            break;
        case 2:
            output = waveTableTriangleWave[(int)phase];
            break;
    }
    
    phase = fmod(phase+increment, wtSize);
    
    return output;
}
