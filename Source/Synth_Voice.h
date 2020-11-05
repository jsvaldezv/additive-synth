#pragma once
#include <JuceHeader.h>
#include "Synth_Sound.h"
#include "Synth_Oscillators.h"
#include "Synth_LFO.h"

class Synth_Voice : public juce::SynthesiserVoice
{
public:
    
    Synth_Voice();
    ~Synth_Voice();
    
    bool canPlaySound (juce::SynthesiserSound* sound);
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition);
    void stopNote (float velocity, bool allowTailOff);
    void pitchWheelMoved (int newPitchWheelValue);
    void controllerMoved (int controllerNumber, int newControllerValue);
    void renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples);
    void getEnvelopeParams (float* attack, float* decay, float* sustain, float* release);
    
    void setMySampleRate(double inSampleRate);
    void getParams(float inVolGen,
                   float inOscOne,
                   float inOscTwo,
                   int inTypeOne,
                   int inTypeTwo,
                   float inRateLfoONe,
                   float inRateLfoTwo,
                   bool onLfoOne,
                   bool onLfoTwo);

private:
    
    double level, frequency, mySampleRate, smoothOsc1, smoothOsc2;
    float volGeneral, volOscOne, volOscTwo, rateLFOOne, rateLFOTwo;
    int valTypeOne, valTypeTwo;
    bool valOnLfoOne, valOnLfoTwo;
    
    Synth_Oscillators osc1, osc2;
    Synth_LFO lfo1, lfo2;
};
