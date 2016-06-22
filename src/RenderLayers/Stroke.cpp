#include "Stroke.h"

Stroke::Stroke(ofMesh mesh, ofTexture tex, float lifeDec, float _minAlpha) {
	ribbon = mesh;
	texture = tex;
	//color = col;		
	lifeDecrement = lifeDec;
	life = 0;
	minAlpha = _minAlpha;
}

void Stroke::draw() {
	if (lifeDecrement > 0.f) {
		int index = 0;
		for (ofFloatColor &color : ribbon.getColors()) {
			if (color.a > minAlpha) {
				color.a -= lifeDecrement;
				ribbon.setColor(index, color);
			}
			index++;
		}
	}
	texture.bind();
	ribbon.draw();
	texture.unbind();
	life++;
}

void Stroke::drawWireframe() {
	ofSetLineWidth(1);
	ribbon.drawWireframe();
}