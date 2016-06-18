#pragma once

#include "ofMain.h"

class Stroke {
public:
	Stroke(ofMesh mesh, ofTexture tex, float life);
	void draw();
	void drawWireframe();
	int life;

protected:
	ofMesh ribbon;
	ofTexture texture;
	ofColor color;
	float lifeDecrement;
	float minAlpha;
};