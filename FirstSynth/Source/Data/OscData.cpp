/*
  ==============================================================================

    OscData.cpp
    Created: 10 Feb 2023 6:47:28pm
    Author:  uaelr

  ==============================================================================
*/

#include "OscData.h"

void OscData::setWaveType(const int choice)/* il fuadrait plutot créer une enum avec les choix plutard*/
{
    //return std::sin(x); //SineWave
    //return x / juce::MathConstants<float>::pi;

    switch (choice)
    {
    case 0:
        //Sine wave
        initialise([](float x) {return std::sin(x);});
            break;
    case 1: 
        //saw wave
        initialise([](float x) {return x / juce::MathConstants<float>::pi; });
        break;
    case 2:
        //Square wave
        initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f;});
        break;
    case 3:
        //Triangle wave
       
        initialise([](float x) {return std::acos(std::sin(x));});

        break;
    case 4:
        //initialise([](float x) {return std::sin(x) * (x / juce::MathConstants<float>::pi); });
        //initialise([](float x) {return std::sin(x) * std::sin(x*5)*4; });
        initialise([](float x) {return std::sin(juce::MathConstants<float>::pi * x) + (4 / juce::MathConstants<float>::pi) * (1 / 5) * std::sin(5*juce::MathConstants<float>::pi*x);});

    default:
        jassertfalse; // On est pas supposer être ici.
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
    noteNumber = midiNoteNumber;
}

void OscData::getNoteNumber()
{
    float noteInHertz = getFrequency();
}

void OscData::setGain(const float levelInDecibels)
{
    gain.setGainLinear(levelInDecibels);
}

