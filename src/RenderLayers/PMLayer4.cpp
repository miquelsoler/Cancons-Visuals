//
// Created by Miquel Àngel Soler on 4/12/15.
//

#include "PMLayer4.h"


PMLayer4::PMLayer4(int _fboWidth, int _fboHeight, KinectNodeType _kinectNodeType)
        : PMBaseLayer(_fboWidth, _fboHeight, _kinectNodeType)
{
    layerID = 4;
    didShake = false;
}

void PMLayer4::setup(ofPoint initialPosition)
{
    PMBaseLayer::setup(initialPosition);
    shootSizeDecrement=0.2;
    shootSpeedDecrement=0.4;
    shootMargin=30;
}

void PMLayer4::update()
{
#if ENABLE_KINECT
    PMBaseLayer::updateToShoot();
#else
    PMBaseLayer::update();
#endif
}

void PMLayer4::draw()
{
    PMBaseLayer::draw();
}
