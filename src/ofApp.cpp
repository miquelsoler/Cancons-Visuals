#include "ofApp.h"
#include "PMSettingsManager.h"
#include "Defaults.h"
#include "PMSc1Settings.hpp"
#include "PMSc2Main.hpp"

///--------------------------------------------------------------
void ofApp::setup()
{
    ofSetWindowShape(640, 480);
    //ofSetLogLevel(OF_LOG_VERBOSE);
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(ofColor::black);

    isFullScreen = (DEFAULT_WINDOW_MODE == OF_FULLSCREEN);

    currentScene = 1;

    // Settings

#ifdef OF_DEBUG
    showFPS = PMSettingsManager::getInstance().debugShowFPS;
#else
    showFPS = PMSettingsManager::getInstance().releaseShowFPS;
#endif

    // Scenes

    sceneManager.addScene(ofPtr<ofxScene>(new PMSc1Settings));
    sceneManager.addScene(ofPtr<ofxScene>(new PMSc2Main));
    sceneManager.run();

    // For testing purposes

    audioAnalyzer = new PMDeviceAudioAnalyzer(0, 2, 0, 44100, 512);

    int channelNumber = 0;
    bool useMelBands = true;
    int numMelBands = 24;
    audioAnalyzer->setup(PMDAA_CHANNEL_MONO, channelNumber, useMelBands, numMelBands);
    
    
    motionExtractor = new PMMotionExtractor();
    motionExtractor->setup();
}

///--------------------------------------------------------------
void ofApp::update()
{
#ifdef OF_DEBUG
    ofShowCursor();
#endif

    sceneManager.update();
    
    motionExtractor->update();
}

///--------------------------------------------------------------
void ofApp::draw()
{
    if (showFPS)
    {
        ofSetColor(ofColor::white);
        ofDrawBitmapString(ofToString(ofGetFrameRate()) + "fps", 15, ofGetHeight() - 15);
    }

    sceneManager.draw();
    
    motionExtractor->draw();
    KinectInfo* kinectOut=motionExtractor->getKinectInfo();
    ofDrawEllipse(kinectOut->leftHand_joint.x*ofGetWidth(), kinectOut->leftHand_joint.y*ofGetHeight(), 10+5*kinectOut->leftHand_joint.a, 10+5*kinectOut->leftHand_joint.a);
    ofDrawEllipse(kinectOut->rightHand_joint.x*ofGetWidth(), kinectOut->rightHand_joint.y*ofGetHeight(), 10+5*kinectOut->rightHand_joint.a, 10+5*kinectOut->rightHand_joint.a);
    ofDrawEllipse(kinectOut->head_joint.x*ofGetWidth(), kinectOut->head_joint.y*ofGetHeight(), 10+7*kinectOut->head_joint.a, 10+7*kinectOut->head_joint.a);
    ofDrawEllipse(kinectOut->torso_joint.x*ofGetWidth(), kinectOut->torso_joint.y*ofGetHeight(), 10+10*kinectOut->torso_joint.a, 10+10*kinectOut->torso_joint.a);
    
}

///--------------------------------------------------------------
void ofApp::exit()
{
    motionExtractor->exit();
}

///--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    switch(currentScene)
    {
        case 0:
        {
            sceneManager.changeScene();
            currentScene = 1;
            break;
        }
        case 1:
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
                default:
                    break;
            }
        }
    }
}
