//
// Created by Miquel Àngel Soler on 10/12/15.
//

#include "PMUICanvasLayers.h"

static const unsigned int PRESETSMATRIX_NUMROWS = 1;
static const unsigned int PRESETSMATRIX_NUMCOLS = 6;

static const float ENERGY_MIN = 0.0f;
static const float ENERGY_MAX = 1.0f;

static const float BRSIZE_MIN = 1.0;
static const float BRSIZE_MAX = 500.0;

static const string STR_LAYER = "LAYER";
static const string STR_ENERGY = "Energy";
static const string STR_ENERGY_MINMAX = "Energy Min/Max";
static const string STR_SIZE = "Size";
static const string STR_SIZE_MINMAX = "Size Min/Max";
static const string STR_SIZE_SCALEENERGY = "Size Scale Energy Factor";
static const string STR_SIZE_SCALEACCELERATION = "Size Scale Acceleration Factor";
static const string STR_SIZE_SCALEZ = "Size Scale Z Factor";

PMUICanvasLayers::PMUICanvasLayers(string title, int headerFontSize) : PMBaseUICanvas(title, headerFontSize)
{
}

void PMUICanvasLayers::init(int posX, int posY, bool autosize, int width, int height)
{
    PMBaseUICanvas::init(posX, posY, autosize, width, height);

    unsigned int numLayers = 4;

    for (int i=0; i<numLayers; ++i)
    {
        LayerParams layerParams;

        layerParams.energyMin = 0.0f;
        layerParams.energyMax = 0.1f;

        layerParams.sizeMin = 10.0f;
        layerParams.sizeMax = 120.0f;
        layerParams.sizeScaleEnergyFactor = 0.0f;
        layerParams.sizeScaleEnergyFactor = 1.0f;
        layerParams.sizeScaleZFactor = 1.0f;

        layerParams.hueVariation = 0.5;
        layerParams.saturationVariation = -0.1f;
        layerParams.brightnessVariation = 0.0f;

        layerParams.alphaMin = 0.0f;
        layerParams.alphaMax = 0.8f;
        layerParams.alphaScaleEnergyFactor = 0.5;
        layerParams.alphaScaleVelocityFactor = 2.0f;
        layerParams.alphaScaleZFactor = 2.0f;

        layerParams.behaviorSpeed = 2;
        layerParams.behaviorCurveSize = 7;

        if ((i==2) || (i==3))
        {
            layerParams.shootBehaviorInitialSize = 80;
            layerParams.shootBehaviorInitialSpeed = 5;
            layerParams.shootBehaviorSpeedDecrement = 0.5;
            layerParams.shootBehaviorSizeDecrement = 7;
            layerParams.shootBehaviorCurveAmount = 7;
        }

        layers.push_back(layerParams);
    }

    // Presets
    {
        addLabel("PRESETS");
        presetsMatrix = addToggleMatrix("PRESETS", PRESETSMATRIX_NUMROWS, PRESETSMATRIX_NUMCOLS, 200/PRESETSMATRIX_NUMCOLS, 20);
        presetsMatrix->setAllowMultiple(false);
        presetsMatrix->setTriggerType(OFX_UI_TRIGGER_NONE );
        addSpacer();
    }

    for (unsigned int i=0; i<numLayers; ++i)
    {
        addLabel(STR_LAYER + " " + ofToString(i + 1));
        addSpacer();

        addLabel(STR_ENERGY);
        addRangeSlider(STR_ENERGY_MINMAX, ENERGY_MIN, ENERGY_MAX, &(layers[i].energyMin), &(layers[i].energyMax));

        addLabel(STR_SIZE);
        addRangeSlider(STR_SIZE_MINMAX, BRSIZE_MIN, BRSIZE_MAX, &(layers[i].sizeMin), &(layers[i].sizeMax));

        if ((i==2) || (i==3))
        {

        }

        addSpacer();
        addSpacer();
    }

    ofAddListener(newGUIEvent, this, &PMUICanvasLayers::handleEvents);

    if (autosize) autoSizeToFitWidgets();

    loadPreset(0);
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

void PMUICanvasLayers::keyPressed(int key)
{
    if (key != OF_KEY_SHIFT) return;
    savingPreset = true;
}

void PMUICanvasLayers::keyReleased(int key)
{
    if (key != OF_KEY_SHIFT) return;
    savingPreset = false;
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
