#include "ofApp.h"
#include "PMSettingsManagerGeneral.h"
#include "PMSettingsManagerAudioAnalyzers.h"
#include "Defaults.h"


///--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    //ofBackground(ofColor::black);

    isFullScreen = (DEFAULT_WINDOW_MODE == OF_FULLSCREEN);

    currentScene = 2;
    currentSceneName = "";

    // Initialize audio analyzer
    {
        PMSettingsManagerAudioAnalyzers settingsAA = PMSettingsManagerAudioAnalyzers::getInstance();
        
        PMAudioAnalyzer::getInstance().init(
                                            settingsAA.getSilenceThreshold(), settingsAA.getSilenceQueueLength(),
                                            settingsAA.getOnsetsThreshold(),
                                            settingsAA.getAscDescAnalysisSize());
    }

    // General Settings
    {

#ifdef OF_DEBUG
    showFPS = PMSettingsManagerGeneral::getInstance().getDebugShowFPS();
#else
    showFPS = PMSettingsManagerGeneral::getInstance().getReleaseShowFPS();
#endif
    }

    // Scenes

    scene1 = new PMSc1Settings();
    sceneManager.add(scene1);
    
    scene2 = new PMSc2Start();
    sceneManager.add(scene2);
    
    scene3 = new PMSc3Song_Choose();
    sceneManager.add(scene3);
    
    scene4 = new PMSc4Palette_Choose();
    sceneManager.add(scene4);
    
    scene5 = new PMSc5Brushes_Choose();
    sceneManager.add(scene5);
    
    scene6 = new PMSc6Kinect_Detect();
    sceneManager.add(scene6);
    
    scene7 = new PMSc7Countdown();
    sceneManager.add(scene7);
    
    scene8 = new PMSc8Main();
    sceneManager.add(scene8);
    
    
    
    sceneManager.setup(false);
    sceneManager.setOverlap(true);
    ofSetLogLevel("ofxSceneManager", OF_LOG_VERBOSE); //lets see whats going on inside
    
    setSceneManager(&sceneManager);
    sceneManager.gotoScene("Scene 1", false);
    

    ofAddListener(scene1->goToSceneEvent, this, &ofApp::changeScene);
    ofAddListener(scene2->goToSceneEvent, this, &ofApp::changeScene);
    ofAddListener(scene3->goToSceneEvent, this, &ofApp::changeScene);
    ofAddListener(scene4->goToSceneEvent, this, &ofApp::changeScene);
    ofAddListener(scene5->goToSceneEvent, this, &ofApp::changeScene);
    ofAddListener(scene6->goToSceneEvent, this, &ofApp::changeScene);
    ofAddListener(scene7->goToSceneEvent, this, &ofApp::changeScene);
    ofAddListener(scene8->goToSceneEvent, this, &ofApp::changeScene);
}

///--------------------------------------------------------------
void ofApp::update()
{
#ifdef OF_DEBUG
    ofShowCursor();

    currentScene = sceneManager.getCurrentSceneIndex();
#endif
}

///--------------------------------------------------------------
void ofApp::draw()
{
    ofColor debugMessagesColor = ofColor(127);

    if (showFPS && sceneManager.getCurrentSceneIndex() != -1)
    {
        ofSetColor(debugMessagesColor);
        ofxBitmapString(15, ofGetHeight() - 15) << roundf(ofGetFrameRate()) << "fps" << endl;
    }

#if OF_DEBUG
    ofSetColor(debugMessagesColor);
    ofxBitmapString(15, ofGetHeight()-28)
            << "[Current Scene] ID: " << sceneManager.getCurrentSceneIndex()
            << " Name: " << sceneManager.getCurrentSceneName() << endl;
#endif

    ofSetColor(ofColor::white);
}

///--------------------------------------------------------------
void ofApp::exit()
{
}

///--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    switch(key) {
        case 'f':
        case 'F': {
            // Change window mode
            isFullScreen = !isFullScreen;
            ofSetFullscreen(isFullScreen);
            break;
        }
        case 'p':
        case 'P': {
            showFPS = !showFPS;
            break;
        }
        case OF_KEY_UP:
        case OF_KEY_RIGHT: {
            sceneManager.nextScene();
            break;
        }
        case OF_KEY_DOWN:
        case OF_KEY_LEFT: {
            sceneManager.prevScene();
            break;
        }
        case 'g':
        case 'G':
        {
            if (currentSceneName == "Scene 8") {
                scene8->keyReleased(key);
            }
            break;
        }
        default:
            break;
    }
    
}


void ofApp::changeScene(string &scene)
{
    sceneManager.gotoScene(scene);
    currentSceneName = scene;
}

