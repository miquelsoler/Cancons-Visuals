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

    directionHistory.assign(10 , ofPoint(0,0));
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
    brushInitalPosition = brushPosition;
    brushDirection = ofPoint(ofRandom(-1, 1), ofRandom(-1, 1)).normalize();
    setBrushSize(int(ofRandom(sizeMin, sizeMax)));

    brushRGBColor = PMColorsSelector::getInstance().getColor(layerID);
    brushRGBColor.getHsb(brushHSBColor.hue, brushHSBColor.saturation, brushHSBColor.brightness);
    brushAlpha = 0;
    didShoot = false;

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
        //Size Factors
        sizeEnergyScaleFactor = settings.getSizeEnergyFactor(layerID);
        sizeZScaleFactor = settings.getSizeZFactor(layerID);
        sizeAccelerationScaleFactor = settings.getSizeAccelerationFactor(layerID);
        //Alpha factors
        alphaEnergyScaleFactor = settings.getAlphaEnergyFactor(layerID);
        alphaZScaleFactor = settings.getAlphaZFactor(layerID);
        alphaVelocityScaleFactor = settings.getAlphaVelocityFactor(layerID);
        
        //Behaviour parameters
        brushSpeed = settings.getSpeed(layerID);
        curveSize = settings.getCurveSize(layerID);
        
        //Shoot parameters
        sizeShootDecrement = settings.getShootSizeDecrement(layerID);
        speedShootDecrement = settings.getShootSpeedDecrement(layerID);
        initialShootSpeeed = settings.getShootInitialSpeed(layerID);
        initialShootSize = settings.getShootInitialSize(layerID);
        shootCurveAmount = settings.getShootCurveAmount(layerID);
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
    kinectNodeData.x = (float) (ofGetMouseX() + (layerID-2)*30 )/ ofGetWidth();
    kinectNodeData.y = (float) (ofGetMouseY() + (layerID-2)*30 )/ ofGetHeight();
    kinectNodeData.v = ofPoint(0, 0);
#endif

//#if ENABLE_KINECT
    // Direction changes
    ofPoint newDirection = ofPoint(kinectNodeData.x * fboWidth, kinectNodeData.y * fboHeight) - brushPosition;
    brushDirection += ((newDirection.normalize()) * curveSize);
//#endif

    brushDirection.normalize();

    if (kinectNodeData.a / KINECT_ACCEL_FACTOR > KINECT_ACCEL_THRESHOLD) {
        brushDirection += (kinectNodeData.v.normalize() * (kinectNodeData.a / 2));
    }
    brushPosition += (brushDirection * brushSpeed);
    brushDirection.normalize();
    brush->update(int(brushPosition.x), int(brushPosition.y));
}

void PMBaseLayer::updateToShoot()
{
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
    
    if (didShoot)
    {
        setBrushSize(brushSize - sizeShootDecrement);
        brushSpeed -= speedShootDecrement;
        if (brushSize <= sizeMin){
            setBrushSize(sizeMin);
        }
        if(brushSpeed <= 0){
            didShoot=false;
            brushSpeed = PMSettingsManagerLayers::getInstance().getSpeed(layerID);
            setBrushSize(ofRandom(sizeMin, sizeMax));
        }
        brushDirection.rotate(shootCurveAmount, ofPoint(0,0,1));
    }
    else
    {
        // Direction changes
        ofPoint noise;
        float noiseAmount=100;
        noise.x= ofMap(ofSignedNoise(ofGetElapsedTimef()/2.0, -1000), -1, 1, -noiseAmount, noiseAmount);
        noise.y= ofMap(ofSignedNoise(ofGetElapsedTimef()/2.0, 1000), -1, 1, -noiseAmount, noiseAmount);
        ofPoint newDirection = (brushInitalPosition+noise)-brushPosition;
        brushDirection = newDirection.getNormalized();
//        brushSpeed = newDirection.length()*5;
        brushDirection.normalize();
        if(brushAlpha>alphaMin)
            brushAlpha-=0.04;
        
        //direction history
        directionHistory.push_back(kinectNodeData.v);
        directionHistory.pop_front();
        if (kinectNodeData.v.length() * kinectNodeData.a > KINECT_VELO_THRESHOLD)
        {
            beginShakeTime = ofGetElapsedTimeMillis();
            setBrushSize(initialShootSize);
            brushSpeed = initialShootSpeeed;
            didShoot = true;
            int directionHistoryMaxIndex=0;
            for(int i=0; i<directionHistory.size(); i++){
                if(directionHistoryMaxIndex < directionHistory[i].length())
                    directionHistoryMaxIndex = i;
            }
            brushDirection=directionHistory[directionHistoryMaxIndex];
        }
    }
    brushPosition += (brushDirection * brushSpeed);
    
//    int MARGIN=30;
//    if (brushPosition.x < -MARGIN) brushPosition.x = -MARGIN;
//    if (brushPosition.y < -MARGIN) brushPosition.y = -MARGIN;
//    if (brushPosition.x > fboWidth + MARGIN) brushPosition.x = fboWidth + MARGIN;
//    if (brushPosition.y > fboHeight + MARGIN) brushPosition.y = fboHeight + MARGIN;
    
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
    //Aquest valors son arbitraris ja que el que volem es aconseguir tots els paràmetres que vagin de 0 a 1
    float normalizedEnergy = ofMap(energy, energyMin, energyMax, 0, 1);
#if ENABLE_KINECT
    float normalizedZ = ofMap((nodeInitialZ-kinectNodeData.z), -0.3, 0.3, 0, 1);
    float normalizedVelocity = ofMap(kinectNodeData.v.length(), 0, 100, 0, 1);
    float normalizedAcceleration = ofMap(kinectNodeData.a, 0, 20, 0, 1);
#endif
    
//    int hsbMin = 0, hsbMax = 255;

    // Size Miquel, sols depen de l'energia
//    {
//        int newSize = int(ofMap(energy, energyMin, energyMax, sizeMin, sizeMax));
//        setBrushSize(newSize);
//    }
    
    //Size Edu
    {
        //Aqui tenim els valors entre 0 i 1, i el factor el que fa es donar importància
        float factorizedEnergySize = normalizedEnergy*sizeEnergyScaleFactor;
#if ENABLE_KINECT
        float factorizedZSize = normalizedZ*sizeZScaleFactor;
        float factorizedAccel = normalizedAcceleration*sizeAccelerationScaleFactor;
        int newBrushSize = ofMap(factorizedEnergySize + factorizedZSize + factorizedAccel, 0, 3, sizeMin, sizeMax, true);
//        if(layerID==2)
//            cout<<"Energy: "<<factorizedEnergySize<<"----Z: "<<factorizedZSize<<"----Accel: "<<factorizedAccel<<"---BrushSize: "<<newBrushSize<<endl;
#else
        int newBrushSize = ofMap(factorizedEnergySize, 0, 1, sizeMin, sizeMax);
#endif
        if(!didShoot)
            setBrushSize(newBrushSize);
    }

    // Alpha Miquel
//    {
//        brushAlpha = ofMap(energy, energyMin, energyMax, alphaMin, alphaMax) * alphaScaleFactor;
//        if (brushAlpha < 0.0f) brushAlpha = 0.0f;
//        if (brushAlpha > 1.0f) brushAlpha = 1.0f;
//    }
    
    // Alpha Edu
    {
        float factorizedEnergyAlpha = normalizedEnergy*alphaEnergyScaleFactor;
#if ENABLE_KINECT
        float factorizedZAlpha = normalizedZ*alphaZScaleFactor;
        float factorizedVel;
        if(kinectNodeData.v.length()!= 1) factorizedVel=normalizedVelocity*alphaVelocityScaleFactor; else factorizedVel=0.5;
        if(didShoot || layerID==1 || layerID ==2)
            brushAlpha = ofMap(factorizedEnergyAlpha *factorizedVel * factorizedZAlpha, 0, 1, alphaMin, alphaMax, true);
#else
        brushAlpha = ofMap(factorizedEnergyAlpha, 0, 1, alphaMin, alphaMax, true);
#endif
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
        int hueIncrement=ofMap(normalizedEnergy, 0, 1, -1, 1)*hueOffset; //maps energy to -1 1, then aplies scale factor to finaly get a number between -hueOffset and hueoffset
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
        int saturationIncrement=ofMap(normalizedEnergy, 0, 1, -1, 1)*saturationOffset;
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
        int brightnessIncrement=ofMap(normalizedEnergy, 0, 1, -1, 1)*brightnessOffset;
        brightnessIncrement=ofMap(brightnessIncrement, -brightnessOffset, brightnessOffset, -brightnessOffset, brightnessOffset, true);
        brushRGBColor.setBrightness(brushHSBColor.brightness+brightnessIncrement);
    }
}
