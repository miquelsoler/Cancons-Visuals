//
//  PMMotionExtractor.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 16/10/15.
//
//

#include "PMMotionExtractor.hpp"


///--------------------------------------------------------------
void PMMotionExtractor::setup()
{
    //kinectNI fist test
    
    kinectNI.setup();
    kinectNI.addDepthGenerator();
    kinectNI.addImageGenerator();
    kinectNI.setRegister(false);
    kinectNI.setMirror(true);
    kinectNI.addUserGenerator();
    kinectNI.setMaxNumUsers(3);
    kinectNI.setSkeletonProfile(XN_SKEL_PROFILE_ALL);
    kinectNI.start();
}

///--------------------------------------------------------------
void PMMotionExtractor::update()
{
    //kinectNI
    
    kinectNI.update();
}

///--------------------------------------------------------------
void PMMotionExtractor::draw()
{
    //inect
    
    kinectNI.drawDebug();
}

///--------------------------------------------------------------
void PMMotionExtractor::exit()
{
    kinectNI.stop();
}