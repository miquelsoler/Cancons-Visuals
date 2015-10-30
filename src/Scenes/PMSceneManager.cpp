//
//  PMSceneManager.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 25/10/15.
//
//

#include "PMSceneManager.hpp"
#include "PMSc1Settings.hpp"
#include "PMSc2Song_Choose.hpp"
#include "PMSc4Brushes_Choose.hpp"
#include "PMSc3Palette_Choose.hpp"
#include "PMSc5Countdown.hpp"
#include "PMSc6Main.hpp"

///--------------------------------------------------------------
void PMSceneManager::init()
{
    sceneManager.addScene(ofPtr<ofxScene>(new PMSc1Settings));
    sceneManager.addScene(ofPtr<ofxScene>(new PMSc2Song_Choose));
    sceneManager.addScene(ofPtr<ofxScene>(new PMSc4Brushes_Choose));
    sceneManager.addScene(ofPtr<ofxScene>(new PMSc3Palette_Choose));
    sceneManager.addScene(ofPtr<ofxScene>(new PMSc5Countdown));
    sceneManager.addScene(ofPtr<ofxScene>(new PMSc6Main));
    sceneManager.run();
}

///--------------------------------------------------------------
void PMSceneManager::update()
{
    sceneManager.update();
}

///--------------------------------------------------------------
void PMSceneManager::draw()
{
    sceneManager.draw();
}

///--------------------------------------------------------------
void PMSceneManager::changeScene()
{
    sceneManager.changeScene();
}
