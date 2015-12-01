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
#include "PMColorContainer.hpp"

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
    
    PMImageContainer* getBrush(int layer){return &brushes[(indexChoosed*brushesXpalette)+layer];};
    void checkMousePassed(int x, int y);
    bool checkMousePressed(int x, int y);
    
private:
    ofImage tempImage;
    int brushesXpalette;
    vector<PMImageContainer > brushes;
    vector<PMColorContainer > rectSelector;
    int indexChoosed;
    
};

#endif /* PMBrushesSelector_hpp */
