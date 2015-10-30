//
//  PMSceneManager.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 25/10/15.
//
//

#include "PMSceneManager.hpp"
#include "PMSc1Settings.hpp"
#include "PMSc2Start.hpp"
#include "PMSc3Song_Choose.hpp"
#include "PMSc4Palette_Choose.hpp"
#include "PMSc5Brushes_Choose.hpp"
#include "PMSc6Kinect_Detect.hpp"
#include "PMSc7Countdown.hpp"
#include "PMSc8Main.hpp"

///--------------------------------------------------------------
void PMSceneManager::init()
{
    sceneManager.addScene(ofPtr<ofxScene>(new PMSc1Settings()));
    sceneManager.addScene(ofPtr<ofxScene>(new PMSc2Start()));
    sceneManager.addScene(ofPtr<ofxScene>(new PMSc3Song_Choose()));
    sceneManager.addScene(ofPtr<ofxScene>(new PMSc4Palette_Choose()));
    sceneManager.addScene(ofPtr<ofxScene>(new PMSc5Brushes_Choose()));
    sceneManager.addScene(ofPtr<ofxScene>(new PMSc6Kinect_Detect()));
    sceneManager.addScene(ofPtr<ofxScene>(new PMSc7Countdown()));
    sceneManager.addScene(ofPtr<ofxScene>(new PMSc8Main()));
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
