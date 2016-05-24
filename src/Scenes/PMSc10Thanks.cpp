//
//  PMSc10Thanks.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 30/10/15.
//
//

#include "PMSc10Thanks.hpp"
#include "PMSongSelector.hpp"
#include "PMSharedSettings.h"
#include "PMMotionExtractor.hpp"

const static int COUNTDOWN_TIME = 15;

PMSc10Thanks::PMSc10Thanks() : PMBaseScene("Scene Thanks")
{
    bigFont.load("fonts/NeutraTextTF-Book.otf", 28, true, true, false, 0.3, 72);
    smallFont.load("fonts/NeutraTextTF-Light.otf", 29, true, true, false, 0.3, 72);
    smallestFont.load("fonts/NeutraTextTF-Light.otf", 21, true, true, false, 0.3, 72);
    originalWidth = 1080;
    originalHeight = 1920;
    setSingleSetup(false);
    songName = "\"Walürenritt\" Richard Wagner";
    dateName = "12/12/2015, 13:13";
    userName = "Interpretat per Xavi Bové";
}

void PMSc10Thanks::setup()
{
    //Primer ha de pillar el nom, sino No es pot generar l'fbo
    songName = PMSongSelector::getInstance().getSongname();
    userName = "Interpretat per " + PMSharedSettings::getInstance().getUserName();
    dateName = ofGetTimestampString("%d/%m/%Y, %H:%M");
    //carrega la imatge, alloca el fbo i genera fbo
    ofClear(0, 0, 0);
    printImage.load("TempRender.png");
    printFbo.allocate(1181, 1772, GL_RGB);
    drawIntoFbo();
    //exportem fbo i el guardem
    ofPixels pix;
    printFbo.readToPixels(pix);
//    ofSaveImage(pix, "toPrint.png", OF_IMAGE_QUALITY_BEST);
    ofStringReplace(songName, " ", "_");
    ofStringReplace(userName, " ", "_");
    ofStringReplace(dateName, " ", "_");
    ofStringReplace(dateName, "/", "_");
//    string saveFilename= "exports/toprint/"+songName+"-"+userName+"_"+dateName+".png";
//    cout<<songName<<"     "<<userName<<"       "<<dateName<<"         "<<saveFilename<<endl;
    string saveFilename = "exports/toprint/toPrint_" + ofGetTimestampString() + ".png";
    ofSaveImage(pix, saveFilename, OF_IMAGE_QUALITY_BEST);

    //imprimir fbo.

#if ENABLE_PRINTING
    string c = "lp -o media=Custom.4x6in -o page-left=0 -o page-right=0 -o page-top=0 -o page-bottom=0 " + ofToDataPath(saveFilename);
    system(c.c_str());
#endif

    countdown.set();
    countdown.setAlarm(COUNTDOWN_TIME * 1000);
    
    count=0;
}

void PMSc10Thanks::exit()
{
//    printFbo.unbind();
}

void PMSc10Thanks::update()
{
    if (countdown.alarm()) {
        countdown.resetAlarm();
        string toScene = "Scene 2";
        ofNotifyEvent(goToSceneEvent, toScene, this);
    }
#if ENABLE_KINECT
    if(count==2){
        PMMotionExtractor::getInstance().exit();
    }else if(count==60){
        PMMotionExtractor::getInstance().setup();
    }
#endif
    count++;
}

void PMSc10Thanks::draw()
{
    PMBaseScene::draw();
    ofPushMatrix();
    float scaleX = (float) ofGetWidth() / (float) originalWidth;
    float scaleY = (float) ofGetHeight() / (float) originalHeight;
    ofScale(scaleX, scaleY);
//    ofBackground(0);
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(ofColor::red);
//    plantilla.draw(0,0, ofGetWidth(), ofGetHeight());
    ofPopStyle();

    ofSetColor(ofColor::white);
//    ofDrawBitmapString("Current X: "+ofToString(ofGetMouseX())+"  Y: "+ofToString(ofGetMouseY()), 15, 28);
    drawCenteredFont(bigFont, "Imprimint", originalWidth / 2, 462);
    drawCenteredFont(bigFont, "Moltes gràcies!", originalWidth / 2, 508);
    drawCenteredFont(bigFont, "Cançons Visuals", originalWidth / 2, 938);
    drawCenteredFont(smallFont, "www.xavibove.com", originalWidth / 2, 988);
    ofPopMatrix();
//    printFbo.draw(0,0, printFbo.getWidth(), printFbo.getHeight());
//    printFbo.draw(0,0);
    ofSetColor(ofColor::black);
//    ofDrawBitmapString("Current X: "+ofToString(ofGetMouseX())+"  Y: "+ofToString(ofGetMouseY()), 15, 28);
}


void PMSc10Thanks::drawIntoFbo()
{
    printFbo.begin();
    {
        ofClear(255);
//        ofSetColor(ofColor::red);
//        print_testImage.draw(0,0, printFbo.getWidth(), printFbo.getHeight());
        ofSetColor(ofColor::black);
        ofPushStyle();
        ofSetRectMode(OF_RECTMODE_CORNER);
        ofNoFill();
        ofSetLineWidth(3);
//        ofDrawRectangle(151, 40, 873, 1552);
        drawRightAlignString(bigFont, songName, 1024, 1633);
        drawRightAlignString(bigFont, userName, 1024, 1675);
        drawRightAlignString(smallFont, dateName, 1024, 1716);
//        drawLeftAlignString(smallFont, dateName, 151, 1633);
        ofPushMatrix();
        ofTranslate(1047, 349);
        ofRotateZ(-90);
        smallestFont.drawString("cançons visuals - www.xavibove.com", 0, 0);
        ofPopMatrix();
        ofSetColor(255);
        printImage.draw(151, 40, 873, 1552);
        ofPopStyle();
    }
    printFbo.end();
}


void PMSc10Thanks::drawRightAlignString(ofTrueTypeFont &font, string s, int x, int y)
{
    int halfStringHeight = font.stringHeight(s) / 2;
    int stringWidth = font.stringWidth(s);
    font.drawString(s, x - stringWidth, y + halfStringHeight);
}

void PMSc10Thanks::drawLeftAlignString(ofTrueTypeFont &font, string s, int x, int y)
{
    int halfStringHeight = font.stringHeight(s) / 2;
    font.drawString(s, x, y + halfStringHeight);
}

void PMSc10Thanks::keyPressed(ofKeyEventArgs &keyargs){
#ifdef OF_DEBUG
    if(keyargs.key == ' '){
        string sceneToChange = "Scene 2";
        ofNotifyEvent(goToSceneEvent, sceneToChange, this);
    }
#endif
}