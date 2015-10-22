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
    kinectNI.setRegister(false);
    kinectNI.setMirror(true);
    kinectNI.addUserGenerator();
    kinectNI.setMaxNumUsers(1);
    kinectNI.setSkeletonProfile(XN_SKEL_PROFILE_ALL);
    //kinectNI.addHandsGenerator();
    //kinectNI.addUserGenerator();
    //kinectNI.addAllHandFocusGestures();
    //kinectNI.setMaxNumHands(2);
    kinectNI.start();
    
    //ofSetWindowShape(640, 480);
    
    font.loadFont("verdana.ttf", 18);
    
    //ofAddListener(kinectNI.userEvent, this, &ofApp::userEvent);
}

///--------------------------------------------------------------
void PMMotionExtractor::update()
{
    kinectNI.update();
    for (int i = 0; i < kinectNI.getNumTrackedUsers(); i++) {
        ofxOpenNIUser user = kinectNI.getTrackedUser(i);
        //The following "if" statement is a hard-coded alternative for if(kinectNI.getUserGenerator().IsNewDataAvailable()), which doesn't work properly in ofxOpenNI
        if (user.getJoint((Joint)0).getWorldPosition() != ofPoint(0,0,0) &&
            user.getJoint((Joint)0).getWorldPosition() != kinectFeatures.getPosition(0) ) {
            map<int, ofPoint> joints;
            for (int j = 0; j < user.getNumJoints(); j++) {
                joints[j] = user.getJoint((Joint)j).getWorldPosition();
            }
            kinectFeatures.update(joints);
        }
    }
    
    //This is a trick to reset the user generator if all users are lost
    if (kinectNI.getNumTrackedUsers()) {
        hadUsers = true;
    } else if (!kinectNI.getNumTrackedUsers() && hadUsers){
        hadUsers = false;
        kinectNI.setPaused(true);
        kinectNI.removeUserGenerator();
        kinectNI.addUserGenerator();
        kinectNI.setPaused(false);
    }
    
    //wraper to kinectInfo struct
}

///--------------------------------------------------------------
void PMMotionExtractor::draw()
{
    kinectNI.drawImage();
    cout<<kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_LEFT_HAND)).x/kinectNI.getWidth() << endl;
    //prova
    ofDrawEllipse(kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_LEFT_HAND)).x, kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_LEFT_HAND)).y, 20, 20);
    ofDrawEllipse(kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_RIGHT_HAND)).x, kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_RIGHT_HAND)).y, 20, 20);
    ofDrawEllipse(kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_HEAD)).x, kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_HEAD)).y, 20, 20);
    ofDrawEllipse(kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_TORSO)).x, kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_TORSO)).y, 20, 20);
    font.drawString(ofToString(kinectFeatures.getAcceleration(JOINT_RIGHT_HAND).y), kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_LEFT_HAND)).x, kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_LEFT_HAND)).y);
    
}

///--------------------------------------------------------------
void PMMotionExtractor::exit()
{
    kinectNI.stop();
}