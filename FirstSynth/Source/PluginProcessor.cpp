/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthVoice.h"
#include "SynthSound.h"


//==============================================================================
FirstSynthAudioProcessor::FirstSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts (*this, nullptr, "Parameters", createParams())
#endif
{
    for (auto i = 0; i < 6; i++)
    {
        SynthVoice* synthVoice = new SynthVoice();
        synthVoice->setApvts(&apvts);
        Synth.addVoice(synthVoice);
    }
    Synth.addSound(new SynthSound());

    //addOscParams();

}

FirstSynthAudioProcessor::~FirstSynthAudioProcessor()
{
}

//==============================================================================
const juce::String FirstSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FirstSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FirstSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FirstSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FirstSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FirstSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FirstSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FirstSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FirstSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void FirstSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FirstSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

    Synth.setCurrentPlaybackSampleRate(sampleRate);

    for (int i = 0; i < Synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(Synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
}

void FirstSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.proce
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FirstSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
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

void FirstSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

   
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    //Update if any user updated a parameter
    for (int i = 0; i < Synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(Synth.getVoice(i)))
        {
            // Osc Controls
            // ADSR
            // On va chercher la valeur de chaque slider
            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");

            // Load car de sont des atomic float. on va chercher le float directe.
            voice->update(attack.load(), decay.load(), sustain.load(), release.load());

            for (int i = 0; i < voice->getOscSize(); i++)
            {
                auto* osc = voice->getOsc(i);
                int id = i + 1;
                auto& oscWaveChoice = *apvts.getRawParameterValue("OSC" + std::to_string(id));
                auto& gainOsc = *apvts.getRawParameterValue("GAINOSC" + std::to_string(id));
                auto& octave = *apvts.getRawParameterValue("OCTAVE" + std::to_string(id));

                
                int noteNumber = osc->noteNumber;
                osc->setFrequency(juce::MidiMessage::getMidiNoteInHertz(noteNumber + octave));
                osc->setWaveType(oscWaveChoice);
                osc->setGain(gainOsc);
            }
        }
    }
    Synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool FirstSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FirstSynthAudioProcessor::createEditor()
{
    return new FirstSynthAudioProcessorEditor (*this);
}

//==============================================================================
void FirstSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FirstSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FirstSynthAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout FirstSynthAudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    //Osc Select

    for (int i = 1; i < 20; i++)
    {
        params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC"+ std::to_string(i), "Oscillator" + std::to_string(i), juce::StringArray{ "Sine","Saw","Square", "Triangle","Custom" }, 0));
        params.push_back(std::make_unique<juce::AudioParameterFloat>("GAINOSC" + std::to_string(i), "GainOsc" + std::to_string(i), juce::NormalisableRange<float> {0.f, 0.1f}, 0.07f));
        params.push_back(std::make_unique<juce::AudioParameterInt>("OCTAVE" + std::to_string(i), "Octave" + std::to_string(i), -36, 36, 0));

    }

    //ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float> {0.f, 1.0f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float> {0.f, 1.0f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float> {0.f, 1.0f}, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float> {0.f, 1.0f}, 0.4f));

    return 
    { params.begin(),params.end()};
}
