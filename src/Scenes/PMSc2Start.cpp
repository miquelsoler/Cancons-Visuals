//
//  PMSc2Start.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 30/10/15.
//
//

#include "PMSc2Start.hpp"

PMSc2Start::PMSc2Start() : PMBaseScene("Scene 2")
{
    //setFade(1000, 1000);
    setFadeIn(1000);
}

void PMSc2Start::setup()
{
    textBoxes.push_back(PMTextContainer(ofGetWidth()/2, ofGetHeight()/10,"Cançons Visuals", baseFont));
    
}

void PMSc2Start::update()
{
    
}

void PMSc2Start::draw()
{
    for(int i=0; i<textBoxes.size(); i++){
        //textBoxes[i].draw();
        ofSetColor(255);
        ofDrawCircle(200, 100, 20);
    }
}