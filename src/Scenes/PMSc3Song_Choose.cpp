//
//  PMSc3Song_Choose.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 29/10/15.
//
//

#include "PMSc3Song_Choose.hpp"
#include "../UI/PMSongSelector.hpp"

PMSc3Song_Choose::PMSc3Song_Choose() : PMBaseScene("Scene 3")
{
    //setFade(1000, 1000);
//    setFadeIn(1000);
    selectFont.load("fonts/NeutraTextTF-Book.otf", 35);
    PMSongSelector::getInstance().init(selectFont);
    setSingleSetup(false);
#if ENABLE_LIVE
	backgroundImage.load("assets/LIVE_02.png");
#else
	backgroundImage.load("assets/PUBLIC_01.png");
#endif
}

void PMSc3Song_Choose::setup()
{
    PMSongSelector::getInstance().resetSize();
    ofShowCursor();
}

void PMSc3Song_Choose::update()
{
    if(!isEntering()){
        PMSongSelector::getInstance().update();
    }
}

void PMSc3Song_Choose::draw()
{
	ofPushMatrix();
	ofMultMatrix(*homography);

	backgroundImage.draw(0, 0, DESIGN_WIDTH, DESIGN_HEIGHT);
    //PMBaseScene::draw();
//    ofBackground(0);
    //drawSettingsNumbers(1);
    //drawCenteredFont(baseBoldFont, "Tria la teva cançó", DESIGN_LEFT_WIDTH/2, 150);
    PMSongSelector::getInstance().draw();   

	ofPopMatrix();
}

void PMSc3Song_Choose::mouseMoved(int x, int y)
{
   //Warp via homography;
	ofVec3f pos = ofVec3f(x, y);
	pos = pos*(homography->getInverse());

    PMSongSelector::getInstance().checkMousePassed(pos.x, pos.y);
}

void PMSc3Song_Choose::mousePressed(int x, int y, int button)
{
	//Warp via homography;
	ofVec3f pos = ofVec3f(x, y);
	pos = pos*(homography->getInverse());

    if(PMSongSelector::getInstance().checkMousePressed(pos.x, pos.y)){
        string sceneToChange="Scene 4";
        ofNotifyEvent(goToSceneEvent, sceneToChange, this);
    }
}