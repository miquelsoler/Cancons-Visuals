//
//  PMSc5Brushes_Choose.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 29/10/15.
//
//

#include "PMSc5Brushes_Choose.hpp"
#include "../UI/PMBrushesSelector.hpp"

PMSc5Brushes_Choose::PMSc5Brushes_Choose() : PMBaseScene("Scene 5")
{
    PMBrushesSelector::getInstance().init();
    setSingleSetup(false);
    infoFont.load("fonts/NeutraTextTF-Light.otf", 20, true, true, false, 0.3, 72);
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
    PMBaseScene::draw();
    ofPushMatrix();
    float scaleX=(float)ofGetWidth()/(float)1080;
    float scaleY=(float)ofGetHeight()/(float)1920;
    ofScale(scaleX, scaleY);
//    ofBackground(0);
    drawSettingsNumbers(3);
    drawCenteredFont(baseBoldFont, "Tria els teus pinzells", 1080/2, 150);
    drawCenteredFont(infoFont, "Mà dreta", 220, 245);
    drawCenteredFont(infoFont, "Mà esquerra", 435, 245);
    drawCenteredFont(infoFont, "Cap", 650, 245);
    drawCenteredFont(infoFont, "Tors", 865, 245);
    PMBrushesSelector::getInstance().draw();
    ofPopMatrix();
}

void PMSc5Brushes_Choose::mouseMoved(int x, int y)
{
    float scaleX=(float)ofGetWidth()/(float)1080;
    float scaleY=(float)ofGetHeight()/(float)1920;
    x/=scaleX;
    y/=scaleY;
    PMBrushesSelector::getInstance().checkMousePassed(x, y);
}

void PMSc5Brushes_Choose::mousePressed(int x, int y, int mouse)
{
    float scaleX=(float)ofGetWidth()/(float)1080;
    float scaleY=(float)ofGetHeight()/(float)1920;
    x/=scaleX;
    y/=scaleY;
    if(PMBrushesSelector::getInstance().checkMousePressed(x, y)){
        string sceneToChange="Scene 6";
        ofNotifyEvent(goToSceneEvent, sceneToChange, this);
    }
    
}