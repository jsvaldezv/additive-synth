#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class SynthCursoAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SynthCursoAudioProcessorEditor (SynthCursoAudioProcessor&);
    ~SynthCursoAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    juce::Slider oscOneVol;
    
    
    SynthCursoAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthCursoAudioProcessorEditor)
};
