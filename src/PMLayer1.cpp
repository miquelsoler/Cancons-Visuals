//
// Created by Miquel Àngel Soler on 4/12/15.
//

#include "PMLayer1.h"

PMLayer1::PMLayer1(int _fboWidth, int _fboHeight) : PMBaseLayer(_fboWidth, _fboHeight)
{
}

void PMLayer1::update()
{

}

void PMLayer1::draw()
{
    ofSetColor(ofColor::red);

    int rectSize = 100;
    int x = 0;
    int y = 0;
    ofDrawRectangle(x, y, rectSize, rectSize);
}
