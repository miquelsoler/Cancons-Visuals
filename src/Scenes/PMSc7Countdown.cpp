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
    countdownFont.load("fonts/NeutraTextTF-Book.otf", 100, true, true, false, 0.3, 72);
    setSingleSetup(false);
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
    line=ofPoint(0, 200);
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
    float timeElapsed=countdown.getDiff()/(float)1000;
    timeElapsed-=(int)timeElapsed;
    line.x=400*sin(timeElapsed*2*PI);
    line.y=-400*cos(timeElapsed*2*PI);
}

void PMSc7Countdown::draw()
{
    PMBaseScene::draw();
    unsigned int countdownTime;
#ifdef OF_DEBUG
    countdownTime = PMSettingsManagerGeneral::getInstance().getDebugScene7CountdownTime();
#else
    countdownTime = PMSettingsManagerGeneral::getInstance().getReleaseScene7CountdownTime();
#endif
    ofPushMatrix();
    float scaleX=(float)ofGetWidth()/(float)1080;
    float scaleY=(float)ofGetHeight()/(float)1920;
    ofScale(scaleX, scaleY);
    ofPoint center=ofPoint(1080/2, 1920/2);
//    ofSetColor(ofColor::gray);
//    ofDrawLine(center, center+line);
//    ofColor(127, 127, 127, 127);
//    ofDrawCircle(center.x, center.y, 100);
    drawCenteredFont(baseBoldFont, "Prem espai", 1080/2, 100);
    drawCenteredFont(baseBoldFont, "quan vulguis finalitzar la visualització", 1080/2, 150);
    ofSetColor(ofColor::white);
    drawCenteredFont(countdownFont, ofToString(countdownTime - (int) countdown.getDiff() / 1000), center.x, center.y);
  
    ofPopMatrix();
}

void PMSc7Countdown::updateExit()
{
    PMBaseScene::updateExit();
}

void PMSc7Countdown::exit()
{
    countdown.~ofxTimer();
}