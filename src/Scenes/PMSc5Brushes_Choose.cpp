//
//  PMSc5Brushes_Choose.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 29/10/15.
//
//

#include "PMSc5Brushes_Choose.hpp"
#include "PMBrushesSelector.hpp"

PMSc5Brushes_Choose::PMSc5Brushes_Choose() : PMBaseScene("Scene 5")
{
    setFade(1000, 1000);
}

void PMSc5Brushes_Choose::setup()
{
    PMBrushesSelector::getInstance().init();
}

void PMSc5Brushes_Choose::update()
{
    
}

void PMSc5Brushes_Choose::draw()
{
    ofBackground(0);
    drawSettingsNumbers(3);
    PMBrushesSelector::getInstance().draw();
}
