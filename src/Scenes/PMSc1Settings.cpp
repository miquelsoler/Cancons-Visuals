//
//  PMSc1Settings.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#include "PMSc1Settings.hpp"
#include "PMMotionExtractor.hpp"
#include "Defaults.h"

#define ENABLE_SOUNDFLOWER true

PMSc1Settings::PMSc1Settings() : PMBaseScene("Scene 1")
{
    ofBackground(150);
    setFade(1000, 1000);
    //setupGUI_SONG();
}

void PMSc1Settings::setup()
{
    // Kinect Setup

    PMMotionExtractor::getInstance().setup();

    // Audio Analysis Setup

    int iDev;
#if ENABLE_SOUNDFLOWER
    iDev = findSoundflowerDeviceIndex();
    if (iDev == -1) exit();
#else
    iDev = 0;
#endif

    vector<ofSoundDevice> devices = PMAudioAnalyzer::getInstance().getInputDevices();

//    unsigned int audioInputIndex = (unsigned int)iDev;
    unsigned int audioInputIndex = 0;
    vector<unsigned int> enabledChannelNumbers;
    for (unsigned int i=0; i<devices[iDev].inputChannels; ++i)
        enabledChannelNumbers.push_back(i);

//    PMAudioAnalyzer::getInstance().addDeviceAnalyzer(audioInputIndex, devices[iDev].deviceID,
//            devices[iDev].inputChannels, devices[iDev].outputChannels,
//            DEFAULT_SAMPLERATE, DEFAULT_BUFFERSIZE,
//            enabledChannelNumbers);
    
    PMAudioAnalyzer::getInstance().addDeviceAnalyzer(0, devices[iDev].deviceID,
                                                                 devices[iDev].inputChannels, devices[iDev].outputChannels,
                                                                 DEFAULT_SAMPLERATE, DEFAULT_BUFFERSIZE,
                                                                 enabledChannelNumbers);
    
    string sceneToChange="Scene 2";
    ofNotifyEvent(goToSceneEvent, sceneToChange, this);
}

/*
void PMSc1Settings::setupGUI_SONG()
{
    gui_song = new ofxUISuperCanvas("Welcome to Visual Songs");
    gui_song->addSpacer();
    gui_song->addSpacer();
    vector<string> song_names;
    song_names.push_back("ONhdfjkdshflaksjdhflksajdhflkjashdljfhE");    song_names.push_back("TWO");    song_names.push_back("THREE");    song_names.push_back("FOUR");    song_names.push_back("FIVE");
    gui_song->setWidgetFontSize(OFX_UI_FONT_SMALL);
    ddl = gui_song->addDropDownList("CHOSE YOUR SONG", song_names);
    ddl->setAllowMultiple(false);
    ddl->setAutoClose(true);
    gui_song->autoSizeToFitWidgets();
    gui_song->setDrawWidgetPadding(true);
    //gui_song->set
    ofAddListener(gui_song->newGUIEvent, this, &PMSc1Settings::guiEvent);
}
*/

void PMSc1Settings::update()
{
    
}

void PMSc1Settings::draw()
{
    
}

void PMSc1Settings::guiEvent(ofxUIEventArgs &e)
{
    
}

int PMSc1Settings::findSoundflowerDeviceIndex()
{
    int deviceIndex = -1;

    vector<ofSoundDevice> devices = PMAudioAnalyzer::getInstance().getInputDevices();
    bool found = false;

    for (unsigned int i=0; i<devices.size() && !found; ++i)
    {
        string deviceName = devices[i].name;
        found = (ofIsStringInString(deviceName, "Soundflower")) && (devices[i].inputChannels == 2);

        if (found) deviceIndex = i;
    }

    return deviceIndex;
}
