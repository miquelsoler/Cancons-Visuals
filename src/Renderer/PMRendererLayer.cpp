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
}

void PMRendererLayer::update()
{
    PMBaseRenderer::update();
    brush->update(ofRandom((ofGetWidth())), ofRandom(ofGetHeight()));
}

void PMRendererLayer::draw()
{
    PMBaseRenderer::draw();
}

void PMRendererLayer::drawIntoFBO()
{
    fbo.begin();
    ofSetColor(255,0,0);
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        ofSetColor(drawColor);
        brush->draw();
    fbo.end();
}