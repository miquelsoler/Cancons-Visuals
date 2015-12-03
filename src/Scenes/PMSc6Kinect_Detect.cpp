//
//  PMSc6Kinect_Detect.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 30/10/15.
//
//

#include "PMSc6Kinect_Detect.hpp"
#include "PMMotionExtractor.hpp"

PMSc6Kinect_Detect::PMSc6Kinect_Detect() :PMBaseScene("Scene 6")
{
    
}

void PMSc6Kinect_Detect::setup()
{
    
}

void PMSc6Kinect_Detect::update()
{
    PMMotionExtractor::getInstance().update();
    if(PMMotionExtractor::getInstance().isReady()){
        string sceneToChange="Scene 7";
        ofNotifyEvent(goToSceneEvent, sceneToChange, this);
    }
}

void PMSc6Kinect_Detect::draw()
{
    PMMotionExtractor::getInstance().draw();
}
