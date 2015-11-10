//
//  PMSc2Start.hpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 30/10/15.
//
//

#ifndef PMSc2Start_hpp
#define PMSc2Start_hpp

#include <stdio.h>
#include "PMBaseScene.hpp"
#include "PMTextContainer.hpp"

#endif /* PMSc2Start_hpp */

class PMSc2Start : public PMBaseScene
{
public:
    
    PMSc2Start();
    
    void setup();
    void update();
    void draw();
    void exit(){};
    void updateEnter(){ofxFadeScene::updateEnter();};
    void updateExit(){ofxFadeScene::updateExit();};
    
private:
    vector<PMTextContainer > textBoxes;
};