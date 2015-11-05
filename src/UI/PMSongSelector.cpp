//
//  PMSongSelector.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 02/11/15.
//
//

#include "PMSongSelector.hpp"
#include "dirent.h"

void PMSongSelector::init(ofTrueTypeFont &_font, ofTrueTypeFont &_boldFont)
{
    font=&_font;
    boldFont=&_boldFont;
    
    
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
        x=ofGetWidth()/2;
        y=((ofGetHeight()-150)*(i+1)/(songFilenames.size()+1))+150;
        songNamesBox.push_back(PMTextContainer(x, y, songFilenames[i].substr(0, songFilenames[i].find_last_of('.')), *font));
    }
}

void PMSongSelector::update()
{
    
}

void PMSongSelector::draw()
{
    for(int i=0; i<songNamesBox.size(); i++){
        songNamesBox[i].draw();
        cout<<"drawing"<<i<<endl;
    }
    
}

void PMSongSelector::checkMousePassed(int x, int y)
{
    for(int i=0; i<songNamesBox.size(); i++){
        int x1=songNamesBox[i].getX()-songNamesBox[i].getWidth();
        int x2=songNamesBox[i].getX()+songNamesBox[i].getWidth();
        int y1=songNamesBox[i].getY()-songNamesBox[i].getHeight();
        int y2=songNamesBox[i].getY()+songNamesBox[i].getHeight();
        if(x>=x1 && x<=x2 && y>=y1 && y<=y2){
            songNamesBox[i].setFont(*boldFont);
        }else{
            songNamesBox[i].setFont(*font);
        }
    }
}

string PMSongSelector::checkMousePressed(int x, int y)
{
    
}