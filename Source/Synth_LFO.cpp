#include "Synth_LFO.h"

Synth_LFO::Synth_LFO()
{
    waveTableSineWave.clear();
    increment = 440 * 1024 / 480000;
    wavetable(48000);
}

Synth_LFO::~Synth_LFO()
{
}

void Synth_LFO::wavetable(float inSampleRate)
{
    phase = 0;
    amplitude = 1;
    frequency = 1;
    wtSize = 1024;
    output = 0;
    mySampleRate = inSampleRate;
    
    for(int i=0; i < wtSize; i++)
    {
        //SINE WAVE
        waveTableSineWave.insert(i, sin(2.0 * VALOR_PI * i/wtSize));
        //DBG("VALUE[" <<i<<"]: " << waveTableSineWave[i]);
    }
}

void Synth_LFO::process(float* inAudio,
                        float* outAudio,
                        float inSampleToRender)
{
    /*increment = frequency * wtSize / mySampleRate;
    
    for(int i=0; i < inSampleToRender; i++)
    {
        outAudio[i] = inAudio[i] * (waveTableSineWave[(int)phase] * 1);
        
        phase = fmod(phase+increment, wtSize);
    }*/
}

double Synth_LFO::LFOOne(double frequency)
{
    wtSize = 1024;
    mySampleRate = 48000;
    
    increment = frequency * wtSize / mySampleRate;
    output = waveTableSineWave[(int)phase];
    phase = fmod(phase+increment, wtSize);
    
    return output;
}
