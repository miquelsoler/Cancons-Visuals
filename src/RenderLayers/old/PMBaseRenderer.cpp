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

    position=ofPoint(0,0);
    direction=ofPoint(-1+layer, 2-layer);
    size=ofRandom(fbo.getWidth()/30, fbo.getWidth()/20);

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

    brush->update(position.x, position.y);
    brush->setSize(size, size);
    gui->setBrushColor(drawColor);
}

void PMBaseRenderer::update()
{
    fbo.begin();
    {
        // background dimming
        //ofFloatColor fc = ofFloatColor(0.0, 0.0, 0.0, gui->getFadeBackground());
        ofFloatColor fc = ofFloatColor(0.0, 0.0, 0.0, 1);
        //ofFloatColor fc = ofFloatColor(gui->getColorBackground().r,gui->getColorBackground().g,gui->getColorBackground().b,gui->getFadeBackground());
//        ofSetColor(fc);
        
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
    ofSetColor(255);
    fbo.draw(0,0);    
}

void PMBaseRenderer::setPosition(ofPoint newPos)
{
    position=newPos;
    brush->update(position.x, position.y);
}

void PMBaseRenderer::addOffset(float offsetFactor)
{
    position+=direction*offsetFactor;
    brush->update(position.x, position.y);
}

void PMBaseRenderer::showGUI(bool show)
{
    gui->setVisible(show);
}

#pragma mark - Kinect events

void PMBaseRenderer::setNodeReference(ofPoint nodePos)
{
    direction=nodePos-position;
    direction.normalize();
//    cout<<direction<<endl;
}

#pragma mark - Audio events

void PMBaseRenderer::pitchChanged(pitchParams pitchParams)
{

}

void PMBaseRenderer::energyChanged(energyParams energyParams)
{

}

void PMBaseRenderer::silenceStateChanged(silenceParams &silenceParams)
{

}

void PMBaseRenderer::pauseStateChanged(pauseParams &pauseParams)
{

}
