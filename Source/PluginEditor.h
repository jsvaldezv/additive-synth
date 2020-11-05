#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Synth_LookAndFeel.h"

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
    juce::Slider rateLFOOne;
    juce::Slider rateLFOTwo;
    juce::ComboBox typeOscOne;
    juce::ComboBox typeOscTwo;
    
    juce::ScopedPointer<juce::ImageButton> offLfoOne;
    juce::ScopedPointer<juce::ImageButton> offLfoTwo;
    
    juce::Image mOnImagen;
    juce::Image mOffImagen;
    juce::Image mBackgroundImagen;
    
    Synth_LookAndFeel synthDesign;
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> volumenAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> oscOneAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> oscTwoAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> lfoRateOneAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> lfoRateTwoAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> typeOscOneAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> typeOscTwoAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment> powerLFOOneAttachment;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ButtonAttachment> powerLFOTwoAttachment;
    
    SynthCursoAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthCursoAudioProcessorEditor)
};
