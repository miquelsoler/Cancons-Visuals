#include "Stroke.h"

Stroke::Stroke(ofMesh mesh, ofTexture tex, float life) {
	ribbon = mesh;
	texture = tex;
	//color = col;		
	lifeDecrement = life;
}

void Stroke::draw() {
	if (lifeDecrement > 0.f) {
		int index = 0;
		for (ofFloatColor &color : ribbon.getColors()) {
			color.a -= lifeDecrement;
			ribbon.setColor(index, color);
			index++;
		}
	}
	texture.bind();
	ribbon.draw();
	texture.unbind();
}

void Stroke::drawWireframe() {
	ofSetLineWidth(1);
	ribbon.drawWireframe();
}