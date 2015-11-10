//
//  PMSc3Song_Choose.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 29/10/15.
//
//

#include "PMSc3Song_Choose.hpp"
#include "PMSongSelector.hpp"

PMSc3Song_Choose::PMSc3Song_Choose() : PMBaseScene("Scene 3")
{
    setFade(1000, 1000);
}

void PMSc3Song_Choose::setup()
{
//    DIR *dpdf;
//    struct dirent *epdf;
//
//    dpdf = opendir(ofToDataPath("songs/", true).c_str());
//    if(dpdf == NULL){
//        return false;
//    }
//    while((epdf = readdir(dpdf))){
//        if (true){
//            string songname=string(epdf->d_name);
//            if(songname[0]!='.'){
//                songname=songname.substr(0,songname.find_last_of('.'));
//                songNames.push_back(songname);
//            }
//        }
//    }
//    
    selectFont.load("verdana.ttf", 30);
    PMSongSelector::getInstance().init(baseFont, selectFont);
}

void PMSc3Song_Choose::update()
{
    
}

void PMSc3Song_Choose::draw()
{
    ofBackground(0);
    drawSettingsNumbers(1);
    PMSongSelector::getInstance().draw();
    
}

void PMSc3Song_Choose::mouseMoved(int x, int y)
{

    PMSongSelector::getInstance().checkMousePassed(x, y);
}

void PMSc3Song_Choose::mousePressed(int x, int y, int button)
{
    if(PMSongSelector::getInstance().checkMousePressed(x, y)){
        //ofxSceneManager::gotoScene("Scene 4");
    }
}