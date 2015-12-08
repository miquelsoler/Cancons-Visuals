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
    birthLineWith=100;
}

void PMComplexPaintbrush::setup()
{
    
}

void PMComplexPaintbrush::setup(ofImage _image, int _size, ofPoint initialPos)
{
    for (int i = 0; i < BRUSH_FILAMENTS_NUM; i++) {
        brushes[i].image = _image;
        brushes[i].size = _size;
        brushes[i].position = initialPos;
    }
}

void PMComplexPaintbrush::update(ofPoint _position, ofPoint direction, float speed, int _size)
{
    //set all points to 0
//    for (int i = 0; i < BRUSH_FILAMENTS_NUM; i++) {
//        brushes[i].size = _size;
//    }
    //update positions to be on the perpendicular of the direction
    birthLine=direction.getNormalized();
    birthLine.rotate(90, ofVec3f(0,0,1));//rotate 90 degrees
    birthLine*=birthLineWith;
    position=_position;//-birthLine/2;
//    for(float i=0; i<birthLineWith; i+=birthLineWith/BRUSH_FILAMENTS_NUM){
//        
//    }
}

void PMComplexPaintbrush::draw()
{
    ofPushStyle();
    ofSetColor(ofColor::red);
//        ofDrawLine(position, position+birthLine);
    ofDrawCircle(position, 5);
    ofPopStyle();
}