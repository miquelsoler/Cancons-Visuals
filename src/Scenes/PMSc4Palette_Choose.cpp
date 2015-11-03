//
//  PMSc4Palette_Choose.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 29/10/15.
//
//

#include "PMSc4Palette_Choose.hpp"
#include "PMColorsSelector.hpp"


void PMSc4Palette_Choose::setup()
{
    PMColorsSelector::getInstance().init();
}

void PMSc4Palette_Choose::update()
{
    
}

void PMSc4Palette_Choose::draw()
{
    ofBackground(0);
    drawSettingsNumbers(2);
    PMColorsSelector::getInstance().draw();
}