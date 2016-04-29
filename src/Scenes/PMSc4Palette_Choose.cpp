//
//  PMSc4Palette_Choose.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 29/10/15.
//
//

#include "PMSc4Palette_Choose.hpp"
#include "../UI/PMColorsSelector.hpp"

PMSc4Palette_Choose::PMSc4Palette_Choose() : PMBaseScene("Scene 4")
{
    infoFont.load("fonts/NeutraTextTF-Light.otf", 20, true, true, false, 0.3, 72);
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
    PMBaseScene::draw();
    ofPushMatrix();
    float scaleX=(float)ofGetWidth()/(float)1080;
    float scaleY=(float)ofGetHeight()/(float)1920;
    ofScale(scaleX, scaleY);
//    ofBackground(0);
    drawSettingsNumbers(2);
    drawCenteredFont(baseBoldFont, "Tria els teus colors", 1080/2, 150);
    drawCenteredFont(infoFont, "Fons", 180, 290);
    drawCenteredFont(infoFont, "Mà dreta", 360, 290);
    drawCenteredFont(infoFont, "Mà esquerra", 540, 290);
    drawCenteredFont(infoFont, "Cap", 720, 290);
    drawCenteredFont(infoFont, "Tors", 900, 290);
    PMColorsSelector::getInstance().draw();
    ofPopMatrix();
}

void PMSc4Palette_Choose::mouseMoved(int x, int y)
{
    float scaleX=(float)ofGetWidth()/(float)1080;
    float scaleY=(float)ofGetHeight()/(float)1920;
    x/=scaleX;
    y/=scaleY;
    PMColorsSelector::getInstance().checkMousePassed(x, y);
}

void PMSc4Palette_Choose::mousePressed(int x, int y, int mouse)
{
    float scaleX=(float)ofGetWidth()/(float)1080;
    float scaleY=(float)ofGetHeight()/(float)1920;
    x/=scaleX;
    y/=scaleY;
    if(PMColorsSelector::getInstance().checkMousePressed(x, y)){
        string sceneToChange="Scene 5";
        ofNotifyEvent(goToSceneEvent, sceneToChange, this);
    }

}
