#pragma once

#include "ofMain.h"

class Stroke {
public:
	Stroke(ofMesh mesh, ofTexture tex, ofColor col);
	void draw();
	void drawWireframe();

protected:
	ofMesh ribbon;
	ofTexture texture;
	ofColor color;
};