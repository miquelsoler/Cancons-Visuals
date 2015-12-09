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

#if ENABLE_MULTIPLE_FBOS
    layerFBO.allocate(fboWidth, fboHeight, GL_RGBA32F_ARB);
#endif

    kinectNodeType = _kinectNodeType;
}

void PMBaseLayer::setup(ofPoint initialPosition)
{
#if ENABLE_MULTIPLE_FBOS
    layerFBO.begin();
    {
        // Often the FBO will contain artifacts from the memory that the graphics card has just allocated for it,
        // so it's good to clear it before starting to draw it
        ofClear(0, 0, 0, 0);
    }
    layerFBO.end();
#endif

    brush = PMBrushesSelector::getInstance().getBrush(layerID - 1);

#if ENABLE_KINECT
    switch (kinectNodeType)
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
    nodeInitialZ = kinectNodeData.z;
#else
    nodeInitialZ = 0;
#endif

    brushPosition = initialPosition;
    brushPrevPosition = brushPosition;
    brushDirection = ofPoint(ofRandom(-1, 1), ofRandom(-1, 1)).normalize();
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

        energyMin = settings.getEnergyMin(layerID);
        energyMax = settings.getEnergyMax(layerID);
        sizeMin = settings.getSizeMin(layerID);
        sizeMax = settings.getSizeMax(layerID);
        hueScaleFactor = settings.getHueScaleFactor(layerID);
        hueVariation = settings.getHueVariation(layerID);
        saturationScaleFactor = settings.getSaturationScaleFactor(layerID);
        saturationVariation = settings.getSaturationVariation(layerID);
        brightnessScaleFactor = settings.getBrightnessScaleFactor(layerID);
        brightnessVariation = settings.getBrightnessVariation(layerID);
        alphaMin = settings.getAlphaMin(layerID);
        alphaMax = settings.getAlphaMax(layerID);
        alphaScaleFactor = settings.getAlphaScaleFactor(layerID);
    }

    // TODO: Treure les crides que no s'utilitzin, si n'hi ha.
    ofAddListener(deviceAudioAnalyzer->eventMelBandsChanged, this, &PMBaseLayer::melBandsChanged);
}

void PMBaseLayer::update()
{

    brushPrevPosition = brushPosition;

#if ENABLE_KINECT
    if (PMMotionExtractor::getInstance().isTracking())
    {
        switch (kinectNodeType) {
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
#else
    kinectNodeData.x = (float) ofGetMouseX() / ofGetWidth();
    kinectNodeData.y = (float) ofGetMouseY() / ofGetHeight();
    kinectNodeData.v = ofPoint(0, 0);
#endif

//#if ENABLE_KINECT
    // Direction changes
    ofPoint newDirection = ofPoint(kinectNodeData.x * fboWidth, kinectNodeData.y * fboHeight) - brushPosition;
    brushDirection += ((newDirection.normalize()) * curveSize);
//#endif

    brushDirection.normalize();
//    direction+=((kinectNodeData.v.normalize())*(kinectNodeData.a/50));
//    cout<<kinectNodeData.a/30<<endl;
//
    if (kinectNodeData.a / KINECT_ACCEL_FACTOR > KINECT_ACCEL_THRESHOLD) {
        brushDirection += (kinectNodeData.v.normalize() * (kinectNodeData.a / 2));
//        cout<<layerID<<"--IS Aceletrstrefd"<<ofGetTimestampString()<<endl;
    }
    brushPosition += (brushDirection * brushSpeed);
    brushDirection.normalize();
    brush->update(int(brushPosition.x), int(brushPosition.y));
}

void PMBaseLayer::draw()
{
#if ENABLE_MULTIPLE_FBOS
    layerFBO.begin();
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
#endif
    ofSetColor(brushRGBColor, int(brushAlpha * 255));

    brush->draw();

    if ((brushPrevPosition - brushPosition).length() > BRUSH_MAX_POSITION_DISTANCE) {
        while ((brushPrevPosition - brushPosition).length() > BRUSH_MIN_POSITION_DISTANCE) {
            brushPrevPosition += ((brushPosition - brushPrevPosition).normalize() * BRUSH_MIN_POSITION_DISTANCE);
            brush->update(int(brushPrevPosition.x), int(brushPrevPosition.y));
//            ofSetColor(brushRGBColor, int(brushAlpha)*255);
            brush->draw();
        }
    }

#if ENABLE_MULTIPLE_FBOS
    layerFBO.end();
#endif
}

void PMBaseLayer::setBrushSize(int _brushSize)
{
    brushSize = _brushSize;
    brush->setSize(brushSize, brushSize);
}

#pragma mark - Audio events

void PMBaseLayer::melBandsChanged(melBandsParams &melBandsParams)
{
    // Layer4: band0 - Layer1: band1 - Layer2: band2 - Layer3: band3
    int melBandIndex = (layerID != 4) ? layerID : 0;
    float energy = melBandsParams.bandsEnergy[melBandIndex];
    float normalizedEnergy = ofMap(energy, energyMin, energyMax, 0, 1);

//    int hsbMin = 0, hsbMax = 255;

    // Size Miquel, sols depen de l'energia
//    {
        int newSize = int(ofMap(energy, energyMin, energyMax, sizeMin, sizeMax));
        setBrushSize(newSize);
//    }
    
    //Size Edu
    {
//        float factorizedEnergySize = normalizedEnergy*sizeEnergyScaleFactor;
//        float factorizedZSize = (nodeInitialZ-kinectNodeData.z)*sizeZScaleFactor; //de -1 a 1
//        float factorizedAccel = kinectNodeData.a*sizeAccelerationScaleFactor; //de 0 a 1
//        int newBrushSize = ofMap(factorizedEnergySize + factorizedZSize + factorizedAccel, 0, 3, sizeMin, sizeMax, true);
    }

    // Alpha
    {
        brushAlpha = ofMap(energy, energyMin, energyMax, alphaMin, alphaMax) * alphaScaleFactor;
        if (brushAlpha < 0.0f) brushAlpha = 0.0f;
        if (brushAlpha > 1.0f) brushAlpha = 1.0f;
    }

    // Hue Miquel
//    {
//        int hue = int(brushHSBColor.hue * (normalizedEnergy * hueScaleFactor));
//        if (hue < hsbMin) hue = hsbMin;
//        if (hue > hsbMax) hue = hsbMax;
//
//        brushRGBColor.setHue(hue);
//    }
    
    //Hue Edu
    {
        float hueOffset = ofMap(hueVariation, 0, 1, 0, 255, true); //Maps % to absolute hue variation values
        int hueIncrement=ofMap(normalizedEnergy, 0, 1, -1, 1)*hueScaleFactor*hueOffset; //maps energy to -1 1, then aplies scale factor to finaly get a number between -hueOffset and hueoffset
        hueIncrement=ofMap(hueIncrement, -hueOffset, hueOffset, -hueOffset, hueOffset, true);
        brushRGBColor.setHue(brushHSBColor.hue+hueIncrement);
    }

    // Saturation Miquel
//    {
//        int saturation = int(brushHSBColor.saturation * (normalizedEnergy * saturationScaleFactor));
//        if (saturation < hsbMin) saturation = hsbMin;
//        if (saturation > hsbMax) saturation = hsbMax;
//
//        brushRGBColor.setSaturation(saturation);
//    }
    
    //Saturation Edu
    {
        float saturationOffset = ofMap(saturationVariation, 0, 1, 0, 255, true); //Maps % to absolute Saturation variation values
        int saturationIncrement=ofMap(normalizedEnergy, 0, 1, -1, 1)*saturationScaleFactor*saturationOffset;
        saturationIncrement=ofMap(saturationIncrement, -saturationOffset, saturationOffset, -saturationOffset, saturationOffset, true);
        brushRGBColor.setSaturation(brushHSBColor.saturation+saturationIncrement);
    }

    // Brightness Miquel
//    {
//        int brightness = int(brushHSBColor.brightness * (normalizedEnergy * brightnessScaleFactor));
//        if (brightness < hsbMin) brightness = hsbMin;
//        if (brightness > hsbMax) brightness = hsbMax;
//
//        brushRGBColor.setBrightness(brightness);
//    }
    
    
    //Brightness Edu
    {
        float brightnessOffset = ofMap(brightnessVariation, 0, 1, 0, 255, true); //Maps % to absolute brightness variation values
        int brightnessIncrement=ofMap(normalizedEnergy, 0, 1, -1, 1)*brightnessScaleFactor*brightnessOffset;
        brightnessIncrement=ofMap(brightnessIncrement, -brightnessOffset, brightnessOffset, -brightnessOffset, brightnessOffset, true);
        brushRGBColor.setBrightness(brushHSBColor.brightness+brightnessIncrement);
    }
}
