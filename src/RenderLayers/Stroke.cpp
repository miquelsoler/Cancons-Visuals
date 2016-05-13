#include "Stroke.h"

Stroke::Stroke(ofMesh mesh, ofTexture tex, ofColor col) {
	ribbon = mesh;
	texture = tex;
	color = col;		
}

void Stroke::draw() {
	//ofSetColor(color);
	texture.bind();
	ribbon.draw();
	texture.unbind();
}

void Stroke::drawWireframe() {
	ribbon.drawWireframe();
}