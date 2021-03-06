//
//  PMBaseScene.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 20/10/15.
//
//

#include "PMBaseScene.hpp"

///--------------------------------------------------------------
PMBaseScene::PMBaseScene(const string &name) : ofxFadeScene(name)
{
//    baseFont.load(OF_TTF_SANS, 20, true, true, false, 0.3, 72);
    baseFont.load("fonts/NeutraTextTF-Light.otf", 30, true, true, false, 0.3, 72);
    baseBoldFont.load("fonts/NeutraTextTF-Book.otf", 50, true, true, false, 0.3, 72);
    numberFont.load("fonts/NeutraTextTF-Light.otf", 110, true, true, false, 0.3, 72);
    numberBoldFont.load("fonts/NeutraTextTF-Book.otf", 110, true, true, false, 0.3, 72);

    // Disable fades
    //this->setSceneDuration(0.2, 0.2);
    setFade(0, 0);

    backgroundColor = ofColor::green;
    backgroundImage.load("assets/background.png");
}

///--------------------------------------------------------------
void PMBaseScene::draw()
{
    ofClear(backgroundColor);
    ofPushStyle();
    ofSetColor(255);
    backgroundImage.draw(0,0, ofGetWidth(), ofGetHeight());
    ofPopStyle();
}

void PMBaseScene::updateEnter()
{
    ofxFadeScene::updateEnter();
}

void PMBaseScene::updateExit()
{
    ofxFadeScene::updateExit();
}

void PMBaseScene::drawCenteredFont(ofTrueTypeFont &font, string s, int x, int y)
{
    int halfStringHeight = font.stringHeight(s)/2;
    int halfStringWidth = font.stringWidth(s)/2;
    font.drawString(s, x-halfStringWidth, y+halfStringHeight);
}






void PMBaseScene::drawSettingsNumbers(int currentNumber)
{
    int numHeight=numberFont.getLineHeight();
    int originalWidth=1080;
    
    //settings number
    ofPoint numberPos;
    numberPos.x=originalWidth/4;
    numberPos.y=50;
    //draw number
    if(currentNumber==1){
        drawCenteredFont(numberBoldFont, "1", numberPos.x, numberPos.y);
    }else{
        drawCenteredFont(numberFont, "1", numberPos.x, numberPos.y);
    }
    //draw line
    if(currentNumber==1){
        ofSetLineWidth(5);
    }else{
        ofSetLineWidth(1);
    }
    ofDrawLine(numberPos.x-numHeight, numberPos.y+numHeight/2, numberPos.x+numHeight, numberPos.y+numHeight/2);
    
    
    //settings number
    numberPos.x=originalWidth/2;
    numberPos.y=50;
    //draw number
    if(currentNumber==2){
        drawCenteredFont(numberBoldFont, "2", numberPos.x, numberPos.y);
    }else{
        drawCenteredFont(numberFont, "2", numberPos.x, numberPos.y);
    }
    //draw line
    if(currentNumber==2){
        ofSetLineWidth(5);
    }else{
        ofSetLineWidth(1);
    }
    ofDrawLine(numberPos.x-numHeight, numberPos.y+numHeight/2, numberPos.x+numHeight, numberPos.y+numHeight/2);
    
    
    
    //settings number
    numberPos.x=originalWidth*3/4;
    numberPos.y=50;
    //draw number
    if(currentNumber==3){
        drawCenteredFont(numberBoldFont, "3", numberPos.x, numberPos.y);
    }else{
        drawCenteredFont(numberFont, "3", numberPos.x, numberPos.y);
    }
    //draw line
    if(currentNumber==3){
        ofSetLineWidth(5);
    }else{
        ofSetLineWidth(1);
    }
    ofDrawLine(numberPos.x-numHeight, numberPos.y+numHeight/2, numberPos.x+numHeight, numberPos.y+numHeight/2);
}