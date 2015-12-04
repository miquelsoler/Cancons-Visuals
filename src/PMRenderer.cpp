//
// Created by Miquel Àngel Soler on 4/12/15.
//

#include "PMRenderer.h"
#include "PMLayer1.h"
#include "PMLayer2.h"
#include "PMLayer3.h"
#include "PMLayer4.h"
#include "Defaults.h"


PMRenderer::PMRenderer()
{
    int fboWidth = FBO_WIDTH;
    int fboHeight = FBO_HEIGHT;

    fbo.allocate(fboWidth, fboHeight, GL_RGBA32F_ARB);

    PMLayer1 *layer1 = new PMLayer1(fboWidth, fboHeight);
    layers.push_back(layer1);
    PMLayer2 *layer2 = new PMLayer2(fboWidth, fboHeight);
    layers.push_back(layer2);
    PMLayer3 *layer3 = new PMLayer3(fboWidth, fboHeight);
    layers.push_back(layer3);
    PMLayer4 *layer4 = new PMLayer4(fboWidth, fboHeight);
    layers.push_back(layer4);
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
/*
        // background dimming
        //ofFloatColor fc = ofFloatColor(0.0, 0.0, 0.0, gui->getFadeBackground());
        ofFloatColor fc = ofFloatColor(1.0, 1.0, 1.0, 1);
        //ofFloatColor fc = ofFloatColor(gui->getColorBackground().r,gui->getColorBackground().g,gui->getColorBackground().b,gui->getFadeBackground());
        ofSetColor(fc);

        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        ofDrawRectangle(0, 0, fbo.getWidth(), fbo.getHeight());
        ofDisableBlendMode();
*/
    }
    fbo.end();

    for (int i=0; i<layers.size(); ++i)
        layers[i]->update();

    drawIntoFBO();
}

void PMRenderer::draw()
{
    ofClear(ofColor::white);

    ofSetColor(255);
    fbo.draw(0, 0, ofGetWidth(), ofGetHeight());
}

void PMRenderer::drawIntoFBO()
{
    fbo.begin();
    {
        for (int i=0; i<layers.size(); ++i)
            layers[i]->draw();
    }
    fbo.end();
}
