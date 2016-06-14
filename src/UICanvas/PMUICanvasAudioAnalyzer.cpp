//
// Created by Miquel Àngel Soler on 7/11/15.
//

static const unsigned int PRESETSMATRIX_NUMROWS = 1;
static const unsigned int PRESETSMATRIX_NUMCOLS = 6;
//static const string STR_CANVAS_BASEPATH = "presets/AUDIO_ANALYZER";


#include "PMUICanvasAudioAnalyzer.h"

//--------------------------------------------------------------------------------------------------
PMUICanvasAudioAnalyzer::PMUICanvasAudioAnalyzer(string title, int headerFontSize) : PMBaseUICanvas(title, headerFontSize)
{
    savingPreset = false;
    
    fullBands = new float[40];
    for(int i = 0; i < 40; i++) { fullBands[i] = ofNoise(i/100.0); }
    fourBands = new float[4];
    for(int i = 0; i < 4; i++) { fourBands[i] = ofNoise(i/100.0); }

}

//--------------------------------------------------------------------------------------------------
void PMUICanvasAudioAnalyzer::init(int posX, int posY, bool autosize, int width, int height)
{
    PMBaseUICanvas::init(posX, posY, autosize, width, height);

//    settings = &PMSettingsManagerAudioAnalyzers::getInstance();
//
//    pitchMinMidiNote = settings->getMaxPitchMidiNote();
//    pitchMaxMidiNote = settings->getMinPitchMidiNote();

        // Presets
        addLabel("PRESETS");
        presetsMatrix = addToggleMatrix("PRESETS", PRESETSMATRIX_NUMROWS, PRESETSMATRIX_NUMCOLS,200/PRESETSMATRIX_NUMCOLS,20);
        presetsMatrix->setAllowMultiple(false);
        presetsMatrix->setTriggerType(OFX_UI_TRIGGER_NONE );

        addSpacer();


        addLabel("FULLMelBands");
        fullMelSpectrum = addSpectrum("FullMelBands", fullBands, 40, 0.0, 0.1);
//        fullMelSpectrum->setTriggerType(OFX_UI_TRIGGER_CHANGE);
        addSpacer();
        addLabel("ScaledBands");
        melSpectrum = addSpectrum("4 Bands", fourBands, 4, 0.0, 0.1);
//        melSpectrum->setTriggerType(OFX_UI_TRIGGER_ALL);

    if (autosize) autoSizeToFitWidgets();
}

//--------------------------------------------------------------------------------------------------
void PMUICanvasAudioAnalyzer::clear()
{
    ofxUICanvas::clearWidgets();
    superInit("AUDIO ANALYZER", OFX_UI_FONT_MEDIUM);
}

//--------------------------------------------------------------------------------------------------
void PMUICanvasAudioAnalyzer::handleEvents(ofxUIEventArgs &e)
{
    string name = e.getName();

    if (name.find("PRESETS")!=-1)
    {
        int activePreset = getActivePreset();

        if (savingPreset) {
            savePreset(activePreset);
        } else {
            loadPreset(activePreset);
        }
    }
   
//    else if(name == "FullMelBands")
//    {
//        vector<PMDeviceAudioAnalyzer *>::iterator itAudioAnalyzer;
//        for (itAudioAnalyzer = audioAnalyzers->begin(); itAudioAnalyzer != audioAnalyzers->end(); ++itAudioAnalyzer)
//        {
//            if ((*itAudioAnalyzer)->getInputIndex() != audioInputIndex) continue;
//            (*itAudioAnalyzer)->setOnsetsThreshold(e.getFloat());
//        }
//    }
    
}

//--------------------------------------------------------------------------------------------------
void PMUICanvasAudioAnalyzer::loadPreset(int presetNumber)
{
    string presetPath = "presets/AUDIO_ANALYZER/" + ofToString(presetNumber) + ".xml";
    loadSettings(presetPath);
    cout << "AudioAnalyzer :: loading preset : " << presetNumber << " to " << presetPath << endl;
}

//--------------------------------------------------------------------------------------------------
void PMUICanvasAudioAnalyzer::savePreset(int presetNumber)
{
    string presetPath = "presets/AUDIO_ANALYZER/" + ofToString(presetNumber) + ".xml";
    saveSettings(presetPath);
    cout << "AudioAnalyzer :: saving preset : " << presetNumber << " to " << presetPath << endl;
}

//--------------------------------------------------------------------------------------------------
int PMUICanvasAudioAnalyzer::getActivePreset()
{
    bool found = false;
    unsigned int col = 0, row = 0;
    for (unsigned int i=0; i<PRESETSMATRIX_NUMCOLS && !found; ++i) {
        col = i;
        for (unsigned int j=0; j<PRESETSMATRIX_NUMROWS && !found; ++j) {
            row = j;
            found = presetsMatrix->getState(j, i);
        }
    }
    
    if (!found) return -1;
    
    return (row * PRESETSMATRIX_NUMCOLS) + col;
}

//--------------------------------------------------------------------------------------------------
void PMUICanvasAudioAnalyzer::keyPressed(int key)
{
    if (key != OF_KEY_SHIFT) return;
    savingPreset = true;
}

//--------------------------------------------------------------------------------------------------
void PMUICanvasAudioAnalyzer::keyReleased(int key)
{
    if (key != OF_KEY_SHIFT) return;
    savingPreset = false;
}
