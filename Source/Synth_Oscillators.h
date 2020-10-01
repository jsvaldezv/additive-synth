#pragma once
#include <JuceHeader.h>
#include "AudioHelpers.h"
#include "math.h"

class Synth_Oscillators
{
    public:
        
    Synth_Oscillators();
    ~Synth_Oscillators();
    
    void wavetable(float inSampleRate);
    void process(float* inAudio,
                 float* outAudio,
                 float inSampleToRender,
                 float inSineWave,
                 float inSquareWave,
                 float inTriangleWave,
                 float inWhiteNoise);
    
    double sineWave(double frequency);
    
    private:
    
    juce::Array<float> waveTableSineWave;
    juce::Array<float> waveTableSquareWave;
    juce::Array<float> waveTableTriangleWave;
    
    juce::Random random;
    
    double phase, amplitude, frequency, increment, wtSize, mySampleRate;
    
    double output;
};
