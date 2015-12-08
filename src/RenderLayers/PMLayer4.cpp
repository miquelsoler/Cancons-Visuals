//
// Created by Miquel Àngel Soler on 4/12/15.
//

#include "PMLayer4.h"

static const int MARGIN = 50; //Valor on es queda el pinzell encomptes de marxar a l'infinit
static const int INITIAL_SHAKE_SPEED = 30; //la velocitat en la qual es dispara
static const float SPEED_DECREMENT = 0.3; //la desecaleració
static const int SIZE_DECREMENT = 1; //com varia de mida
static const int INITIAL_SHAKE_SIZE = BRUSH_MAX_SIZE*4; //la mida inicial del pinzell quan es dispara
static const int    DIR_HISTORY_SIZE = 10; //es perque agafi be la direcció
static const float CURVE_SIZE=10;

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
        setBrushSize(brushSize - SIZE_DECREMENT);
        brushSpeed -= SPEED_DECREMENT;
        if (brushSize <= BRUSH_MIN_SIZE || brushSpeed <= 0){
            didShake = false;
            setBrushSize(BRUSH_MIN_SIZE);
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

    if (brushPosition.x < -MARGIN) brushPosition.x = -MARGIN;
    if (brushPosition.y < -MARGIN) brushPosition.y = -MARGIN;
    if (brushPosition.x > fboWidth + MARGIN) brushPosition.x = fboWidth + MARGIN;
    if (brushPosition.y > fboHeight + MARGIN) brushPosition.y = fboHeight + MARGIN;

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
    if(didShake)
        brushDirection.rotate(melodyDirectionParams.direction*CURVE_SIZE, ofVec3f(0,0,1)); //rotate arround z axis
}

void PMLayer4::melBandsChanged(melBandsParams &melBandsParams)
{
//    float myEnergy = melBandsParams.bandsEnergy[0];
//    brushHSBColor.brightness = ofMap(myEnergy, 0.0, bandMaxEnergy, brushMinBrightness, brushMaxBrightness, true);
//    brushRGBColor.setHsb(brushHSBColor.hue, brushHSBColor.saturation, brushHSBColor.brightness);
//    
    float myEnergy = melBandsParams.bandsEnergy[3];
    if(!didShake){
        int newSize = int(ofMap(myEnergy, 0.0, bandMaxEnergy, brushMinSize, brushMaxSize, true));
        
#if ENABLE_MULTIPLE_FBOS
        // TODO: Remove after multiple FBO tests succeed.
        newSize *= 10;
#endif
        brush->setSize(newSize, newSize);
    }

//    cout << "Brush Brightness L4> En:" << myEnergy << " Brightness: " << brushHSBColor.brightness << endl;
}