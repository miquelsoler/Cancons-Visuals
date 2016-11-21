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
    setFade(0, 0);
//    setFadeIn(1000);
    backgroundImage.load("assets/01.png");
    setSingleSetup(false);
}

void PMSc2Start::setup()
{
    ofHideCursor();
}

void PMSc2Start::update()
{
    
}

void PMSc2Start::draw()
{
	ofPushMatrix();
	ofMultMatrix(*homography);

    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(255);
    backgroundImage.draw(0,0, DESIGN_WIDTH, DESIGN_HEIGHT);
    ofPopStyle();

	ofPopStyle();
}

void PMSc2Start::keyPressed(int key)
{
	string sceneToChange = "Scene 3";
	if (key == ' ')
        ofNotifyEvent(goToSceneEvent, sceneToChange, this);
	if (key == 'f')
		ofToggleFullscreen();
}
