//
// Created by Miquel Àngel Soler on 4/12/15.
//

#include "PMLayer1.h"

static const float Z_SIZE_OFFSET  = 2;
static const float Z_SIZE_FACTOR = 10;

static const int HUE_FACTOR = 180;

PMLayer1::PMLayer1(int _fboWidth, int _fboHeight, KinectNodeType _kinectNodeType) : PMBaseLayer(_fboWidth, _fboHeight, _kinectNodeType)
{
    layerID = 1;
}

void PMLayer1::setup(ofPoint initialPosition)
{
    PMBaseLayer::setup(initialPosition);
}

void PMLayer1::update()
{
    PMBaseLayer::update();

#if ENABLE_KINECT
    int newBrushSize = int((((nodeInitialZ-kinectNodeData.z)*Z_SIZE_FACTOR)+Z_SIZE_OFFSET)*BRUSH_MAX_SIZE);
//    cout<<newBrushSize<<endl;
    if(newBrushSize<BRUSH_MIN_SIZE)
        setBrushSize(BRUSH_MIN_SIZE);
    else if(newBrushSize>BRUSH_MAX_SIZE)
        setBrushSize(BRUSH_MAX_SIZE);
    else
        setBrushSize(newBrushSize);

#endif
}

void PMLayer1::draw()
{
    PMBaseLayer::draw();
}

#pragma mark - Audio Events

void PMLayer1::pitchChanged(pitchParams &pitchParams)
{
    int centerMidiNote = 64; //nota midi de referència
    brushHSBColor.hue+=ofMap(pitchParams.midiNote-centerMidiNote, -64, 64, -HUE_FACTOR, HUE_FACTOR);
    brushRGBColor.setHsb(brushHSBColor.hue, brushHSBColor.saturation, brushHSBColor.brightness);
}

void PMLayer1::energyChanged(energyParams &energyParams)
{
}

void PMLayer1::silenceStateChanged(silenceParams &silenceParams)
{
}

void PMLayer1::pauseStateChanged(pauseParams &pauseParams)
{
}

void PMLayer1::onsetDetected(onsetParams &onsetParams)
{
}

void PMLayer1::shtDetected(shtParams &shtParams)
{
}

void PMLayer1::melodyDirection(melodyDirectionParams &melodyDirectionParams)
{
}

void PMLayer1::melBandsChanged(melBandsParams &melBandsParams)
{
    float myEnergy = melBandsParams.bandsEnergy[1];
    brushAlpha = ofMap(myEnergy, 0.0, bandMaxEnergy, brushMinAlpha, brushMaxAlpha, true);

//    cout << "Brush Alpha L1> En:" << myEnergy << " Alpha: " << brushAlpha << endl;
}
