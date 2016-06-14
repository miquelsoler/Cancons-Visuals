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
#include "PMSharedSettings.h"

static const int MINIMUM_SONG_TIME = 10;


PMSc8Main::PMSc8Main() : PMBaseScene("Scene 8")
{
#ifdef OF_DEBUG
    showGUI = PMSettingsManagerGeneral::getInstance().getDebugShowGUIScene8();
#else
    showGUI = PMSettingsManagerGeneral::getInstance().getReleaseShowGUIScene8();
#endif

    setSingleSetup(false);
    //guiAudioAnalyzerCreated = false;

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

	//FFT
	fftSmoothed = new float[8192];
	for (int i = 0; i < 8192; i++)
		fftSmoothed[i] = 0;

	nMelBands = 4;
	melBands = new float[4];
	for (int i = 0; i < nMelBands; i++)
		melBands[i] = 0;

	nBandsToGet = 8;

	//createGui to guiApp
	PMSharedSettings shared = PMSharedSettings::getInstance();
	auto audioGui = shared.guiApp->audioGui;
	
	//bindVariables
	audioGui->bindLimits(&bandLimit_low, &bandLimit_1, &bandLimit_2, &bandLimit_3, &bandLimit_hight);
	audioGui->bindSpectrums(fftSmoothed, melBands);


	//setup Gui
	audioGui->init(5, 5);
	audioGui->setBackgroundColor(ofColor::slateGrey);
	audioGui->setVisible(false);
	audioGui->loadPreset(0);

	shared.guiApp->layoutGuis();
}

void PMSc8Main::update()
{
    if (songIsStarted) {
        if (!song.isPlaying()) {
            exportImageAndLeaveScene();
        }
    }
    ofSoundUpdate();
	computeFFT();

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
    //PMAudioAnalyzer::getInstance().stop();
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

void PMSc8Main::computeFFT()
{
	float * val = ofSoundGetSpectrum(nBandsToGet);
	for (int i = 0; i < nBandsToGet; i++) {
		fftSmoothed[i] *= 0.96f;
		if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
	}
	for (int i = 0; i < nMelBands; i++)
		melBands[i] = fftSmoothed[i];

	vector<float> bandsVec;
	bandsVec.push_back(melBands[0]);
	bandsVec.push_back(melBands[1]);
	bandsVec.push_back(melBands[2]);
	bandsVec.push_back(melBands[3]);
	renderer->melBandsChange(bandsVec);
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
            //guiAudioAnalyzer->setVisible(showGUI);
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
