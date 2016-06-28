//
//  PMSc4Palette_Choose.hpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 29/10/15.
//
//

#ifndef PMSc4Palette_Choose_hpp
#define PMSc4Palette_Choose_hpp


#include "PMBaseScene.hpp"

#endif /* PMSc4Palette_Choose_hpp */

class PMSc4Palette_Choose : public PMBaseScene
{
public:
    
    PMSc4Palette_Choose();
    
    void setup();
    void update();
    void draw();
    void exit(){};
    void updateEnter(){PMBaseScene::updateEnter();};
    void updateExit(){PMBaseScene::updateExit();};

    void mouseMoved(int x, int y);
    void mousePressed(int x, int y, int button);
    
protected:
    
private:
    ofTrueTypeFont infoFont;

    
};