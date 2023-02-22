/*
  ==============================================================================

    AdsrData.h
    Created: 10 Feb 2023 1:47:37pm
    Author:  uaelr

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class AdsrData : public juce::ADSR
{
public:
    void updateADSR (const float attack, const float decay, const float sustain, const float release);

private:
    juce::ADSR::Parameters adsrParams;

};