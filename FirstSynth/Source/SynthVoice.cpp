/*
  ==============================================================================

    SynthVoice.cpp
    Created: 2 Feb 2023 8:02:37pm
    Author:  uaelr

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound) 
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}
void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) 
{
    for (auto osc : oscArrays)
        osc->setWaveFrequency(midiNoteNumber);

    //osc1.setWaveFrequency(midiNoteNumber);
    adsrData.noteOn();
}
void SynthVoice::stopNote(float velocity, bool allowTailOff) 
{
    adsrData.noteOff();

    if (!allowTailOff || !adsrData.isActive())
        clearCurrentNote();
}
void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue) {}
void SynthVoice::pitchWheelMoved(int newPitchWheelValue) {}
void SynthVoice::prepareToPlay(double sampleRate, int samplePerBlock, int outputChannels)
{


    adsrData.setSampleRate(sampleRate);

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplePerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;


    for (auto osc : oscArrays)
        osc->prepare(spec);

    //osc1.prepare(spec);

    masterGain.prepare(spec);

    masterGain.setGainLinear(0.09f);

    isPrepared = true;
}
//pour l'instant on uipdate juste le adsr mais eventuellement on peut update nimporte quoi
void SynthVoice::update(const float attack, const float decay, const float sustain, const float release) 
{
    adsrData.updateADSR(attack,  decay,  sustain, release);
}
void SynthVoice::setApvts(juce::AudioProcessorValueTreeState* apvtsTemp)
{
    apvts = apvtsTemp;
}
void SynthVoice::renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);

    if (!isVoiceActive())
        return;

    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();



    juce::AudioBuffer<float> cleanBuffer = synthBuffer;

    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };
    //osc1.getNextAudioBlock(audioBlock);

    // Upgrade Peut etre on devrait utilisé le context non replacing
    masterGain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    for (auto osc : oscArrays)
    {
        juce::dsp::AudioBlock<float> cleanAudioBlock{ cleanBuffer };
        osc->getNextAudioBlock(cleanAudioBlock);

        audioBlock.add(cleanAudioBlock);
    }


    adsrData.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

    for (int channel = 0; channel < synthBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);

        if (!adsrData.isActive())
            clearCurrentNote();
    }
}
