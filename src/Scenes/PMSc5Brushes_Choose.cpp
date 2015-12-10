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
    PMBrushesSelector::getInstance().init();
    setSingleSetup(false);
}

void PMSc5Brushes_Choose::setup()
{
    PMBrushesSelector::getInstance().setInitialState();
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

void PMSc5Brushes_Choose::mouseMoved(int x, int y)
{
    PMBrushesSelector::getInstance().checkMousePassed(x, y);
}

void PMSc5Brushes_Choose::mousePressed(int x, int y, int mouse)
{
    if(PMBrushesSelector::getInstance().checkMousePressed(x, y)){
        string sceneToChange="Scene 6";
        ofNotifyEvent(goToSceneEvent, sceneToChange, this);
    }
    
}