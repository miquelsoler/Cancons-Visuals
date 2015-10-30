//
//  PMSc6Main.hpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#ifndef PMSc6Main_hpp
#define PMSc6Main_hpp

#include <stdio.h>
#include "ofxScene.h"
#include "PMMotionExtractor.hpp"

#endif /* PMSc6Main_hpp */

class PMSc6Main : public PMBaseScene
{
public:

    PMSc6Main() {};

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