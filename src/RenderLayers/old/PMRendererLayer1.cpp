//
//  PMRendererLayer.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 30/11/15.
//
//

#include "PMRendererLayer1.hpp"
#include "PMUICanvasBrushRenderer.h"


PMRendererLayer1::PMRendererLayer1(int _layer) : PMBaseRenderer(_layer)
{
    gui = new PMUICanvasBrushRenderer(UI_RENDERERTYPE_PAINTBRUSH, "BRUSH_RENDERER",OFX_UI_FONT_SMALL);
    gui->init(layer*150, 500, false, 200, 300);
}

void PMRendererLayer1::setup()
{
    PMBaseRenderer::setup();
}

void PMRendererLayer1::update()
{
    PMBaseRenderer::update();
    drawColor=gui->getBrushColor();
}

void PMRendererLayer1::draw()
{
    PMBaseRenderer::draw();
}

void PMRendererLayer1::drawIntoFBO()
{
    fbo.begin();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        ofSetColor(drawColor);
        drawColor.getHsb(hue, saturation, brightness);
        brush->draw();
    ofDisableBlendMode();
    fbo.end();
    
    ofSetColor(255, 255, 255, 255);
}
