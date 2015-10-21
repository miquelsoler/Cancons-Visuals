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


class PMMotionExtractor
{
public:
    PMMotionExtractor() {};
    ~PMMotionExtractor() {};
    void setup();
    void update();
    void draw(); //noexistirà?
    void exit();
    
private:
    ofxKinectFeatures kinectFeatures;
    ofxOpenNI kinectNI;
    
};

#endif /* PMMotionExtractor_hpp */