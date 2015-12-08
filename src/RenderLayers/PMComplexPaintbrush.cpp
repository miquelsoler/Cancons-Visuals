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
    birthLineWith=20;
}

void PMComplexPaintbrush::setup(ofImage _image, int _size, ofPoint initialPos)
{
    for (int i = 0; i < BRUSH_FILAMENTS_NUM; i++) {
        brushes[i].image = _image;
        brushes[i].size = _size;
        brushes[i].position = initialPos;
    }
}

void PMComplexPaintbrush::update(ofPoint position, ofPoint direction, float speed, int _size)
{
    //set all points to 0
    for (int i = 0; i < BRUSH_FILAMENTS_NUM; i++) {
        brushes[i].size = _size;
    }
    //update positions to be on the perpendicular of the direction
    birthLine=direction;
    birthLine.x*=-1;
    birthLine*=birthLineWith;
    for(float i=0; i<birthLineWith; i+=birthLineWith/BRUSH_FILAMENTS_NUM){
        
    }
}

void PMComplexPaintbrush::draw()
{

}