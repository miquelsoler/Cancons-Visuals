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
    kinectNI.setup();
    kinectNI.addDepthGenerator();
    kinectNI.addImageGenerator();
    kinectNI.setRegister(true);
    kinectNI.setMirror(true);
    //kinectNI.addUserGenerator();
    kinectNI.setMaxNumUsers(1);
    kinectNI.setSkeletonProfile(XN_SKEL_PROFILE_ALL);
    kinectNI.addHandsGenerator();
    kinectNI.addUserGenerator();
    kinectNI.addAllHandFocusGestures();
    kinectNI.setMaxNumHands(2);
    kinectNI.start();
    
}

///--------------------------------------------------------------
void PMMotionExtractor::update()
{
    kinectNI.update();
//    int numHands = kinectNI.getNumTrackedHands();
//    
//    // iterate through users
//    for (int i = 0; i < numHands; i++){
//        
//        // get a reference to this user
//        ofxOpenNIHand & hand = kinectNI.getTrackedHand(i);
//        
//        // get hand position
//        ofPoint & handPosition = hand.getPosition();
//        // do something with the positions like:
//        
//        // draw a rect at the position (don't confuse this with the debug draw which shows circles!!)
//        ofSetColor(255,0,0);
//        ofRect(handPosition.x, handPosition.y, 10, 10);
//    }
}

///--------------------------------------------------------------
void PMMotionExtractor::draw()
{
    kinectNI.drawImage();
    int numHands = kinectNI.getNumTrackedHands();
    
    // iterate through hands
    for (int i = 0; i < numHands; i++){
        
        // get a reference to this user
        ofxOpenNIHand & hand = kinectNI.getTrackedHand(i);
        
        // get hand position
        ofPoint & handPosition = hand.getPosition();
        // do something with the positions like:
        
        // draw a rect at the position (don't confuse this with the debug draw which shows circles!!)
        ofSetColor(255,0,0);
        ofDrawEllipse(handPosition.x, handPosition.y, 20, 20);
    }
}

///--------------------------------------------------------------
void PMMotionExtractor::exit()
{
    kinectNI.stop();
}