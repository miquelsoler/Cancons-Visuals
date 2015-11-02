//
//  PMSc3Song_Choose.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 29/10/15.
//
//

#include "PMSc3Song_Choose.hpp"

void PMSc3Song_Choose::setup()
{
    DIR *dpdf;
    struct dirent *epdf;

    dpdf = opendir(ofToDataPath("songs/", true).c_str());
    if(dpdf == NULL){
        return false;
    }
    while((epdf = readdir(dpdf))){
        if (true){
            string songname=string(epdf->d_name);
            if(songname[0]!='.'){
                songname=songname.substr(0,songname.find_last_of('.'));
                songNames.push_back(songname);
            }
        }
    }
    
    selectFont.load("verdana.ttf", 30);
}

void PMSc3Song_Choose::update()
{
    
}

void PMSc3Song_Choose::draw()
{
    ofBackground(0);
    drawSettingsNumbers(1);
    
    for(int i=0; i<songNames.size(); i++){
        if(pseudoSelectedSong==i){
            drawCenteredFont(selectFont, songNames[i], ofGetWidth()/2, ((ofGetHeight()-100)*(i+1)/(songNames.size()+1))+100);
        }else{
            drawCenteredFont(baseFont, songNames[i], ofGetWidth()/2, ((ofGetHeight()-100)*(i+1)/(songNames.size()+1))+100);
        }
    }
    
}

void PMSc3Song_Choose::mouseMoved(int x, int y)
{
    bool assigned=false;
    for(int i=0; i<songNames.size(); i++){
        int x1=ofGetWidth()/2-(baseFont.stringWidth(songNames[i])/2);
        int x2=ofGetWidth()/2+(baseFont.stringWidth(songNames[i])/2);
        int y1=((ofGetHeight()-100)*(i+1)/(songNames.size()+1))+100-(baseFont.stringHeight(songNames[i])/2);
        int y2=((ofGetHeight()-100)*(i+1)/(songNames.size()+1))+100+(baseFont.stringHeight(songNames[i])/2);
        if(x>=x1 && x<=x2 && y>=y1 && y<=y2){
            pseudoSelectedSong=i;
            assigned=true;
        }
    }
    if(!assigned){
        pseudoSelectedSong=-1;
    }
    cout<<pseudoSelectedSong<<endl;
}

void PMSc3Song_Choose::mousePressed(int x, int y, int button)
{
    for(int i=0; i<songNames.size(); i++){
        int x1=ofGetWidth()/2-(baseFont.stringWidth(songNames[i])/2);
        int x2=ofGetWidth()/2+(baseFont.stringWidth(songNames[i])/2);
        int y1=((ofGetHeight()-100)*(i+1)/(songNames.size()+1))+100-(baseFont.stringHeight(songNames[i])/2);
        int y2=((ofGetHeight()-100)*(i+1)/(songNames.size()+1))+100+(baseFont.stringHeight(songNames[i])/2);
        if(x>=x1 && x<=x2 && y>=y1 && y<=y2){
            PMSceneManager::getInstance().changeScene();
        }
    }
}