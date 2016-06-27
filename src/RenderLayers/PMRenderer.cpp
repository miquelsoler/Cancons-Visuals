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
    backgroundFBO.allocate(1, 1, GL_RGBA32F_ARB);
#endif

    PMLayer1 *layer1 = new PMLayer1(fboWidth, fboHeight, KINECTNODE_RIGHTHAND);
	layer1->setStrokesVector(&strokes);
    layers.push_back(layer1);
    PMLayer2 *layer2 = new PMLayer2(fboWidth, fboHeight, KINECTNODE_LEFTHAND);
	layer2->setStrokesVector(&strokes);
    layers.push_back(layer2);
    PMLayer3 *layer3 = new PMLayer3(fboWidth, fboHeight, KINECTNODE_HEAD);
	layer3->setStrokesVector(&strokes);
    layers.push_back(layer3);
    PMLayer4 *layer4 = new PMLayer4(fboWidth, fboHeight, KINECTNODE_TORSO);
	layer4->setStrokesVector(&strokes);
    layers.push_back(layer4);
	ofRegisterKeyEvents(this);
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
    int INITIAL_POS_MARGIN_X=FBO_WIDTH*0.2;
    int INITIAL_POS_MARGIN_Y=FBO_HEIGHT*0.2;
    ofPoint initialPosition = ofPoint(ofRandom(INITIAL_POS_MARGIN_X, FBO_WIDTH-INITIAL_POS_MARGIN_X), ofRandom(INITIAL_POS_MARGIN_Y, FBO_HEIGHT-INITIAL_POS_MARGIN_Y));    for (int i=0; i<layers.size(); ++i)
        layers[i]->setup(initialPosition);
	tweening = false;
	counter = 0;
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

	 //remove elements with a life higher than a threshold
	if ( PERFORMANCE_MODE && layers[0]->isFading()) {
		for (auto it = strokes.cbegin(); it != strokes.cend() ; )
		{
			if (it->life > layers[0]->getMaxLife())
				it = strokes.erase(it);
			else
				++it;
		}
	}
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
        ofSetColor(255, 255, 255, 255);
        backgroundFBO.draw(0, 0, FBO_WIDTH, FBO_HEIGHT);

//        glBlendEquation(GL_MAX);
//        //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_DST_ALPHA);
//        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        for (int i=layers.size()-1; i>=0; --i)
        {
            ofFbo *layerFBO = layers[i]->getFBO();
            ofSetColor(255, 255, 255, 255);
            layerFBO->draw(0, 0);
        }
    }
    mainFBO.end();

    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    ofEnableAlphaBlending();
#else
    mainFBO.begin();
    {
		ofPushMatrix();
		float scaleX = (float)ofGetWidth() / (float)DESIGN_WIDTH;
		float scaleY = (float)ofGetHeight() / (float)DESIGN_HEIGHT;
		ofScale(1.0/scaleX, 1.0/scaleY);
		if (tweening)
		{
			counter += 0.01;
			ofBackground(prevColor.lerp(PMColorsSelector::getInstance().getColor(0), counter));
			if(counter >= 1)
				tweening = false;
		}
		else
			ofBackground(PMColorsSelector::getInstance().getColor(0));
//#if ENABLE_KINECT
//		PMMotionExtractor::getInstance().draw();
//#endif


//draw past strokes
		for (Stroke & m : strokes) {
			m.draw();
			if (layers[0]->showWireframe) {
			ofSetColor(100, 100, 100);
			m.drawWireframe();
			}
		}
		//cambio orden pintado de capas, mano izquierda debajo del todo.
        //for (int i=0; i<layers.size(); ++i)
        //    layers[i]->draw();
		layers[1]->draw();
		layers[2]->draw();
		layers[3]->draw();
		layers[0]->draw();
		ofPopMatrix();
    }
    mainFBO.end();
#endif
}

void PMRenderer::exportToImage(string path)
{
#if ENABLE_MULTILAYER_EXPORT && ENABLE_MULTIPLE_FBOS
    // Export separate layers
    {
        ofPixels bgPixels;
        string bgPath = path + "-Background";
        backgroundFBO.readToPixels(bgPixels);
        ofSaveImage(bgPixels, bgPath + ".png", OF_IMAGE_QUALITY_BEST);

        for (int i=0; i<layers.size(); ++i)
        {
            ofPixels layerPixels;
            string layerPath = path + "-Layer" + ofToString(i+1);
            ofFbo *layerFBO = layers[i]->getFBO();
            layerFBO->readToPixels(layerPixels);
            ofSaveImage(layerPixels, layerPath + ".png", OF_IMAGE_QUALITY_BEST);
        }
    }

    // Export full composition
    {
        ofPixels fullPixels;
        string fullPath = path + "-FULL";
        mainFBO.readToPixels(fullPixels);
        ofSaveImage(fullPixels, fullPath + ".png", OF_IMAGE_QUALITY_BEST);
    }
#else
    ofPixels pix;
    mainFBO.readToPixels(pix);
    ofSaveImage(pix, path + ".tiff", OF_IMAGE_QUALITY_BEST);
#endif
}

void PMRenderer::resetPositions()
{
    KinectElement kinectNodeData;
    kinectNodeData = PMMotionExtractor::getInstance().getKinectInfo()->rightHand;
    layers[0]->setPosition(ofPoint(ofGetWidth()/2, ofGetHeight()/2));
    kinectNodeData = PMMotionExtractor::getInstance().getKinectInfo()->leftHand;
    layers[1]->setPosition(ofPoint(ofGetWidth()/2, ofGetHeight()/2));
    kinectNodeData = PMMotionExtractor::getInstance().getKinectInfo()->head;
    layers[2]->setPosition(ofPoint(ofGetWidth()/2, ofGetHeight()/2));
    kinectNodeData = PMMotionExtractor::getInstance().getKinectInfo()->torso;
    layers[3]->setPosition(ofPoint(ofGetWidth()/2, ofGetHeight()/2));
}

void PMRenderer::melBandsChange(vector<float> melBands)
{
	if (mainFBO.isAllocated()) {
		for (auto layer : layers) {
			int melBandIndex = layer->getLayerID() - 1;
			layer->melBandsChanged(melBands[melBandIndex]);
		}
	}
}

void PMRenderer::keyPressed(ofKeyEventArgs &a) {
	if (a.key == 'R')
		strokes.clear();
	else if (a.key == 'h') {
		prevColor = PMColorsSelector::getInstance().getColor(0);
		PMColorsSelector::getInstance().nexPalette();
		tweening = true;
		counter = 0;
	}
}
