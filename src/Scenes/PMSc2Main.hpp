//
//  PMSc2Main.hpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#ifndef PMSc2Main_hpp
#define PMSc2Main_hpp

#include <stdio.h>
#include "ofxScene.h"
#include "PMMotionExtractor.hpp"

#endif /* PMSc2Main_hpp */

class PMSc2Main : public ofxScene
{
public:

    PMSc2Main() {};

    void setup();
    void update();
    void draw();
    
    void loadSong(string filename);
    void playSong();

protected:

private:
    
    ofSoundPlayer  song;
    bool    songIsStarted;

};