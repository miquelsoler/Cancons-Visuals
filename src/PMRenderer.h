//
// Created by Miquel Àngel Soler on 4/12/15.
//

#ifndef PMCANCONS_VISUALS_PMRENDERER_H
#define PMCANCONS_VISUALS_PMRENDERER_H

#include "ofMain.h"
#include "PMUICanvasBrushRenderer.h"
#include "PMLayer1.h"
#include "PMLayer2.h"
#include "PMLayer3.h"
#include "PMLayer4.h"

class PMRenderer
{
public:

    PMRenderer();

    void setup();
    void update();
    void draw();

    void addLayer(PMBaseLayer *layer);

private:

    void drawIntoFBO();

    vector<PMBaseLayer *>       layers;
    ofFbo                       fbo;

    PMUICanvasBrushRenderer     *gui;
};


#endif //PMCANCONS_VISUALS_PMRENDERER_H
