//
//  PMSongSelector.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 02/11/15.
//
//

#include "PMSongSelector.hpp"
#include "dirent.h"

void PMSongSelector::init(ofTrueTypeFont &_font)
{
    originalHeight=1920;
    originalWidth=1080;
    
    indexChoosed=0;
    
    font=&_font;
    
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
                songFilenames.push_back(songname);
            }
        }
    }
    
    int x,y;
    for(int i=0; i<songFilenames.size(); i++){
        x=originalWidth/2;
        y=((originalHeight-150)*(i+1)/(songFilenames.size()+1))+150;
        songNamesBox.push_back(PMTextContainer(x, y, songFilenames[i].substr(0, songFilenames[i].find_last_of('.')), *font, 0.5));
    }
    
    for(int i=0; i<songFilenames.size(); i++){
        ofxTimer tempTimer=ofxTimer();
        tempTimer.set();
        timers.push_back(tempTimer);
        textScales.push_back(0.5);
        selectedText.push_back(false);
    }
}

void PMSongSelector::update()
{
    for(int i=0; i<timers.size(); i++){
        if(timers[i].getDiff()<250 && selectedText[i]){
            textScales[i]=0.5+((float)timers[i].getDiff()/500);
        }
        if(!selectedText[i]){
            textScales[i]=0.5;
        }
    }
}

void PMSongSelector::draw()
{
    for(int i=0; i<songNamesBox.size(); i++){
        songNamesBox[i].draw(textScales[i]);
    }
    
}

void PMSongSelector::checkMousePassed(int x, int y)
{
    for(int i=0; i<songNamesBox.size(); i++){
        int x1=songNamesBox[i].getX()-songNamesBox[i].getWidth()/2;
        int x2=songNamesBox[i].getX()+songNamesBox[i].getWidth()/2;
        int y1=songNamesBox[i].getY()-songNamesBox[i].getHeight()/2;
        int y2=songNamesBox[i].getY()+songNamesBox[i].getHeight()/2;
        if(x>=x1 && x<=x2 && y>=y1 && y<=y2){
            if(!selectedText[i]){
                timers[i].set();
                selectedText[i]=true;
            }
        }else{
            selectedText[i]=false;
        }
    }
}

bool PMSongSelector::checkMousePressed(int x, int y)
{
    for(int i=0; i<songNamesBox.size(); i++){
        int x1=songNamesBox[i].getX()-songNamesBox[i].getWidth()/2;
        int x2=songNamesBox[i].getX()+songNamesBox[i].getWidth()/2;
        int y1=songNamesBox[i].getY()-songNamesBox[i].getHeight()/2;
        int y2=songNamesBox[i].getY()+songNamesBox[i].getHeight()/2;
        if(x>=x1 && x<=x2 && y>=y1 && y<=y2){
            indexChoosed=i;
            return true;
        }
    }
    return false;
}