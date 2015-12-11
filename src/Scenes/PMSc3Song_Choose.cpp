//
//  PMSc3Song_Choose.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 29/10/15.
//
//

#include "PMSc3Song_Choose.hpp"
#include "PMSongSelector.hpp"

PMSc3Song_Choose::PMSc3Song_Choose() : PMBaseScene("Scene 3")
{
    //setFade(1000, 1000);
//    setFadeIn(1000);
    selectFont.load("fonts/NeutraTextTF-Book.otf", 43);
}

void PMSc3Song_Choose::setup()
{
    PMSongSelector::getInstance().init(selectFont);
}

void PMSc3Song_Choose::update()
{
    if(!isEntering()){
        PMSongSelector::getInstance().update();
    }
}

void PMSc3Song_Choose::draw()
{
    PMBaseScene::draw();
    ofPushMatrix();
    float scaleX=(float)ofGetWidth()/(float)1080;
    float scaleY=(float)ofGetHeight()/(float)1920;
    ofScale(scaleX, scaleY);
//    ofBackground(0);
    drawSettingsNumbers(1);
    drawCenteredFont(baseBoldFont, "Tria la teva cançó", 1080/2, 200);
    PMSongSelector::getInstance().draw();
    ofPopMatrix();
}

void PMSc3Song_Choose::mouseMoved(int x, int y)
{
    float scaleX=(float)ofGetWidth()/(float)1080;
    float scaleY=(float)ofGetHeight()/(float)1920;
    x/=scaleX;
    y/=scaleY;
    PMSongSelector::getInstance().checkMousePassed(x, y);
}

void PMSc3Song_Choose::mousePressed(int x, int y, int button)
{
    float scaleX=(float)ofGetWidth()/(float)1080;
    float scaleY=(float)ofGetHeight()/(float)1920;
    x/=scaleX;
    y/=scaleY;
    if(PMSongSelector::getInstance().checkMousePressed(x, y)){
        string sceneToChange="Scene 4";
        ofNotifyEvent(goToSceneEvent, sceneToChange, this);
    }
}