//
//  PMComplexPaintbrush.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 07/12/15.
//
//

#include "PMComplexPaintbrush.hpp"

PMComplexPaintbrush::PMComplexPaintbrush()
{
    for (int i = 0; i < BRUSH_FILAMENTS_NUM; i++) {
        BrushSimpleContainer tempContainer;
        brushes.push_back(tempContainer);
    }
}

void PMComplexPaintbrush::setup(ofImage _image, int _size, ofPoint initialPos)
{
    for (int i = 0; i < BRUSH_FILAMENTS_NUM; i++) {
        brushes[i].image = _image;
        brushes[i].size = _size;
        brushes[i].position = initialPos;
    }
}

void PMComplexPaintbrush::update()
{

}

void PMComplexPaintbrush::draw()
{

}