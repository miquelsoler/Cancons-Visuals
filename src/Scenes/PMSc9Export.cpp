//
//  PMSc9Export.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 30/10/15.
//
//

#include "PMSc9Export.hpp"
#include "PMMotionExtractor.hpp"
#include "PMSharedSettings.h"

PMSc9Export::PMSc9Export() : PMBaseScene("Scene 9")
{
    bigFont.load("fonts/NeutraTextTF-Book.otf", 40, true, true, false, 0.3, 72);
    smallFont.load("fonts/NeutraTextTF-Light.otf", 30, true, true, false, 0.3, 72);
    textInput="";
    setSingleSetup(false);
    originalWidth=1080;
    originalHeight=1920;
}

void PMSc9Export::setup()
{
    painting.load("TempRender.png");
    textInput="";
    ofClear(0,0,0);
    timestamp=ofGetElapsedTimef()-1;
    isSlash=false;
    accentCharacter=0;
}

void PMSc9Export::update()
{
    if(ofGetElapsedTimef()-timestamp>0.7){
        timestamp=ofGetElapsedTimef();
        isSlash=!isSlash;
    }
}

void PMSc9Export::exit()
{
//    PMSharedSettings::getInstance().setUserName(textInput);
}

void PMSc9Export::draw()
{
    PMBaseScene::draw();
    ofPushMatrix();
    float scaleX=(float)ofGetWidth()/(float)originalWidth;
    float scaleY=(float)ofGetHeight()/(float)originalHeight;
    ofScale(scaleX, scaleY);
//    ofBackground(0);
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(ofColor::red);
    ofPopStyle();
    
    ofSetColor(ofColor::white);
    drawCenteredFont(bigFont, "Enhorabona!", originalWidth/2, 145);
    drawCenteredFont(bigFont, "Aquesta és la teva interpretació!", originalWidth/2, 190);
    drawCenteredFont(bigFont, "Si us plau, introdueix el teu nom, prem Enter", originalWidth/2, 265);
    drawCenteredFont(bigFont, "i emporta't una impressió de la teva obra!", originalWidth/2, 315);
    drawCenteredFont(smallFont, "(màxim 25 caràcters)", originalWidth/2, 550);
    drawTextBox(bigFont, textInput, isSlash);
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofNoFill();
    ofSetLineWidth(3);
    ofDrawRectangle(originalWidth/2, 480, 850, 85);
    ofDrawRectangle(originalWidth/2, 1200, originalWidth/1.7, originalHeight/1.7);
    painting.draw(originalWidth/2, 1200, originalWidth/1.7, originalHeight/1.7);
    ofPopStyle();
    ofPopMatrix();
}


void PMSc9Export::drawTextBox(ofTrueTypeFont &font, string s, bool slash)
{
    int halfStringWidth = 0;
    if(s != "") halfStringWidth = font.stringWidth(s)/2;
    if(isSlash){
        bigFont.drawString(textInput, (originalWidth/2)-halfStringWidth, 495);
    }else{
        bigFont.drawString(textInput+'|', (originalWidth/2)-halfStringWidth, 495);
    }
}



void PMSc9Export::keyPressed(ofKeyEventArgs  &keyargs){
    if(keyargs.keycode==91)
        accentCharacter=-1;
    else if(keyargs.keycode == 39)
        accentCharacter=1;
    
    int key=keyargs.key;
    switch(accentCharacter){
        case 0:
        {
            switch (key) {
                case -1:
                case 2304:
                case 2306:
                case 2305:
                    break;
                case OF_KEY_DEL:
                case OF_KEY_BACKSPACE:
                {
                    textInput=textInput.substr(0, textInput.length()-1);
                    break;
                }
                case OF_KEY_RETURN:
                {
                    PMSharedSettings::getInstance().setUserName(textInput);
                    string sceneToChange = "Scene Thanks";
                    ofNotifyEvent(goToSceneEvent, sceneToChange, this);
                    break;
                }
                case 231:
                    textInput+="ç";
                    break;
                case 199:
                    textInput+="Ç";
                    break;
                case 241:
                    textInput+="ñ";
                    break;
                case 209:
                    textInput+="Ñ";
                    break;
                default:
                {
                    textInput.append(1, (char)key);
                    break;
                }
            }
            break;
        }
        case -1:
        {
            switch (key) {
                case -1:
                case 2304:
                case 2306:
                case 2305:
                    break;
                case OF_KEY_DEL:
                case OF_KEY_BACKSPACE:
                {
                    accentCharacter=0;
                    break;
                }
                case OF_KEY_RETURN:
                {
                    PMSharedSettings::getInstance().setUserName(textInput);
                    string sceneToChange = "Scene Thanks";
                    ofNotifyEvent(goToSceneEvent, sceneToChange, this);
                    break;
                }case 'a':
                    textInput+="à";
                    break;
                case 'A':
                    textInput+="À";
                    break;
                case 'e':
                    textInput+="è";
                    break;
                case 'E':
                    textInput+="È";
                    break;
                case 'i':
                    textInput+="ì";
                    break;
                case 'I':
                    textInput+="Ì";
                    break;
                case 'o':
                    textInput+="ò";
                    break;
                case 'O':
                    textInput+="Ò";
                    break;
                case 'u':
                    textInput+="ù";
                    break;
                case 'U':
                    textInput+="Ù";
                    break;
                case 231:
                    textInput+="ç";
                    break;
                case 199:
                    textInput+="Ç";
                    break;
                case 241:
                    textInput+="ñ";
                    break;
                case 209:
                    textInput+="Ñ";
                    break;
                default:
                {
                    textInput.append(1, (char)key);
                    accentCharacter=0;
                    break;
                }
            }
            break;
        }
        case 1: //acent tancat
        {
            switch (key) {
                case -1:
                case 2304:
                case 2306:
                case 2305:
                    break;
                case OF_KEY_DEL:
                case OF_KEY_BACKSPACE:
                {
                    accentCharacter=0;
                    break;
                }
                case OF_KEY_RETURN:
                {
                    PMSharedSettings::getInstance().setUserName(textInput);
                    string sceneToChange = "Scene Thanks";
                    ofNotifyEvent(goToSceneEvent, sceneToChange, this);
                    break;
                }
                case 'a':
                    textInput+="á";
                    break;
                case 'A':
                    textInput+="Á";
                    break;
                case 'e':
                    textInput+="é";
                    break;
                case 'E':
                    textInput+="É";
                    break;
                case 'i':
                    textInput+="í";
                    break;
                case 'I':
                    textInput+="Í";
                    break;
                case 'o':
                    textInput+="ó";
                    break;
                case 'O':
                    textInput+="Ó";
                    break;
                case 'u':
                    textInput+="ú";
                    break;
                case 'U':
                    textInput+="Ú";
                    break;
                case 231:
                    textInput+="ç";
                    break;
                case 199:
                    textInput+="Ç";
                    break;
                case 241:
                    textInput+="ñ";
                    break;
                case 209:
                    textInput+="Ñ";
                    break;
                default:
                {
                    textInput.append(1, (char)key);
                    accentCharacter=0;
                    break;
                }
            }
            break;
        default:
            break;
            
        }
            
    }
    
}


