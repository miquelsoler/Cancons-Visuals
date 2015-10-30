//
//  PMSc1Settings.hpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#ifndef PMSc1Settings_hpp
#define PMSc1Settings_hpp

#include <stdio.h>
#include "ofxScene.h"
#include "ofxUI.h"

#endif /* PMSc1Settings_hpp */

class PMSc1Settings : public PMBaseScene
{
public:

    PMSc1Settings() {};

    void setup();
    void update();
    void draw();
    void guiEvent(ofxUIEventArgs &e);
    
    void setupGUI_SONG();


protected:

private:
    ofxUISuperCanvas *gui_song;
    ofxUIDropDownList *ddl;
};