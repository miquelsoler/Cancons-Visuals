//
//  PMSc3Song_Choose.hpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 29/10/15.
//
//

#ifndef PMSc3Song_Choose_hpp
#define PMSc3Song_Choose_hpp

#include <stdio.h>
#include "PMBaseScene.hpp"

#endif /* PMSc3Song_Choose_hpp */

class PMSc3Song_Choose : public PMBaseScene
{
public:
    
    PMSc3Song_Choose();
    
    void setup();
    void update();
    void draw();
    void exit(){};
    void updateEnter(){PMBaseScene::updateEnter();};
    void updateExit(){PMBaseScene::updateExit();};

    
    void mousePressed(int x, int y, int button);
    void mouseMoved(int x, int y);
    
    
    
protected:
    
private:
    vector<string> songNames;
    int pseudoSelectedSong;
    ofTrueTypeFont selectFont;
    
    
    
};