//
//  PMSc4Palette_Choose.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 29/10/15.
//
//

#include "PMSc4Palette_Choose.hpp"
#include "PMSongSelector.hpp"
#include "../UI/PMColorsSelector.hpp"

PMSc4Palette_Choose::PMSc4Palette_Choose() : PMBaseScene("Scene 4")
{
    infoFont.load("fonts/NeutraTextTF-Light.otf", 20, true, true, false, 0.3, 72);
	backgroundImage.load("assets/cartela_colors.png");
}

void PMSc4Palette_Choose::setup()
{
    PMColorsSelector::getInstance().init(baseFont);
}

void PMSc4Palette_Choose::update()
{
	if (!isEntering()) {
		PMColorsSelector::getInstance().update();
	}
}

void PMSc4Palette_Choose::draw()
{
    PMBaseScene::draw();
    ofPushMatrix();
	ofMultMatrix(*homography);

	backgroundImage.draw(0, 0, DESIGN_WIDTH, DESIGN_HEIGHT);
//    ofBackground(0);
    //drawSettingsNumbers(2);
    //drawCenteredFont(baseBoldFont, "Tria els teus colors", DESIGN_WIDTH/2, 150);
    //drawCenteredFont(infoFont, "Fons", 315, 215);
    //drawCenteredFont(infoFont, "Mà dreta", 640, 215);
    //drawCenteredFont(infoFont, "Mà esquerra", 960, 215);
    //drawCenteredFont(infoFont, "Genoll dret", 1275, 215);
    //drawCenteredFont(infoFont, "Genoll esquerra", 1600, 215);
    PMColorsSelector::getInstance().draw();
    ofPopMatrix();
}

void PMSc4Palette_Choose::mouseMoved(int x, int y)
{
	ofVec3f pos = ofVec3f(x, y);
	pos = pos*(homography->getInverse());

    PMColorsSelector::getInstance().checkMousePassed(pos.x, pos.y);
}

void PMSc4Palette_Choose::mousePressed(int x, int y, int mouse)
{
	//Warp via homography;
	ofVec3f pos = ofVec3f(x, y);
	pos = pos*(homography->getInverse());

    if(PMColorsSelector::getInstance().checkMousePressed(pos.x, pos.y)){
        string sceneToChange="Scene 6";
        ofNotifyEvent(goToSceneEvent, sceneToChange, this);
    }
}
