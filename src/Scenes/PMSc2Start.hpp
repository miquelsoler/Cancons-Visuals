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

#endif /* PMSc2Start_hpp */

class PMSc2Start : public PMBaseScene
{
public:
    
    PMSc2Start();
    
    void setup();
    void update();
    void draw();
    void exit(){};
    void updateEnter(){PMBaseScene::updateEnter();};
    void updateExit(){PMBaseScene::updateExit();};
    
    
protected:
    
private:
    
};