#include "Synth_Volumen.h"

Synth_Volumen::Synth_Volumen()
{
    
}
Synth_Volumen::~Synth_Volumen()
{
    
}

void Synth_Volumen::processVolumen(float*  inAudio,
                                   float   inGain,
                                   float*  outAudio,
                                   int     inNumSamplesToRender)
{
    float gainMapped = juce::jmap(inGain, 0.0f, 1.0f, -24.0f, 24.0f);
    
    gainMapped = juce::Decibels::decibelsToGain(gainMapped, -24.0f);
    
    for(int i=0; i < inNumSamplesToRender; i++)
    {
        outAudio[i] = inAudio[i] * gainMapped;
    }
}
