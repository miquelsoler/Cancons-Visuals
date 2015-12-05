//
// Created by Miquel Àngel Soler on 4/12/15.
//

#include "PMBaseLayer.h"
#include "PMColorsSelector.hpp"

PMBaseLayer::PMBaseLayer(int _fboWidth, int _fboHeight)
{
    fboWidth = _fboWidth;
    fboHeight = _fboHeight;
}

void PMBaseLayer::setup()//ofPoint pos, int _size, float _alpha, float _angle)
{
//    position=pos;
//    size=_size;
//    alpha=_alpha;
//    angle=_angle;
    vector<int> layerToColorMap {2,3,4,5}; //per asignar un pinzell diferent a ordre pinzell 1, a la capa 1.
    //FIXME: Definir aquest vector per parametre o potser a la gui
    brush = PMBrushesSelector::getInstance().getBrush(layerToColorMap[layerID]);
    drawColor = PMColorsSelector::getInstance().getColor(layerID);
    drawColor.setHsb(hsbColor.hue, hsbColor.saturation, hsbColor.brightness);
    
    vector<PMDeviceAudioAnalyzer*> deviceAudioAnalyzers = *PMAudioAnalyzer::getInstance().getAudioAnalyzers();
    PMDeviceAudioAnalyzer* deviceAudioAnalyzer = deviceAudioAnalyzers[0];
    
    ofAddListener(deviceAudioAnalyzer->eventPitchChanged, this, &PMBaseLayer::pitchChanged);
    ofAddListener(deviceAudioAnalyzer->eventEnergyChanged, this, &PMBaseLayer::energyChanged);
    //
    ofAddListener(deviceAudioAnalyzer->eventSilenceStateChanged, this, &PMBaseLayer::silenceStateChanged);
    ofAddListener(deviceAudioAnalyzer->eventPauseStateChanged, this, &PMBaseLayer::pauseStateChanged);
    ofAddListener(deviceAudioAnalyzer->eventOnsetStateChanged, this, &PMBaseLayer::onsetDetected);
    ofAddListener(deviceAudioAnalyzer->eventShtStateChanged, this, &PMBaseLayer::shtDetected);
    ofAddListener(deviceAudioAnalyzer->eventMelodyDirection, this, &PMBaseLayer::melodyDirection);
    ofAddListener(deviceAudioAnalyzer->eventMelBandsChanged, this, &PMBaseLayer::melBandsChanged);
}

void PMBaseLayer::update()
{
    
}

void PMBaseLayer::draw()
{
    ofSetColor(drawColor);
}

void PMBaseLayer::setSize(int _size)
{
    size=_size;
    brush->setSize(size, size);
}

