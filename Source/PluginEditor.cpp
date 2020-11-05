#include "PluginProcessor.h"
#include "PluginEditor.h"

SynthCursoAudioProcessorEditor::SynthCursoAudioProcessorEditor (SynthCursoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    auto& params = processor.getParameters();
    
    setSize (600, 400);
    
    mOffImagen = juce::ImageCache::getFromMemory(BinaryData::off_png, BinaryData::off_pngSize);
    mOnImagen = juce::ImageCache::getFromMemory(BinaryData::on_png, BinaryData::on_pngSize);
    mBackgroundImagen = juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);

    //SOBREESCRIBIR INTERFAZ A UNA PERSONALIZADA
    setLookAndFeel(&synthDesign);

    //GAIN OSC1
    addAndMakeVisible(volumenOscOne);
    volumenOscOne.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    volumenOscOne.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 20);
    volumenOscOne.setRange(0.0f, 1.0f, 0.7f);
    volumenOscOne.setBounds(97, 60, 90, 90);
    volumenOscOne.addListener(this);
    
    oscOneAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, "oscone", volumenOscOne);
    
    //GAIN OSC2
    addAndMakeVisible(volumenOscTwo);
    volumenOscTwo.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    volumenOscTwo.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 20);
    volumenOscTwo.setRange(0.0f, 1.0f, 0.7f);
    volumenOscTwo.setBounds(427, 60, 90, 90);
    volumenOscTwo.addListener(this);
    
    oscTwoAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment> (audioProcessor.parameters, "osctwo", volumenOscTwo);
    
    //RATE LFO ONE
    addAndMakeVisible(rateLFOOne);
    rateLFOOne.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rateLFOOne.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 20);
    rateLFOOne.setRange(1.0f, 10.0f, 1.0f);
    rateLFOOne.setBounds(110, 200, 80, 80);
    rateLFOOne.addListener(this);
    
    lfoRateOneAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
                        (audioProcessor.parameters, "lfoone", rateLFOOne);
    
    //RATE LFO TWO
    addAndMakeVisible(rateLFOTwo);
    rateLFOTwo.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    rateLFOTwo.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 20);
    rateLFOTwo.setRange(1.0f, 10.0f, 1.0f);
    rateLFOTwo.setBounds(410, 200, 80, 80);
    rateLFOTwo.addListener(this);
    
    lfoRateTwoAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>
                        (audioProcessor.parameters, "lfotwo", rateLFOTwo);
    
    //TYPE OSC1
    typeOscOne.addItem("Sine", 1);
    typeOscOne.addItem("Square", 2);
    typeOscOne.addItem("Triangle", 3);
    typeOscOne.setJustificationType(juce::Justification::centred);
    typeOscOne.setBounds(90, 155, 100, 20);
    addAndMakeVisible(typeOscOne);
    
    typeOscOneAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment> (audioProcessor.parameters, "typeoscone", typeOscOne);
    
    //TYPE OSC2
    typeOscTwo.addItem("Sine", 1);
    typeOscTwo.addItem("Square", 2);
    typeOscTwo.addItem("Triangle", 3);
    typeOscTwo.setJustificationType(juce::Justification::centred);
    typeOscTwo.setBounds(420, 155, 100, 20);
    addAndMakeVisible(typeOscTwo);
    
    typeOscTwoAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment> (audioProcessor.parameters, "typeosctwo", typeOscTwo);
    
    //*********************************************************************************************
    
    //POWER LFO ONE
    offLfoOne = new juce::ImageButton();
    offLfoOne->setButtonText("LFO1");
    offLfoOne->setClickingTogglesState(true);
    offLfoOne->onClick = [this]() {};
    offLfoOne->setBounds(186, 188, 30, 30);
    offLfoOne->setImages(false, true, false, mOffImagen, 1.0f, {}, mOffImagen, 1.0f, {}, mOnImagen, 1.0f, {});
    addAndMakeVisible(offLfoOne);
    
    powerLFOOneAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.parameters, "lfooneButton", *offLfoOne);
    
    //POWER LFO TWO
    offLfoTwo = new juce::ImageButton();
    offLfoTwo->setButtonText("LFO2");
    offLfoTwo->setClickingTogglesState(true);
    offLfoTwo->onClick = [this]() {};
    offLfoTwo->setBounds(383, 188, 30, 30);
    offLfoTwo->setImages(false, true, false, mOffImagen, 1.0f, {}, mOffImagen, 1.0f, {}, mOnImagen, 1.0f, {});
    addAndMakeVisible(offLfoTwo);
    
    powerLFOTwoAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.parameters, "lfotwoButton", *offLfoTwo);
}

SynthCursoAudioProcessorEditor::~SynthCursoAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

void SynthCursoAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.drawImage(mBackgroundImagen, getLocalBounds().toFloat());
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
