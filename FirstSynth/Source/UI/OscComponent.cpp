/*
  ==============================================================================

    OscComponent.cpp
    Created: 10 Feb 2023 9:23:15pm
    Author:  uaelr

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, std::string oscId, std::string gainId)
{
    juce::StringArray waveChoices{ "Sine", "Saw", "Square", "Custom"};
    oscWaveSelector.addItemList(waveChoices, 1);
    oscWaveSelector.setSelectedItemIndex(0);
     
    oscSelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, oscId, oscWaveSelector);
    addAndMakeVisible(oscWaveSelector);


    oscGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, gainId, gainOscSlider);
    setSliderParams(gainOscSlider);
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void OscComponent::resized()
{
    oscWaveSelector.setBounds(0, 0, 100, 30);
    gainOscSlider.setBounds(oscWaveSelector.getWidth() + 10, 0, 100, 50);
}

void OscComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}
