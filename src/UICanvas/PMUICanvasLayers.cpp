//
// Created by Miquel Àngel Soler on 10/12/15.
//

#include "PMUICanvasLayers.h"

PMUICanvasLayers::PMUICanvasLayers(string title, int headerFontSize) : PMBaseUICanvas(title, headerFontSize)
{
}

void PMUICanvasLayers::init(int posX, int posY, bool autosize, int width, int height)
{
}

void PMUICanvasLayers::clear()
{
    ofxUICanvas::clearWidgets();
    superInit("LAYERS", OFX_UI_FONT_MEDIUM);
}

void PMUICanvasLayers::handleEvents(ofxUIEventArgs &e)
{
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
