//
//  PMMotionExtractor.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 16/10/15.
//
//

#include "PMMotionExtractor.hpp"

///--------------------------------------------------------------
bool PMMotionExtractor::setup()
{
	ofAddListener(ofEvents().update, this, &PMMotionExtractor::update);
	positionDetectedCounter = 0;

	kinect.open();
	kinect.initDepthSource();
	kinect.initColorSource();
	kinect.initInfraredSource();
	kinect.initBodySource();
	kinect.initBodyIndexSource();

	//TODO: Implement kinect detection
	//hasKinect = kinect.isOpen();
	hasKinect = true;
	return hasKinect;
}

///--------------------------------------------------------------
void PMMotionExtractor::update(ofEventArgs & a)
{
	if (hasKinect) {
		kinect.update();
		// Count number of tracked bodies
		int numBodiesTracked = 0;
		auto& bodies = kinect.getBodySource()->getBodies();
		for (auto& body : bodies) {
			if (body.tracked) {
				numBodiesTracked++;
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
			{
				auto closestBody = findClosestBody();
				//auto bodies = kinect.getBodySource()->getBodies();
				for (auto body : bodies) {
					if (body.trackingId == closestBody->trackingId)
						break;
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
				computeVelocity(5);
			}
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

}

///--------------------------------------------------------------
void PMMotionExtractor::draw(int x, int y, int width, int height, bool drawHands, bool drawBody)
{
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
}

///--------------------------------------------------------------
void PMMotionExtractor::exit()
{
	kinect.close();
}

KinectInfo* PMMotionExtractor::getKinectInfo() {
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
	return &handsInfo;
}

ofxKFW2::Data::Body* PMMotionExtractor::findClosestBody()
{
	ofxKFW2::Data::Body* result = nullptr;

	double closestBodyDistance = 10000000.0;

	auto& bodies = kinect.getBodySource()->getBodies();
	for (auto& body : bodies) {
		if (body.tracked) {

		}
	}

	for (auto body : bodies)
	{
		if (body.tracked)
		{
			auto joints = body.joints;

			auto currentLocation = joints[JointType_SpineBase].getPosition();

			//auto currentDistance = sqrt(pow(currentLocation.x, 2) + pow(currentLocation.y, 2) + pow(currentLocation.z, 2));
			auto currentDistance = currentLocation.z;


			if (result == nullptr || currentDistance < closestBodyDistance)
			{
				result = &body;
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