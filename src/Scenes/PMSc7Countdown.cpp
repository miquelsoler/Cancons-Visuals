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
//#include "PMAudioAnalyzer.hpp"


PMSc7Countdown::PMSc7Countdown() : PMBaseScene("Scene 7")
{
    countdownFont.load("fonts/NeutraTextTF-Book.otf", 100, true, true, false, 0.3, 72);
    setSingleSetup(false);
	backgroundImage.load("assets/PUBLIC_03.png");
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
    line=ofPoint(0, 200);
}

void PMSc7Countdown::updateEnter()
{
    PMBaseScene::updateEnter();
}

void PMSc7Countdown::update()
{
#if ENABLE_LIVE
	string toScene = "Scene 8";
	ofNotifyEvent(goToSceneEvent, toScene, this);
#else
    if (countdown.alarm()) {
        countdown.resetAlarm();
        string toScene = "Scene 8";
        ofNotifyEvent(goToSceneEvent, toScene, this);
    }
    float timeElapsed=countdown.getDiff()/(float)1000;
    timeElapsed-=(int)timeElapsed;
    line.x=400*sin(timeElapsed*2*PI);
    line.y=-400*cos(timeElapsed*2*PI);
#endif
}

void PMSc7Countdown::draw()
{
	ofPushMatrix();
	ofMultMatrix(*homography);

	ofPushStyle();
	ofSetColor(255);
	backgroundImage.draw(0, 0);
	ofPopStyle();

    unsigned int countdownTime;
#ifdef OF_DEBUG
    countdownTime = PMSettingsManagerGeneral::getInstance().getDebugScene7CountdownTime();
#else
    countdownTime = PMSettingsManagerGeneral::getInstance().getReleaseScene7CountdownTime();
#endif
    ofPoint center=ofPoint(DESIGN_WIDTH-((DESIGN_WIDTH - DESIGN_LEFT_WIDTH)/2) - 35, DESIGN_HEIGHT/2);

	ofPushStyle();
    ofSetColor(ofColor::white);
    drawCenteredFont(countdownFont, ofToString(countdownTime - (int) countdown.getDiff() / 1000), center.x, center.y);
	ofPopStyle();

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