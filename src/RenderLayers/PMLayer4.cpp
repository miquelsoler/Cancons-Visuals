//
// Created by Miquel Àngel Soler on 4/12/15.
//

#include "PMLayer4.h"

PMLayer4::PMLayer4(int _fboWidth, int _fboHeight, KinectNodeType _kinectNodeType)
        : PMBaseLayer(_fboWidth, _fboHeight, _kinectNodeType)
{
    layerID = 4;
    didShake = false;
}

void PMLayer4::setup()
{
    PMBaseLayer::setup();
}

void PMLayer4::update()
{
//    PMBaseLayer::update();
    brushPrevPosition = brushPosition;

#if ENABLE_KINECT
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
#else
    kinectNodeData.x = (float) ofGetMouseX() / ofGetWidth();
    kinectNodeData.y = (float) ofGetMouseY() / ofGetHeight();
    kinectNodeData.v = ofPoint(0, 0);
#endif

    if (didShake)
    {
        // TODO: setBrushSize espera un enter, però se li passa un paràmetre al qual se li resta un float.
        setBrushSize(brushSize - 0.2);
        brushSpeed -= 0.5;
        if (brushSize <= BRUSH_MIN_SIZE || brushSpeed <= 0)
            didShake = false;
    }
    else
    {
#if ENABLE_KINECT
        // Direction changes
        ofPoint newDirection = kinectNodeData.v;
        brushDirection = newDirection.normalize();
        brushSpeed = newDirection.length()*5;
#endif

        brushDirection.normalize();
//        cout<<"Velocity: "<<kinectNodeData.v.length()<<"     Aceleration: "<<kinectNodeData.a<<"   Velocity*Acceleration: "<<kinectNodeData.v.length()*kinectNodeData.a<<endl;
        if (kinectNodeData.v.length() * kinectNodeData.a > KINECT_VELO_THRESHOLD)
        {
            beginShakeTime = ofGetElapsedTimeMillis();
            setBrushSize(BRUSH_MAX_SIZE * 4);
            brushDirection = kinectNodeData.v;
            brushSpeed = 30;
            didShake = true;
        }
    }
    brushPosition += (brushDirection * brushSpeed);

    if (brushPosition.x < -MARGIN) brushPosition.x = -MARGIN;
    if (brushPosition.y < -MARGIN) brushPosition.y = -MARGIN;
    if (brushPosition.x > fboWidth + MARGIN) brushPosition.x = fboWidth + MARGIN;
    if (brushPosition.y > fboHeight + MARGIN) brushPosition.y = fboHeight + MARGIN;

    brushDirection.normalize();
    brush->update(int(brushPosition.x), int(brushPosition.y));
}

void PMLayer4::draw()
{
    PMBaseLayer::draw();
}

#pragma mark - Audio Events

void PMLayer4::pitchChanged(pitchParams &pitchParams)
{
}

void PMLayer4::energyChanged(energyParams &energyParams)
{
}

void PMLayer4::silenceStateChanged(silenceParams &silenceParams)
{
}

void PMLayer4::pauseStateChanged(pauseParams &pauseParams)
{
}

void PMLayer4::onsetDetected(onsetParams &onsetParams)
{
}

void PMLayer4::shtDetected(shtParams &shtParams)
{
}

void PMLayer4::melodyDirection(melodyDirectionParams &melodyDirectionParams)
{
}

void PMLayer4::melBandsChanged(melBandsParams &melBandsParams)
{
    float myEnergy = melBandsParams.bandsEnergy[0];
    brushHSBColor.brightness = ofMap(myEnergy, 0.0, bandMaxEnergy, brushMinBrightness, brushMaxBrightness, true);
    brushRGBColor.setHsb(brushHSBColor.hue, brushHSBColor.saturation, brushHSBColor.brightness);

//    cout << "Brush Brightness L4> En:" << myEnergy << " Brightness: " << brushHSBColor.brightness << endl;
}