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
                       ), parameters(*this, nullptr, "PARAMETERS", initializeGUI())
#endif
{
    mySynth.clearVoices();
    
    for(int i=0; i<5; i++)
    {
        mySynth.addVoice(new Synth_Voice);
    }
    
    mySynth.clearSounds();
    mySynth.addSound(new Synth_Sound);
    
    volGeneral = 0.1f;
}

SynthCursoAudioProcessor::~SynthCursoAudioProcessor()
{
    
}

juce::AudioProcessorValueTreeState::ParameterLayout SynthCursoAudioProcessor::initializeGUI()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>("volume",
                                                                 "Volume",
                                                                 0.0f,
                                                                 1.0f,
                                                                 0.5f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>("oscone",
                                                                 "Oscone",
                                                                 0.0f,
                                                                 1.0f,
                                                                 0.5f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat>("osctwo",
                                                                 "Osctwo",
                                                                 0.0f,
                                                                 1.0f,
                                                                 0.5f));
    
    params.push_back(std::make_unique<juce::AudioParameterChoice>("typeoscone",
                                                                  "Typeoscone",
                                                                  juce::StringArray("Sine",
                                                                                    "Square",
                                                                                    "Triangle"),0));
    
    params.push_back(std::make_unique<juce::AudioParameterChoice>("typeosctwo",
                                                                  "Typeosctwo",
                                                                  juce::StringArray("Sine",
                                                                                    "Square",
                                                                                    "Triangle"),0));
    
    return {params.begin(), params.end()};
}

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
    return 1;
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
    /*for(int i=0; i<2; i++)
    {
        //paraVolumen[i] = new Synth_Volumen;
        //paraOscillator[i] = new Synth_Oscillators;
        //paraLFO[i] = new Synth_LFO;
    }*/
}

void SynthCursoAudioProcessor::releaseResources()
{

}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthCursoAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else

    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

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
    
    for(int i=0; i < mySynth.getNumVoices(); i++)
    {
        if((myVoice = dynamic_cast<Synth_Voice*>(mySynth.getVoice(i))))
        {
            myVoice->getParams(*parameters.getRawParameterValue("volume"),
                               *parameters.getRawParameterValue("oscone"),
                               *parameters.getRawParameterValue("osctwo"),
                               *parameters.getRawParameterValue("typeoscone"),
                               *parameters.getRawParameterValue("typeosctwo"));
        }
    }
    
    buffer.clear();
    mySynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

bool SynthCursoAudioProcessor::hasEditor() const
{
    return true;
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
