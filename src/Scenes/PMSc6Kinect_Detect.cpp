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
	backgroundImage.load("assets/04_plantilla.png");
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
	ofPushMatrix();
	ofMultMatrix(*homography);

    //PMBaseScene::draw();ç
	ofPushStyle();
	ofSetColor(255, 255, 255, 255);
	backgroundImage.draw(0, 0);
	ofPopStyle();

#if ENABLE_KINECT
	//auto heightToDraw = 424 * ofGetWidth() / 512;
	//PMMotionExtractor::getInstance().draw(0, (ofGetHeight() - heightToDraw) / 2, ofGetWidth(), heightToDraw);
	auto heightToDraw = 424 * (DESIGN_WIDTH-DESIGN_LEFT_WIDTH-350) / 512;
	//PMMotionExtractor::getInstance().draw( (ofGetHeight() - heightToDraw) / 2, DESIGN_LEFT_HEIGHT - 25, DESIGN_WIDTH - DESIGN_LEFT_WIDTH - 50, heightToDraw);
	//ofSetColor(255);
	//ofDrawRectangle(1050, 230, DESIGN_WIDTH - DESIGN_LEFT_WIDTH - 350, heightToDraw);
#endif

	ofPopMatrix();
}
