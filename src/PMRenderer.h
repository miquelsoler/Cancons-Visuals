//
// Created by Miquel Àngel Soler on 4/12/15.
//

#ifndef PMCANCONS_VISUALS_PMRENDERER_H
#define PMCANCONS_VISUALS_PMRENDERER_H

#include "ofMain.h"
#include "PMBaseLayer.h"
#include "PMUICanvasBrushRenderer.h"

class PMRenderer
{
public:

    PMRenderer();

    void setup();
    void update();
    void draw();

private:

    void drawIntoFBO();

    vector<PMBaseLayer *>       layers;
    ofFbo                       fbo;

    PMUICanvasBrushRenderer     *gui;
};


#endif //PMCANCONS_VISUALS_PMRENDERER_H
