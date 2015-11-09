#include "ofApp.h"
#include "PMSettingsManager.h"
#include "PMSettingsManagerGeneral.hpp"
#include "Defaults.h"

#include "PMSc1Settings.hpp"
#include "PMSc2Start.hpp"
#include "PMSc3Song_Choose.hpp"
#include "PMSc4Palette_Choose.hpp"
#include "PMSc5Brushes_Choose.hpp"
#include "PMSc6Kinect_Detect.hpp"
#include "PMSc7Countdown.hpp"
#include "PMSc8Main.hpp"

///--------------------------------------------------------------
void ofApp::setup()
{
    //ofSetWindowShape(640, 480);
    //ofSetLogLevel(OF_LOG_VERBOSE);
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(ofColor::black);

    isFullScreen = (DEFAULT_WINDOW_MODE == OF_FULLSCREEN);

    currentScene = 2;

    // Settings

#ifdef OF_DEBUG
    showFPS = PMSettingsManagerGeneral::getInstance().getDebugShowFPS();
#else
    showFPS = PMSettingsManagerGeneral::getInstance().getReleaseShowFPS();
#endif

    // Scenes

    PMSc1Settings *scene1 = new PMSc1Settings();
    scene1->setSingleSetup(true);
    ofAddListener(scene1->eventChangeScene, this, &ofApp::changeScene);
    sceneManager.add(scene1);
    
    PMSc2Start *scene2 = new PMSc2Start();
    scene2->setSingleSetup(true);
    ofAddListener(scene2->eventChangeScene, this, &ofApp::changeScene);
    sceneManager.add(scene2);
    
    PMSc3Song_Choose *scene3 = new PMSc3Song_Choose();
    scene3->setSingleSetup(true);
    ofAddListener(scene3->eventChangeScene, this, &ofApp::changeScene);
    sceneManager.add(scene3);
    
    PMSc4Palette_Choose *scene4 = new PMSc4Palette_Choose();
    scene4->setSingleSetup(true);
    ofAddListener(scene4->eventChangeScene, this, &ofApp::changeScene);
    sceneManager.add(scene4);
    
    PMSc5Brushes_Choose *scene5 = new PMSc5Brushes_Choose();
    scene5->setSingleSetup(true);
    ofAddListener(scene5->eventChangeScene, this, &ofApp::changeScene);
    sceneManager.add(scene5);
    
    PMSc6Kinect_Detect *scene6 = new PMSc6Kinect_Detect();
    scene6->setSingleSetup(true);
    sceneManager.add(scene6);
    
    PMSc7Countdown *scene7 = new PMSc7Countdown();
    scene7->setSingleSetup(true);
    sceneManager.add(scene7);
    
    PMSc8Main *scene8 = new PMSc8Main();
    scene8->setSingleSetup(true);
    sceneManager.add(scene8);
    
    sceneManager.setup(true);
    sceneManager.setOverlap(false);
    ofSetLogLevel("ofxSceneManager", OF_LOG_VERBOSE); // lets see whats going on inside
    
    setSceneManager(&sceneManager);
    sceneManager.gotoScene(2, false);

    // For testing purposes

    audioAnalyzer = new PMDeviceAudioAnalyzer(0, 2, 0, 44100, 512);

    int channelNumber = 0;
    bool useMelBands = true;
    int numMelBands = 24;
    audioAnalyzer->setup(PMDAA_CHANNEL_MONO, channelNumber, useMelBands, numMelBands);
    
    
    //PMMotionExtractor::getInstance().setup();
}

///--------------------------------------------------------------
void ofApp::update()
{
#ifdef OF_DEBUG
    ofShowCursor();
#endif

    //sceneManager->update();
}

///--------------------------------------------------------------
void ofApp::draw()
{
    if (showFPS)
    {
        ofSetColor(ofColor::white);
        ofDrawBitmapString(ofToString(ofGetFrameRate()) + "fps", 15, ofGetHeight() - 15);
    }

    //sceneManager->draw();
}

///--------------------------------------------------------------
void ofApp::exit()
{
    PMMotionExtractor::getInstance().exit();
}

///--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    switch(currentScene)
    {
//        case 0:
//        {
//            //sceneManager->changeScene();
//            currentScene = 1;
//            break;
//        }
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        {
            switch(key)
            {
                case 'f':
                case 'F':
                {
                    // Change window mode
                    isFullScreen = !isFullScreen;
                    ofSetFullscreen(isFullScreen);
                    break;
                }
                case 'p':
                case 'P':
                {
                    showFPS = !showFPS;
                    break;
                }
                case 'k':
                case 'K':
                {
                    audioAnalyzer->start();
                    break;
                }
                case 'l':
                case 'L':
                {
                    audioAnalyzer->stop();
                    break;
                }
                case OF_KEY_UP:
                {
                    //currentScene++;
                    sceneManager.nextScene();
                    break;
                }
                case OF_KEY_DOWN:
                {
                    //currentScene--;
                    sceneManager.prevScene();
                    break;
                }
                default:
                    break;
            }
            
        }
    }
}

void ofApp::changeScene(unsigned int &sceneIndex)
{
    sceneManager.gotoScene(sceneIndex, true);
}
