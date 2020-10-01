#include "Synth_Voice.h"

Synth_Voice::Synth_Voice()
{
    osc1.wavetable(48000);
}

Synth_Voice::~Synth_Voice()
{
    
}

void Synth_Voice::setMySampleRate(double inSampleRate)
{
    /*mySampleRate = inSampleRate;
    osc1.wavetable(mySampleRate);
    myADSR.setSampleRate(mySampleRate);*/
}

bool Synth_Voice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<Synth_Sound*>(sound) != nullptr;
}

void Synth_Voice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    level = velocity;
    frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    myADSR.noteOn();
    
    //CHECAR SI FUNCIONA
    //DBG("MIDI NOTE: " << midiNoteNumber);
    //DBG("FREQ: " << frequency);
}

void Synth_Voice::stopNote (float velocity, bool allowTailOff)
{
    level = 0;
    myADSR.noteOff();
}

void Synth_Voice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
    myADSR.setParameters(myADSRParams);
    
    for (int i=0; i < numSamples; i++)
    {
        double theWaveMine = osc1.sineWave(frequency) * level;
        
        for (int channel=0; channel < outputBuffer.getNumChannels(); channel++)
        {
            outputBuffer.addSample(channel, startSample, theWaveMine * 0.5);
        }
        
        ++startSample;
    }
}

void Synth_Voice::getEnvelopeParams (float* attack, float* decay, float* sustain, float* release)
{
    myADSRParams.attack = 0.5;
    myADSRParams.decay = 0.5;
    myADSRParams.sustain = 1;
    myADSRParams.release = 1;
}

void Synth_Voice::pitchWheelMoved (int newPitchWheelValue)
{
    
}

void Synth_Voice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}
