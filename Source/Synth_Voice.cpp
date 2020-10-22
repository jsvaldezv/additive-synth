#include "Synth_Voice.h"

Synth_Voice::Synth_Voice()
{
    osc1.wavetable(48000);
    smoothOsc1 = 0.0;
    smoothOsc2 = 0.0;
    volGeneral = 0.0;
    volOscOne = 0.0;
    volOscTwo = 0.0;
    valTypeOne = 0;
    valTypeTwo = 0;
    rateLFOOne = 0.0;
}

Synth_Voice::~Synth_Voice()
{
    
}

void Synth_Voice::setMySampleRate(double inSampleRate)
{

}

bool Synth_Voice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<Synth_Sound*>(sound) != nullptr;
}

void Synth_Voice::getParams(float inVolGen,
                            float inOscOne,
                            float inOscTwo,
                            int inTypeOne,
                            int inTypeTwo,
                            float inRateLfoONe)
{
    volGeneral = inVolGen;
    volOscOne = inOscOne;
    volOscTwo = inOscTwo;
    valTypeOne = inTypeOne;
    valTypeTwo = inTypeTwo;
    rateLFOOne = inRateLfoONe;
}

void Synth_Voice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    level = velocity;
    frequency = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
}

void Synth_Voice::stopNote (float velocity, bool allowTailOff)
{
    level = 0;
}

void Synth_Voice::renderNextBlock (juce::AudioBuffer<float> &outputBuffer,
                                   int startSample,
                                   int numSamples)
{
    for (int i=0; i < numSamples; i++)
    {
        //FUNCION SMOOTH
        double osc1Signal = osc1.oscillatorOne(frequency, valTypeOne) * level * volOscOne;
        double osc2Signal = osc1.oscillatorTwo(frequency, valTypeTwo) * level * volOscTwo;
        double lfo1Signal = lfo1.LFOOne(rateLFOOne) * level;
        
        smoothOsc1 = smoothOsc1 - 0.002*(smoothOsc1 - osc1Signal);
        smoothOsc2 = smoothOsc2 - 0.002*(smoothOsc2 - osc2Signal);
        //OBTENER SAMPLES DE WAVETABLE
        for (int channel=0; channel < outputBuffer.getNumChannels(); channel++)
        {
            outputBuffer.addSample(channel, startSample, (smoothOsc1 + smoothOsc2) * lfo1Signal);
        }

        ++startSample;
    }
}

void Synth_Voice::getEnvelopeParams (float* attack, float* decay, float* sustain, float* release)
{
    
}

void Synth_Voice::pitchWheelMoved (int newPitchWheelValue)
{
    
}

void Synth_Voice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}
