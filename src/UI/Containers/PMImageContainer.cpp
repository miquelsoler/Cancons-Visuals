//
//  PMImageContainer.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 02/11/15.
//
//

#include "PMImageContainer.hpp"

PMImageContainer::PMImageContainer(ofImage _image)
{
    this->image=_image;
    this->x=ofRandomWidth();
    this->y=ofRandomHeight();
    this->width=20;
    this->height=20;
}

PMImageContainer::PMImageContainer(string filename)
{
    image.load(filename);
    this->x=ofRandomWidth();
    this->y=ofRandomHeight();
    this->width=20;
    this->height=20;
}

PMImageContainer::PMImageContainer(int _x, int _y, int _width, int _height, ofImage _image)
{
    this->image=_image;
    this->x=_x;
    this->y=_y;
    this->width=_width;
    this->height=_height;
}

void PMImageContainer::draw()
{
    ofPushMatrix();
        ofSetRectMode(OF_RECTMODE_CENTER);
        image.resize(width, height);
        image.draw(x, y);
    ofPopMatrix();
}

void PMImageContainer::setImage(ofImage _image)
{
    image=_image;
}

void PMImageContainer::loadImage(string filename)
{
    image.load(filename);
}