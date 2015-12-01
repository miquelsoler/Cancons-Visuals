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
    drawIntoFBO();
}

void PMBaseRenderer::draw()
{
    ofSetColor(255);
    fbo.draw(0,0);
}
