//
//  PMSc7Countdown.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 29/10/15.
//
//

#include "PMSc7Countdown.hpp"

PMSc7Countdown::PMSc7Countdown() : PMBaseScene("Scene 7")
{
//    setFadeOut(0);
}

void PMSc7Countdown::setup()
{

}

void PMSc7Countdown::updateEnter()
{
    countdown.set();
    countdown.setAlarm(5000);
    PMBaseScene::updateEnter();
}

void PMSc7Countdown::update()
{
    cout<<(int)countdown.getDiff()/1000<<endl;
    if(countdown.alarm()){
        string toScene="Scene 8";
        ofNotifyEvent(goToSceneEvent, toScene, this);
    }
}

void PMSc7Countdown::draw()
{
    drawCenteredFont(baseFont, ofToString(5-(int)countdown.getDiff()/1000), ofGetWidth()/2, ofGetHeight()/2);
}

void PMSc7Countdown::updateExit()
{
    
}