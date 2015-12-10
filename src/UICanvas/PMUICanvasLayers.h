//
// Created by Miquel Àngel Soler on 10/12/15.
//

#ifndef PMCANCONS_VISUALS_PMUICANVASLAYERS_H
#define PMCANCONS_VISUALS_PMUICANVASLAYERS_H

#include "PMBaseUICanvas.h"

class LayerParams
{
public:
    float energyMin;
    float energyMax;

    float sizeMin;
    float sizeMax;
    float sizeScaleEnergyFactor;
    float sizeScaleAccelerationFactor;
    float sizeScaleZFactor;

    float hueVariation;
    float saturationVariation;
    float brightnessVariation;

    float alphaMin;
    float alphaMax;
    float alphaScaleEnergyFactor;
    float alphaScaleVelocityFactor;
    float alphaScaleZFactor;

    int behaviorSpeed;
    int behaviorCurveSize;

    int shootBehaviorInitialSize;
    int shootBehaviorInitialSpeed;
    float shootBehaviorSpeedDecrement;
    int shootBehaviorSizeDecrement;
    int shootBehaviorCurveAmount;
};


class PMUICanvasLayers : public PMBaseUICanvas
{
public:

    PMUICanvasLayers(string title, int headerFontSize);

    virtual void init(int posX, int posY, bool autosize = true, int width = 0, int height = 0);
    virtual void clear();

    virtual void handleEvents(ofxUIEventArgs &e);
    void keyPressed(int key);
    void keyReleased(int key);

protected:

    void            loadPreset(int presetNumber = 0);
    void            savePreset(int presetNumber = 0);

private:

    vector<LayerParams> layers;

    // Matrix --------------------------------

    ofxUIToggleMatrix       *presetsMatrix;
    int                     getActivePreset();
    bool                    savingPreset;
};


#endif //PMCANCONS_VISUALS_PMUICANVASLAYERS_H
