//
//  PMSongSelector.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 02/11/15.
//
//

#include "PMSongSelector.hpp"

void PMSongSelector::init(ofTrueTypeFont &_font)
{
    originalHeight= DESIGN_HEIGHT;
    originalWidth= DESIGN_WIDTH - DESIGN_LEFT_WIDTH;
	int topOffset = 150;

    indexChoosed=0;
    
    font=&_font;
    
    ofDirectory dir;
    dir.listDir("songs/");
    for(int i = 0; i < (int)dir.size(); i++){
        songFilenames.push_back(dir.getName(i));
    }
    
    int x,y;
    for(int i=0; i<songFilenames.size(); i++){
        //x= originalWidth/2 + DESIGN_LEFT_WIDTH;
		x = DESIGN_LEFT_WIDTH - 150;
		y = ((font->getLineHeight()) * (i+1)) + topOffset;//((originalHeight - topOffset)*(i + 1) / (songFilenames.size() + 1)) + topOffset;
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


void PMSongSelector::resetSize()
{
    for(auto & textScale : textScales)
        textScale=0.5;
}