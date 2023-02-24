/*
  ==============================================================================

    SynthVoice.h
    Created: 2 Feb 2023 8:02:37pm
    Author:  uaelr

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "Data/AdsrData.h"
#include "Data/OscData.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void prepareToPlay(double sampleRate, int samplePerBlock, int outputChannels);
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    void SynthVoice::update(const float attack, const float decay, const float sustain, const float release);
    OscData& getOscillator1() { return osc1; };
    //OscData& getOscillator2() { return osc2; };
    OscData* getOsc(const int index) { return oscArrays[index]; };
    const int getOscSize() { return oscArrays.size(); };
    void addOsc(OscData* oscData) { oscArrays.add(oscData); };
    void setApvts(juce::AudioProcessorValueTreeState* apvts);

private:
    AdsrData adsrData;

    juce::AudioBuffer<float> synthBuffer;
    juce::AudioProcessorValueTreeState* apvts;


    //juce::dsp::Oscillator<float> osc{ [](float x) {return std::sin(x)  + (x / juce::MathConstants<float>::pi ); } };
    juce::dsp::Gain<float> masterGain;
    bool isPrepared{ false };

    juce::OwnedArray<OscData> oscArrays = {new OscData(), new OscData() };

   OscData osc1;


};