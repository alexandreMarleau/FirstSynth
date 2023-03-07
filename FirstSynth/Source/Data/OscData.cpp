/*
  ==============================================================================

    OscData.cpp
    Created: 10 Feb 2023 6:47:28pm
    Author:  uaelr

  ==============================================================================
*/

#include "OscData.h"

void OscData::setWaveType(const int choice, const float modifier, const float offset,
                          std::function<NumericType(NumericType)> modulatingWave)/* il fuadrait plutot créer une enum avec les choix plutard*/
{
    //return std::sin(x); //SineWave
    //return x / juce::MathConstants<float>::pi;
    switch (choice)
    {
    case 0://Sine wave
    {
        std::function<float(float x)> wave = [](float x) { return std::sin(x); };
        initialise(wave);
        generator = (wave);
        break;
    }

    case 1: //saw wave
    {
        std::function<float(float x)> wave = [](float x) {return x / juce::MathConstants<float>::pi; };
        initialise(wave);
        generator = (wave);
        break;
    }

    case 2:// Square Wave
    {
        std::function<float(float x)> wave = [](float x) {return x < 0.0f ? -1.0f : 1.0f;};
        initialise(wave);
        generator = (wave);
        break;
    }

    case 3://Triangle wave
    {
        std::function<float(float x)> wave = [](float x) {return std::acos(std::sin(x));};
        initialise(wave);
        generator = (wave);
        break;
    }

    case 4:
    {
        //initialise([](float x) {return std::sin(x) * (x / juce::MathConstants<float>::pi); });
        //initialise([](float x) {return std::sin(x) * std::sin(x*5)*4; });
        //initialise([](float x) {return std::sin(juce::MathConstants<float>::pi * x) + (4 / juce::MathConstants<float>::pi) * (1 / 5) * std::sin(5*juce::MathConstants<float>::pi*x);});

        //initialise([modifier](float x) {return std::sin(x) * std::sin(modifier *x ) * 4; });

        //std::function<float(float x)> wave = [modifier](float x) {return std::sin(1 * x + modifier * std::sin(1 * x));};
        std::function<float(float x)> wave = [modifier, offset, modulatingWave](float x) {return std::sin(1 * x + offset + modifier * modulatingWave(x));};
        initialise(wave);
        generator = (wave);
        break;
    }

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

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& audioBlock)
{

    process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

}

void OscData::setWaveFrequency(const int midiNoteNumber)
{
    fmOsc.setFrequency(midiNoteNumber);
    
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
