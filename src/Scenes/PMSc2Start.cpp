//
//  PMSc2Start.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 30/10/15.
//
//

#include "PMSc2Start.hpp"

PMSc2Start::PMSc2Start() : PMBaseScene("Scene 2")
{
    //setFade(1000, 1000);
//    setFadeIn(1000);
    backgroundImage.load("assets/escena2.jpg");
}

void PMSc2Start::setup()
{
    
}

void PMSc2Start::update()
{
    
}

void PMSc2Start::draw()
{
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(255);
    backgroundImage.draw(0,0, ofGetWidth(), ofGetHeight());
    ofPopStyle();
}

void PMSc2Start::keyPressed(int key)
{
    string sceneToChange = "Scene 3";
    if(key == ' ')
        ofNotifyEvent(goToSceneEvent, sceneToChange, this);
}
