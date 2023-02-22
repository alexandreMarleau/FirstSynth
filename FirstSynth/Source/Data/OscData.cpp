/*
  ==============================================================================

    OscData.cpp
    Created: 10 Feb 2023 6:47:28pm
    Author:  uaelr

  ==============================================================================
*/

#include "OscData.h"

void OscData::setWaveType(const int choice)/* il fuadrait plutot cr�er une enum avec les choix plutard*/
{
    //return std::sin(x); //SineWave
    //return x / juce::MathConstants<float>::pi;

    switch (choice)
    {
    case 0:
        //SineWave
        initialise([](float x) {return std::sin(x);});
            break;
    case 1: 
        //saw wave
        initialise([](float x) {return x / juce::MathConstants<float>::pi; });
        break;
    case 2:
        initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f;});
        break;
    case 3:
        //initialise([](float x) {return std::sin(x) * (x / juce::MathConstants<float>::pi); });
        initialise([](float x) {return std::sin(x) * std::sin(x*5)*4; });

        break;
        //square wave
    default:
        jassertfalse; // On est pas supposer �tre ici.
        break;
    }
}

void OscData::prepareToPlay(juce::dsp::ProcessSpec spec)
{
    prepare(spec);
    gain.prepare(spec);
}

void OscData::getNextAudioBlock(juce::dsp::ProcessContextReplacing<float>(audioBlock))
{
    process(audioBlock);
    gain.process(audioBlock);

}

void OscData::setWaveFrequency(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
}

void OscData::setGain(const float levelInDecibels)
{
    gain.setGainLinear(levelInDecibels);
}

