//
// Created by Miquel Àngel Soler on 4/12/15.
//

#include "PMLayer2.h"

PMLayer2::PMLayer2(int _fboWidth, int _fboHeight) : PMBaseLayer(_fboWidth, _fboHeight)
{
}

void PMLayer2::update()
{

}

void PMLayer2::draw()
{
    ofSetColor(ofColor::green);

    int rectSize = 100;
    int x = fboWidth - rectSize;
    int y = 0;
    ofDrawRectangle(x, y, rectSize, rectSize);
}
