//
// Created by Miquel Àngel Soler on 4/12/15.
//

#include "PMLayer3.h"

PMLayer3::PMLayer3(int _fboWidth, int _fboHeight) : PMBaseLayer(_fboWidth, _fboHeight)
{
    layerID=3;
}

void PMLayer3::update()
{
    PMBaseLayer::update();
    kinectNodeData=PMMotionExtractor::getInstance().getKinectInfo()->head_joint;

}

void PMLayer3::draw()
{
    ofSetColor(ofColor::blue);

    int rectSize = 100;
    int x = 0;
    int y = fboHeight - rectSize;
    ofDrawRectangle(x, y, rectSize, rectSize);
}
