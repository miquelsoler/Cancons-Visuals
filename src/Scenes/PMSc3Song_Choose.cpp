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
}

void PMSc3Song_Choose::setup()
{
 
    selectFont.load("fonts/NeutraTextTF-Book.otf", 40);
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
    ofBackground(0);
    drawSettingsNumbers(1);
    PMSongSelector::getInstance().draw();
}

void PMSc3Song_Choose::mouseMoved(int x, int y)
{

    PMSongSelector::getInstance().checkMousePassed(x, y);
}

void PMSc3Song_Choose::mousePressed(int x, int y, int button)
{
    if(PMSongSelector::getInstance().checkMousePressed(x, y)){
        string sceneToChange="Scene 4";
        ofNotifyEvent(goToSceneEvent, sceneToChange, this);
    }
}