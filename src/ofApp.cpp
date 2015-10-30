#include "ofApp.h"
#include "PMSettingsManager.h"
#include "Defaults.h"

///--------------------------------------------------------------
void ofApp::setup()
{
    //ofSetWindowShape(640, 480);
    //ofSetLogLevel(OF_LOG_VERBOSE);
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(ofColor::black);

    isFullScreen = (DEFAULT_WINDOW_MODE == OF_FULLSCREEN);

    currentScene = 0;

    // Settings

#ifdef OF_DEBUG
    showFPS = PMSettingsManager::getInstance().debugShowFPS;
#else
    showFPS = PMSettingsManager::getInstance().releaseShowFPS;
#endif

    // Scenes

    sceneManager = &(PMSceneManager::getInstance());
    sceneManager->init();

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

    sceneManager->update();
}

///--------------------------------------------------------------
void ofApp::draw()
{
    if (showFPS)
    {
        ofSetColor(ofColor::white);
        ofDrawBitmapString(ofToString(ofGetFrameRate()) + "fps", 15, ofGetHeight() - 15);
    }

    sceneManager->draw();
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
        case 0:
        {
            sceneManager->changeScene();
            currentScene = 1;
            break;
        }
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
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
                    currentScene++;
                    sceneManager->changeScene();
                    break;
                }
//                case OF_KEY_DOWN:
//                {
//                    currentScene--;
//                    sceneManager->changeScene(currentScene);
//                    break;
//                }
                default:
                    break;
            }
            
        }
    }
}
