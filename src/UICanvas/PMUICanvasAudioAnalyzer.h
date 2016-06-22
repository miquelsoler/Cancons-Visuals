//
// Created by Miquel Àngel Soler on 7/11/15.
//

#ifndef PMCONCERTPARAULES_PMUICANVASAUDIOANALYZER_H
#define PMCONCERTPARAULES_PMUICANVASAUDIOANALYZER_H

#include "PMBaseUICanvas.h"

class PMUICanvasAudioAnalyzer : public PMBaseUICanvas
{
public:

    PMUICanvasAudioAnalyzer(string title, int headerFontSize);

    virtual void init(int posX, int posY, bool autosize = true, int width = 0, int height = 0);
    virtual void clear();


	//variable binding
	void bindLimits(float *_bandLimit_low, float *_bandLimit_1, float *_bandLimit_2, float *_bandLimit_3, float  *_bandLimit_high) {
		bandLimit_low = _bandLimit_low;
		bandLimit_1 = _bandLimit_1;
		bandLimit_2 = _bandLimit_2;
		bandLimit_3 = _bandLimit_3;
		bandLimit_high = _bandLimit_high;
	}

	/*void bindMaxs(float	*_bandMax_low, float *_bandMax_lowmid, float *_bandMax_highmid, float *_bandMax_high) {
		bandMax_low = _bandMax_low;
		bandMax_lowmid = _bandMax_lowmid;
		bandMax_highmid = _bandMax_highmid;
		bandMax_high = _bandMax_high;
	}*/
	void bindMaxs(float *_bandMaxs) { bandMaxs = _bandMaxs; };

	void bindSpectrums(float *_fullBands, float *_fourBands) {
		fullBands = _fullBands;
		fourBands = _fourBands;
	}

	void updateMaxs();

    virtual void handleEvents(ofxUIEventArgs &e);

	void            loadPreset(int presetNumber = 0);
	void            savePreset(int presetNumber = 0);

protected:
    
    

private:

    // Matrix --------------------------------
    
    ofxUIToggleMatrix       *presetsMatrix;
    int                     getActivePreset();
    bool                    savingPreset;
    
    // Bands control ---------------

	float					*bandLimit_low, *bandLimit_1, *bandLimit_2, *bandLimit_3, *bandLimit_high;
	float					*bandMaxs;
	ofxUISlider				*band_l, *band_lm, *band_hm, *band_h;

    // Vu-Bands---------------------------------
        
    ofxUISpectrum *fullMelSpectrum;
    ofxUISpectrum *melSpectrum;
    
    float *fullBands;
    float *fourBands;

	bool guiCreated;


	// KEYBOARD

	void                    keyPressed(int key);
	void                    keyReleased(int key);
   
};


#endif //PMCONCERTPARAULES_PMUICANVASAUDIOANALYZER_H
