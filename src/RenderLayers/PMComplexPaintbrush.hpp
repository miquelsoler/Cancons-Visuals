//
//  PMComplexPaintbrush.hpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 07/12/15.
//
//

#ifndef PMComplexPaintbrush_hpp
#define PMComplexPaintbrush_hpp

#include "ofMain.h"

const static int          BRUSH_FILAMENTS_NUM = 10;

struct BrushSimpleContainer{
    ofImage image;
    int size;
    ofPoint position;
    
};

class PMComplexPaintbrush
{
public:
    PMComplexPaintbrush();
    ~PMComplexPaintbrush(){};
    
    void setup(ofImage image, int size, ofPoint initialPos);
    void update();
    void draw();
    
    vector<BrushSimpleContainer> brushes;
    ofPoint                         birthLine; //Where all brushes are painted;
    ofPoint                         position;
    
};

#endif /* PMComplexPaintbrush_hpp */
