//
//  PMRendererLayer1.hpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 30/11/15.
//
//

#ifndef PMRendererLayer1_hpp
#define PMRendererLayer1_hpp

#include "ofMain.h"
#include "PMBaseRenderer.hpp"

class PMRendererLayer1: public PMBaseRenderer
{
public:
    PMRendererLayer1(int layer);
    ~PMRendererLayer1(){};
    
    void setup();
    void update();
    void draw();
    
    void drawIntoFBO();
    
private:

};

#endif /* PMRendererLayer1_hpp */
