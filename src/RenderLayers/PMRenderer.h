//
// Created by Miquel Àngel Soler on 4/12/15.
//

#ifndef PMCANCONS_VISUALS_PMRENDERER_H
#define PMCANCONS_VISUALS_PMRENDERER_H

#include "ofMain.h"
#include "PMBaseLayer.h"
#include "Defaults.h"

class PMRenderer
{
public:

    PMRenderer();

    void setup();
    void update();
    void draw();

    void exportToImage(string path);
    void resetPositions();

private:

    void drawIntoFBO();

    vector<PMBaseLayer *>       layers;
    ofFbo                       mainFBO;
#if ENABLE_MULTIPLE_FBOS
    ofFbo                       backgroundFBO;
#endif
};


#endif //PMCANCONS_VISUALS_PMRENDERER_H
