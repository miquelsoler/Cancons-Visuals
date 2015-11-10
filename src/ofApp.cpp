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
    //ofBackground(ofColor::black);

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
    sceneManager.add(scene1);
    
    PMSc2Start *scene2 = new PMSc2Start();
    sceneManager.add(scene2);
    
    PMSc3Song_Choose *scene3 = new PMSc3Song_Choose();
    sceneManager.add(scene3);
    
    PMSc4Palette_Choose *scene4 = new PMSc4Palette_Choose();
    sceneManager.add(scene4);
    
    PMSc5Brushes_Choose *scene5 = new PMSc5Brushes_Choose();
    sceneManager.add(scene5);
    
    PMSc6Kinect_Detect *scene6 = new PMSc6Kinect_Detect();
    sceneManager.add(scene6);
    
    PMSc7Countdown *scene7 = new PMSc7Countdown();
    sceneManager.add(scene7);
    
    PMSc8Main *scene8 = new PMSc8Main();
    sceneManager.add(scene8);
    
    
    
    sceneManager.setup(false);
    sceneManager.setOverlap(true);
    ofSetLogLevel("ofxSceneManager", OF_LOG_VERBOSE); //lets see whats going on inside
    
    setSceneManager(&sceneManager);
    sceneManager.gotoScene("Scene 3", false);
    
    // For testing purposes

//    audioAnalyzer = new PMDeviceAudioAnalyzer(0, 2, 0, 44100, 512);
//
//    int channelNumber = 0;
//    bool useMelBands = true;
//    int numMelBands = 24;
//    audioAnalyzer->setup(PMDAA_CHANNEL_MONO, channelNumber, useMelBands, numMelBands);
//    
    
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
//    PMMotionExtractor::getInstance().exit();
}

///--------------------------------------------------------------
void ofApp::keyReleased(int key)
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
//            audioAnalyzer->start();
            break;
        }
        case 'l':
        case 'L':
        {
//            audioAnalyzer->stop();
            break;
        }
        case OF_KEY_UP:
        {
            sceneManager.nextScene();
            break;
        }
        case OF_KEY_DOWN:
        {
            sceneManager.prevScene();
            break;
        }
        default:
            break;
    }
    
}

