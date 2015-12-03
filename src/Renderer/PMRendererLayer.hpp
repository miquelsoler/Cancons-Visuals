//
//  PMRendererLayer.hpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 30/11/15.
//
//

#ifndef PMRendererLayer_hpp
#define PMRendererLayer_hpp

#include "ofMain.h"
#include "PMBaseRenderer.hpp"

class PMRendererLayer: public PMBaseRenderer
{
public:
    PMRendererLayer(int layer);
    ~PMRendererLayer(){};
    
    void setup();
    void update();
    void draw();
    
    void drawIntoFBO();
    
    void                setPosition(ofPoint newPos);
    ofPoint             getPosition(){return position;};
    
private:
    float size;
    ofPoint position;
};

#endif /* PMRendererLayer_hpp */
