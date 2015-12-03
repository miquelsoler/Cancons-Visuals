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
    
    isSomeoneTracked=false;
    
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
            isSomeoneTracked=true;
            map<int, ofPoint> joints;
            for (int j = 0; j < user.getNumJoints(); j++) {
                joints[j] = user.getJoint((Joint)j).getWorldPosition();
            }
            kinectFeatures.update(joints);
        }else{isSomeoneTracked=false;}
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
    int mean_values=5;
    
    //LEFT HAND
    kinectOut.leftHand_joint.x=kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_LEFT_HAND)).x/kinectNI.getWidth();
    kinectOut.leftHand_joint.y=kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_LEFT_HAND)).y/kinectNI.getHeight();
    kinectOut.leftHand_joint.z=ofMap(kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_LEFT_HAND)).z, 1000, 3000, 0, 1);
    kinectOut.leftHand_joint.a=kinectFeatures.getAccelerationMagnitudeMean(JOINT_LEFT_HAND, mean_values);
    
    //RIGHT HAND
    kinectOut.rightHand_joint.x=kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_RIGHT_HAND)).x/kinectNI.getWidth();
    kinectOut.rightHand_joint.y=kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_RIGHT_HAND)).y/kinectNI.getHeight();
    kinectOut.rightHand_joint.z=ofMap(kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_RIGHT_HAND)).z, 1000, 3000, 0, 1);
    kinectOut.rightHand_joint.a=kinectFeatures.getAccelerationMagnitudeMean(JOINT_RIGHT_HAND, mean_values);
    
    //HEAD
    kinectOut.head_joint.x=kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_HEAD)).x/kinectNI.getWidth();
    kinectOut.head_joint.y=kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_HEAD)).y/kinectNI.getHeight();
    kinectOut.head_joint.z=ofMap(kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_HEAD)).z, 1000, 3000, 0, 1);
    kinectOut.head_joint.a=kinectFeatures.getAccelerationMagnitudeMean(JOINT_HEAD, mean_values);
    
    //TORSO
    kinectOut.torso_joint.x=kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_TORSO)).x/kinectNI.getWidth();
    kinectOut.torso_joint.y=kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_TORSO)).y/kinectNI.getHeight();
    kinectOut.torso_joint.z=ofMap(kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_TORSO)).z, 1000, 3000, 0, 1);
    kinectOut.torso_joint.a=kinectFeatures.getAccelerationMagnitudeMean(JOINT_TORSO, mean_values);
}

///--------------------------------------------------------------
void PMMotionExtractor::draw()
{
    kinectNI.drawImage();
//    cout<<kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_LEFT_HAND)).z << endl;
//    //prova
//    ofDrawEllipse(kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_LEFT_HAND)).x, kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_LEFT_HAND)).y, 20, 20);
//    ofDrawEllipse(kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_RIGHT_HAND)).x, kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_RIGHT_HAND)).y, 20, 20);
//    ofDrawEllipse(kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_HEAD)).x, kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_HEAD)).y, 20, 20);
//    ofDrawEllipse(kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_TORSO)).x, kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_TORSO)).y, 20, 20);
    //font.drawString(ofToString(kinectFeatures.getAcceleration(JOINT_RIGHT_HAND).y), kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_LEFT_HAND)).x, kinectNI.worldToProjective(kinectFeatures.getPosition(JOINT_LEFT_HAND)).y);
}

///--------------------------------------------------------------
void PMMotionExtractor::exit()
{
    kinectNI.stop();
}

KinectInfo* PMMotionExtractor::getKinectInfo()
{
    return &kinectOut;
}