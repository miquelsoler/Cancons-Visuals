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


PMSc8Main::PMSc8Main() : PMBaseScene("Scene 8")
{
#ifdef OF_DEBUG
    showGUI = PMSettingsManagerGeneral::getInstance().getDebugShowGUIScene8();
#else
    showGUI = PMSettingsManagerGeneral::getInstance().getReleaseShowGUIScene8();
#endif

    setSingleSetup(true);
    guiAudioAnalyzerCreated = false;

    renderer = new PMRenderer();
}

void PMSc8Main::setup()
{
    motionExtractor = &PMMotionExtractor::getInstance();
    renderer->setup();
}

void PMSc8Main::update()
{
#if ENABLE_KINECT
    motionExtractor->update();
    kinectInfo = motionExtractor->getKinectInfo();
#endif

    if (songIsStarted) {
        if (!song.isPlaying()) {
            cout << "song_has_finished" << endl;
            string sceneToChange = "Scene 2";
//            ofNotifyEvent(goToSceneEvent, sceneToChange, this);
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
    renderer->exportToImage("TempRender");
}

void PMSc8Main::updateEnter()
{

    PMBaseScene::updateEnter();
    string songPath = "songs/" + PMSongSelector::getInstance().getFilename();
    songIsStarted = false;
    loadSong(songPath);
    playSong();

    
}

void PMSc8Main::updateExit()
{
    PMBaseScene::updateExit();
    //motionExtractor->exit();
    
//    renderer->exportToImage("testImage_"+ofGetTimestampString());
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
            renderer->exportToImage("TempRender");
            break;
        }
        case ' ': {
#ifdef OF_DEBUG
            songIsPlaying = !songIsPlaying;
            song.setPaused(!songIsPlaying);
#endif
            break;
        }
        default:
            break;
    }
}
