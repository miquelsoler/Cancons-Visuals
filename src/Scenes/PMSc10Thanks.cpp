//
//  PMSc10Thanks.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 30/10/15.
//
//

#include "PMSc10Thanks.hpp"

#include "PMSharedSettings.h"

PMSc10Thanks::PMSc10Thanks() : PMBaseScene("Scene Thanks")
{
    plantilla.load("escena10.jpg");
    bigFont.load("fonts/NeutraTextTF-Book.otf", 40, true, true, false, 0.3, 72);
    smallFont.load("fonts/NeutraTextTF-Light.otf", 35, true, true, false, 0.3, 72);
    originalWidth=1080;
    originalHeight=1920;
    
}

void PMSc10Thanks::setup()
{
    ofClear(0,0,0);
    print_testImage.load("assets/export_plantilla.jpg");
    printFbo.allocate(1181, 1772, GL_RGB);
    drawIntoFbo();

    // Edu:

    // Aquí hi haurà el codi de generació de FBO que servirà per imprimir

    // Després el de pillar el nom
    string userName = PMSharedSettings::getInstance().getUserName();

    // I després el d'imprimir (la comanda és: lp -o media=Custom.10x15cm filename)
}

void PMSc10Thanks::update()
{
}

void PMSc10Thanks::draw()
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
//    plantilla.draw(0,0, ofGetWidth(), ofGetHeight());
    ofPopStyle();
    
    ofSetColor(ofColor::white);
//    ofDrawBitmapString("Current X: "+ofToString(ofGetMouseX())+"  Y: "+ofToString(ofGetMouseY()), 15, 28);
    drawCenteredFont(bigFont, "Imprimint", originalWidth/2, 462);
    drawCenteredFont(bigFont, "Moltes gràcies!", originalWidth/2, 508);
    drawCenteredFont(bigFont, "Cançons Visuals", originalWidth/2, 938);
    drawCenteredFont(smallFont, "www.xavibove.com", originalWidth/2, 988);
    ofPopMatrix();
//    printFbo.draw(0,0, printFbo.getWidth(), printFbo.getHeight());
    printFbo.draw(0,0);
    ofSetColor(ofColor::black);
    ofDrawBitmapString("Current X: "+ofToString(ofGetMouseX())+"  Y: "+ofToString(ofGetMouseY()), 15, 28);
}


void PMSc10Thanks::drawIntoFbo()
{
    printFbo.begin();
    {
        print_testImage.draw(0,0, printFbo.getWidth(), printFbo.getHeight());
        ofSetColor(ofColor::black);
        ofPushStyle();
        ofSetRectMode(OF_RECTMODE_CORNER);
        ofNoFill();
        ofSetLineWidth(3);
        ofDrawRectangle(150, 40, 878, originalHeight/1.7);
//    painting.draw(originalWidth/2, 1200, originalWidth/1.7, originalHeight/1.7);
        ofPopStyle();
    }
    printFbo.end();
}