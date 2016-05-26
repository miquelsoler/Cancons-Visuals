//
// Created by Miquel Àngel Soler on 10/12/15.
//

#include "PMUICanvasLayers.h"

static const unsigned int PRESETSMATRIX_NUMROWS = 1;
static const unsigned int PRESETSMATRIX_NUMCOLS = 6;

PMUICanvasLayers::PMUICanvasLayers(string title, int headerFontSize) : PMBaseUICanvas(title, headerFontSize)
{
    guiCreated=false;
}

void PMUICanvasLayers::init(int layerNum, int posX, int posY, bool autosize, int width, int height)
{
    if(guiCreated) clearWidgets();
    PMBaseUICanvas::init(posX, posY, autosize, width, height);
    layer = layerNum;
    
    addLabel("Layer " + ofToString(layer));
    addSpacer();
    
    // Presets
    addLabel("PRESETS");
    presetsMatrix = addToggleMatrix("PRESETS", PRESETSMATRIX_NUMROWS, PRESETSMATRIX_NUMCOLS,200/PRESETSMATRIX_NUMCOLS,20);
    presetsMatrix->setAllowMultiple(false);
    presetsMatrix->setTriggerType(OFX_UI_TRIGGER_NONE );
    
    ofAddListener(newGUIEvent, this, &PMUICanvasLayers::handleEvents);
    
    addSpacer();
    
    addLabel("Energy");
    addSlider("Min Energy", 0, 1, minEnergy);
    addSlider("Max Energy", 0, 1, maxEnergy);
    
    addSpacer();
    
    addLabel("Size");
    addIntSlider("Min Size", 0, 200, minSize);
    addIntSlider("Max Size", 0, 200, maxSize);
    addSlider("Scale Energy Factor Size", 0, 1, scaleEnergy_Size);
    addSlider("Scale Acceleration Factor Size", 0, 1, scaleAcceleration_Size);
    addSlider("Scale Z Factor Size", 0, 1, scaleZ_Size);
    
    addSpacer();
    
    addLabel("Hue");
    addSlider("Hue Scale Factor", 0, 1, scaleHue);
    addSlider("Hue Variation", 0, 1, variationHue);
    
    addSpacer();
    
    addLabel("Saturation");
    addSlider("Saturation Scale Factor", 0, 1, scaleSaturation);
    addSlider("Saturation Variation", 0, 1, variationSaturation);
    
    addSpacer();
    
    addLabel("Brightness");
    addSlider("Brightness Scale Factor", 0, 1, scaleBrightness);
    addSlider("Brightness Variation", 0, 1, variationBrightness);
    
    addSpacer();
    
    addLabel("Alpha");
    addSlider("Min Alpha", 0, 1, minAlpha);
    addSlider("Max Alpha", 0, 1, maxAlpha);
    addSlider("Scale Energy Factor Alpha", 0, 1, scaleEnergy_Alpha);
    addSlider("Scale Velocity Factor Alpha", 0, 1, scaleVelocity_Alpha);
    addSlider("Scale Z Factor Alpha", 0, 1, scaleZ_Alpha);
    
    addSpacer();
    
    addLabel("Behaviour");
    addSlider("Speed", 0, 10, curveSpeed);
    addSlider("Curve Size", 0, 20, curveSize);
    
    if (autosize) autoSizeToFitWidgets();
    
    guiCreated = true;
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
	ofPoint oldPos = ofPoint(rect->getX(), rect->getY());
    loadSettings(presetPath);
	setPosition(oldPos.x, oldPos.y);
    cout << "PMUICanvasLayers :: loading preset : " << presetNumber << " to " << presetPath << endl;
}

void PMUICanvasLayers::savePreset(int presetNumber)
{
    string presetPath = "presets/LAYERS/" + ofToString(presetNumber) + ".xml";
    saveSettings(presetPath);
    cout << "PMUICanvasLayers :: saving preset : " << presetNumber << " to " << presetPath << endl;
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
