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

struct ofColorHSB{
    float hue;
    float saturation;
    float brightness;
};

class PMBaseLayer
{
public:

    PMBaseLayer(int _fboWidth, int _fboHeight);

    virtual void setup();//ofPoint position=ofPoint(0,0), int size=10, float alpha=1, float angle=0);
    virtual void update();
    virtual void draw();
    void setBrushSize(int brushSize);
    void setPosition(ofPoint pos){position=pos;};
    void setAngle(float _angle){angle=_angle;}
    
    
    //Audio listeners
    virtual void pitchChanged(pitchParams &pitchParams){};
    virtual void energyChanged(energyParams &energyParams){};
    virtual void silenceStateChanged(silenceParams &silenceParams){};
    virtual void pauseStateChanged(pauseParams &_auseParams){};
    virtual void onsetDetected(onsetParams &onsetParams){};
    virtual void shtDetected(shtParams &shtParams){};
    virtual void melodyDirection(melodyDirectionParams &melodyDirectionParams){};
    virtual void melBandsChanged(melBandsParams &melBandsParams){};

protected:

    int                     layerID;
    int                     fboWidth, fboHeight;
    PMImageContainer        *brush;
    ofColor                 drawColor;
    ofColorHSB              hsbColor;
    
    ofPoint                 position;
    int                     brushSize; //size of brush
    float                   alpha; //value between 0 and 1
    float                   angle; //in radians
    KinectElement           kinectNodeData;
    
};


#endif //PMCANCONS_VISUALS_PMBASELAYER_H
