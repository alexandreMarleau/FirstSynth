/*
  ==============================================================================

    OscComponent.h
    Created: 10 Feb 2023 9:23:15pm
    Author:  uaelr

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, std::string Id, std::string gainId);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void setSliderParams(juce::Slider& slider);

    juce::ComboBox oscWaveSelector;
    juce::Slider gainOscSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> oscGainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscComponent)
};


