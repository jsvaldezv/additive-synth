#include "Synth_Oscillators.h"

Synth_Oscillators::Synth_Oscillators()
{
    waveTableSineWave.clear();
    waveTableSquareWave.clear();
    waveTableTriangleWave.clear();
}

Synth_Oscillators::~Synth_Oscillators()
{
    
}

void Synth_Oscillators::wavetable(float inSampleRate)
{
    //waveTableSineWave.clear();
    
    phase = 0;
    amplitude = 1;
    frequency = 300;
    wtSize = 1024;
    //increment = frequency * wtSize;
    mySampleRate = inSampleRate;
    
    for(int i=0; i < wtSize; i++)
    {
        waveTableSineWave.insert(i, sin(2.0 * VALOR_PI * i/wtSize));
        
        if(i<=(wtSize/2))
            waveTableSquareWave.insert(i,1);
        else
            waveTableSquareWave.insert(i, 0);
        
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
    increment = frequency * wtSize / mySampleRate;
    
    for(int i=0; i < inSampleToRender; i++)
    {
        outAudio[i] = inAudio[i] + (waveTableSineWave[(int)phase] * inSineWave);
        outAudio[i] = inAudio[i] + (waveTableSquareWave[(int)phase] * inSquareWave);
        outAudio[i] = inAudio[i] + (waveTableTriangleWave[(int)phase] * inTriangleWave);
        outAudio[i] = inAudio[i] + ((random.nextFloat() * 0.25f - 0.125f) * inWhiteNoise);
        
        phase = fmod(phase+increment, wtSize);
    }
}
