#pragma once
#include <JuceHeader.h>

class Synth_Sound : public juce::SynthesiserSound
{
public:
    
    Synth_Sound();
    ~Synth_Sound();
    
    bool appliesToNote (int);
    bool appliesToChannel (int);
};
