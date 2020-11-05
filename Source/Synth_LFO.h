#pragma once
#include <JuceHeader.h>
#include "AudioHelpers.h"

class Synth_LFO
{
public:
    
    Synth_LFO();
    ~Synth_LFO();
    
    void wavetable(float inSampleRate);
    void process(float* inAudio,
                 float* outAudio,
                 float inSampleToRender);
    double LFOOne(double frequency);
    double LFOTwo(double frequency);
    
private:
    
    juce::Array<float> waveTableSineWave;
    
    double phase, amplitude, frequency, increment, wtSize, mySampleRate;
    double output1, output2;
};
