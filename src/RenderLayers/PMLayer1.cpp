//
// Created by Miquel Àngel Soler on 4/12/15.
//

#include "PMLayer1.h"

PMLayer1::PMLayer1(int _fboWidth, int _fboHeight, KinectNodeType _kinectNodeType) : PMBaseLayer(_fboWidth, _fboHeight, _kinectNodeType)
{
    layerID = 1;
}

void PMLayer1::setup()
{
    PMBaseLayer::setup();
}

void PMLayer1::update()
{
    PMBaseLayer::update();
    float smoothDelta=0.1;
//    int newbrushSize=(brushSize*(1-smoothDelta))+(kinectNodeData.z*smoothDelta);
    int newbrushSize =(1-kinectNodeData.z)*BRUSH_MAX_SIZE*5;
//    cout<<brushSize<<"------------"<<newbrushSize<<endl;
    brush->setSize(newbrushSize, newbrushSize);
}

void PMLayer1::draw()
{
    PMBaseLayer::draw();
}

#pragma mark - Audio Events

void PMLayer1::pitchChanged(pitchParams &pitchParams)
{
}

void PMLayer1::energyChanged(energyParams &energyParams)
{
    brushAlpha = energyParams.energy*10;
}

void PMLayer1::silenceStateChanged(silenceParams &silenceParams)
{
}

void PMLayer1::pauseStateChanged(pauseParams &pauseParams)
{
}

void PMLayer1::onsetDetected(onsetParams &onsetParams)
{
}

void PMLayer1::shtDetected(shtParams &shtParams)
{
}

void PMLayer1::melodyDirection(melodyDirectionParams &melodyDirectionParams)
{
}

void PMLayer1::melBandsChanged(melBandsParams &melBandsParams)
{
}
