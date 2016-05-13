//
// Created by Miquel Àngel Soler on 4/12/15.
//

#include "PMBaseLayer.h"
#include "PMColorsSelector.hpp"
#include "PMSettingsManagerLayers.h"
#include "PMSharedSettings.h"



PMBaseLayer::PMBaseLayer(int _fboWidth, int _fboHeight, KinectNodeType _kinectNodeType)
{
    fboWidth = _fboWidth;
    fboHeight = _fboHeight;

#if ENABLE_MULTIPLE_FBOS
    layerFBO.allocate(fboWidth, fboHeight, GL_RGBA32F_ARB);
#endif

    kinectNodeType = _kinectNodeType;

    directionHistory.assign(10 , ofPoint(0,0));

    settings = PMSettingsManagerLayers::getInstance();
}

void PMBaseLayer::setup(ofPoint initialPosition)
{
    
    ofRegisterKeyEvents(this);


	//vector<PMDeviceAudioAnalyzer *> deviceAudioAnalyzers = *PMAudioAnalyzer::getInstance().getAudioAnalyzers();
	//PMDeviceAudioAnalyzer *deviceAudioAnalyzer = deviceAudioAnalyzers[0];

	settings.reload();

	// Mapping values initialization
	{
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

	//createGui to guiApp
	PMSharedSettings shared = PMSharedSettings::getInstance();
	auto layersGui = shared.guiApp->getGuiOfLayer(layerID);

	//bindVariables
	layersGui->bindEnergy(&energyMin, &energyMax);
	layersGui->bindSize(&sizeMin, &sizeMax, &sizeEnergyScaleFactor, &sizeAccelerationScaleFactor, &sizeZScaleFactor);
	layersGui->bindHue(&hueScaleFactor, &hueVariation);
	layersGui->bindSaturation(&saturationScaleFactor, &saturationVariation);
	layersGui->bindBrightness(&brightnessScaleFactor, &brightnessVariation);
	layersGui->bindAlpha(&alphaMin, &alphaMax, &alphaScaleFactor, &alphaEnergyScaleFactor, &alphaVelocityScaleFactor, &alphaZScaleFactor);
	layersGui->bindBehaviour(&brushSpeed, &curveSize);

	layersGui->bindDistanceThreshold(&distanceThreshold);
	layersGui->bindWireframeToggle(&showWireframe);

	//setup Gui
	layersGui->init(layerID, 5, 5);
	layersGui->setBackgroundColor(ofColor::gray);
	layersGui->setVisible(false);

	shared.guiApp->layoutGuis();

	// TODO: Treure les crides que no s'utilitzin, si n'hi ha.
	//ofAddListener(deviceAudioAnalyzer->eventMelBandsChanged, this, &PMBaseLayer::melBandsChanged);
    
    
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
            kinectNodeData = PMMotionExtractor::getInstance().getKinectInfo()->rightHand;
            break;
        }
        case KINECTNODE_LEFTHAND: {
            kinectNodeData = PMMotionExtractor::getInstance().getKinectInfo()->leftHand;
            break;
        }
        case KINECTNODE_HEAD: {
            kinectNodeData = PMMotionExtractor::getInstance().getKinectInfo()->head;
            break;
        }
        case KINECTNODE_TORSO: {
            kinectNodeData = PMMotionExtractor::getInstance().getKinectInfo()->torso;
            break;
        }
    }
    nodeInitialZ = kinectNodeData.pos.z;
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
    brushAlpha = 1;
    didShoot = false;

	//ofEnableNormalizedTexCoords();
	strokeTex.load("stroke.png");
	ribbon.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
}

void PMBaseLayer::update()
{
    float anglenoise=ofNoise(ofGetElapsedTimeMicros()*layerID)*360;
    brush->setAngle(anglenoise);
    brushPrevPosition = brushPosition;

#if ENABLE_KINECT
    if (PMMotionExtractor::getInstance().isTracking())
    {
        switch (kinectNodeType) {
            case KINECTNODE_RIGHTHAND: {
                kinectNodeData = PMMotionExtractor::getInstance().getKinectInfo()->rightHand;
                break;
            }
            case KINECTNODE_LEFTHAND: {
                kinectNodeData = PMMotionExtractor::getInstance().getKinectInfo()->leftHand;
                break;
            }
#if ENABLE_KNEES_DETECTION
            case KINECTNODE_HEAD: {
                kinectNodeData = PMMotionExtractor::getInstance().getKinectInfo()->rightKnee;
                break;
            }
            case KINECTNODE_TORSO: {
                kinectNodeData = PMMotionExtractor::getInstance().getKinectInfo()->leftKnee;
                break;
            }
#else
            case KINECTNODE_HEAD: {
                kinectNodeData = PMMotionExtractor::getInstance().getKinectInfo()->head;
                break;
            }
            case KINECTNODE_TORSO: {
                kinectNodeData = PMMotionExtractor::getInstance().getKinectInfo()->torso;
                break;
            }
#endif
        }
    }
#else
    kinectNodeData.pos.x =  (ofGetMouseX() + (layerID-1)*200 )/ (float)ofGetWidth();
    kinectNodeData.pos.y = (ofGetMouseY() + (layerID-1)*200 )/ (float)ofGetHeight();
    kinectNodeData.v = ofPoint(0, 0);
	
#endif

//#if ENABLE_KINECT
    // Direction changes
    ofPoint newDirection;
    if(layerID==1)
        newDirection = ofPoint(ofMap(kinectNodeData.pos.x, 0.2,1, 0, fboWidth), kinectNodeData.pos.y * fboHeight) - brushPosition;
    else if(layerID==2)
        newDirection = ofPoint(ofMap(kinectNodeData.pos.x, 0,0.8, 0, fboWidth), kinectNodeData.pos.y * fboHeight) - brushPosition;
#if ENABLE_KNEES_DETECTION
    //detection of knees
    else if(layerID == 3)
        newDirection = ofPoint(ofMap(kinectNodeData.pos.x, 0.2,1, 0, fboWidth), kinectNodeData.pos.y * fboHeight) - brushPosition;
    else if(layerID == 4)
        newDirection = ofPoint(ofMap(kinectNodeData.pos.x, 0,0.8, 0, fboWidth), kinectNodeData.pos.y * fboHeight) - brushPosition;
#else
    else if(layerID==3 || layerID==4)
        newDirection = ofPoint(kinectNodeData.pos.x * fboWidth, kinectNodeData.pos.y * fboHeight) - brushPosition;
#endif
    
    brushDirection += ((newDirection.normalize()) * curveSize);
//#endif

    brushDirection.normalize();

    if (kinectNodeData.a / KINECT_ACCEL_FACTOR > KINECT_ACCEL_THRESHOLD) {
        brushDirection += (kinectNodeData.v.normalize() * (kinectNodeData.a / 3));
    }
    brushPosition += (brushDirection * brushSpeed);
	ofPoint brushDirectionUnormalized = brushDirection;
    brushDirection.normalize();
    brush->update(int(brushPosition.x), int(brushPosition.y));
	
	//Fort Pienc version
	brushPosition.z = 0;
	
//	cout << "mouse pos normalized " << kinectNodeData.pos << endl;
	ofPoint newPoint(kinectNodeData.pos.x * ofGetWidth(), kinectNodeData.pos.y * ofGetHeight(), 0);
	addPointToRibbon(newPoint, brushDirectionUnormalized, brushSize);
	//cout << "mouse pos " << newPoint << endl;
	if (points.size() > maxPoints)
		finishStroke();
}

void PMBaseLayer::updateToShoot()
{
    if(layerID==4){
        ofPoint layer1pos=ofPoint(ofMap(kinectNodeData.pos.x, 0.2,1, 0, fboWidth), kinectNodeData.pos.y * fboHeight);
        ofPoint layer2pos=ofPoint(ofMap(kinectNodeData.pos.x, 0,0.8, 0, fboWidth), kinectNodeData.pos.y * fboHeight);
        brushInitalPosition=(layer1pos+layer2pos)/2;
    }
    
    float anglenoise=ofNoise(ofGetElapsedTimeMicros()*layerID)*360;
    brush->setAngle(anglenoise);
    brushPrevPosition = brushPosition;
    
    if (PMMotionExtractor::getInstance().isTracking())
    {
        switch(kinectNodeType)
        {
            case KINECTNODE_RIGHTHAND: {
                kinectNodeData = PMMotionExtractor::getInstance().getKinectInfo()->rightHand;
                break;
            }
            case KINECTNODE_LEFTHAND: {
                kinectNodeData = PMMotionExtractor::getInstance().getKinectInfo()->leftHand;
                break;
            }
            case KINECTNODE_HEAD: {
                kinectNodeData = PMMotionExtractor::getInstance().getKinectInfo()->head;
                break;
            }
            case KINECTNODE_TORSO: {
                kinectNodeData = PMMotionExtractor::getInstance().getKinectInfo()->torso;
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
        brushDirection.rotate(shootCurveAmount+ofSignedNoise(ofGetElapsedTimef()), ofPoint(0,0,1));
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
        brushAlpha-=0.1;
        if(brushAlpha<0)
            brushAlpha=0;
        
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
            brushAlpha=alphaMax;
            brushDirection=directionHistory[directionHistoryMaxIndex];
        }
    }
    brushPosition += (brushDirection * brushSpeed);
    
//    int MARGIN=30;
//    if (brushPosition.pos.pos.x < -MARGIN) brushPosition.pos.x = -MARGIN;
//    if (brushPosition.pos.y < -MARGIN) brushPosition.pos.y = -MARGIN;
//    if (brushPosition.pos.x > fboWidth + MARGIN) brushPosition.pos.x = fboWidth + MARGIN;
//    if (brushPosition.pos.y > fboHeight + MARGIN) brushPosition.pos.y = fboHeight + MARGIN;
    
    brushDirection.normalize();
    brush->update(int(brushPosition.x), int(brushPosition.y));
}

void PMBaseLayer::draw()
{
#if ENABLE_MULTIPLE_FBOS
    layerFBO.begin();
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
#endif
	//ofBackground(PMColorsSelector::getInstance().getColor(0));
    ofSetColor(brushRGBColor, int(brushAlpha * 255));

    brush->draw();

    if ((brushPrevPosition - brushPosition).length() > brushSpeed) {
        while ((brushPrevPosition - brushPosition).length() > brushSpeed*2) {
            float anglenoise=ofNoise(brushPrevPosition.x*brushPrevPosition.y)*360;
            brush->setAngle(anglenoise);
            ofPoint tempDirection = (brushPosition - brushPrevPosition).normalize();
            tempDirection.rotate(ofSignedNoise(brushPosition.x, brushPosition.y), ofPoint(0,0,1));
            brushPrevPosition += tempDirection* brushSpeed;
            brush->update(int(brushPrevPosition.x), int(brushPrevPosition.y));
//            ofSetColor(brushRGBColor, int(brushAlpha)*255);
            brush->draw();
        }
    }
	drawStrokes(); 
	/*ofSetColor(255, 0, 0);
	ofFill();
	ofDrawRectangle(kinectNodeData.pos.x * ofGetWidth(), kinectNodeData.pos.y * ofGetHeight(), 200, 200);*/

#if ENABLE_MULTIPLE_FBOS
    layerFBO.end();
#endif
}

void PMBaseLayer::addPointToRibbon(ofPoint point, ofPoint direction, float thickness) {
	points.push_back(point);

	/*ribbon.clear();
	ribbon.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
	for (unsigned int i = 1; i < points.size(); i++) {*/

	int index = points.size() - 2;
	if (index < 0)
		return;
	//find this point and the next point
	ofVec3f thisPoint = point;
	ofVec3f nextPoint = points[index];

	//ofVec3f direction = (nextPoint - thisPoint);
	

	//get the distance from one point to the next
	float distance = direction.length();
	if (distance < distanceThreshold) {
		points.pop_back();
		return;
	}

	ofVec3f unitDirection = direction.getNormalized();

	//find both directions to the left and to the right
	ofVec3f toTheLeft = unitDirection.getRotated(-90, ofVec3f(0, 0, 1));
	ofVec3f toTheRight = unitDirection.getRotated(90, ofVec3f(0, 0, 1));

	//		cout << "brush size " << thisPoint.z << endl;
	//float thickness = 20;// (thisPoint.z, 0, 150, 20, 30, true);// ofMap(distance, 0, 100, 20, 10, true);
	//calculate the points to the left and to the right
	//by extending the current point in the direction of left/right by the length
	ofVec3f leftPoint = thisPoint + toTheLeft*thickness;
	ofVec3f rightPoint = thisPoint + toTheRight*thickness;

	ofVec3f check = leftPoint - rightPoint;
	cout << "Check distance " << check.length() << endl;
	//add these points to the triangle strip
	ofFloatColor c(brushRGBColor.r / 255.0f, brushRGBColor.g / 255.0f, brushRGBColor.b / 255.0f, brushAlpha);
	
	//cout << "Adding points to ribbon " << leftPoint << " - " << rightPoint << endl;
	ribbon.addVertex(ofVec3f(leftPoint.x, leftPoint.y, 0));
	ribbon.addTexCoord(ofVec2f(index / maxPoints * strokeTex.getWidth(), 0));
	ribbon.addColor(c);
		
	ribbon.addVertex(ofVec3f(rightPoint.x, rightPoint.y, 0));
	ribbon.addTexCoord(ofVec2f(index / maxPoints * strokeTex.getWidth(), strokeTex.getHeight()));
	ribbon.addColor(c);


	//}
}

void PMBaseLayer::drawStrokes() {
	ofScale(1.6f, 1.6f, 1.0f);
	for (Stroke & m : pastStrokes) {
		m.draw();
		if (showWireframe) {
			ofSetColor(100, 100, 100);
			m.drawWireframe();
		}
	}

	strokeTex.getTextureReference().bind();
	ribbon.draw();
	strokeTex.getTextureReference().unbind();
	if (showWireframe) {
		ofSetColor(100, 100, 100);
		ribbon.drawWireframe();
	}
}

void PMBaseLayer::finishStroke() {
	pastStrokes.push_back(Stroke(ribbon, strokeTex.getTexture(), ofColor(brushRGBColor, int(brushAlpha * 255))));
	ribbon.clear();
	points.clear();
}

void PMBaseLayer::setBrushSize(int _brushSize)
{
    brushSize = _brushSize;
    brush->setSize(brushSize, brushSize);
}

#pragma mark - Audio events

void PMBaseLayer::melBandsChanged(float energy)
{
    // Layer4: band0 - Layer1: band1 - Layer2: band2 - Layer3: band3
    //int melBandIndex = (layerID != 4) ? layerID : 0;
    //float energy = melBandsParams.bandsEnergy[melBandIndex];
    //Aquest valors son arbitraris ja que el que volem es aconseguir tots els paràmetres que vagin de 0 a 1
    float normalizedEnergy = ofMap(energy, energyMin, energyMax, 0, 1);
//    cout<<energyMin<<" "<<energyMax<<endl;
#if ENABLE_KINECT
    float normalizedZ = ofMap((nodeInitialZ-kinectNodeData.pos.z), -0.3, 0.3, 0, 1);
    float normalizedVelocity = ofMap(kinectNodeData.v.length(), 0, 100, 0, 1);
    float normalizedAcceleration = ofMap(kinectNodeData.a, 0, 20, 0, 1);
#endif
    
    //Size Edu
    {
        //Aqui tenim els valors entre 0 i 1, i el factor el que fa es donar importància
        float factorizedEnergySize = normalizedEnergy*sizeEnergyScaleFactor;
#if ENABLE_KINECT
        float factorizedZSize = normalizedZ*sizeZScaleFactor;
        float factorizedAccel = normalizedAcceleration*sizeAccelerationScaleFactor;
        float scales_total = sizeEnergyScaleFactor+sizeZScaleFactor+sizeAccelerationScaleFactor;
        int newBrushSize = ofMap(factorizedEnergySize + factorizedZSize + factorizedAccel, 0, scales_total, sizeMin, sizeMax, true);
//        if(layerID==2)
//            cout<<"Energy: "<<factorizedEnergySize<<"----Z: "<<factorizedZSize<<"----Accel: "<<factorizedAccel<<"---BrushSize: "<<newBrushSize<<endl;
#else
        int newBrushSize = ofMap(factorizedEnergySize, 0, 1, sizeMin, sizeMax);
#endif
        //if(!didShoot)
            setBrushSize(newBrushSize);
    }

    // Alpha Edu
    {
        float factorizedEnergyAlpha = normalizedEnergy*alphaEnergyScaleFactor;
#if ENABLE_KINECT
        float factorizedZAlpha = normalizedZ*alphaZScaleFactor;
        float factorizedVel;
        if(kinectNodeData.v.length()!= 1) factorizedVel=normalizedVelocity*alphaVelocityScaleFactor; else factorizedVel=0.5;
#if ENABLE_KNEES_DETECTION
        brushAlpha = ofMap(factorizedEnergyAlpha *factorizedVel * factorizedZAlpha, 0, 1, alphaMin, alphaMax, true);
#else
        if(didShoot || layerID==1 || layerID ==2)
            brushAlpha = ofMap(factorizedEnergyAlpha *factorizedVel * factorizedZAlpha, 0, 1, alphaMin, alphaMax, true);
#endif
#else
        brushAlpha = ofMap(factorizedEnergyAlpha, 0, 1, alphaMin, alphaMax, true);
#endif
    }

    //Hue Edu
    {
        float hueOffset = ofMap(hueVariation, 0, 1, 0, 255, true); //Maps % to absolute hue variation values
        int hueIncrement=ofMap(normalizedEnergy, 0, 1, -1, 1)*hueOffset; //maps energy to -1 1, then aplies scale factor to finaly get a number between -hueOffset and hueoffset
        hueIncrement=ofMap(hueIncrement, -hueOffset, hueOffset, -hueOffset, hueOffset, true);
        brushRGBColor.setHue(brushHSBColor.hue+hueIncrement);
    }

    //Saturation Edu
    {
        float saturationOffset = ofMap(saturationVariation, 0, 1, 0, 255, true); //Maps % to absolute Saturation variation values
        int saturationIncrement=ofMap(normalizedEnergy, 0, 1, -1, 1)*saturationOffset;
        saturationIncrement=ofMap(saturationIncrement, -saturationOffset, saturationOffset, -saturationOffset, saturationOffset, true);
        brushRGBColor.setSaturation(brushHSBColor.saturation+saturationIncrement);
    }
   
    //Brightness Edu
    {
        float brightnessOffset = ofMap(brightnessVariation, 0, 1, 0, 255, true); //Maps % to absolute brightness variation values
        int brightnessIncrement=ofMap(normalizedEnergy, 0, 1, -1, 1)*brightnessOffset;
        brightnessIncrement=ofMap(brightnessIncrement, -brightnessOffset, brightnessOffset, -brightnessOffset, brightnessOffset, true);
        brushRGBColor.setBrightness(brushHSBColor.brightness+brightnessIncrement);
    }
}


void PMBaseLayer::keyPressed(ofKeyEventArgs &a){

}

void PMBaseLayer::keyReleased(ofKeyEventArgs &a){
    
}
