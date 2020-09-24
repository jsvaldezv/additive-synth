#pragma once
#include <JuceHeader.h>
#include "Synth_Sound.h"

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
    
private:
    
    double level, frequency;
    
};
