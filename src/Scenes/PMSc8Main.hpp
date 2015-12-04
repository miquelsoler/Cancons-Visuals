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
#include "PMRendererLayer.hpp"
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
    
    ofSoundPlayer  song;
    bool    songIsStarted;
    vector<PMRendererLayer> renderers;
    
    PMUICanvasAudioAnalyzer* guiAudioAnalyzer;
    bool                    guiAudioAnalyzerCreated;
    
    PMMotionExtractor* motionExtractor;
    KinectInfo* kinectInfo;

    bool showGUI;
};