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
    position=ofPoint(0,0);
}

void PMRendererLayer::setup()
{
    PMBaseRenderer::setup();
    brush->update(position.x, position.y);
}

void PMRendererLayer::update()
{
    PMBaseRenderer::update();
    brush->update(position.x, position.y);
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
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
//        ofSetColor(255,0,0);
//        ofDrawRectangle(0, 0, fbo.getWidth(), fbo.getHeight());
        ofSetColor(drawColor);
        brush->draw();
    ofDisableBlendMode();
    fbo.end();
    
    ofSetColor(255, 255, 255, 255);
}

void PMRendererLayer::setPosition(ofPoint newPos)
{
    position=newPos;
    
}