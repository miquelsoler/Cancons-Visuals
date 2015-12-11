//
//  PMSc10Thanks.hpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 30/10/15.
//
//

#ifndef PMSc10Thanks_hpp
#define PMSc10Thanks_hpp

#include "PMBaseScene.hpp"

#endif /* PMSc10Thanks_hpp */

class PMSc10Thanks : public PMBaseScene
{
public:
    
    PMSc10Thanks();
    
    void setup();
    void update();
    void draw();
    void exit(){};
    void updateEnter() { PMBaseScene::updateEnter(); };
    void updateExit() { PMBaseScene::updateExit(); };
    
    void drawIntoFbo();

    
private:
    
    ofImage         plantilla;
    ofTrueTypeFont  bigFont, smallFont;
    int             originalWidth, originalHeight;
    
    ofFbo           printFbo;
    ofImage         print_testImage;
    
};