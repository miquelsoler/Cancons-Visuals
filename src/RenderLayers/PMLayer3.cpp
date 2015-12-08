//
// Created by Miquel Àngel Soler on 4/12/15.
//

#include "PMLayer3.h"

PMLayer3::PMLayer3(int _fboWidth, int _fboHeight, KinectNodeType _kinectNodeType)
        : PMBaseLayer(_fboWidth, _fboHeight, _kinectNodeType)
{
    layerID = 3;
    didShake = false;
}

void PMLayer3::setup()
{
    PMBaseLayer::setup();
}

void PMLayer3::update()
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
        didShake = false;
    }
    else
    {

        // Direction changes
        ofPoint newDirection = kinectNodeData.v;
        brushDirection = newDirection.normalize();
        brushSpeed = newDirection.length()*5;


        brushDirection.normalize();
//        cout<<kinectNodeData.a / KINECT_ACCEL_FACTOR<<endl;
        if (kinectNodeData.a / KINECT_ACCEL_FACTOR > 1) {
//            cout<<layerID<<"--IS Aceletrstrefd"<<ofGetTimestampString()<<endl;
            didShake = true;
        }
    }
    brushPosition += (brushDirection * brushSpeed);
    brushDirection.normalize();
    brush->update(int(brushPosition.x), int(brushPosition.y));
#else
    PMBaseLayer::update();
#endif
}

void PMLayer3::draw()
{
    PMBaseLayer::draw();
}

#pragma mark - Audio Events

void PMLayer3::pitchChanged(pitchParams &pitchParams)
{
}

void PMLayer3::energyChanged(energyParams &energyParams)
{
}

void PMLayer3::silenceStateChanged(silenceParams &silenceParams)
{
}

void PMLayer3::pauseStateChanged(pauseParams &pauseParams)
{
}

void PMLayer3::onsetDetected(onsetParams &onsetParams)
{
}

void PMLayer3::shtDetected(shtParams &shtParams)
{
}

void PMLayer3::melodyDirection(melodyDirectionParams &melodyDirectionParams)
{
}

void PMLayer3::melBandsChanged(melBandsParams &melBandsParams)
{
    float myEnergy = melBandsParams.bandsEnergy[3];
    int newSize = int(ofMap(myEnergy, 0.0, bandMaxEnergy, brushMinSize, brushMaxSize, true));
    brush->setSize(newSize, newSize);

//    cout << "Brush Size L3> En:" << myEnergy << " Size: " << newSize << endl;
}