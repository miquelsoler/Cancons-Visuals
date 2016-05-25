//
//  PMSc8Main.hpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#ifndef PMSc8Main_hpp
#define PMSc8Main_hpp

#include "PMBaseScene.hpp"
#include "../motion/PMMotionExtractor.hpp"
#include "../RenderLayers/PMRenderer.h"
//#include "PMUICanvasAudioAnalyzer.h"

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
    
	void computeFFT();
    void loadSong(string filename);
    void playSong();

    void keyReleased(int key);
    void keyPressed(ofKeyEventArgs &keyargs){
        if(keyargs.keycode==291){
            motionExtractor->resetUsers();
            renderer->resetPositions();
        }
    }


private:
    
    PMRenderer *renderer;
    
    PMMotionExtractor* motionExtractor;
    KinectInfo* kinectInfo;

    ofSoundPlayer   song;
    bool            songIsStarted;
    bool            songIsPlaying;

	float			*fftSmoothed;
	vector<float> 	melBands;
	int				nBandsToGet;
	int				nMelBands;

    bool            enteredScene;
    bool            disablePainting;

    bool            showGUI;
    
    float           timeBeginSong;

    void exportImageAndLeaveScene();
};