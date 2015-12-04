//
// Created by Miquel Àngel Soler on 4/12/15.
//

#include "PMRenderer.h"

PMRenderer::PMRenderer()
{
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA32F_ARB);
}

void PMRenderer::setup()
{
    fbo.begin();
    {
        // Often the FBO will contain artifacts from the memory that the graphics card has just allocated for it,
        // so it's good to clear it before starting to draw it
        ofClear(0, 0, 0, 0);
    }
    fbo.end();
}

void PMRenderer::update()
{
    fbo.begin();
    {
        // background dimming
        //ofFloatColor fc = ofFloatColor(0.0, 0.0, 0.0, gui->getFadeBackground());
        ofFloatColor fc = ofFloatColor(1.0, 1.0, 1.0, 1);
        //ofFloatColor fc = ofFloatColor(gui->getColorBackground().r,gui->getColorBackground().g,gui->getColorBackground().b,gui->getFadeBackground());
        ofSetColor(fc);

        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        ofDrawRectangle(0, 0, fbo.getWidth(), fbo.getHeight());
        ofDisableBlendMode();
    }
    fbo.end();

    drawIntoFBO();
}

void PMRenderer::draw()
{
    ofClear(ofColor::white);

//    ofColor c = ofColor(ofColor::white);
//    ofClear(c);
    ofSetColor(255);
    fbo.draw(0,0);
}

void PMRenderer::addLayer(PMBaseLayer *layer)
{
    layers.push_back(layer);
}

void PMRenderer::drawIntoFBO()
{
    fbo.begin();
    {
//        for (int i=0; i<layers.size(); ++i)
//            layers[i]->draw();
    }
    fbo.end();
}
