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

struct KinectElement{
    float x;
    float y;
    float z;
    float a;
    ofPoint v;
};
struct KinectInfo{
    KinectElement leftHand_joint;
    KinectElement rightHand_joint;
    KinectElement head_joint;
    KinectElement torso_joint;
};

class PMMotionExtractor
{
public:
    /**
     * getInstance()
     * Returns singleton instance
     */
    static PMMotionExtractor &getInstance()
    {
        static PMMotionExtractor instance;
        return instance;
    }
    
    PMMotionExtractor() {};
    ~PMMotionExtractor() {};
    void setup();
    void update();
    void draw(); //noexistirà?
    void exit();
    KinectInfo* getKinectInfo();
    
    bool isReady(){return isSomeoneTracked;};
    bool isTracking(){return hadUsers;}
    
private:
    ofTrueTypeFont font;
    ofxKinectFeatures kinectFeatures;
    ofxOpenNI kinectNI;
    bool hadUsers;
    KinectInfo kinectOut;
//    KinectInfo oldKinectOut;
    
    bool isSomeoneTracked;
};

#endif /* PMMotionExtractor_hpp */