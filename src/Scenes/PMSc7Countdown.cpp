//
//  PMSc7Countdown.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 29/10/15.
//
//

#include "PMSc7Countdown.hpp"
#include "PMSettingsManagerGeneral.h"
#include "PMMotionExtractor.hpp"
#include "PMAudioAnalyzer.hpp"


PMSc7Countdown::PMSc7Countdown() : PMBaseScene("Scene 7")
{
}

void PMSc7Countdown::setup()
{
    unsigned int countdownTime;
#ifdef OF_DEBUG
    countdownTime = PMSettingsManagerGeneral::getInstance().getDebugScene7CountdownTime();
#else
    countdownTime = PMSettingsManagerGeneral::getInstance().getReleaseScene7CountdownTime();
#endif
    
    countdown.set();
    countdown.setAlarm(countdownTime * 1000);
    PMAudioAnalyzer::getInstance().start();
}

void PMSc7Countdown::updateEnter()
{
    PMBaseScene::updateEnter();
}

void PMSc7Countdown::update()
{
#if ENABLE_KINECT
    PMMotionExtractor::getInstance().update();
#endif

    if (countdown.alarm()) {
        countdown.resetAlarm();
        string toScene = "Scene 8";
        ofNotifyEvent(goToSceneEvent, toScene, this);
    }
}

void PMSc7Countdown::draw()
{
    unsigned int countdownTime;
#ifdef OF_DEBUG
    countdownTime = PMSettingsManagerGeneral::getInstance().getDebugScene7CountdownTime();
#else
    countdownTime = PMSettingsManagerGeneral::getInstance().getReleaseScene7CountdownTime();
#endif

    drawCenteredFont(baseFont, ofToString(countdownTime - (int) countdown.getDiff() / 1000), ofGetWidth() / 2, ofGetHeight() / 2);
}

void PMSc7Countdown::updateExit()
{
    PMBaseScene::updateExit();
}

void PMSc7Countdown::exit()
{
    countdown.~ofxTimer();
}