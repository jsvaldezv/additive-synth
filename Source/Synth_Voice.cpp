#include "Synth_Voice.h"

Synth_Voice::Synth_Voice()
{
    
}

Synth_Voice::~Synth_Voice()
{
    
}

bool Synth_Voice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<Synth_Sound*>(sound) != nullptr;
}

void Synth_Voice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    DBG("MIDI NOTE: " << midiNoteNumber);
    DBG("FREQ: " << frequency);
}

void Synth_Voice::stopNote (float velocity, bool allowTailOff)
{
    clearCurrentNote();
}

void Synth_Voice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    
}

void Synth_Voice::pitchWheelMoved (int newPitchWheelValue)
{
    
}

void Synth_Voice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}
