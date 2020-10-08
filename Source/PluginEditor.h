#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class SynthCursoAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                        public juce::ComboBox::Listener,
                                        public juce::Slider::Listener
{
public:
    SynthCursoAudioProcessorEditor (SynthCursoAudioProcessor&);
    ~SynthCursoAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void sliderValueChanged (juce::Slider* slider) override;
    void comboBoxChanged (juce::ComboBox* comboBox) override;
    

private:
    
    juce::Slider volumenSlider;
    juce::Slider volumenOscOne;
    juce::Slider volumenOscTwo;
    juce::ComboBox typeOscOne;
    juce::ComboBox typeOscTwo;
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> volumenAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> oscOneAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> oscTwoAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> typeOscOneAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> typeOscTwoAttachment;
    
    SynthCursoAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthCursoAudioProcessorEditor)
};
