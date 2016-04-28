//
// Created by Miquel Àngel Soler on 4/12/15.
//

#include "PMLayer3.h"

PMLayer3::PMLayer3(int _fboWidth, int _fboHeight, KinectNodeType _kinectNodeType)
        : PMBaseLayer(_fboWidth, _fboHeight, _kinectNodeType)
{
    layerID = 3;
    didShake = false;
}

void PMLayer3::setup(ofPoint initialPosition)
{
    PMBaseLayer::setup(initialPosition);
}

void PMLayer3::update()
{
#if ENABLE_KINECT && !ENABLE_KNEES_DETECTION
    PMBaseLayer::updateToShoot();
#else
    PMBaseLayer::update();
#endif
}

void PMLayer3::draw()
{
    PMBaseLayer::draw();
}
