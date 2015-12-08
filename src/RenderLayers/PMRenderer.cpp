//
// Created by Miquel Àngel Soler on 4/12/15.
//

#include "PMRenderer.h"
#include "PMLayer1.h"
#include "PMLayer2.h"
#include "PMLayer3.h"
#include "PMLayer4.h"
#include "Defaults.h"
#include "PMColorsSelector.hpp"


PMRenderer::PMRenderer()
{
    int fboWidth = FBO_WIDTH;
    int fboHeight = FBO_HEIGHT;

    mainFBO.allocate(fboWidth, fboHeight, GL_RGBA32F_ARB);
#if ENABLE_MULTIPLE_FBOS
    backgroundFBO.allocate(fboWidth, fboHeight, GL_RGBA32F_ARB);
#endif

    PMLayer1 *layer1 = new PMLayer1(fboWidth, fboHeight, KINECTNODE_RIGHTHAND);
    layers.push_back(layer1);
    PMLayer2 *layer2 = new PMLayer2(fboWidth, fboHeight, KINECTNODE_LEFTHAND);
    layers.push_back(layer2);
    PMLayer3 *layer3 = new PMLayer3(fboWidth, fboHeight, KINECTNODE_HEAD);
    layers.push_back(layer3);
    PMLayer4 *layer4 = new PMLayer4(fboWidth, fboHeight, KINECTNODE_TORSO);
    layers.push_back(layer4);
}

void PMRenderer::setup()
{
    mainFBO.begin();
    {
        // Often the FBO will contain artifacts from the memory that the graphics card has just allocated for it,
        // so it's good to clear it before starting to draw it
        ofClear(0, 0, 0, 0);
        ofSetColor(PMColorsSelector::getInstance().getColor(0));
        ofDrawRectangle(0, 0, FBO_WIDTH, FBO_HEIGHT);
    }
    mainFBO.end();

#if ENABLE_MULTIPLE_FBOS
    backgroundFBO.begin();
    {
        // Often the FBO will contain artifacts from the memory that the graphics card has just allocated for it,
        // so it's good to clear it before starting to draw it
        ofClear(0, 0, 0, 0);
        ofSetColor(PMColorsSelector::getInstance().getColor(0));
        ofDrawRectangle(0, 0, FBO_WIDTH, FBO_HEIGHT);
    }
    backgroundFBO.end();
#endif

    for (int i=0; i<layers.size(); ++i)
        layers[i]->setup();
}

void PMRenderer::update()
{
    mainFBO.begin();
    {
    }
    mainFBO.end();

    for (int i=0; i<layers.size(); ++i)
        layers[i]->update();

    drawIntoFBO();
}

void PMRenderer::draw()
{
//    ofClear(ofColor::white);

    ofSetColor(255);
    mainFBO.draw(0, 0, ofGetWidth(), ofGetHeight());
}

void PMRenderer::drawIntoFBO()
{
#if ENABLE_MULTIPLE_FBOS
    backgroundFBO.begin();
    {
        ofSetColor(PMColorsSelector::getInstance().getColor(0));
        ofDrawRectangle(0, 0, FBO_WIDTH, FBO_HEIGHT);
    }
    backgroundFBO.end();

    for (int i=0; i<layers.size(); ++i)
        layers[i]->draw();

    mainFBO.begin();
    {
//        backgroundFBO.draw(0, 0);
        for (int i=0; i<layers.size(); ++i)
        {
            ofFbo *layerFBO = layers[i]->getFBO();
            layerFBO->draw(0, 0);
        }
    }
    mainFBO.end();
#else
    mainFBO.begin();
    {
        for (int i=0; i<layers.size(); ++i)
            layers[i]->draw();
    }
    mainFBO.end();
#endif
}

void PMRenderer::exportToImage(string path)
{
    ofPixels pix;
    mainFBO.readToPixels(pix);
    ofSaveImage(pix, path+".png", OF_IMAGE_QUALITY_BEST);
}
