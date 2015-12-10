//
//  PMSc4Palette_Choose.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 29/10/15.
//
//

#include "PMSc4Palette_Choose.hpp"
#include "PMColorsSelector.hpp"

PMSc4Palette_Choose::PMSc4Palette_Choose() : PMBaseScene("Scene 4")
{

}

void PMSc4Palette_Choose::setup()
{
    PMColorsSelector::getInstance().init(baseFont);
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

void PMSc4Palette_Choose::mouseMoved(int x, int y)
{
    PMColorsSelector::getInstance().checkMousePassed(x, y);
}

void PMSc4Palette_Choose::mousePressed(int x, int y, int mouse)
{
    if(PMColorsSelector::getInstance().checkMousePressed(x, y)){
        string sceneToChange="Scene 5";
        ofNotifyEvent(goToSceneEvent, sceneToChange, this);
    }

}
