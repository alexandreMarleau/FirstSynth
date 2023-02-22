/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/AdsrComponent.h"
#include "UI/OscComponent.h"
#include "UI/ButtonComponenth.h"


//==============================================================================
/**
*/
class FirstSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FirstSynthAudioProcessorEditor (FirstSynthAudioProcessor&);
    ~FirstSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void FirstSynthAudioProcessorEditor::updateToggleState(juce::Button* button, juce::String name);
    void FirstSynthAudioProcessorEditor::initOsc();



private:
    FirstSynthAudioProcessor& audioProcessor;

    //ButtonComponent button;

    
    AdsrComponent adsr;


    juce::OwnedArray<OscComponent> oscComponentArrays;
    std::vector<OscComponent> oscComponentVector;;

    juce::TextButton button;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FirstSynthAudioProcessorEditor)
};
