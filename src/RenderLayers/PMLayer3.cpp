//
// Created by Miquel Àngel Soler on 4/12/15.
//

#include "PMLayer3.h"

static const int MARGIN = 50; //Valor on es queda el pinzell encomptes de marxar a l'infinit
static const int INITIAL_SHAKE_SPEED = 30; //la velocitat en la qual es dispara
static const float SPEED_DECREMENT = 0.3; //la desecaleració
static const int SIZE_DECREMENT = 1; //com varia de mida
static const int INITIAL_SHAKE_SIZE = BRUSH_MAX_SIZE*4; //la mida inicial del pinzell quan es dispara
static const int    DIR_HISTORY_SIZE = 10; //es perque agafi be la direcció

PMLayer3::PMLayer3(int _fboWidth, int _fboHeight, KinectNodeType _kinectNodeType)
        : PMBaseLayer(_fboWidth, _fboHeight, _kinectNodeType)
{
    layerID = 3;
    didShake = false;
    for(int i=0; i<DIR_HISTORY_SIZE; i++)
        directionHistory.push_back(ofPoint(0,0));
}

void PMLayer3::setup(ofPoint initialPosition)
{
    PMBaseLayer::setup(initialPosition);
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
    brushHSBColor.brightness = ofMap(myEnergy, 0.0, bandMaxEnergy, brushMinBrightness, brushMaxBrightness, true);
    brushRGBColor.setHsb(brushHSBColor.hue, brushHSBColor.saturation, brushHSBColor.brightness);
    
    brushAlpha = ofMap(myEnergy, 0.0, bandMaxEnergy, brushMinAlpha, brushMaxAlpha);
    
//    float myEnergy = melBandsParams.bandsEnergy[3];
//    if(!didShake){
//        int newSize = int(ofMap(myEnergy, 0.0, bandMaxEnergy, brushMinSize, brushMaxSize, true));
//    
//#if ENABLE_MULTIPLE_FBOS
//    // TODO: Remove after multiple FBO tests succeed.
//    newSize *= 10;
//#endif
//    brush->setSize(newSize, newSize);
//    }
//    cout << "Brush Size L3> En:" << myEnergy << " Size: " << newSize << endl;
}