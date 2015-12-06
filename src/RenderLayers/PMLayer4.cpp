//
// Created by Miquel Àngel Soler on 4/12/15.
//

#include "PMLayer4.h"

PMLayer4::PMLayer4(int _fboWidth, int _fboHeight, KinectNodeType _kinectNodeType) : PMBaseLayer(_fboWidth, _fboHeight, _kinectNodeType)
{
    layerID=4;
}

void PMLayer4::setup()
{
    PMBaseLayer::setup();
}

void PMLayer4::update()
{
    PMBaseLayer::update();
}

void PMLayer4::draw()
{
    PMBaseLayer::draw();
}

#pragma mark - Audio Events

void PMLayer4::pitchChanged(pitchParams &pitchParams)
{
}

void PMLayer4::energyChanged(energyParams &energyParams)
{
}

void PMLayer4::silenceStateChanged(silenceParams &silenceParams)
{
}

void PMLayer4::pauseStateChanged(pauseParams &pauseParams)
{
}

void PMLayer4::onsetDetected(onsetParams &onsetParams)
{
}

void PMLayer4::shtDetected(shtParams &shtParams)
{
}

void PMLayer4::melodyDirection(melodyDirectionParams &melodyDirectionParams)
{
}

void PMLayer4::melBandsChanged(melBandsParams &melBandsParams)
{
}