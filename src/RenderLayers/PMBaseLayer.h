//
// Created by Miquel Àngel Soler on 4/12/15.
//

#ifndef PMCANCONS_VISUALS_PMBASELAYER_H
#define PMCANCONS_VISUALS_PMBASELAYER_H

#include "ofMain.h"
#include "PMBrushesSelector.hpp"
#include "PMMotionExtractor.hpp"
#include "PMAudioAnalyzer.hpp"
#include "PMMotionExtractor.hpp"

const static unsigned int   KINECT_ACCEL_FACTOR = 20;
const static float          KINECT_ACCEL_THRESHOLD = 0.5f;
const static unsigned int   BRUSH_MIN_SIZE = 20;
const static unsigned int   BRUSH_MAX_SIZE = 50;
const static float          BRUSH_MAX_POSITION_DISTANCE = 20.0f;
const static float          BRUSH_MIN_POSITION_DISTANCE = 10;

typedef enum
{
    KINECTNODE_HEAD         = 0,
    KINECTNODE_LEFTHAND     = 1,
    KINECTNODE_RIGHTHAND    = 2,
    KINECTNODE_TORSO        = 3
} KinectNodeType;

struct ofColorHSB{
    float hue;
    float saturation;
    float brightness;
};

class PMBaseLayer
{
public:

    PMBaseLayer(int fboWidth, int fboHeight, KinectNodeType kinectNodeType);

    virtual void setup();
    virtual void update();
    virtual void draw();
    void setBrushSize(int brushSize);
    void setPosition(ofPoint pos) { brushPosition = pos; };

    // Audio listeners
    virtual void pitchChanged(pitchParams &pitchParams) {};
    virtual void energyChanged(energyParams &energyParams){};
    virtual void silenceStateChanged(silenceParams &silenceParams) {};
    virtual void pauseStateChanged(pauseParams &_auseParams) {};
    virtual void onsetDetected(onsetParams &onsetParams) {};
    virtual void shtDetected(shtParams &shtParams) {};
    virtual void melodyDirection(melodyDirectionParams &melodyDirectionParams) {};
    virtual void melBandsChanged(melBandsParams &melBandsParams) {};

protected:

    int                     layerID;
    int                     fboWidth, fboHeight;
    KinectNodeType          kinectNodeType;

    PMImageContainer        *brush;

    ofColor                 brushRGBColor;
    ofColorHSB              brushHSBColor;
    float                   brushAlpha; // value between 0 and 1

    ofPoint                 brushPosition;
    ofPoint                 brushPrevPosition;
    int                     brushSize;
    ofPoint                 brushDirection;
    float                   brushSpeed;

    float                   curveSize;

    // Audio to render mappings
    float                   energyScaleFactor;

    KinectElement           kinectNodeData;
    
};


#endif //PMCANCONS_VISUALS_PMBASELAYER_H
