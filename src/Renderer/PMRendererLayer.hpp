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
};

#endif /* PMRendererLayer_hpp */
