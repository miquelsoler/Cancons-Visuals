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
#include "PMRenderer.h"
#include "PMUICanvasAudioAnalyzer.h"

#endif /* PMSc8Main_hpp */

class PMSc8Main : public PMBaseScene
{
public:

    PMSc8Main();

    void setup();
    void update();
    void draw();
    void exit();
    void updateEnter();
    void updateExit();
    
    void loadSong(string filename);
    void playSong();

    void keyReleased(int key);

private:
    
    PMRenderer *renderer;
//    vector<PMBaseRenderer *> renderers;
    
    PMUICanvasAudioAnalyzer* guiAudioAnalyzer;
    bool                    guiAudioAnalyzerCreated;
    
    PMMotionExtractor* motionExtractor;
    KinectInfo* kinectInfo;

    ofSoundPlayer   song;
    bool            songIsStarted;
    bool            songIsPlaying;

    bool            enteredScene;

    bool showGUI;
    
    float           timeBeginSong;
};