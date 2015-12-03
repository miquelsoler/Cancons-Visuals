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

class PMBaseRenderer
{
public:
    PMBaseRenderer(int layer);
    
    virtual void        setup();
    virtual void        update();
    virtual void        draw();
//    virtual void        clear();
    
    virtual void        drawIntoFBO() = 0;
    

    
    ofFbo*              getFbo(){return &fbo;};
    int                 getLayer(){return layer;};
    
    void                showGUI(bool show);
    
    // changed ...
//    virtual void        pitchChanged(pitchParams pitchParams);
//    virtual void        energyChanged(energyParams energyParams);
//    virtual void        silenceStateChanged(silenceParams &silenceParams);
//    virtual void        pauseStateChanged(pauseParams &pauseParams);
    
protected:
    int                 layer;
    ofFbo               fbo;
    
    PMImageContainer    *brush;
    ofColor             drawColor;
    
};

#endif /* PMBaseRenderer_hpp */


