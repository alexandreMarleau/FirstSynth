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
    OscComponent(juce::AudioProcessorValueTreeState& apvts, int oscId);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void setSliderParams(juce::Slider& slider, juce::Label& label);

    juce::ComboBox oscWaveSelector;
    juce::Slider gainOscSlider;
    juce::Label gainOscLabel;
    juce::Slider octaveSlider;
    juce::Slider modifierSlider;
    juce::Label modifierLabel;
    juce::Slider offsetSlider;
    juce::Label offsetLabel;



    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> oscGainAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> octaveAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> modifierAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> offsetAttachment;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscComponent)
};


