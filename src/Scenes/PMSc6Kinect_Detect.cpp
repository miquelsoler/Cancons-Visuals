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

}

void PMSc6Kinect_Detect::setup()
{

}

void PMSc6Kinect_Detect::update()
{
#if ENABLE_KINECT
    PMMotionExtractor::getInstance().update();
    if (PMMotionExtractor::getInstance().isReady())
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
#if ENABLE_KINECT
    PMMotionExtractor::getInstance().draw();
#endif
}
