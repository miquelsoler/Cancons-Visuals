//
// Created by Miquel Àngel Soler on 4/12/15.
//

#include "PMLayer2.h"

static const float Z_SIZE_OFFSET  = 2;
static const float Z_SIZE_FACTOR = 10;

static const int SATURATION_FACTOR = 50;

PMLayer2::PMLayer2(int _fboWidth, int _fboHeight, KinectNodeType _kinectNodeType) : PMBaseLayer(_fboWidth, _fboHeight, _kinectNodeType)
{
    layerID = 2;
}

void PMLayer2::setup(ofPoint initialPosition)
{
    PMBaseLayer::setup(initialPosition);
}

void PMLayer2::update()
{
    PMBaseLayer::update();
#if ENABLE_KINECT
    int newBrushSize = int((((nodeInitialZ-kinectNodeData.z)*Z_SIZE_FACTOR)+Z_SIZE_OFFSET)*BRUSH_MAX_SIZE);
    cout<<newBrushSize<<endl;
    if(newBrushSize<BRUSH_MIN_SIZE)
        setBrushSize(BRUSH_MIN_SIZE);
    else if(newBrushSize>BRUSH_MAX_SIZE)
        setBrushSize(BRUSH_MAX_SIZE);
    else
        setBrushSize(newBrushSize);
    
#endif
}

void PMLayer2::draw()
{
    PMBaseLayer::draw();
}

#pragma mark - Audio Events

void PMLayer2::pitchChanged(pitchParams &pitchParams)
{
    int centerMidiNote = 64; //nota midi de referència
    brushHSBColor.saturation+=ofMap(pitchParams.midiNote-centerMidiNote, -64, 64, -SATURATION_FACTOR, SATURATION_FACTOR);
    brushRGBColor.setHsb(brushHSBColor.hue, brushHSBColor.saturation, brushHSBColor.brightness);
}

void PMLayer2::energyChanged(energyParams &energyParams)
{
}

void PMLayer2::silenceStateChanged(silenceParams &silenceParams)
{
}

void PMLayer2::pauseStateChanged(pauseParams &pauseParams)
{
}

void PMLayer2::onsetDetected(onsetParams &onsetParams)
{
}

void PMLayer2::shtDetected(shtParams &shtParams)
{
}

void PMLayer2::melodyDirection(melodyDirectionParams &melodyDirectionParams)
{
}

void PMLayer2::melBandsChanged(melBandsParams &melBandsParams)
{
    float myEnergy = melBandsParams.bandsEnergy[2];
    brushAlpha = ofMap(myEnergy, 0.0, bandMaxEnergy, brushMinAlpha, brushMaxAlpha, true);

//    cout << "Brush Alpha L2> En:" << myEnergy << " Alpha: " << brushAlpha << endl;
}
