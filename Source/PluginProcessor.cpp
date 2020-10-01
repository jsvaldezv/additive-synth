#include "PluginProcessor.h"
#include "PluginEditor.h"

SynthCursoAudioProcessor::SynthCursoAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    addParameter(sliVolume = new juce::AudioParameterFloat("sliVolume", "Volumen", 0.0f, 1.0f, 0.5f));
    addParameter(sliSineWave = new juce::AudioParameterFloat("sliSineWave", "SineWave", 0.0f, 1.0f, 0.0f));
    addParameter(sliSquareWave = new juce::AudioParameterFloat("sliSquareWave", "SquareWave", 0.0f, 1.0f, 0.0f));
    addParameter(sliTriangleWave = new juce::AudioParameterFloat("sliTriangleWave", "TriangleWave", 0.0f, 1.0f, 0.0f));
    addParameter(sliWhiteNoise = new juce::AudioParameterFloat("sliWhiteNoise", "WhiteNoise", 0.0f, 1.0f, 0.0f));
    
    mySynth.clearVoices();
    
    for(int i=0; i<5; i++)
    {
        mySynth.addVoice(new Synth_Voice);
    }
    
    mySynth.clearSounds();
    mySynth.addSound(new Synth_Sound);
}

SynthCursoAudioProcessor::~SynthCursoAudioProcessor()
{
    
}

//==============================================================================
const juce::String SynthCursoAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthCursoAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthCursoAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthCursoAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthCursoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthCursoAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthCursoAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthCursoAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SynthCursoAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthCursoAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SynthCursoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    initializeDSP();
    
    /*for(int i=0; i<2; i++)
    {
        paraOscillator[i]->wavetable(sampleRate);
        paraLFO[i]->wavetable(sampleRate);
    }*/

    juce::ignoreUnused(samplesPerBlock);
    
    lastSampleRate = sampleRate;
    mySynth.setCurrentPlaybackSampleRate(lastSampleRate);
}

void SynthCursoAudioProcessor::initializeDSP()
{
    for(int i=0; i<2; i++)
    {
        //paraVolumen[i] = new Synth_Volumen;
        //paraOscillator[i] = new Synth_Oscillators;
        //paraLFO[i] = new Synth_LFO;
    }
}

void SynthCursoAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthCursoAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthCursoAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

    /*for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
    
        paraOscillator[channel]->process(channelData,
                                         channelData,
                                         buffer.getNumSamples(),
                                         *sliSineWave,
                                         *sliSquareWave,
                                         *sliTriangleWave,
                                         *sliWhiteNoise);
        
        paraLFO[channel]->process(channelData,
                                  channelData,
                                  buffer.getNumSamples());

        paraVolumen[channel]->processVolumen(channelData,
                                             *sliVolume,
                                             channelData,
                                             buffer.getNumSamples());
    }*/
}

bool SynthCursoAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SynthCursoAudioProcessor::createEditor()
{
    return new SynthCursoAudioProcessorEditor (*this);
}

//==============================================================================
void SynthCursoAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthCursoAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthCursoAudioProcessor();
}
