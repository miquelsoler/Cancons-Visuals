//
// Created by Miquel Àngel Soler on 4/12/15.
//

#include "PMLayer1.h"

PMLayer1::PMLayer1(int _fboWidth, int _fboHeight) : PMBaseLayer(_fboWidth, _fboHeight)
{
    layerID=1;
}

void PMLayer1::setup()
{
    PMBaseLayer::setup();
    position=ofPoint(ofRandom(fboWidth), ofRandom(fboHeight));
    direction=ofPoint(0,0);
    size=ofRandom(20, 50);
    alpha=1;
    angle=0;
}


void PMLayer1::update()
{
    PMBaseLayer::update();
    if(PMMotionExtractor::getInstance().isReady()){
        kinectNodeData=PMMotionExtractor::getInstance().getKinectInfo()->rightHand_joint;
    }else{
        kinectNodeData.x=(float)ofGetMouseX()/ofGetWidth();
        kinectNodeData.y=(float)ofGetMouseY()/ofGetHeight();
        kinectNodeData.v=ofPoint(0,0);
    }
    //direction changes
    ofPoint newdirection=ofPoint(kinectNodeData.x*fboWidth, kinectNodeData.y*fboHeight)-position;
    direction+=(newdirection.normalize());
    direction.normalize();
    direction+=(kinectNodeData.v.normalize());
    direction.normalize();
    position+=(direction*10);
    brush->update(position.x, position.y);
}

void PMLayer1::draw()
{
    PMBaseLayer::draw();
//    ofSetColor(drawColor);
//    brush->draw();
}

#pragma mark - Audio Events

void PMLayer1::pitchChanged(pitchParams &pitchParams)
{
    
}

void PMLayer1::energyChanged(energyParams &energyParams)
{
    
}

void PMLayer1::silenceStateChanged(silenceParams &silenceParams)
{
    
}

void PMLayer1::pauseStateChanged(pauseParams &pauseParams)
{
    
}

void PMLayer1::onsetDetected(onsetParams &onsetParams)
{
}

void PMLayer1::shtDetected(shtParams &shtParams)
{
    
}

void PMLayer1::melodyDirection(melodyDirectionParams &melodyDirectionParams)
{
    
}

void PMLayer1::melBandsChanged(melBandsParams &melBandsParams)
{
    
}