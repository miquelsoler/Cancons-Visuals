//
// Created by Miquel Àngel Soler on 4/12/15.
//

#ifndef PMCANCONS_VISUALS_PMRENDERER_H
#define PMCANCONS_VISUALS_PMRENDERER_H

#include "ofMain.h"
#include "PMBaseLayer.h"
#include "Defaults.h"
#include "ofxTween.h"
#include "ofxSpout2Sender.h"

class PMRenderer
{
public:

    PMRenderer();

    void setup();
    void update();
    void draw();

    void exportToImage(string path);
    void resetPositions();

	void melBandsChange(vector<float> melBands);
	void keyPressed(ofKeyEventArgs &a);
	void keyReleased(ofKeyEventArgs &a) {};
private:

    void drawIntoFBO();

    vector<PMBaseLayer *>       layers;
    ofFbo                       mainFBO;
#if ENABLE_MULTIPLE_FBOS
    ofFbo                       backgroundFBO;
#endif
	vector<Stroke> strokes;

	ofColor prevColor;
	bool tweening ;
	float counter;
	ofxTween tweenColor;
	ofxEasingLinear easing;

	ofxSpout2::Sender spout;
};


#endif //PMCANCONS_VISUALS_PMRENDERER_H
