//
//  PMSc2Main.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#include "PMSc2Main.hpp"

void PMSc2Main::update()
{
    PMMotionExtractor::getInstance().update();
}

void PMSc2Main::draw()
{
//    cout << "PMSc2Main::draw()" << endl;
    //motionExtractor->draw();
    //KinectInfo* kinectOut=motionExtractor->getKinectInfo();
    PMMotionExtractor::getInstance().draw();
    KinectInfo* kinectOut=PMMotionExtractor::getInstance().getKinectInfo();
    ofDrawEllipse(kinectOut->leftHand_joint.x*ofGetWidth(), kinectOut->leftHand_joint.y*ofGetHeight(), 10+5*kinectOut->leftHand_joint.a, 10+5*kinectOut->leftHand_joint.a);
    ofDrawEllipse(kinectOut->rightHand_joint.x*ofGetWidth(), kinectOut->rightHand_joint.y*ofGetHeight(), 10+5*kinectOut->rightHand_joint.a, 10+5*kinectOut->rightHand_joint.a);
    ofDrawEllipse(kinectOut->head_joint.x*ofGetWidth(), kinectOut->head_joint.y*ofGetHeight(), 10+7*kinectOut->head_joint.a, 10+7*kinectOut->head_joint.a);
    ofDrawEllipse(kinectOut->torso_joint.x*ofGetWidth(), kinectOut->torso_joint.y*ofGetHeight(), 10+10*kinectOut->torso_joint.a, 10+10*kinectOut->torso_joint.a);
}