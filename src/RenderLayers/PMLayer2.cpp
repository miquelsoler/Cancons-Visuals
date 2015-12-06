//
// Created by Miquel Àngel Soler on 4/12/15.
//

#include "PMLayer2.h"

PMLayer2::PMLayer2(int _fboWidth, int _fboHeight, KinectNodeType _kinectNodeType) : PMBaseLayer(_fboWidth, _fboHeight, _kinectNodeType)
{
    layerID=2;
}

void PMLayer2::setup()
{
    PMBaseLayer::setup();
}

void PMLayer2::update()
{
    PMBaseLayer::update();
}

void PMLayer2::draw()
{
    PMBaseLayer::draw();
}

#pragma mark - Audio Events

void PMLayer2::pitchChanged(pitchParams &pitchParams)
{
}

void PMLayer2::energyChanged(energyParams &energyParams)
{
}

void PMLayer2::silenceStateChanged(silenceParams &silenceParams)
{
}

void PMLayer2::pauseStateChanged(pauseParams &pauseParams)
{
}

void PMLayer2::onsetDetected(onsetParams &onsetParams)
{
}

void PMLayer2::shtDetected(shtParams &shtParams)
{
}

void PMLayer2::melodyDirection(melodyDirectionParams &melodyDirectionParams)
{
}

void PMLayer2::melBandsChanged(melBandsParams &melBandsParams)
{
}
