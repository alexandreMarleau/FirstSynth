/*
  ==============================================================================

    OscData.h
    Created: 10 Feb 2023 6:47:28pm
    Author:  uaelr

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class OscData : public juce::dsp::Oscillator<float>
{
public:
    void setWaveType(const int choice, const float modifier, std::function<NumericType(NumericType)> modulatingWave);
    void prepareToPlay(juce::dsp::ProcessSpec spec);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& audioBlock);
    void setWaveFrequency(const int midiNoteNumber);
    void setGain(const float levelInDecibels);
    void OscData::getNoteNumber();
    int noteNumber;
    std::function<NumericType(NumericType)> generator;

private:
    juce::dsp::Gain<float> gain;
    juce::dsp::Oscillator<float> fmOsc;
};
