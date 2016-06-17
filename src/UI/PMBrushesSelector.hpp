//
//  PMBrushesSelector.hpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 02/11/15.
//
//

#ifndef PMBrushesSelector_hpp
#define PMBrushesSelector_hpp


#include "ofMain.h"
#include "Containers/PMImageContainer.hpp"
#include "Containers/PMColorContainer.hpp"
#include "Defaults.h"

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
    void setInitialState();
    
    PMImageContainer* getBrush(int layer);
    void checkMousePassed(int x, int y);
    bool checkMousePressed(int x, int y);
    
private:
    ofImage tempImage;
    int brushesXpalette;
    vector<PMImageContainer > brushes;
    vector<PMColorContainer > rectSelector;
    int selectedPaletteIndex;
    int originalWidth, originalHeight;
    
};

#endif /* PMBrushesSelector_hpp */
