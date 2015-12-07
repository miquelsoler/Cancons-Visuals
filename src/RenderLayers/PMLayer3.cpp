//
// Created by Miquel Àngel Soler on 4/12/15.
//

#include "PMLayer3.h"

PMLayer3::PMLayer3(int _fboWidth, int _fboHeight, KinectNodeType _kinectNodeType) : PMBaseLayer(_fboWidth, _fboHeight, _kinectNodeType)
{
    layerID = 3;
}

void PMLayer3::setup()
{
    PMBaseLayer::setup();
}

void PMLayer3::update()
{
    PMBaseLayer::update();
}

void PMLayer3::draw()
{
    PMBaseLayer::draw();
}

#pragma mark - Audio Events

void PMLayer3::pitchChanged(pitchParams &pitchParams)
{
}

void PMLayer3::energyChanged(energyParams &energyParams)
{
}

void PMLayer3::silenceStateChanged(silenceParams &silenceParams)
{
}

void PMLayer3::pauseStateChanged(pauseParams &pauseParams)
{
}

void PMLayer3::onsetDetected(onsetParams &onsetParams)
{
}

void PMLayer3::shtDetected(shtParams &shtParams)
{
}

void PMLayer3::melodyDirection(melodyDirectionParams &melodyDirectionParams)
{
}

void PMLayer3::melBandsChanged(melBandsParams &melBandsParams)
{
    float myEnergy = melBandsParams.bandsEnergy[3];
    int newSize = int(ofMap(myEnergy, 0.0, bandMaxEnergy, brushMinSize, brushMaxSize, true));
    brush->setSize(newSize, newSize);

//    cout << "Brush Size L3> En:" << myEnergy << " Size: " << newSize << endl;
}