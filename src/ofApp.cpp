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
        //PMSettingsManagerAudioAnalyzers settingsAA = PMSettingsManagerAudioAnalyzers::getInstance();
        
       // PMAudioAnalyzer::getInstance().init(
       //                                     settingsAA.getSilenceThreshold(), settingsAA.getSilenceQueueLength(),
       //                                     settingsAA.getOnsetsThreshold(),
       //                                     settingsAA.getAscDescAnalysisSize());
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
    
    scene9 = new PMSc9Export();
    sceneManager.add(scene9);
    
    scene10 = new PMSc10Thanks();
    sceneManager.add(scene10);
    
    
    
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
    ofAddListener(scene9->goToSceneEvent, this, &ofApp::changeScene);
    ofAddListener(scene10->goToSceneEvent, this, &ofApp::changeScene);
    
}

///--------------------------------------------------------------
void ofApp::update()
{
#ifdef OF_DEBUG
    ofShowCursor();

    currentScene = sceneManager.getCurrentSceneIndex();
#endif
	/*int w = ofGetWidth();
	int h = ofGetHeight();

	ofTexture tex;
	tex.allocate(w, h, GL_RGBA);

	tex.loadScreenData(0, 0, w, h);
	spout.sendTexture(tex, "Cancons-Main");
	tex.clear();*/
}

///--------------------------------------------------------------
void ofApp::draw()
{
    ofColor debugMessagesColor = ofColor(127);

    if (showFPS && sceneManager.getCurrentSceneIndex() != -1)
    {
		ofPushStyle();
        ofSetColor(debugMessagesColor);
        ofxBitmapString(15, ofGetHeight() - 15) << roundf(ofGetFrameRate()) << "fps" << endl;
		ofPopStyle();
    }

	//draw mask
	ofPushStyle();
    //ofSetColor(ofColor::black);
	//ofDrawRectangle(0, DESIGN_LEFT_HEIGHT, DESIGN_LEFT_WIDTH, DESIGN_HEIGHT - DESIGN_LEFT_HEIGHT);
	ofPopStyle();
	//ofSetColor(255);
	//if (ofGetKeyPressed(OF_KEY_SHIFT)) {
	//	ofImage tempimg;
	//	tempimg.load("assets/plantilla_projeccio.tiff");
	//	tempimg.draw(0, 0);
	//}


#ifdef OF_DEBUG
	ofPushStyle();
	ofSetColor(debugMessagesColor);
	ofxBitmapString(15, ofGetHeight() - 28)
		<< "[Current Scene] ID: " << sceneManager.getCurrentSceneIndex()
		<< " Name: " << sceneManager.getCurrentSceneName()
		<< " Screen Size: " << ofGetWidth() << " " << ofGetHeight()
		<< " Mouse Position: " << ofGetMouseX() << " " << ofGetMouseY() << endl;
	ofPopStyle();
#endif
}

///--------------------------------------------------------------
void ofApp::exit()
{
#if ENABLE_KINECT
	PMMotionExtractor::getInstance().stop();
#endif
}

///--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    switch(key) {
        case 'f':
        case 'F': {
            // Change window mode
//            isFullScreen = !isFullScreen;
//            ofSetFullscreen(isFullScreen);
            break;
        }
        case '*':
        {
            showFPS = !showFPS;
            break;
        }
        case OF_KEY_UP:
        case OF_KEY_RIGHT: {
#ifdef OF_DEBUG
			cout << "nextScene" << endl;
            if(currentScene!=9)
                sceneManager.nextScene(true);
            else{
                string toScene = "Scene 2";
                changeScene(toScene);
            }
#endif
            break;
        }
        case OF_KEY_DOWN:
        case OF_KEY_LEFT: {
#ifdef OF_DEBUG
            sceneManager.prevScene();
#endif
            break;
        }
//        case 's':
//        case 'S':
//        {
//            if (currentSceneName == "Scene 8") {
//                scene8->keyReleased(key);
//            }
//            break;
//        }
//        case ' ':
//            if (currentSceneName == "Scene 8") {
//                scene8->keyReleased(key);
//            }
        default:
            break;
    }
    
}

void ofApp::keyPressed(ofKeyEventArgs &keyargs){
    if(keyargs.keycode == 290){
        sceneManager.gotoScene(1);
        PMMotionExtractor::getInstance().exit();
        PMMotionExtractor::getInstance().setup();
    }
}

void ofApp::changeScene(string &scene)
{
    sceneManager.gotoScene(scene);
    currentSceneName = scene;
}
