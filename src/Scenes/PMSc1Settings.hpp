//
//  PMSc1Settings.hpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#ifndef PMSc1Settings_hpp
#define PMSc1Settings_hpp

#include "PMBaseScene.hpp"

#include "ofxUI.h"

#endif /* PMSc1Settings_hpp */

class PMSc1Settings : public PMBaseScene
{
public:

    PMSc1Settings();
    ~PMSc1Settings(){};

    void setup();
    void update();
    void draw();
    void exit(){};
    void updateEnter(){PMBaseScene::updateEnter();};
    void updateExit(){PMBaseScene::updateExit();};
    
//    void setupGUI_SONG();

private:

    ofxUISuperCanvas *gui_song;
    ofxUIDropDownList *ddl;

    //int findSoundflowerDeviceIndex();
};