/*
  ==============================================================================

    ButtonComponenth.h
    Created: 20 Feb 2023 9:56:08pm
    Author:  uaelr

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../PluginProcessor.h"


class ButtonComponent : public juce::Component
{
public:
    ButtonComponent(juce::AudioProcessorValueTreeState& apvts, FirstSynthAudioProcessor&);
    ~ButtonComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void updateToggleState(juce::Button* button, juce::String name);

private:
    juce::AudioProcessorValueTreeState& apvts2;
    FirstSynthAudioProcessor& audioProcessor;

    juce::TextButton button;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ButtonComponent)
};