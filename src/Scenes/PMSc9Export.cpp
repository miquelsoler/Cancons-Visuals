//
//  PMSc9Export.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 30/10/15.
//
//

#include "PMSc9Export.hpp"
#include "PMMotionExtractor.hpp"

PMSc9Export::PMSc9Export() : PMBaseScene("Scene 9")
{
    plantilla.load("escena9.jpg");
    bigFont.load("fonts/NeutraTextTF-Book.otf", 30, true, true, false, 0.3, 72);
    smallFont.load("fonts/NeutraTextTF-Light.otf", 50, true, true, false, 0.3, 72);

}

void PMSc9Export::setup()
{
    ofClear(0,0,0);
}

void PMSc9Export::update()
{
    
}

void PMSc9Export::draw()
{
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(ofColor::red);
    plantilla.draw(0,0, ofGetWidth(), ofGetHeight());
    ofPopStyle();
    ofSetColor(ofColor::white);
    ofDrawBitmapString("Current X: "+ofToString(ofGetMouseX())+"  Y: "+ofToString(ofGetMouseY()), 15, 28);
    
    drawCenteredFont(bigFont, "Enhorabona!", ofGetWidth()/2, 145);
    drawCenteredFont(bigFont, "Aquesta és la teva interpretació!", ofGetWidth()/2, 190);
    drawCenteredFont(bigFont, "Si us plau, introdueix el teu nom", ofGetWidth()/2, 275);
    drawCenteredFont(bigFont, "i emporta't una impressió de la teva obra!", ofGetWidth()/2, 325);
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofNoFill();
    ofDrawRectangle(ofGetWidth()/2, 455, 850, 85);
    ofPopStyle();
}
