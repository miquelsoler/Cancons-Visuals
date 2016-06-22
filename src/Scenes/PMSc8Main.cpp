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
#if ENABLE_LIVE
	fft = ofxFft::create(1024, OF_FFT_WINDOW_HAMMING);
	soundStream.printDeviceList();

	//if you want to set a different device id 
	soundStream.setDeviceID(3); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.

	int bufferSize = 1024;

	soundStream.setup(this, 0, 1, 44100, bufferSize, 4);
#else
    string songPath = "songs/" + PMSongSelector::getInstance().getFilename();
    songIsStarted = false;
    songIsPlaying = false;
    loadSong(songPath);
    playSong();
#endif

	//FFT
	nBandsToGet = 1024;
	fftSmoothed = new float[1024];
	for (int i = 0; i < nBandsToGet; i++)
		fftSmoothed[i] = 0;

	nMelBands = 4;
	melBands = new float[4];
	scaledBands = new float[4];
	for (int i = 0; i < nMelBands; i++) {
		melBands[i] = 0;
		scaledBands[i] = 0;
	}

	bandMaxs = new float[4];

	

	//createGui to guiApp
	PMSharedSettings shared = PMSharedSettings::getInstance();
	auto audioGui = shared.guiApp->audioGui;
	
	//bindVariables
	audioGui->bindLimits(&bandLimit_low, &bandLimit_1, &bandLimit_2, &bandLimit_3, &bandLimit_high);
	//audioGui->bindMaxs(&bandMax_low, &bandMax_lowmid, &bandMax_highmid, &bandMax_high);
	audioGui->bindMaxs(bandMaxs);
	audioGui->bindSpectrums(fftSmoothed, scaledBands);

	bandMax_low = bandMax_lowmid = bandMax_highmid = bandMax_high = 0;


	//setup Gui
	audioGui->init(5, 5);
	audioGui->setBackgroundColor(ofColor::slateGrey);
	audioGui->setVisible(false);
#if ENABLE_LIVE
	audioGui->loadPreset(1);
#else
	audioGui->loadPreset(0);
#endif

	shared.guiApp->layoutGuis();
}

void PMSc8Main::update()
{
#if !ENABLE_LIVE
    if (songIsStarted) {
        if (!song.isPlaying()) {
            exportImageAndLeaveScene();
        }
    }
    ofSoundUpdate();
	computeFFT();
#endif

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
        
        disablePainting = false;

        renderer = new PMRenderer();
        renderer->setup();

		enteredScene = true;

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

#if ENABLE_LIVE
void PMSc8Main::audioIn(float* input, int bufferSize, int nChannels) {
	//ofx fft stuff
	float maxValue = 0;
	for (int i = 0; i < bufferSize; i++) {
		if (abs(input[i]) > maxValue) {
			maxValue = abs(input[i]);
		}
	}
	for (int i = 0; i < bufferSize; i++) {
		//input[i] /= maxValue;
	}

	fft->setSignal(input);
	float* curFft = fft->getAmplitude();
	memcpy(&fftSmoothed[0], curFft, sizeof(float) * fft->getBinSize());

	maxValue = 0;
	for (int i = 0; i < fft->getBinSize(); i++) {
		if (abs(fftSmoothed[i]) > maxValue) {
			maxValue = abs(fftSmoothed[i]);
		}
	}
	for (int i = 0; i < fft->getBinSize(); i++) {
		//fftSmoothed[i] /= maxValue;
	}

	//reset melbands
	for (int i = 0; i < nMelBands; i++){
		melBands[i] = 0;
		scaledBands[i] = 0;
	}


	/*fft->setSignal(input);
	float * val = fft->getAmplitude();
	for (int i = 0; i < nBandsToGet; i++) {
		//fftSmoothed[i] *= 0.96f;
		//if (fftSmoothed[i] < val[i]) 
		fftSmoothed[i] = val[i];
	}*/

	int bandSize = 0;
	for (int i = toBin(bandLimit_low); i < toBin(bandLimit_1); i++) {
		melBands[0] += fftSmoothed[i];
		bandSize++;
	}
	melBands[0] /= bandSize;
	if (bandMaxs[0] < melBands[0])bandMaxs[0] = melBands[0];
	

	bandSize = 0;
	for (int i = toBin(bandLimit_1); i < toBin(bandLimit_2); i++) {
		melBands[1] += fftSmoothed[i];
		bandSize++;
	}
	melBands[1] /= bandSize;
	if (bandMaxs[1] < melBands[1]) bandMaxs[1] = melBands[1];

	bandSize = 0;
	for (int i = toBin(bandLimit_2); i < toBin(bandLimit_3); i++) {
		melBands[2] += fftSmoothed[i];
		bandSize++;
	}
	melBands[2] /= bandSize;
	if (bandMaxs[2] < melBands[2]) bandMaxs[2] = melBands[2];

	bandSize = 0;
	for (int i = toBin(bandLimit_3); i < toBin(bandLimit_high); i++) {
		melBands[3] += fftSmoothed[i];
		bandSize++;
	}
	melBands[3] /= bandSize;
	if (bandMaxs[3] < melBands[3]) bandMaxs[3] = melBands[3];

	//scaled bands
	for (int i = 0; i < 4; i++) {
		scaledBands[i] = melBands[i] / bandMaxs[i];
	}

	//for (int i = 0; i < nMelBands; i++)
	//	melBands[i] = fftSmoothed[i+1];

	vector<float> bandsVec;
	for (int i = 0; i < 4; i++) {
		bandsVec.push_back(scaledBands[i]);
		//bandsVec.push_back(melBands[i]);
	}
	bandsVec.push_back(melBands[0]);
	bandsVec.push_back(melBands[1]);
	bandsVec.push_back(melBands[2]);
	bandsVec.push_back(melBands[3]);
	if(enteredScene)
		renderer->melBandsChange(bandsVec);
}
#else

void PMSc8Main::computeFFT()
{
	//reset melbands
	for (int i = 0; i < nMelBands; i++)
		melBands[i] = 0;

	float * val = ofSoundGetSpectrum(nBandsToGet);
	for (int i = 0; i < nBandsToGet; i++) {
		//fftSmoothed[i] *= 0.96f;
		//if (fftSmoothed[i] < val[i]) 
		fftSmoothed[i] = val[i];
	}

	int bandSize = 0;
	for (int i = toBin(bandLimit_low); i < toBin(bandLimit_1); i++) {
		melBands[0] += fftSmoothed[i];
		bandSize++;
	}
	melBands[0] /= bandSize;
	if (bandMax_low < melBands[0]) bandMax_low = melBands[0];

	bandSize = 0;
	for (int i = toBin(bandLimit_1); i < toBin(bandLimit_2); i++) {
		melBands[1] += fftSmoothed[i];
		bandSize++;
	}
	melBands[1] /= bandSize;
	if (bandMax_lowmid < melBands[1]) bandMax_lowmid = melBands[1];

	bandSize = 0;
	for (int i = toBin(bandLimit_2); i < toBin(bandLimit_3); i++) {
		melBands[2] += fftSmoothed[i];
		bandSize++;
	}
	melBands[2] /= bandSize;
	if (bandMax_highmid < melBands[2]) bandMax_highmid = melBands[2];

	bandSize = 0;
	for (int i = toBin(bandLimit_3); i < toBin(bandLimit_high); i++) {
		melBands[3] += fftSmoothed[i];
		bandSize++;
	}
	melBands[3] /= bandSize;
	if (bandMax_high < melBands[3]) bandMax_high = melBands[3];

	cout << bandMax_low << endl;

	//for (int i = 0; i < nMelBands; i++)
	//	melBands[i] = fftSmoothed[i+1];

	vector<float> bandsVec;
	bandsVec.push_back(melBands[0]);
	bandsVec.push_back(melBands[1]);
	bandsVec.push_back(melBands[2]);
	bandsVec.push_back(melBands[3]);
	renderer->melBandsChange(bandsVec);
}
#endif

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
