//
// Created by Miquel Àngel Soler on 4/12/15.
//

#include "PMLayer1.h"

static const float Z_SIZE_OFFSET  = 2;
static const float Z_SIZE_FACTOR = 10;

static const int HUE_FACTOR = 180;

PMLayer1::PMLayer1(int _fboWidth, int _fboHeight, KinectNodeType _kinectNodeType) : PMBaseLayer(_fboWidth, _fboHeight, _kinectNodeType)
{
    layerID = 1;
}

void PMLayer1::setup(ofPoint initialPosition)
{
    PMBaseLayer::setup(initialPosition);
}

void PMLayer1::update()
{
    PMBaseLayer::update();
}

void PMLayer1::draw()
{
    PMBaseLayer::draw();
}
