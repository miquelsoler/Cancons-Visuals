//
// Created by Miquel Àngel Soler on 10/12/15.
//

#include "PMUICanvasLayers.h"

static const unsigned int PRESETSMATRIX_NUMROWS = 1;
static const unsigned int PRESETSMATRIX_NUMCOLS = 6;

PMUICanvasLayers::PMUICanvasLayers(string title, int headerFontSize) : PMBaseUICanvas(title, headerFontSize)
{
}

void PMUICanvasLayers::init(int layerNum, int posX, int posY, bool autosize, int width, int height)
{
    PMBaseUICanvas::init(posX, posY, autosize, width, height);
    layer = layerNum;
    
    addLabel("Layer " + ofToString(layer));
    addSpacer();
    
    // Presets
    addLabel("PRESETS");
    auto presetsMatrix = addToggleMatrix("PRESETS", PRESETSMATRIX_NUMROWS, PRESETSMATRIX_NUMCOLS,200/PRESETSMATRIX_NUMCOLS,20);
    presetsMatrix->setAllowMultiple(false);
    presetsMatrix->setTriggerType(OFX_UI_TRIGGER_NONE );
    
    ofAddListener(newGUIEvent, this, &PMUICanvasLayers::handleEvents);
    
    addSpacer();
    
    addLabel("Energy");
    addSlider("Min", 0, 1, &minEnergy);
    addSlider("Max", 0, 1, &maxEnergy);
    
    addSpacer();
    
}

void PMUICanvasLayers::clear()
{
    ofxUICanvas::clearWidgets();
    superInit("LAYERS", OFX_UI_FONT_MEDIUM);
}

void PMUICanvasLayers::handleEvents(ofxUIEventArgs &e)
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
}

void PMUICanvasLayers::loadPreset(int presetNumber)
{
    string presetPath = "presets/LAYERS/" + ofToString(presetNumber) + ".xml";
    loadSettings(presetPath);
    cout << "PMUICanvasLayers :: loading preset : " << presetNumber << " to " << presetPath << endl;
}

void PMUICanvasLayers::savePreset(int presetNumber)
{
    string presetPath = "presets/LAYERS/" + ofToString(presetNumber) + ".xml";
    saveSettings(presetPath);
    cout << "AudioAnalyzer :: saving preset : " << presetNumber << " to " << presetPath << endl;
}

//--------------------------------------------------------------------------------------------------
int PMUICanvasLayers::getActivePreset()
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
void PMUICanvasLayers::keyPressed(int key)
{
    if (key != OF_KEY_SHIFT) return;
    savingPreset = true;
}

//--------------------------------------------------------------------------------------------------
void PMUICanvasLayers::keyReleased(int key)
{
    if (key != OF_KEY_SHIFT) return;
    savingPreset = false;
}
