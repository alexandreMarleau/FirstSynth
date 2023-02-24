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
    void setWaveType(const int choice);
    void prepareToPlay(juce::dsp::ProcessSpec spec);
    void getNextAudioBlock(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    void setWaveFrequency(const int midiNoteNumber);
    void setGain(const float levelInDecibels);
    void OscData::getNoteNumber();
    int noteNumber;


private:
    juce::dsp::Gain<float> gain;
};
