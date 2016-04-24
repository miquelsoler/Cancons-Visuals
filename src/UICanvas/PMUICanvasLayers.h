//
// Created by Miquel Àngel Soler on 10/12/15.
//

#ifndef PMCANCONS_VISUALS_PMUICANVASLAYERS_H
#define PMCANCONS_VISUALS_PMUICANVASLAYERS_H

#include "PMBaseUICanvas.h"

class PMUICanvasLayers : public PMBaseUICanvas
{
public:

    PMUICanvasLayers(string title, int headerFontSize);

    virtual void init(int layerNum, int posX, int posY, bool autosize = true, int width = 0, int height = 0);
    virtual void clear();

    virtual void handleEvents(ofxUIEventArgs &e);
    
    //variable binding
    void bindEnergy(float *_minEnergy, float *_maxEnergy){
        minEnergy = _minEnergy;
        maxEnergy = _maxEnergy;
    }

protected:

    void            loadPreset(int presetNumber = 0);
    void            savePreset(int presetNumber = 0);

private:
    
    int layer;
    
    // Matrix --------------------------------
    ofxUIToggleMatrix       *presetsMatrix;
    int                     getActivePreset();
    bool                    savingPreset;
    
    //Energy
    float                   *minEnergy, *maxEnergy;
    
    //Size
    int*                     minSize, maxSize;
    float*                   scaleEnergy_Size, scaleAcceleration_Size, scaleZ_Size;
    
    //Hue
    float*                   scaleHue, variationHue;
    
    //Saturation
    float*                   scaleSaturation, variationSaturation;
    
    //Brightness
    float*                   scaleBrightness, variationBrightness;
    
    //Alpha
    float*                   minAlpha, maxAlpha, scaleAlpha, scaleEnergy_Alpha, scaleVelocity_Alpha, scaleZ_Alpha;
    
    //Behaviour
    int*                     curveSpeed, curveSize;
    
    
    void                    keyPressed(int key);
    void                    keyReleased(int key);

};


#endif //PMCANCONS_VISUALS_PMUICANVASLAYERS_H
