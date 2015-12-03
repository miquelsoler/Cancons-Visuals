//
//  PMBaseRenderer.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 30/11/15.
//
//

#include "PMBaseRenderer.hpp"


PMBaseRenderer::PMBaseRenderer(int _layer)
{
    layer=_layer;
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F_ARB);
//    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
}

void PMBaseRenderer::setup()
{
    fbo.begin();
    {
        // Often the FBO will contain artifacts from the memory that the graphics card has just allocated for it,
        // so it's good to clear it before starting to draw it
        ofClear(0, 0, 0, 0);
    }
    fbo.end();
    brush = PMBrushesSelector::getInstance().getBrush(layer);
    drawColor = PMColorsSelector::getInstance().getColor(layer);
}

void PMBaseRenderer::update()
{
    fbo.begin();
    {
        // background dimming
        //ofFloatColor fc = ofFloatColor(0.0, 0.0, 0.0, gui->getFadeBackground());
        ofFloatColor fc = ofFloatColor(0.0, 0.0, 0.0, 1);
        //ofFloatColor fc = ofFloatColor(gui->getColorBackground().r,gui->getColorBackground().g,gui->getColorBackground().b,gui->getFadeBackground());
        ofSetColor(fc);
        
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
//        ofDrawRectangle(0, 0, fbo.getWidth(), fbo.getHeight());
    }
    fbo.end();
    drawIntoFBO();
}

void PMBaseRenderer::draw()
{
//    ofColor c = ofColor(ofColor::white);
//    ofClear(c);
    fbo.draw(0,0);
}

