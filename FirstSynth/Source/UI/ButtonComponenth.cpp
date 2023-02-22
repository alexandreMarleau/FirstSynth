/*
  ==============================================================================

    ButtonComponenth.cpp
    Created: 20 Feb 2023 9:56:08pm
    Author:  uaelr

  ==============================================================================
*/

#include "ButtonComponenth.h"
#include "../PluginProcessor.h"
#include "../SynthVoice.h"


ButtonComponent::ButtonComponent(juce::AudioProcessorValueTreeState& apvts, FirstSynthAudioProcessor& audioProcessor) : apvts2(apvts),
                                                                                                                    audioProcessor(audioProcessor)
{
    button.setTitle(juce::String("button"));
    button.setColour(1, juce::Colours::aqua);
    button.onClick = [this] { updateToggleState(&button, "Male");   };
    addAndMakeVisible(button);
}

ButtonComponent::~ButtonComponent()
{
}

void ButtonComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void ButtonComponent::resized()
{
    button.setBounds(0, 0, 100, 30);
}

void ButtonComponent::updateToggleState(juce::Button* button, juce::String name)
{
    for (int i = 0; i < audioProcessor.Synth.getNumVoices(); i++) 
    {
        dynamic_cast<SynthVoice*>(audioProcessor.Synth.getVoice(i))->addOsc(new OscData());
    }
    audioProcessor.prepareToPlay(44100,441);
    auto state = button->getToggleState();
    juce::String stateString = state ? "ON" : "OFF";
    juce::String selectedString = state ? " (selected)" : "";

    juce::Logger::outputDebugString(name + " Button changed to " + stateString);
    button->setButtonText(name + selectedString);
}
