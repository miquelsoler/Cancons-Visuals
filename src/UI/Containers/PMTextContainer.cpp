//
//  PMTextContainer.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 02/11/15.
//
//

#include "PMTextContainer.hpp"

PMTextContainer::PMTextContainer(int _x, int _y, string _s, ofTrueTypeFont &_font)
{
    this->s=_s;
    this->font=&_font;
    this->x=_x;
    this->y=_y;
    this->width=font->stringWidth(s);
    this->height=font->stringHeight(s);

}

void PMTextContainer::draw()
{
    font->drawString(s, x-width/2, y+height/2);
}