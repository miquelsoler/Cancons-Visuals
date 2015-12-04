//
//  PMBaseRenderer.hpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 30/11/15.
//
//

#ifndef PMBaseRenderer_hpp
#define PMBaseRenderer_hpp

#include "ofMain.h"
#include "PMAudioAnalyzer.hpp"

#include "PMBrushesSelector.hpp"
#include "PMImageContainer.hpp"
#include "PMColorsSelector.hpp"
#include "PMColorContainer.hpp"
#include "PMUICanvasBrushRenderer.h"

class PMBaseRenderer
{
public:
    PMBaseRenderer(int layer);
    
    virtual void        setup();
    virtual void        update();
    virtual void        draw();
//    virtual void        clear();
    
    virtual void        drawIntoFBO() = 0;

    void                setPosition(ofPoint newPos);
    ofPoint             getPosition() { return position; };
    void                addOffset(float offsetFactor);

    int                 getSize() { return size; };

    void setNodeReference(ofPoint nodePos);


    ofFbo*              getFbo(){return &fbo;};
    int                 getLayer(){return layer;};
    
    void                showGUI(bool show);


    // changed ...
//    virtual void        pitchChanged(pitchParams pitchParams);
//    virtual void        energyChanged(energyParams energyParams);
//    virtual void        silenceStateChanged(silenceParams &silenceParams);
//    virtual void        pauseStateChanged(pauseParams &pauseParams);
    
protected:

    int                     layer;
    ofFbo                   fbo;
    
    PMImageContainer        *brush;
    ofColor                 drawColor;
    
    PMUICanvasBrushRenderer* gui;

    // TODO: Check which ones we really need for base renderer. Remove/move those who aren't shared.
    int size;
    ofPoint position;
    ofPoint direction;
    float hue, saturation, brightness;
};

#endif /* PMBaseRenderer_hpp */


