//
//  PMMotionExtractor.hpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 16/10/15.
//
//

#ifndef PMMotionExtractor_hpp
#define PMMotionExtractor_hpp

#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "ofxKinectFeatures.h"
#include "ofxOpenNI.h"

#define MAX_DEVICES 1

struct kinectElement{
    float x;
    float y;
    float z;
    float a;
};
struct kinectInfo{
    kinectElement leftHand_joint;
    kinectElement rightHand_joint;
    kinectElement head_joint;
    kinectElement torso_joint;
};

class PMMotionExtractor
{
public:
    /**
     * getInstance()
     * Returns singleton instance
     */
//    static PMMotionExtractor &getInstance()
//    {
//        static PMMotionExtractor instance;
//        return instance;
//    }
    
    PMMotionExtractor() {};
    ~PMMotionExtractor() {};
    void setup();
    void update();
    void draw(); //noexistirà?
    void exit();
    kinectInfo kinectOut;
private:
    ofTrueTypeFont font;
    ofxKinectFeatures kinectFeatures;
    ofxOpenNI kinectNI;
    bool hadUsers;
    
    
    ofEvent<kinectInfo> eventKinectInfo;
};

#endif /* PMMotionExtractor_hpp */