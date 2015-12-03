//
// Created by Miquel Àngel Soler on 7/11/15.
//

#include "PMUICanvasBrushRenderer.h"

PMUICanvasBrushRenderer::PMUICanvasBrushRenderer(PMUIRendererType type, string title, int headerFontSize) : PMUICanvasBaseRenderer(type, title, headerFontSize)
{
}

void PMUICanvasBrushRenderer::init(int posX, int posY, bool autosize, int width, int height)
{
    PMUICanvasBaseRenderer::init(posX, posY, autosize, width, height);
    
    addSpacer();
    addSlider("Brush H",0,360,&hue);
    addSlider("Brush S",0,100,&saturation);
    addSlider("Brush B",0,100,&brightness);
    addSpacer();
    addToggle("Bouncy Walls", &bounceWalls);
    if (autosize) autoSizeToFitWidgets();

    loadPreset(0);
}

void PMUICanvasBrushRenderer::clear()
{
    ofxUICanvas::clearWidgets();
    superInit("BRUSH_RENDERER", OFX_UI_FONT_MEDIUM);
}

void PMUICanvasBrushRenderer::handleEvents(ofxUIEventArgs &e)
{
    PMUICanvasBaseRenderer::handleEvents(e);
}


// GETTERS
int PMUICanvasBrushRenderer::getMode()
{
    return guiMode;
}

ofColor PMUICanvasBrushRenderer::getBrushColor()
{
    paintColor.setHsb(hue, saturation, brightness);
    return paintColor;
}


//Setters

void PMUICanvasBrushRenderer::setBrushColor(ofColor newColor)
{
    paintColor=newColor;
    paintColor.getHsb(hue, saturation, brightness);
}