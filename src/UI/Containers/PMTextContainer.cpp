//
//  PMTextContainer.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 02/11/15.
//
//

#include "PMTextContainer.hpp"

PMTextContainer::PMTextContainer(int _x, int _y, int _width, int _height, string _s, ofTrueTypeFont _font)
{
    this->s=_s;
    this->font=_font;
    this->x=_x;
    this->y=_y;
    this->width=_width;
    this->height=_height;

}

void PMTextContainer::draw()
{
    
}