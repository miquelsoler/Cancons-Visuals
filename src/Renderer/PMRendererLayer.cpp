//
//  PMRendererLayer.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 30/11/15.
//
//

#include "PMRendererLayer.hpp"
#include "PMUICanvasBrushRenderer.h"



PMRendererLayer::PMRendererLayer(int _layer) : PMBaseRenderer(_layer)
{
    position=ofPoint(0,0);
    direction=ofPoint(-1+layer, 2-layer);
    size=ofRandom(fbo.getWidth()/30, fbo.getWidth()/20);
    
    gui = new PMUICanvasBrushRenderer(UI_RENDERERTYPE_PAINTBRUSH, "BRUSH_RENDERER",OFX_UI_FONT_SMALL);
    gui->init(layer*150, 500, 200, 300);
}

void PMRendererLayer::setup()
{
    PMBaseRenderer::setup();
    brush->update(position.x, position.y);
    brush->setSize(size, size);
}

void PMRendererLayer::update()
{
    
    PMBaseRenderer::update();
    gui->setBrushColor(drawColor);
//    brush->update(position.x, position.y);
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
        drawColor.getHsb(hue, saturation, brightness);
        cout<<hue<<"   "<<saturation<<"    "<<brightness<<endl;
        brush->draw();
    ofDisableBlendMode();
    fbo.end();
    
    ofSetColor(255, 255, 255, 255);
}

void PMRendererLayer::setPosition(ofPoint newPos)
{
    position=newPos;
    brush->update(position.x, position.y);
}

void PMRendererLayer::addOffset(float offsetFactor)
{
    position+=direction*offsetFactor;
    brush->update(position.x, position.y);
}

void PMRendererLayer::setNodeReference(ofPoint nodePos)
{
    direction=nodePos-position;
    direction.normalize();
//    cout<<direction<<endl;
}
