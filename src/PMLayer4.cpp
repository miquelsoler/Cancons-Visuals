//
// Created by Miquel Àngel Soler on 4/12/15.
//

#include "PMLayer4.h"

PMLayer4::PMLayer4(int _fboWidth, int _fboHeight) : PMBaseLayer(_fboWidth, _fboHeight)
{
    layerID=4;
}

void PMLayer4::update()
{
    PMBaseLayer::update();
    kinectNodeData=PMMotionExtractor::getInstance().getKinectInfo()->torso_joint;
}

void PMLayer4::draw()
{
    ofSetColor(ofColor::yellow);

    int rectSize = 100;
    int x = fboWidth - rectSize;
    int y = fboHeight - rectSize;
    ofDrawRectangle(x, y, rectSize, rectSize);
}
