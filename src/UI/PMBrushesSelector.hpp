//
//  PMBrushesSelector.hpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 02/11/15.
//
//

#ifndef PMBrushesSelector_hpp
#define PMBrushesSelector_hpp


#include <stdio.h>
#include "ofMain.h"
#include "PMImageContainer.hpp"

class PMBrushesSelector
{
public:
    
    static PMBrushesSelector &getInstance()
    {
        static PMBrushesSelector instance;
        return instance;
    }

    
    void init();
    void update();
    void draw();
    
    void getBrush(){};
    
private:
    ofImage tempImage;
    //vector<ofImage > brushes;
    int brushesXpalette;
    vector<PMImageContainer > brushes;
    
};

#endif /* PMBrushesSelector_hpp */
