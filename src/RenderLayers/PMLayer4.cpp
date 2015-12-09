//
// Created by Miquel Àngel Soler on 4/12/15.
//

#include "PMLayer4.h"

static const int DIR_HISTORY_SIZE = 10; //es perque agafi be la direcció

PMLayer4::PMLayer4(int _fboWidth, int _fboHeight, KinectNodeType _kinectNodeType)
        : PMBaseLayer(_fboWidth, _fboHeight, _kinectNodeType)
{
    layerID = 4;
    didShake = false;
    for(int i=0; i<DIR_HISTORY_SIZE; i++)
        directionHistory.push_back(ofPoint(0,0));
}

void PMLayer4::setup(ofPoint initialPosition)
{
    PMBaseLayer::setup(initialPosition);
    shootSizeDecrement=0.2;
    shootSpeedDecrement=0.4;
    shootMargin=30;
}

void PMLayer4::update()
{
#if ENABLE_KINECT
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

    if (didShake)
    {
        setBrushSize(brushSize - shootSizeDecrement);
        brushSpeed -= shootSpeedDecrement;
        if (brushSize <= sizeMin || brushSpeed <= 0){
            didShake = false;
            setBrushSize(sizeMin);
        }
    }
    else
    {
        // Direction changes
        
        ofPoint newDirection = kinectNodeData.v;
        brushDirection = newDirection.normalize();
        brushSpeed = newDirection.length()*5;

        brushDirection.normalize();
        
        //direction history
        directionHistory.push_back(kinectNodeData.v);
        directionHistory.pop_front();
        if (kinectNodeData.v.length() * kinectNodeData.a > KINECT_VELO_THRESHOLD)
        {
            beginShakeTime = ofGetElapsedTimeMillis();
            setBrushSize(BRUSH_MAX_SIZE * 4);
            brushSpeed = 30;
            didShake = true;
            int directionHistoryMaxIndex=0;
            for(int i=0; i<directionHistory.size(); i++){
                if(directionHistoryMaxIndex < directionHistory[i].length())
                    directionHistoryMaxIndex = i;
            }
            brushDirection=directionHistory[directionHistoryMaxIndex];
        }
    }
    brushPosition += (brushDirection * brushSpeed);

    if (brushPosition.x < -shootMargin) brushPosition.x = -shootMargin;
    if (brushPosition.y < -shootMargin) brushPosition.y = -shootMargin;
    if (brushPosition.x > fboWidth + shootMargin) brushPosition.x = fboWidth + shootMargin;
    if (brushPosition.y > fboHeight + shootMargin) brushPosition.y = fboHeight + shootMargin;

    brushDirection.normalize();
    brush->update(int(brushPosition.x), int(brushPosition.y));
#else
    PMBaseLayer::update();
#endif
}

void PMLayer4::draw()
{
    PMBaseLayer::draw();
}
