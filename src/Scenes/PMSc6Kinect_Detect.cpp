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
	backgroundImage.load("assets/PUBLIC_02.png");
}

void PMSc6Kinect_Detect::setup()
{
#if ENABLE_KINECT
    ofHideCursor();
#endif
	alarmIsSet = false;
	countdown.set();
	countdown.setAlarm(40000);
}

void PMSc6Kinect_Detect::update()
{
#if ENABLE_KINECT
    if (PMMotionExtractor::getInstance().isTracking() && !alarmIsSet)
    {
        //string sceneToChange = "Scene 7";
        //ofNotifyEvent(goToSceneEvent, sceneToChange, this);
		countdown.set();
		countdown.setAlarm(2000);
		alarmIsSet = true;
    }

	if (countdown.alarm()) {
		countdown.resetAlarm();
		string toScene = "Scene 7";
		ofNotifyEvent(goToSceneEvent, toScene, this);
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

    //PMBaseScene::draw();
	ofPushStyle();
	ofSetColor(255, 255, 255, 255);
	backgroundImage.draw(0, 0);
	ofPopStyle();

#if ENABLE_KINECT
	//auto heightToDraw = 424 * ofGetWidth() / 512;
	//PMMotionExtractor::getInstance().draw(0, (ofGetHeight() - heightToDraw) / 2, ofGetWidth(), heightToDraw);
	auto heightToDraw = DESIGN_HEIGHT / 2;
	auto widthToDraw = DESIGN_WIDTH / 2;
	PMMotionExtractor::getInstance().draw(widthToDraw/2, heightToDraw/2, widthToDraw, heightToDraw, false, true);
	//ofSetColor(255);
	//ofDrawRectangle(widthToDraw/2, heightToDraw/2, widthToDraw, heightToDraw);
#endif

	ofPopMatrix();
}
