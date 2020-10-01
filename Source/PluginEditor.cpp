#include "PluginProcessor.h"
#include "PluginEditor.h"

SynthCursoAudioProcessorEditor::SynthCursoAudioProcessorEditor (SynthCursoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 300);
    
    addAndMakeVisible(oscOneVol);
    oscOneVol.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    oscOneVol.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 20);
    oscOneVol.setRange(0.0f, 1.0f, 0.7f);
    oscOneVol.setBounds(0, 0, 100, 100);
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
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
