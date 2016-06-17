//
//  PMSc6Kinect_Detect.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 30/10/15.
//
//

#include "PMSc6Kinect_Detect.hpp"
#include "PMMotionExtractor.hpp"

PMSc6Kinect_Detect::PMSc6Kinect_Detect() : PMBaseScene("Scene 6")
{
    setSingleSetup(false);
}

void PMSc6Kinect_Detect::setup()
{
#if ENABLE_KINECT
    ofHideCursor();
#endif
}

void PMSc6Kinect_Detect::update()
{
#if ENABLE_KINECT
    if (PMMotionExtractor::getInstance().isTracking())
    {
        string sceneToChange = "Scene 7";
        ofNotifyEvent(goToSceneEvent, sceneToChange, this);
    }
#else
    string sceneToChange="Scene 7";
    ofNotifyEvent(goToSceneEvent, sceneToChange, this);
#endif
}

void PMSc6Kinect_Detect::draw()
{

    PMBaseScene::draw();

#if ENABLE_KINECT
	auto heightToDraw = 424 * ofGetWidth() / 512;
	PMMotionExtractor::getInstance().draw(0, (ofGetHeight() - heightToDraw) / 2, ofGetWidth(), heightToDraw);
#endif


    ofPushMatrix();
	float scaleX = (float)ofGetWidth() / (float)DESIGN_WIDTH;
    float scaleY=(float)ofGetHeight()/(float)DESIGN_HEIGHT;
    ofScale(scaleX, scaleY);
    drawCenteredFont(baseBoldFont, "Detecció de cos", DESIGN_WIDTH /2, 100);
    drawCenteredFont(baseBoldFont, "Si us plau, mira endavant i obre els braços", DESIGN_WIDTH /2, 150);
    ofPopMatrix();
    

}
