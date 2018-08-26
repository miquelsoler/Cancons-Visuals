//
//  PMMotionExtractor.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 16/10/15.
//
//

#include "PMMotionExtractor.hpp"
#include "PMSharedSettings.h"

///--------------------------------------------------------------
bool PMMotionExtractor::setup()
{
	ofAddListener(ofEvents().update, this, &PMMotionExtractor::update);
	
	if (XML.load("settings\\KinectSettings.xml")) {
		//cout << "Kinect Settings loaded" << endl;
		maxTrackingDistance = XML.getValue<float>("//MaxDepth"); 
	}
	else {
		XML.addChild("Settings");
		XML.setTo("Settings");
		XML.addValue("MaxDepth", maxTrackingDistance);
		saveSettings();
		//cout << "unable to load Kinect Settings" <<endl;
	}
	/*if (XML.exists("//MaxDepth")) {
		
	}*/

	//ofAddListener(ofEvents().keyReleased, this, &PMMotionExtractor::keyPressed);
	positionDetectedCounter = 0;

	

#if ENABLE_REMOTE_KINECT
#if ENABLE_LIVE
	receiver.setup(30304);
#else
	receiver.setup(30305);
#endif
#else
	kinect.open();
	kinect.initDepthSource();
	kinect.initColorSource();
	kinect.initInfraredSource();
	kinect.initBodySource();
	kinect.initBodyIndexSource();

	//TODO: Implement kinect detection
	//hasKinect = kinect.isOpen();
	hasKinect = true;

	//createGui to guiApp
	/*PMSharedSettings shared = PMSharedSettings::getInstance();
	auto layersGui = shared.guiApp->getGuiOfLayer(1);
	layersGui->bindmaxUserDistance(& maxUserDistance);*/

	return hasKinect;
#endif
	return true;
}

///--------------------------------------------------------------
void PMMotionExtractor::update(ofEventArgs & a)
{
#if ENABLE_REMOTE_KINECT
	// check for waiting messages
	while (receiver.hasWaitingMessages()) {
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
		//        cout<<m.getAddress()<<endl;
		if (m.getAddress() == (OSC_KINECT_ADDR_BASE + OSC_KINECT_ADDR_STATE)) {
			auto receivedMessage = m.getArgAsString(0);
			if (receivedMessage == OSC_KINECT_STATE_CAPTURING || receivedMessage == OSC_KINECT_STATE_POSITIONED)
				hasUser = true;
			else if(receivedMessage == OSC_KINECT_STATE_DETECTING)
				hasUser = false;
		}
		if (m.getAddress() == (OSC_KINECT_ADDR_BASE + OSC_KINECT_ADDR_KEY))
			cout << "KEY Received " << m.getArgAsChar(0) << " - " << m.getArgAsInt32(1) << endl;
		if (m.getAddress() == (OSC_KINECT_ADDR_BASE + OSC_KINECT_ADDR_MOUSE_MOVE))
			cout << "Mouse moved: " << m.getArgAsInt32(0) << " " << m.getArgAsInt32(1) << endl;
		if (m.getAddress() == (OSC_KINECT_ADDR_BASE + OSC_KINECT_ADDR_MOUSE_PRESS))
			cout << "Mouse pressed: " << m.getArgAsInt32(0) << " " << m.getArgAsInt32(1) << endl;

		if (m.getAddress() == (OSC_KINECT_ADDR_BASE + OSC_KINECT_ADDR_LHAND + OSC_KINECT_ADDR_POSITION))
			handsInfo.leftHand.pos = ofPoint(m.getArgAsFloat(0), m.getArgAsFloat(1), m.getArgAsFloat(2));
		if (m.getAddress() == (OSC_KINECT_ADDR_BASE + OSC_KINECT_ADDR_RHAND + OSC_KINECT_ADDR_POSITION))
			handsInfo.rightHand.pos = ofPoint(m.getArgAsFloat(0), m.getArgAsFloat(1), m.getArgAsFloat(2));
		if (m.getAddress() == (OSC_KINECT_ADDR_BASE + OSC_KINECT_ADDR_LKNEE + OSC_KINECT_ADDR_POSITION))
			handsInfo.leftKnee.pos = ofPoint(m.getArgAsFloat(0), m.getArgAsFloat(1), m.getArgAsFloat(2));
		if (m.getAddress() == (OSC_KINECT_ADDR_BASE + OSC_KINECT_ADDR_RKNEE + OSC_KINECT_ADDR_POSITION))
			handsInfo.rightKnee.pos = ofPoint(m.getArgAsFloat(0), m.getArgAsFloat(1), m.getArgAsFloat(2));

		if (m.getAddress() == (OSC_KINECT_ADDR_BASE + OSC_KINECT_ADDR_LHAND + OSC_KINECT_ADDR_VELOCITY))
			handsInfo.leftHand.v = ofPoint(m.getArgAsFloat(0), m.getArgAsFloat(1), m.getArgAsFloat(2));
		if (m.getAddress() == (OSC_KINECT_ADDR_BASE + OSC_KINECT_ADDR_RHAND + OSC_KINECT_ADDR_VELOCITY))
			handsInfo.rightHand.v = ofPoint(m.getArgAsFloat(0), m.getArgAsFloat(1), m.getArgAsFloat(2));
		if (m.getAddress() == (OSC_KINECT_ADDR_BASE + OSC_KINECT_ADDR_LKNEE + OSC_KINECT_ADDR_VELOCITY))
			handsInfo.leftKnee.v = ofPoint(m.getArgAsFloat(0), m.getArgAsFloat(1), m.getArgAsFloat(2));
		if (m.getAddress() == (OSC_KINECT_ADDR_BASE + OSC_KINECT_ADDR_RKNEE + OSC_KINECT_ADDR_VELOCITY))
			handsInfo.rightKnee.v = ofPoint(m.getArgAsFloat(0), m.getArgAsFloat(1), m.getArgAsFloat(2));

	}
#else
	if (hasKinect) {
		kinect.update();
		// Count number of tracked bodies
		int numBodiesTracked = 0;
		auto& rawBodies = kinect.getBodySource()->getBodies();
		vector<ofxKFW2::Data::Body> bodies; //should be a vector of references?
		for (auto& body : rawBodies) {
			if (body.tracked) {
				auto joints = body.joints;

				auto currentLocation = joints[JointType_SpineBase].getPosition();
				auto currentDistance = currentLocation.z;
				//float maxTrackingDistance = 2000;
				if (currentDistance < maxTrackingDistance) {
					numBodiesTracked++;
					bodies.push_back(body);
				}
			}
		}
		if (numBodiesTracked != 0) {
			if (!hasUser) {
				hasUser = true;
				ofNotifyEvent(eventUserDetection, hasUser, this);
			}
			//--
			//Getting joint positions (skeleton tracking)
			//--
			//
#ifdef ENABLE_MULTI_USER
			if (numBodiesTracked == 1) {
#endif // ENABLE_MULTI_USER
			{
				auto closestBody = findClosestBody(bodies);
				//auto bodies = kinect.getBodySource()->getBodies();
				//for (auto body : bodies) {
				//	if (body.trackingId == closestBody->trackingId)
				//		break;
				auto body = closestBody;
				{
					//cout << body.trackingId << endl;
					for (auto joint : body.joints) {
						if (joint.first == JointType_HandLeft) {
							handsInfo.leftHand.pos = joint.second.getProjected(kinect.getBodySource()->getCoordinateMapper(), ofxKFW2::ProjectionCoordinates::DepthCamera);
							handsInfo.leftHand.pos.x /= 512;
							handsInfo.leftHand.pos.y /= 424;
							handsInfo.leftHand.pos.z = joint.second.getPosition().z;
						}
						else if (joint.first == JointType_HandRight) {
							handsInfo.rightHand.pos = joint.second.getProjected(kinect.getBodySource()->getCoordinateMapper(), ofxKFW2::ProjectionCoordinates::DepthCamera);
							handsInfo.rightHand.pos.x /= 512;
							handsInfo.rightHand.pos.y /= 424;
							handsInfo.rightHand.pos.z = joint.second.getPosition().z;
						}
						else if (joint.first == JointType_KneeLeft) {
							handsInfo.leftKnee.pos = joint.second.getProjected(kinect.getBodySource()->getCoordinateMapper(), ofxKFW2::ProjectionCoordinates::DepthCamera);
							handsInfo.leftKnee.pos.x /= 512;
							handsInfo.leftKnee.pos.y /= 424;
							handsInfo.leftKnee.pos.z = joint.second.getPosition().z;
						}
						else if (joint.first == JointType_KneeRight) {
							handsInfo.rightKnee.pos = joint.second.getProjected(kinect.getBodySource()->getCoordinateMapper(), ofxKFW2::ProjectionCoordinates::DepthCamera);
							handsInfo.rightKnee.pos.x /= 512;
							handsInfo.rightKnee.pos.y /= 424;
							handsInfo.rightKnee.pos.z = joint.second.getPosition().z;
						}
						else if (joint.first == JointType_Head) {
							auto headPos = joint.second.getProjected(kinect.getBodySource()->getCoordinateMapper(), ofxKFW2::ProjectionCoordinates::DepthCamera);
							headPos.y /= 424;
							if (abs(headPos.y - handsInfo.leftHand.pos.y) < 0.05 && abs(headPos.y - handsInfo.rightHand.pos.y) < 0.05) {
								positionDetectedCounter++;
							}
							else {
								positionDetectedCounter = 0;
							}

							if (positionDetectedCounter >= 60) {
								auto userPositioned = true;
								ofNotifyEvent(eventUserPositioned, userPositioned, this);
								positionDetectedCounter = 0;
							}
						}
					}
				}
			}
#ifdef ENABLE_MULTI_USER
			}else{
				int index = 0;
				for (auto& body : bodies) {
					if (body.tracked) {
						for (auto joint : body.joints) {
							if (joint.first == JointType_HandLeft) {
								if (index == 0) {
									handsInfo.leftHand.pos = joint.second.getProjected(kinect.getBodySource()->getCoordinateMapper(), ofxKFW2::ProjectionCoordinates::DepthCamera);
									handsInfo.leftHand.pos.x /= 512;
									handsInfo.leftHand.pos.y /= 424;
									handsInfo.leftHand.pos.z = joint.second.getPosition().z;
								}
								else if (index == 1 && numBodiesTracked == 2) {
									handsInfo.leftKnee.pos = joint.second.getProjected(kinect.getBodySource()->getCoordinateMapper(), ofxKFW2::ProjectionCoordinates::DepthCamera);
									handsInfo.leftKnee.pos.x /= 512;
									handsInfo.leftKnee.pos.y /= 424;
									handsInfo.leftKnee.pos.z = joint.second.getPosition().z;
								}
							}
							else if (joint.first == JointType_HandRight) {
								if (index == 0 && (numBodiesTracked == 2 || numBodiesTracked == 3)) {
									handsInfo.rightHand.pos = joint.second.getProjected(kinect.getBodySource()->getCoordinateMapper(), ofxKFW2::ProjectionCoordinates::DepthCamera);
									handsInfo.rightHand.pos.x /= 512;
									handsInfo.rightHand.pos.y /= 424;
									handsInfo.rightHand.pos.z = joint.second.getPosition().z;
								}
								else if (index == 1 && numBodiesTracked == 2) {
									handsInfo.rightKnee.pos = joint.second.getProjected(kinect.getBodySource()->getCoordinateMapper(), ofxKFW2::ProjectionCoordinates::DepthCamera);
									handsInfo.rightKnee.pos.x /= 512;
									handsInfo.rightKnee.pos.y /= 424;
									handsInfo.rightKnee.pos.z = joint.second.getPosition().z;
								}
								else if (index == 1 && numBodiesTracked == 4) {
									handsInfo.leftHand.pos = joint.second.getProjected(kinect.getBodySource()->getCoordinateMapper(), ofxKFW2::ProjectionCoordinates::DepthCamera);
									handsInfo.leftHand.pos.x /= 512;
									handsInfo.leftHand.pos.y /= 424;
									handsInfo.leftHand.pos.z = joint.second.getPosition().z;
								}
								else if (index == 2 && (numBodiesTracked == 3 || numBodiesTracked == 4)) {
									handsInfo.leftKnee.pos = joint.second.getProjected(kinect.getBodySource()->getCoordinateMapper(), ofxKFW2::ProjectionCoordinates::DepthCamera);
									handsInfo.leftKnee.pos.x /= 512;
									handsInfo.leftKnee.pos.y /= 424;
									handsInfo.leftKnee.pos.z = joint.second.getPosition().z;
								}
								else if (index == 3 && (numBodiesTracked == 3 || numBodiesTracked == 4)) {
									handsInfo.rightKnee.pos = joint.second.getProjected(kinect.getBodySource()->getCoordinateMapper(), ofxKFW2::ProjectionCoordinates::DepthCamera);
									handsInfo.rightKnee.pos.x /= 512;
									handsInfo.rightKnee.pos.y /= 424;
									handsInfo.rightKnee.pos.z = joint.second.getPosition().z;
								}
							}
							else if (joint.first == JointType_Head && index == 0) {
								auto headPos = joint.second.getProjected(kinect.getBodySource()->getCoordinateMapper(), ofxKFW2::ProjectionCoordinates::DepthCamera);
								headPos.y /= 424;
								if (abs(headPos.y - handsInfo.leftHand.pos.y) < 0.05 && abs(headPos.y - handsInfo.rightHand.pos.y) < 0.05) {
									positionDetectedCounter++;
								}
								else {
									positionDetectedCounter = 0;
								}

								if (positionDetectedCounter >= 60) {
									auto userPositioned = true;
									ofNotifyEvent(eventUserPositioned, userPositioned, this);
									positionDetectedCounter = 0;
								}
							}
						}
					}
					index++;
				}
			}
#endif // ENABLE_MULTI_USER
				computeVelocity(5);
		}
		else {
			if (hasUser) {
				hasUser = false;
				ofNotifyEvent(eventUserDetection, hasUser, this);
				rHandPosHist.clear();
				lHandPosHist.clear();
				rKneePosHist.clear();
				lKneePosHist.clear();
			}
		}

	}
	else if (ofGetMousePressed()) {
		hasUser = true;
		ofNotifyEvent(eventUserDetection, hasUser, this);
		handsInfo.leftHand.pos.x = (float)ofGetMouseX() / (float)ofGetWidth();
		handsInfo.leftHand.pos.y = (float)ofGetMouseY() / (float)ofGetHeight();
		handsInfo.leftHand.pos.z = 1;
		handsInfo.rightHand.pos.x = ofMap(handsInfo.leftHand.pos.x, 0, 1, 1, 0);
		handsInfo.rightHand.pos.y = handsInfo.leftHand.pos.y;
		handsInfo.leftHand.pos.z = 1;
		computeVelocity(5);
		//cout << ofGetMouseX() << endl;
	}
	else {
		hasUser = false;
		ofNotifyEvent(eventUserDetection, hasUser, this);
		rHandPosHist.clear();
		lHandPosHist.clear();
	}
#endif
}

///--------------------------------------------------------------
void PMMotionExtractor::draw(int x, int y, int width, int height, bool drawHands, bool drawBody)
{
#if ENABLE_REMOTE_KINECT

#else
	if (true) {
		auto infraredImage = kinect.getInfraredSource();
		auto infraredPixels = infraredImage->getPixels();
		for (auto & pixel : infraredPixels) {
			pixel += pixel * 2;
		}
		ofTexture drawTexture;
		drawTexture.allocate(512, 424, GL_LUMINANCE);
		drawTexture.loadData(infraredPixels);
		drawTexture.draw(x, y, width, height);
	}
	if (drawBody) {
		kinect.getBodySource()->drawProjected(x, y, width, height, ofxKFW2::ProjectionCoordinates::DepthCamera);
		auto& bodies = kinect.getBodySource()->getBodies();
		for (auto body : bodies) {
			auto bodyBase = body.joints[JointType_SpineBase];
			auto basePos = bodyBase.getProjected(kinect.getBodySource()->getCoordinateMapper(), ofxKFW2::ProjectionCoordinates::DepthCamera);
			basePos = (((basePos / ofVec2f(512, 424)) + ofVec2f(0.05, -0.05)) * ofVec2f(width, height) + ofVec2f(x, y));
			ofDrawBitmapString(ofToString(bodyBase.getPosition().z), basePos);
		}
	}
	if (drawHands) {
		ofPushStyle();
		ofPushMatrix();
		ofTranslate(x, y);
		ofNoFill();
		ofSetLineWidth(3);
		ofSetColor(ofColor::red);
		ofDrawEllipse(handsInfo.rightHand.pos.x * width, handsInfo.rightHand.pos.y * height, 50 + 20 * (handsInfo.rightHand.v.x), 50 + 20 * (handsInfo.rightHand.v.y));
		ofDrawEllipse(handsInfo.leftHand.pos.x * width, handsInfo.leftHand.pos.y * height, 50 + 20 * (handsInfo.leftHand.v.x), 50 + 20 * (handsInfo.leftHand.v.y));
		ofPopMatrix();
		ofPopStyle();
	}
	ofDrawBitmapString(positionDetectedCounter, x, y);
#endif
}

///--------------------------------------------------------------
void PMMotionExtractor::exit()
{
	kinect.close();
}

KinectInfo* PMMotionExtractor::getKinectInfo() {
#if !ENABLE_REMOTE_KINECT
	KinectInfo tempInfo = handsInfo;

	//Compute hand Mean value;
	ofPoint lHandPosMean = ofPoint(0);
	for (auto & tempPos : lHandPosHist) {
		lHandPosMean += tempPos;
	}
	lHandPosMean /= lHandPosHist.size();

	ofPoint rHandPosMean = ofPoint(0);
	for (auto & tempPos : rHandPosHist) {
		rHandPosMean += tempPos;
	}
	rHandPosMean /= rHandPosHist.size();

	//Compute knee Mean value;
	ofPoint lKneePosMean = ofPoint(0);
	for (auto & tempPos : lKneePosHist) {
		lKneePosMean += tempPos;
	}
	lKneePosMean /= lKneePosHist.size();

	ofPoint rKneePosMean = ofPoint(0);
	for (auto & tempPos : rKneePosHist) {
		rKneePosMean += tempPos;
	}
	rKneePosMean /= rKneePosHist.size();

	//Assign mean value to output value;
	tempInfo.leftHand.pos = lHandPosMean;
	tempInfo.rightHand.pos = rHandPosMean;

	//Assign mean value to output value;
	tempInfo.leftKnee.pos = lKneePosMean;
	tempInfo.rightKnee.pos = rKneePosMean;

	handsInfo = tempInfo;
#endif
	return &handsInfo;
}

ofxKFW2::Data::Body PMMotionExtractor::findClosestBody(vector<ofxKFW2::Data::Body> bodies)
{
	ofxKFW2::Data::Body result;
	bool noBody = true;

	double closestBodyDistance = 10000000.0;

	//auto& bodies = kinect.getBodySource()->getBodies();

	for (auto body : bodies)
	{
		if (body.tracked)
		{
			auto joints = body.joints;

			auto currentLocation = joints[JointType_SpineBase].getPosition();

			//auto currentDistance = sqrt(pow(currentLocation.x, 2) + pow(currentLocation.y, 2) + pow(currentLocation.z, 2));
			auto currentDistance = currentLocation.z;


			if (noBody || currentDistance < closestBodyDistance)
			{
				result = body;
				noBody = false;
				closestBodyDistance = currentDistance;
			}
		}
	}

	return result;
}


void PMMotionExtractor::computeVelocity(int meanSize)
{
	//HANDS
	while (rHandPosHist.size() > meanSize)
		rHandPosHist.pop_back();
	while (lHandPosHist.size() > meanSize)
		lHandPosHist.pop_back();

	//KNEES
	while (rKneePosHist.size() > meanSize)
		rKneePosHist.pop_back();
	while (lKneePosHist.size() > meanSize)
		lKneePosHist.pop_back();

	//HANDS
	rHandPosHist.push_front(handsInfo.rightHand.pos);
	lHandPosHist.push_front(handsInfo.leftHand.pos);

	//KNEES
	rKneePosHist.push_front(handsInfo.rightKnee.pos);
	lKneePosHist.push_front(handsInfo.leftKnee.pos);

	//HANDS
	ofPoint rHandPosMean = ofPoint(0);
	for (auto & tempPos : rHandPosHist) {
		rHandPosMean += tempPos;
	}
	rHandPosMean /= rHandPosHist.size();

	ofPoint lHandPosMean = ofPoint(0);
	for (auto & tempPos : lHandPosHist) {
		lHandPosMean += tempPos;
	}
	lHandPosMean /= lHandPosHist.size();

	//KNEES
	ofPoint rKneePosMean = ofPoint(0);
	for (auto & tempPos : rKneePosHist) {
		rKneePosMean += tempPos;
	}
	rKneePosMean /= rKneePosHist.size();

	ofPoint lKneePosMean = ofPoint(0);
	for (auto & tempPos : lKneePosHist) {
		lKneePosMean += tempPos;
	}
	lKneePosMean /= lKneePosHist.size();


	//HANDS
	ofPoint rHandVel = ofPoint(0);
	for (auto & tempPos : rHandPosHist) {
		rHandVel = (tempPos - rHandPosMean)*(tempPos - rHandPosMean);
	}
	rHandVel /= rHandPosHist.size();
	rHandVel *= 1000;
	handsInfo.rightHand.v = rHandVel;

	ofPoint lHandVel = ofPoint(0);
	for (auto & tempPos : lHandPosHist) {
		lHandVel = (tempPos - lHandPosMean)*(tempPos - lHandPosMean);
	}
	lHandVel /= lHandPosHist.size();
	lHandVel *= 1000;
	handsInfo.leftHand.v = lHandVel;


	//Knees
	ofPoint rKneeVel = ofPoint(0);
	for (auto & tempPos : rKneePosHist) {
		rKneeVel = (tempPos - rKneePosMean)*(tempPos - rKneePosMean);
	}
	rKneeVel /= rKneePosHist.size();
	rKneeVel *= 1000;
	handsInfo.rightKnee.v = rKneeVel;

	ofPoint lKneeVel = ofPoint(0);
	for (auto & tempPos : lKneePosHist) {
		lKneeVel = (tempPos - lKneePosMean)*(tempPos - lKneePosMean);
	}
	lKneeVel /= lKneePosHist.size();
	lKneeVel *= 1000;
	handsInfo.leftKnee.v = lKneeVel;
}

bool PMMotionExtractor::reset(bool kinectActivated) {
	kinect.close();
	kinect.open();

	return true;
}


ofPixels PMMotionExtractor::getColorPixels() {
	auto ColoredImage = kinect.getColorSource();
	return ColoredImage->getPixels();
}

void PMMotionExtractor::increaseDistance()
{
	maxTrackingDistance += 0.1;
	if (maxTrackingDistance > 8)
		maxTrackingDistance = 8;
}

void PMMotionExtractor::decreaseDistance()
{
	maxTrackingDistance -= 0.1;
	if (maxTrackingDistance < 0)
		maxTrackingDistance = 0;
}

void PMMotionExtractor::saveSettings() {
	XML.setTo("Settings");
	XML.setValue("MaxDepth", ofToString(maxTrackingDistance));
	XML.save("settings\\KinectSettings.xml");
}

//void PMMotionExtractor::keyPressed(ofKeyEventArgs &e)
//{
//	if (e.key) {
//
//	}
//	else if (e.key) {
//
//	}
//}