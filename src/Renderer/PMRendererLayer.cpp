//
//  PMRendererLayer.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 30/11/15.
//
//

#include "PMRendererLayer.hpp"


PMRendererLayer::PMRendererLayer(int _layer) : PMBaseRenderer(_layer)
{
    
}

void PMRendererLayer::setup()
{
    PMBaseRenderer::setup();
    brush->update(ofRandom((ofGetWidth())), ofRandom(ofGetHeight()));
}

void PMRendererLayer::update()
{
    PMBaseRenderer::update();
    brush->update(ofRandom((ofGetWidth())), ofRandom(ofGetHeight()));
}

void PMRendererLayer::draw()
{
    PMBaseRenderer::draw();
//    ofSetColor(drawColor);
//    brush->draw();
}

void PMRendererLayer::drawIntoFBO()
{
    fbo.begin();
//    ofDisableBlendMode();
//        ofSetColor(255,0,0);
//        ofDrawRectangle(0, 0, fbo.getWidth(), fbo.getHeight());
        ofSetColor(drawColor);
        brush->draw();
    fbo.end();
    
    ofSetColor(255, 255, 255, 255);
}