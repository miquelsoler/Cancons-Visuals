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
    
    void bindSize(int *_minSize, int *_maxSize, float *_scaleEnergy_Size, float *_scaleAcceleration_Size, float *_scaleZ_Size){
        minSize = _minSize;
        maxSize = _maxSize;
        scaleEnergy_Size = _scaleEnergy_Size;
        scaleAcceleration_Size = _scaleAcceleration_Size;
        scaleZ_Size = _scaleZ_Size;
    }
    
    void bindHue(float *_scaleHue, float *_variationHue){
        scaleHue = _scaleHue;
        variationHue = _variationHue;
    }
    
    void bindSaturation(float *_scaleSaturation, float *_variationSaturation){
        scaleSaturation = _scaleSaturation;
        variationSaturation = _variationSaturation;
    }

    void bindBrightness(float *_scaleBrightness, float *_variationBrightness){
        scaleBrightness = _scaleBrightness;
        variationBrightness = _variationBrightness;
    }
    
    void bindAlpha(float *_minAlpha, float *_maxAlpha, float *_scaleAlpha, float *_scaleEnergy_Alpha, float *_scaleVelocity_Alpha, float *_scaleZ_Alpha){
        minAlpha = _minAlpha;
        maxAlpha = _maxAlpha;
        scaleAlpha = _scaleAlpha;
        scaleEnergy_Alpha = _scaleEnergy_Alpha;
        scaleVelocity_Alpha = _scaleVelocity_Alpha;
        scaleZ_Alpha = _scaleZ_Alpha;
    }
    
    void bindBehaviour(float *_curveSpeed, float *_curveSize, float *_noiseSpeed, float *_kneeScaleFactor){
        curveSpeed = _curveSpeed;
        curveSize = _curveSize;
		noiseSpeed = _noiseSpeed;
		kneeScaleFactor = _kneeScaleFactor;
    }

	void bindAlphaThreshold(float * _alphaThreshold) {
		alphaThreshold = _alphaThreshold;
	}

	void bindStrokeFadeOut(float * _strokeFadeOut) {
		strokeFadeOut = _strokeFadeOut;
	}

	void bindDistanceThreshold(float *_distThres) {
		distanceThreshold = _distThres;
	}

	void bindWireframeToggle(bool *_showWireframe) {
		showWireframe = _showWireframe;
	}

	void bindmaxDistance(float *_maxDistance) {
		maxDistance = _maxDistance;
	}
    
	void            loadPreset(int presetNumber = 0);
	void            savePreset(int presetNumber = 0);

protected:

    

private:
    
    int layer;
    bool guiCreated;
    
    // Matrix --------------------------------
    ofxUIToggleMatrix       *presetsMatrix;
    int                     getActivePreset();
    bool                    savingPreset;
    
    //Energy
    float                   *minEnergy, *maxEnergy;
    
    //Size
    int                     *minSize, *maxSize;
    float                   *scaleEnergy_Size, *scaleAcceleration_Size, *scaleZ_Size;
    
    //Hue
    float                   *scaleHue, *variationHue;
    
    //Saturation
    float                   *scaleSaturation, *variationSaturation;
    
    //Brightness
    float                   *scaleBrightness, *variationBrightness;
    
    //Alpha
    float                   *minAlpha, *maxAlpha, *scaleAlpha, *scaleEnergy_Alpha, *scaleVelocity_Alpha, *scaleZ_Alpha, *alphaThreshold, *strokeFadeOut;
    
    //Behaviour
    float                     *curveSpeed, *curveSize, *noiseSpeed, *kneeScaleFactor;

	// Stroke
	float *distanceThreshold;
	bool *showWireframe;
	float *maxDistance;
    
    void                    keyPressed(int key);
    void                    keyReleased(int key);

};


#endif //PMCANCONS_VISUALS_PMUICANVASLAYERS_H
