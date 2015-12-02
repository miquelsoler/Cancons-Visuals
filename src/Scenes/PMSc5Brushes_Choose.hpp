//
//  PMSc5Brushes_Choose.hpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 29/10/15.
//
//

#ifndef PMSc5Brushes_Choose_hpp
#define PMSc5Brushes_Choose_hpp

#include <stdio.h>
#include "PMBaseScene.hpp"

#endif /* PMSc5Brushes_Choose_hpp */

class PMSc5Brushes_Choose : public PMBaseScene
{
public:
    
    PMSc5Brushes_Choose();
    
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
    
};

    