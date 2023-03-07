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
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, int oscId)
{
    juce::StringArray waveChoices{ "Sine", "Saw", "Square", "Triangle","Custom"};
    oscWaveSelector.addItemList(waveChoices, 1);
    oscWaveSelector.setSelectedItemIndex(0);
     
    oscSelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, "OSC" + std::to_string(oscId + 1), oscWaveSelector);
    addAndMakeVisible(oscWaveSelector);


    oscGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "GAINOSC" + std::to_string(oscId + 1), gainOscSlider);
    setSliderParams(gainOscSlider, gainOscLabel);

    octaveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "OCTAVE" + std::to_string(oscId + 1), octaveSlider);
    addAndMakeVisible(octaveSlider);

    offsetAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "OFFSET" + std::to_string(oscId + 1), offsetSlider);
    setSliderParams(offsetSlider, offsetLabel);

    // Modifiers
    modifierAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, "MODIFIER" + std::to_string(oscId + 1), modifierSlider);
    setSliderParams(modifierSlider, modifierLabel);

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
    setSize(500, 100);

    oscWaveSelector.setBounds(0, getHeight() / 2 - 15, 100, 30);
    gainOscSlider.setBounds(oscWaveSelector.getWidth() + 10, 0, 75, 75);
    octaveSlider.setBounds(gainOscSlider.getX() + gainOscSlider.getWidth() + 10, 0, 75, 75);
    modifierSlider.setBounds(octaveSlider.getX() + octaveSlider.getWidth() + 10, 0, 75, 75);
    offsetSlider.setBounds(modifierSlider.getX() + modifierSlider.getWidth() + 10, 0, 75, 75);


}

void OscComponent::setSliderParams(juce::Slider& slider, juce::Label& label)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);

    label.attachToComponent(&slider, false); // [4]
    juce::Font myFont = juce::Font(17.0f, juce::Font::bold);
    myFont.setTypefaceName("Arial");
    label.setFont(myFont);
    label.setColour(juce::Label::textColourId, juce::Colours::white);
    label.setText("Gain", juce::dontSendNotification);
    addAndMakeVisible(label);

}
