//
// Created by Eduard Frigola on 28/04/16.
//

#include "GUIApp.h"
#include "ofApp.h"


void GUIApp::setup()
{
    for( int i = 0 ; i < 4 ; i++){
        auto tempGui = new PMUICanvasLayers("LAYER PARAMETERS", OFX_UI_FONT_MEDIUM);
//        tempGui->set
        layersGui.push_back(tempGui);
    }
	audioGui = new PMUICanvasAudioAnalyzer("AUDIO PARAMETERS", OFX_UI_FONT_MEDIUM);
}

void GUIApp::update()
{
    
}

void GUIApp::draw()
{
#if ENABLE_KINECT
	auto imageHeight = layersGui[0]->getHeight() - audioGui->getHeight();
	PMMotionExtractor::getInstance().draw(audioGui->getRect()->getX(), audioGui->getHeight(), imageHeight*513/424, imageHeight, true, true);
#endif
}

void GUIApp::exit()
{

}

void GUIApp::layoutGuis(){
    layersGui[0]->setPosition(0, 0);
    layersGui[1]->setPosition(layersGui[0]->getWidth()+layersGui[0]->getRect()->getX(), 0);
    layersGui[2]->setPosition(layersGui[1]->getWidth()+layersGui[1]->getRect()->getX(), 0);
    layersGui[3]->setPosition(layersGui[2]->getWidth()+layersGui[2]->getRect()->getX(), 0);
	audioGui->setPosition(layersGui[3]->getWidth() + layersGui[3]->getRect()->getX(), 0);
}

void GUIApp::keyPressed(int key)
{
    //if(key != ofToChar(ofToString(layerID))) return;
//    if(key != '1' && key != '2' && key != '3' && key != '4') return;
//    if(getGuiOfLayer(key-'0')->isVisible()) getGuiOfLayer(key-'0')->setVisible(false);
//    else getGuiOfLayer(key-'0')->setVisible(true);
}

void GUIApp::keyReleased(int key)
{
    //mainApp->keyReleased(key);
}

