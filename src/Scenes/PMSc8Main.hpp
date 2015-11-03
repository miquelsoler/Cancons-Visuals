//
//  PMSc8Main.hpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#ifndef PMSc8Main_hpp
#define PMSc8Main_hpp

#include <stdio.h>
#include "PMBaseScene.hpp"
#include "PMMotionExtractor.hpp"

#endif /* PMSc8Main_hpp */

class PMSc8Main : public PMBaseScene
{
public:

    PMSc8Main() {};

    void setup();
    void update();
    void draw();
    
    void loadSong(string filename);
    void playSong();
    
    void willExit() {};

protected:

private:
    
    ofSoundPlayer  song;
    bool    songIsStarted;

};