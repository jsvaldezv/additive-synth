#include "PluginProcessor.h"
#include "PluginEditor.h"

SynthCursoAudioProcessorEditor::SynthCursoAudioProcessorEditor (SynthCursoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    auto& params = processor.getParameters();
    setSize (400, 300);
    
    addAndMakeVisible(volumenSlider);
    volumenSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    volumenSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 20);
    volumenSlider.setRange(0.0f, 1.0f, 0.7f);
    volumenSlider.setBounds(0, 0, 100, 100);
    volumenSlider.addListener(this);
    
    volumenAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, "volume", volumenSlider);
    
    addAndMakeVisible(volumenOscOne);
    volumenOscOne.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    volumenOscOne.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 20);
    volumenOscOne.setRange(0.0f, 1.0f, 0.7f);
    volumenOscOne.setBounds(100, 0, 100, 100);
    volumenOscOne.addListener(this);
    
    oscOneAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, "oscone", volumenOscOne);
    
    addAndMakeVisible(volumenOscTwo);
    volumenOscTwo.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    volumenOscTwo.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 20);
    volumenOscTwo.setRange(0.0f, 1.0f, 0.7f);
    volumenOscTwo.setBounds(200, 0, 100, 100);
    volumenOscTwo.addListener(this);
    
    oscTwoAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, "osctwo", volumenOscTwo);
    
    typeOscOne.addItem("Sine", 1);
    typeOscOne.addItem("Square", 2);
    typeOscOne.addItem("Triangle", 3);
    typeOscOne.setJustificationType(juce::Justification::centred);
    typeOscOne.setBounds(0, 100, 100, 20);
    addAndMakeVisible(typeOscOne);
    
    typeOscOneAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment> (audioProcessor.parameters, "typeoscone", typeOscOne);
    
    typeOscTwo.addItem("Sine", 1);
    typeOscTwo.addItem("Square", 2);
    typeOscTwo.addItem("Triangle", 3);
    typeOscTwo.setJustificationType(juce::Justification::centred);
    typeOscTwo.setBounds(100, 100, 100, 20);
    addAndMakeVisible(typeOscTwo);
    
    typeOscTwoAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment> (audioProcessor.parameters, "typeosctwo", typeOscTwo);
}

SynthCursoAudioProcessorEditor::~SynthCursoAudioProcessorEditor()
{
    
}

void SynthCursoAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Synth", getLocalBounds(), juce::Justification::centred, 1);
}

void SynthCursoAudioProcessorEditor::resized()
{

}

void SynthCursoAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    if(slider == &volumenSlider)
    {
        audioProcessor.volGeneral = volumenSlider.getValue();
    }
}

void SynthCursoAudioProcessorEditor::comboBoxChanged (juce::ComboBox* comboBox)
{
    
}
