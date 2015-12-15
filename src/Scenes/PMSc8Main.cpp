//
//  PMSc8Main.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#include "PMSc8Main.hpp"
#include "PMSongSelector.hpp"
#include "PMSettingsManagerGeneral.h"

static const int MINIMUM_SONG_TIME = 10;


PMSc8Main::PMSc8Main() : PMBaseScene("Scene 8")
{
#ifdef OF_DEBUG
    showGUI = PMSettingsManagerGeneral::getInstance().getDebugShowGUIScene8();
#else
    showGUI = PMSettingsManagerGeneral::getInstance().getReleaseShowGUIScene8();
#endif

    setSingleSetup(false);
    guiAudioAnalyzerCreated = false;

    motionExtractor = &PMMotionExtractor::getInstance();

    enteredScene = false;
}

void PMSc8Main::setup()
{
    string songPath = "songs/" + PMSongSelector::getInstance().getFilename();
    songIsStarted = false;
    songIsPlaying = false;
    loadSong(songPath);
    playSong();
}

void PMSc8Main::update()
{
//#if ENABLE_KINECT
//    cout<<"update"<<endl;
    PMMotionExtractor::getInstance().update();
//    kinectInfo = motionExtractor->getKinectInfo();
//    if(motionExtractor->getNumUsers() != 1)
//        renderer->exportToImage("TempRender");
    
//    cout<<kinectInfo->rightHand_joint.x<<" "<<kinectInfo->rightHand_joint.y<<endl;
//    cout<<motionExtractor->isReady()<<endl;
//    if(motionExtractor->isReady() & kinectInfo->rightHand_joint.x == 0 && kinectInfo->rightHand_joint.y == 0 && kinectInfo->leftHand_joint.x == 0 && kinectInfo->leftHand_joint.y == 0){
//    if(!motionExtractor->isReady()){
//        motionExtractor->resetUsers();
//        renderer->resetPositions();
//        cout<<"reset Users"<<endl;
//    }
//#endif

    if (songIsStarted) {
        if (!song.isPlaying()) {
            exportImageAndLeaveScene();
        }
    }
    ofSoundUpdate();


    // GUI
    {
        if (!guiAudioAnalyzerCreated) {
            int audioInputIndex = 0;
            guiAudioAnalyzer = new PMUICanvasAudioAnalyzer("AUDIO ANALYZER", OFX_UI_FONT_MEDIUM, audioInputIndex);
            guiAudioAnalyzer->init(5, 5);
            guiAudioAnalyzer->setBackgroundColor(ofColor::gray);
            guiAudioAnalyzer->setVisible(false);
        }
        guiAudioAnalyzerCreated = true;
    }

    if (!disablePainting)
        renderer->update();
}

void PMSc8Main::draw()
{
    renderer->draw();
}

void PMSc8Main::exit()
{
    song.stop();
    PMAudioAnalyzer::getInstance().stop();
    if (enteredScene) {
        delete renderer;
    }

    song.unload();

    enteredScene = false;
//    motionExtractor->stop();
}

void PMSc8Main::updateEnter()
{
    if (isEnteringFirst()) {
        enteredScene = true;
        disablePainting = false;

        renderer = new PMRenderer();
        renderer->setup();

        PMBaseScene::updateEnter();
//        string songPath = "songs/" + PMSongSelector::getInstance().getFilename();
//        songIsStarted = false;
//        songIsPlaying = false;
//        loadSong(songPath);
//        playSong();
    }
}

void PMSc8Main::updateExit()
{
    cout << "S8 updateExit()" << endl;
    PMBaseScene::updateExit();
}

void PMSc8Main::loadSong(string filename)
{
    song.load(filename);
    song.setVolume(1.0f);
    song.setMultiPlay(false);
}

void PMSc8Main::playSong()
{
    if (!song.isLoaded()) {
        cout << "Error - No loaded Sound!" << endl;
    }
    song.play();
    songIsStarted = true;
    songIsPlaying = true;
    timeBeginSong = ofGetElapsedTimef();
}


void PMSc8Main::keyReleased(int key)
{
    PMBaseScene::keyReleased(key);

    switch (key) {
        case 'g':
        case 'G': {
            showGUI = !showGUI;
            guiAudioAnalyzer->setVisible(showGUI);
//            ofClear(backgroundColor);
            break;
        }
        case 's':
        case 'S': {
//            renderer->exportToImage("TempRender");
            renderer->exportToImage("exports/unprocessed/testImage_" + ofGetTimestampString());
            break;
        }
        case 'z':
        case 'Z': {
#ifdef OF_DEBUG
            songIsPlaying = !songIsPlaying;
            song.setPaused(!songIsPlaying);
#endif
        }
        case ' ': {
            if (ofGetElapsedTimef() - timeBeginSong > MINIMUM_SONG_TIME) {
                disablePainting = true;
                exportImageAndLeaveScene();
            }else{
                string sceneToChange = "Scene 2";
                ofNotifyEvent(goToSceneEvent, sceneToChange, this);
            }
            break;
        }
        default:
            break;
    }
}

void PMSc8Main::exportImageAndLeaveScene()
{
    renderer->exportToImage("TempRender");
    renderer->exportToImage("exports/unprocessed/testImage_" + ofGetTimestampString());
    cout << "song_has_finished" << endl;
    string sceneToChange = "Scene 9";
    ofNotifyEvent(goToSceneEvent, sceneToChange, this);
}
