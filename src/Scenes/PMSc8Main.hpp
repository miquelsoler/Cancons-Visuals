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
//#include "PMBaseRenderer.hpp"
//#include "PMRendererLayer1.hpp"
#include "PMRenderer.h"
#include "PMLayer1.h"
#include "PMUICanvasAudioAnalyzer.h"

#endif /* PMSc8Main_hpp */

class PMSc8Main : public PMBaseScene
{
public:

    PMSc8Main();

    void setup();
    void update();
    void draw();
    void exit(){};
    void updateEnter();
    void updateExit();
    
    void loadSong(string filename);
    void playSong();
    
    //AUdio
    void pitchChanged(pitchParams &pitchParams);
    void energyChanged(energyParams &energyParams);
//    void silenceStateChanged(silenceParams &silenceParams);
//    void pauseStateChanged(pauseParams &pauseParams);
//    void onsetDetected(onsetParams &onsetParams);
//    void shtDetected(shtParams &shtParams);
//    void melodyDirection(melodyDirectionParams &melodyDirectionParams);

    void keyReleased(int key);


protected:

private:
    
    PMRenderer *renderer;
//    vector<PMBaseRenderer *> renderers;
    
    PMUICanvasAudioAnalyzer* guiAudioAnalyzer;
    bool                    guiAudioAnalyzerCreated;
    
    PMMotionExtractor* motionExtractor;
    KinectInfo* kinectInfo;

    ofSoundPlayer  song;
    bool    songIsStarted;

    bool showGUI;
};