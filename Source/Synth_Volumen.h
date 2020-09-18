#pragma once
#include <JuceHeader.h>

class Synth_Volumen
{

public:
    Synth_Volumen();
    ~Synth_Volumen();
    
    void processVolumen(float*  inAudio,
                        float   inGain,
                        float*  outAudio,
                        int     inNumSamplesToRender);

    
};
