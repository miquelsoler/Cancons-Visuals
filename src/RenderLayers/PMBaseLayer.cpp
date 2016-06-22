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
	noiseSpeed = 0.1;
	kneeScaleFactor = 10;
	layersGui->bindBehaviour(&brushSpeed, &curveSize, &noiseSpeed, &kneeScaleFactor, &maxLife);

	layersGui->bindAlphaThreshold(&alphaThreshold);
	layersGui->bindStrokeFadeOut(&strokeFadeOut);

	layersGui->bindDistanceThreshold(&distanceThreshold);
	showWireframe = false;
	layersGui->bindWireframeToggle(&showWireframe);
	layersGui->bindmaxDistance(&maxDistance);

	
	//setup Gui
	layersGui->init(layerID, 5, 5);
	layersGui->setBackgroundColor(ofColor::gray);
	layersGui->setVisible(false);
	layersGui->loadPreset(0);


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
	ofImage tex;
	tex.loadImage("strokes/oil/oil1.png");
	textures.push_back(tex);
	tex.loadImage("strokes/oil/oil2.png");
	textures.push_back(tex);
	tex.loadImage("strokes/oil/oil3.png");
	textures.push_back(tex);
	tex.loadImage("strokes/oil/oil4.png");
	currentTexture = 0;
	ribbon.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
}

void PMBaseLayer::update()
{
	brushRGBColor = PMColorsSelector::getInstance().getColor(layerID);
	brushRGBColor.getHsb(brushHSBColor.hue, brushHSBColor.saturation, brushHSBColor.brightness);
    brushPrevPosition = brushPosition;
	actualNodePrevPosition = actualNodePosition;

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

    if (kinectNodeData.a / KINECT_ACCEL_FACTOR > KINECT_ACCEL_THRESHOLD) {
        brushDirection += (kinectNodeData.v.normalize() * (kinectNodeData.a / 3));
    }
    brushPosition += (brushDirection * brushSpeed);
	ofPoint brushDirectionUnormalized = brushDirection;
    brushDirection.normalize();
	
	//Fort Pienc version
	ofPoint newPoint;
	if (layerID == 1 || layerID == 2)
		newPoint = ofPoint(kinectNodeData.pos.x * ofGetWidth(), kinectNodeData.pos.y * ofGetHeight(), kinectNodeData.pos.z * 100);
	// Knees follow perlin noise afected by real movement
	else {
		if (PERFORMANCE_MODE) {
			newPoint = ofPoint(kinectNodeData.pos.x * ofGetWidth(), kinectNodeData.pos.y * ofGetHeight(), kinectNodeData.pos.z * 100);
		}
		else {
			float heightSpan = ofNoise(layerID * 1000, ofGetElapsedTimef() * noiseSpeed) * 0.7 + 0.3; //make sure knees range stay in the lower side of the canvas
			newPoint = ofPoint(ofNoise(ofGetElapsedTimef() * noiseSpeed, layerID * 1000) * ofGetWidth(), heightSpan * ofGetHeight(), kinectNodeData.pos.z * 100);
			actualNodePosition = ofPoint(kinectNodeData.pos.x * ofGetWidth(), kinectNodeData.pos.y * ofGetHeight(), kinectNodeData.pos.z * 100);
			ofPoint direction = actualNodePosition - actualNodePrevPosition;
			prevDirection = 0.2 * direction + 0.8 * prevDirection;
			newPoint += prevDirection * kneeScaleFactor;
		}
	}
	//cout << "Adding point z" << kinectNodeData.pos.z * 400 << endl;

	int index = points.size() - 1;
	if (index >= 0) {
		ofVec3f thisPoint = newPoint;
		ofVec3f nextPoint = points[index];
		ofVec3f direction = (nextPoint - thisPoint);
		float distance = direction.length();
		brushVelocity = distance;
		if (distance > maxDistance) {
			//crear nuevos vertices intermedio
			//cout << "Creating vertices" << endl;
			float thick = (brushSizes[index] + brushSize) / 2.0f;
			ofPoint n = (thisPoint + nextPoint) / 2.0f;
			addPointToRibbon(n, brushDirection, thick);
		}
	}

	addPointToRibbon(newPoint, brushDirection, brushSize);
	brush->update(int(newPoint.x), int(newPoint.y));
	//cout << "mouse pos " << newPoint << endl;
	if (points.size() > maxPoints)
		finishStroke();
}

void PMBaseLayer::draw()
{
#if ENABLE_MULTIPLE_FBOS
    layerFBO.begin();
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
#endif
   // ofSetColor(brushRGBColor, int(brushAlpha * 255));
	drawStrokes(); 

#if ENABLE_MULTIPLE_FBOS
    layerFBO.end();
#endif
}

void PMBaseLayer::addPointToRibbon(ofPoint point, ofPoint direction, float thickness) {
	points.push_back(point);
	brushSizes.push_back(thickness);

	int index = points.size() - 2;
	if (index < 0)
		return;
	//find this point and the next point
	ofVec3f thisPoint = point;
	ofVec3f nextPoint = points[index];

	//direction = (nextPoint - thisPoint);
	//get the distance from one point to the next
	float distance = (nextPoint - thisPoint).length();
	if (distance < distanceThreshold) {
		points.pop_back();
		brushSizes.pop_back();
		return;
	}

	ofVec3f unitDirection = direction.getNormalized();
	//find both directions to the left and to the right
	//ofVec3f toTheLeft = unitDirection.getRotated(-90, ofVec3f(0, 0, 1));
	//ofVec3f toTheRight = unitDirection.getRotated(90, ofVec3f(0, 0, 1));
	ofVec3f axis = direction.cross(ofVec3f(0,-1,0)).getNormalized();
	//cout << direction << " - " << axis << endl;
	ofVec3f toTheLeft = unitDirection.getRotated(-90, axis);
	ofVec3f toTheRight = unitDirection.getRotated(90, axis);

	ofVec3f leftPoint = thisPoint + toTheLeft * thickness;
	ofVec3f rightPoint = thisPoint + toTheRight*thickness;

	//add these points to the triangle strip
	ofFloatColor c(brushRGBColor.r / 255.0f, brushRGBColor.g / 255.0f, brushRGBColor.b / 255.0f, brushAlpha);
	
	ribbon.addVertex(ofVec3f(leftPoint.x, leftPoint.y, leftPoint.z));
	ribbon.addTexCoord(ofVec2f(index / maxPoints * strokeTex.getWidth(), 0));
	ribbon.addColor(c);
		
	ribbon.addVertex(ofVec3f(rightPoint.x, rightPoint.y, rightPoint.z));
	ribbon.addTexCoord(ofVec2f(index / maxPoints * strokeTex.getWidth(), strokeTex.getHeight()));
	ribbon.addColor(c);
}

void PMBaseLayer::drawStrokes() {
	textures[currentTexture].getTextureReference().bind();
	ribbon.draw();
	textures[currentTexture].getTextureReference().unbind();
	if (showWireframe) {
		ofSetColor(100, 100, 100);
		ribbon.drawWireframe();
	}
}

void PMBaseLayer::finishStroke() {
	// we know store all past strokes in a unique vector in PMRenderer so they are all drawn in the creation order
	/*pastStrokes.push_back(Stroke(ribbon, textures[currentTexture].getTexture(), strokeFadeOut));*/
	float minAlpha = PERFORMANCE_MODE ? 0 : 0.1;
	strokes->push_back(Stroke(ribbon, textures[currentTexture].getTexture(), strokeFadeOut, minAlpha));
	ribbon.clear();
	points.clear();
	brushSizes.clear();
	currentTexture = (int)ofRandom(0, textures.size());
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
    float normalizedEnergy = ofMap(energy, energyMin, energyMax, 0, 1, true);
//    cout<<energyMin<<" "<<energyMax<<endl;
#if ENABLE_KINECT
    float normalizedZ = ofMap((nodeInitialZ-kinectNodeData.pos.z), -0.3, 0.3, 0, 1);
    float normalizedVelocity = ofMap(kinectNodeData.v.length(), 0, 10, 0, 1, true);
    float normalizedAcceleration = ofMap(kinectNodeData.a, 0, 20, 0, 1);
#endif
    
    //Size Edu
    {
        //Aqui tenim els valors entre 0 i 1, i el factor el que fa es donar importància
        float factorizedEnergySize = normalizedEnergy * sizeEnergyScaleFactor;
#if ENABLE_KINECT
        //float factorizedZSize = normalizedZ * sizeZScaleFactor;
        //float factorizedAccel = normalizedAcceleration * sizeAccelerationScaleFactor;
		float factorizedAccel = ofMap(brushVelocity , 0, maxDistance, 0.0, 1.0, true) * sizeAccelerationScaleFactor;
        float scales_total = sizeEnergyScaleFactor +  sizeAccelerationScaleFactor;
        int newBrushSize = ofMap(factorizedEnergySize + factorizedAccel, 0, scales_total, sizeMin, sizeMax, true);
#else
        int newBrushSize = ofMap(factorizedEnergySize, 0, 1, sizeMin, sizeMax);
#endif
        setBrushSize(newBrushSize);
    }

    // Alpha Edu
    {

        float factorizedVel;
		//factorizedVel = normalizedVelocity * alphaVelocityScaleFactor;
		factorizedVel = brushVelocity * alphaVelocityScaleFactor;

		brushAlpha = ofMap(factorizedVel, 0, maxDistance, alphaMin, alphaMax, true);
		// if energy lower than threshold (silence) do not paint (by having full transparency)
		if (normalizedEnergy < alphaThreshold)
			brushAlpha = 0;
		//cout << "Alpha " << brushAlpha << endl;
    }
   
    //Brightness
    {
		float brightnessOffset =  ofMap(brightnessVariation, 0, 1, 0, 255, true); //Maps % to absolute brightness variation values
        int brightnessIncrement = ofMap(normalizedEnergy, 0, 1, -0.5, 0.5)*brightnessOffset;
        //brightnessIncrement=ofMap(brightnessIncrement, -brightnessOffset, brightnessOffset, -brightnessOffset, brightnessOffset, true);
        brushRGBColor.setBrightness(brushHSBColor.brightness + brightnessIncrement);
		//cout << normalizedEnergy << endl;
    }
}


void PMBaseLayer::keyPressed(ofKeyEventArgs &a){
	if (a.key == 'R')
		pastStrokes.clear();
	else if(a.key == 'h'){
		PMColorsSelector::getInstance().nexPalette();
	}
}

void PMBaseLayer::keyReleased(ofKeyEventArgs &a){
    
}
