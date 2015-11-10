//
//  PMSc7Countdown.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 29/10/15.
//
//

#include "PMSc7Countdown.hpp"

PMSc7Countdown::PMSc7Countdown() : PMBaseScene("Scene 7")
{
    
}

void PMSc7Countdown::setup()
{
    countdown.set();
}

void PMSc7Countdown::update()
{
    cout<<(int)countdown.getDiff()/1000<<endl;
}

void PMSc7Countdown::draw()
{
    drawCenteredFont(baseFont, ofToString(5-(int)countdown.getDiff()/1000), ofGetWidth()/2, ofGetHeight()/2);
}
