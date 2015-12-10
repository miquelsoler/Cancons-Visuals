//
//  PMSc7Countdown.hpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 29/10/15.
//
//

#ifndef PMSc7Countdown_hpp
#define PMSc7Countdown_hpp

#include <stdio.h>
#include "PMBaseScene.hpp"

#endif /* PMSc7Countdown_hpp */

class PMSc7Countdown : public PMBaseScene
{
public:
    
    PMSc7Countdown();
    
    void setup();
    void update();
    void draw();
    void exit();
    void updateEnter();
    void updateExit();


private:
    ofTrueTypeFont countdownFont;
    ofxTimer countdown;
    ofPoint line;
    
};