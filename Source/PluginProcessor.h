#pragma once

#include <JuceHeader.h>
#include "Synth_Volumen.h"
#include "Synth_Oscillators.h"
#include "Synth_LFO.h"
#include "Synth_Sound.h"
#include "Synth_Voice.h"

class SynthCursoAudioProcessor  : public juce::AudioProcessor
{
public:
    SynthCursoAudioProcessor();
    ~SynthCursoAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void initializeDSP();

private:

    juce::AudioParameterFloat* sliVolume;
    juce::AudioParameterFloat* sliSineWave;
    juce::AudioParameterFloat* sliSquareWave;
    juce::AudioParameterFloat* sliTriangleWave;
    juce::AudioParameterFloat* sliWhiteNoise;
    
    //juce::ScopedPointer<Synth_Volumen> paraVolumen [2];
    //juce::ScopedPointer<Synth_Oscillators> paraOscillator [2];
    //juce::ScopedPointer<Synth_LFO> paraLFO [2];
    
    juce::Synthesiser mySynth;
    //juce::Synthesiser* myVoice;
    Synth_Voice* myVoice;
    
    double lastSampleRate;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthCursoAudioProcessor)
};
