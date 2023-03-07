/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SynthVoice.h"

//==============================================================================
FirstSynthAudioProcessorEditor::FirstSynthAudioProcessorEditor (FirstSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), adsr (audioProcessor.apvts) /*osc1(audioProcessor.apvts,"OSC1","GAINOSC1"), osc2(audioProcessor.apvts,"OSC2","GAINOSC2"),*/
                           // button(audioProcessor.apvts, audioProcessor)
{
    initOsc();

    button.setTitle(juce::String("button"));
    button.setColour(1, juce::Colours::aqua);
    button.setButtonText("Add Osc");
    button.onClick = [this] { updateToggleState(&button, "Male");   };
    addAndMakeVisible(button);

    setSize (800, 700);

    addAndMakeVisible(adsr);
    addAndMakeVisible(button);
}

FirstSynthAudioProcessorEditor::~FirstSynthAudioProcessorEditor()
{
}

//==============================================================================
void FirstSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);

}

void FirstSynthAudioProcessorEditor::resized()
{

    const auto oscWidth = 500;
    const auto oscHeight = 300;

 
    for (int i = 0; i < oscComponentArrays.size(); i++) 
    {
        int y = 0;
        if (i > 0)
            y = oscComponentArrays[i - 1]->getY() + oscComponentArrays[i - 1]->getHeight();

        oscComponentArrays[i]->setBounds(0, y, 200, 75);
    }

    //adsr.setBounds(getWidth() / 2, 0, getWidth() / 2, getWidth());
    button.setBounds(0, oscComponentArrays.getLast()->getY() + oscComponentArrays.getLast()->getHeight(), 400, 30);

}

void FirstSynthAudioProcessorEditor::updateToggleState(juce::Button* button, juce::String name)
{
    for (int i = 0; i < audioProcessor.Synth.getNumVoices(); i++)
        dynamic_cast<SynthVoice*>(audioProcessor.Synth.getVoice(i))->addOsc(new OscData());
    
    audioProcessor.prepareToPlay(44100, 441);
    auto state = button->getToggleState();

    initOsc();
    this->resized();
    this->repaint();
}

void FirstSynthAudioProcessorEditor::initOsc()
{
    oscComponentArrays.clear();
    auto voice = dynamic_cast<SynthVoice*>(audioProcessor.Synth.getVoice(0));

    for (int i = 0; i < dynamic_cast<SynthVoice*>(audioProcessor.Synth.getVoice(0))->getOscSize(); i++)
    {
        OscComponent* oscComp = new OscComponent(audioProcessor.apvts, i);
        oscComponentArrays.add(oscComp);
        addAndMakeVisible(oscComp);
    }
}