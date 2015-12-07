//
// Created by Miquel Àngel Soler on 4/12/15.
//

#include "PMBaseLayer.h"
#include "PMColorsSelector.hpp"
#include "PMSettingsManagerLayers.h"

PMBaseLayer::PMBaseLayer(int _fboWidth, int _fboHeight, KinectNodeType _kinectNodeType)
{
    fboWidth = _fboWidth;
    fboHeight = _fboHeight;

    kinectNodeType = _kinectNodeType;
}

void PMBaseLayer::setup()
{
    //FIXME: Definir aquest vector per parametre o potser a la gui
    vector<int> layerToColorMap{1, 2, 3, 4}; //per asignar un pinzell diferent a ordre pinzell 1, a la capa 1.

    brush = PMBrushesSelector::getInstance().getBrush(layerID - 1);
    
    
    if(PMMotionExtractor::getInstance().isReady()){
    switch(kinectNodeType)
    {
        case KINECTNODE_RIGHTHAND: {
            kinectNodeData = PMMotionExtractor::getInstance().getKinectInfo()->rightHand_joint;
            break;
        }
        case KINECTNODE_LEFTHAND: {
            kinectNodeData = PMMotionExtractor::getInstance().getKinectInfo()->leftHand_joint;
            break;
        }
        case KINECTNODE_HEAD: {
            kinectNodeData = PMMotionExtractor::getInstance().getKinectInfo()->head_joint;
            break;
        }
        case KINECTNODE_TORSO: {
            kinectNodeData = PMMotionExtractor::getInstance().getKinectInfo()->torso_joint;
            break;
        }
    }
    nodeInitialZ=kinectNodeData.z;
    brushPosition = ofPoint(kinectNodeData.x*fboWidth, kinectNodeData.y*fboHeight);
    }else{
        brushPosition = ofPoint(ofRandom(fboWidth), ofRandom(fboHeight));
        nodeInitialZ=0;
    }
    
    brushPrevPosition = brushPosition;
    brushDirection = ofPoint(0, 0);
//    brushSize = int(ofRandom(BRUSH_MIN_SIZE, BRUSH_MAX_SIZE));
//    brush->setSize(brushSize, brushSize);
    setBrushSize(int(ofRandom(BRUSH_MIN_SIZE, BRUSH_MAX_SIZE)));

    brushRGBColor = PMColorsSelector::getInstance().getColor(layerID);
    brushRGBColor.getHsb(brushHSBColor.hue, brushHSBColor.saturation, brushHSBColor.brightness);
    brushAlpha = 1;

    brushSpeed = 10;
    curveSize = 1;

    vector<PMDeviceAudioAnalyzer *> deviceAudioAnalyzers = *PMAudioAnalyzer::getInstance().getAudioAnalyzers();
    PMDeviceAudioAnalyzer *deviceAudioAnalyzer = deviceAudioAnalyzers[0];

    // Mapping values initialization
    {
        PMSettingsManagerLayers settings = PMSettingsManagerLayers::getInstance();

        bandMaxEnergy = settings.getBandMaxEnergy(layerID);
        brushMinAlpha = settings.getMinAlpha(layerID);
        brushMaxAlpha = settings.getMaxAlpha(layerID);
        brushMinSize = settings.getMinSize(layerID);
        brushMaxSize = settings.getMaxSize(layerID);
        brushMinBrightness = settings.getMinBrightness(layerID);
        brushMaxBrightness = settings.getMaxBrightness(layerID);
    }

    // TODO: Treure les crides que no s'utilitzin, si n'hi ha.
    ofAddListener(deviceAudioAnalyzer->eventPitchChanged, this, &PMBaseLayer::pitchChanged);
    ofAddListener(deviceAudioAnalyzer->eventEnergyChanged, this, &PMBaseLayer::energyChanged);
    ofAddListener(deviceAudioAnalyzer->eventSilenceStateChanged, this, &PMBaseLayer::silenceStateChanged);
    ofAddListener(deviceAudioAnalyzer->eventPauseStateChanged, this, &PMBaseLayer::pauseStateChanged);
    ofAddListener(deviceAudioAnalyzer->eventOnsetStateChanged, this, &PMBaseLayer::onsetDetected);
    ofAddListener(deviceAudioAnalyzer->eventShtStateChanged, this, &PMBaseLayer::shtDetected);
    ofAddListener(deviceAudioAnalyzer->eventMelodyDirection, this, &PMBaseLayer::melodyDirection);
    ofAddListener(deviceAudioAnalyzer->eventMelBandsChanged, this, &PMBaseLayer::melBandsChanged);
}

void PMBaseLayer::update()
{
    
    //FIXME: Hack perquè no inicialitzi posició a 0.0
    
    brushPrevPosition = brushPosition;

    if (PMMotionExtractor::getInstance().isTracking())
    {
        switch(kinectNodeType)
        {
            case KINECTNODE_RIGHTHAND: {
                kinectNodeData = PMMotionExtractor::getInstance().getKinectInfo()->rightHand_joint;
                break;
            }
            case KINECTNODE_LEFTHAND: {
                kinectNodeData = PMMotionExtractor::getInstance().getKinectInfo()->leftHand_joint;
                break;
            }
            case KINECTNODE_HEAD: {
                kinectNodeData = PMMotionExtractor::getInstance().getKinectInfo()->head_joint;
                break;
            }
            case KINECTNODE_TORSO: {
                kinectNodeData = PMMotionExtractor::getInstance().getKinectInfo()->torso_joint;
                break;
            }
        }
    }
    else if(!PMMotionExtractor::getInstance().isReady())
    {
        kinectNodeData.x = (float) ofGetMouseX() / ofGetWidth();
        kinectNodeData.y = (float) ofGetMouseY() / ofGetHeight();
        kinectNodeData.v = ofPoint(0, 0);
    }
    //direction changes
    ofPoint newDirection = ofPoint(kinectNodeData.x * fboWidth, kinectNodeData.y * fboHeight) - brushPosition;
    brushDirection += ((newDirection.normalize()) * curveSize);
    brushDirection.normalize();
//    direction+=((kinectNodeData.v.normalize())*(kinectNodeData.a/50));
//    cout<<kinectNodeData.a/30<<endl;
//
    if (kinectNodeData.a / KINECT_ACCEL_FACTOR > KINECT_ACCEL_THRESHOLD) {
        brushDirection += (kinectNodeData.v.normalize() * (kinectNodeData.a / 2));
    }
    brushPosition += (brushDirection * brushSpeed);
    brushDirection.normalize();
    brush->update(int(brushPosition.x), int(brushPosition.y));
}

void PMBaseLayer::draw()
{
    ofSetColor(brushRGBColor, int(brushAlpha * 255));
    brush->draw();

    if ((brushPrevPosition - brushPosition).length() > BRUSH_MAX_POSITION_DISTANCE)
    {
        while ((brushPrevPosition - brushPosition).length() > BRUSH_MIN_POSITION_DISTANCE)
        {
            brushPrevPosition += ((brushPosition - brushPrevPosition).normalize()*BRUSH_MIN_POSITION_DISTANCE);
            brush->update(int(brushPrevPosition.x), int(brushPrevPosition.y));
//            ofSetColor(brushRGBColor, int(brushAlpha)*255);
            brush->draw();
        }
    }
}

void PMBaseLayer::setBrushSize(int _brushSize)
{
    brushSize = _brushSize;
    brush->setSize(brushSize, brushSize);
}
