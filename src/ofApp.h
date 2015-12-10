#pragma once


#include "ofMain.h"
#include "PMAudioAnalyzer.hpp"
#include "PMMotionExtractor.hpp"
#include "ofxAppUtils.h"
#include "ofxOpenNI.h"
#include "ofxKinectFeatures.h"


#include "PMSc1Settings.hpp"
#include "PMSc2Start.hpp"
#include "PMSc3Song_Choose.hpp"
#include "PMSc4Palette_Choose.hpp"
#include "PMSc5Brushes_Choose.hpp"
#include "PMSc6Kinect_Detect.hpp"
#include "PMSc7Countdown.hpp"
#include "PMSc8Main.hpp"
#include "PMSc9Export.hpp"

class ofApp : public ofxApp
{
public:

    void setup();

    void update();

    void draw();

    void exit();

//    void keyPressed(int key);
    void keyReleased(int key);

//    void mouseMoved(int x, int y );
//    void mouseDragged(int x, int y, int button);
//    void mousePressed(int x, int y, int button);
//    void mouseReleased(int x, int y, int button);
//    void mouseEntered(int x, int y);
//    void mouseExited(int x, int y);
//    void windowResized(int w, int h);
//    void dragEvent(ofDragInfo dragInfo);
//    void gotMessage(ofMessage msg);
    void changeScene(string &scene);

private:

    PMDeviceAudioAnalyzer *audioAnalyzer;

    bool showFPS;
    bool isFullScreen;

    ofxSceneManager sceneManager;
    unsigned int currentScene;
    string currentSceneName;

    PMSc1Settings           *scene1;
    PMSc2Start              *scene2;
    PMSc3Song_Choose        *scene3;
    PMSc4Palette_Choose     *scene4;
    PMSc5Brushes_Choose     *scene5;
    PMSc6Kinect_Detect      *scene6;
    PMSc7Countdown          *scene7;
    PMSc8Main               *scene8;
    PMSc9Export             *scene9;
};
