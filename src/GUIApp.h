//
// Created by Eduard Frigola on 28/04/16.
//

#ifndef CANCONSVISUALS_GUIAPP_H
#define CANCONSVISUALS_GUIAPP_H

#include "ofMain.h"
#include "ofxAppUtils.h"
#include "PMUICanvasLayers.h"
#include "PMUICanvasAudioAnalyzer.h"

class ofApp;

class GUIApp : public ofxApp
{
public:

    void setup();
    void update();
    void draw();

    void exit();

    void keyPressed(int key);
    void keyReleased(int key);

    void setMainApp(const shared_ptr<ofApp> &mainApp) { GUIApp::mainApp = mainApp; };
    
    void layoutGuis();
    PMUICanvasLayers* getGuiOfLayer(int layerId){return layersGui.at(layerId-1);};
	PMUICanvasAudioAnalyzer* audioGui;

private:
    
    shared_ptr<ofApp> mainApp;
    
    vector<PMUICanvasLayers*> layersGui;
    
};


#endif //CANCONSVISUALS_GUIAPP_H
