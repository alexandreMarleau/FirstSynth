/*
  ==============================================================================

    OscData.cpp
    Created: 10 Feb 2023 6:47:28pm
    Author:  uaelr

  ==============================================================================
*/

#include "OscData.h"

void OscData::setWaveType(const int choice, const float modifier)/* il fuadrait plutot créer une enum avec les choix plutard*/
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
        //initialise([](float x) {return std::sin(juce::MathConstants<float>::pi * x) + (4 / juce::MathConstants<float>::pi) * (1 / 5) * std::sin(5*juce::MathConstants<float>::pi*x);});
       
        //initialise([modifier](float x) {return std::sin(x) * std::sin(modifier *x ) * 4; });

        //initialise([modifier](float x) {return std::sin(2 * x + 1.5*std::sin(2*2*x)) ;});
        initialise([modifier](float x) {return std::sin(1 * x +  modifier * std::sin( 1 * x));});


        break;
    default:
        jassertfalse; // On est pas supposer être ici.
        break;
    }
}

void OscData::prepareToPlay(juce::dsp::ProcessSpec spec)
{
   /* fmOsc.prepare(spec);
    fmOsc.initialise([](float x) {return std::sin(x);});*/
    prepare(spec);
    gain.prepare(spec);
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& audioBlock)
{

    process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    processFmMod(audioBlock);


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

void OscData::processFmMod(juce::dsp::AudioBlock<float>& audioBlock)
{
    for (int ch = 0; ch < audioBlock.getNumChannels(); ++ch)
    {
        for (int s = 0; s < audioBlock.getNumSamples(); ++s)
        {
           // audioBlock.setSample(ch,s, audioBlock.getSample(ch, s) + std::sin(std::asin(audioBlock.getSample(ch, s)*0)    ) );
            float x = std::asin(audioBlock.getSample(ch, s));
            float r = audioBlock.getSample(ch, s);
            //audioBlock.setSample(ch, s, std::sin(std::cos(x*4)*x));
            //audioBlock.setSample(ch, s, audioBlock.getSample(ch, s));
           // fmOsc.processSample(audioBlock.getSample(ch, s));
            float v = audioBlock.getSample(ch, s);


        }
    }

}

