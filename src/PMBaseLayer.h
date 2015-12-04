//
// Created by Miquel Àngel Soler on 4/12/15.
//

#ifndef PMCANCONS_VISUALS_PMBASELAYER_H
#define PMCANCONS_VISUALS_PMBASELAYER_H

#include "ofMain.h"

class PMBaseLayer
{
public:

    PMBaseLayer(int _fboWidth, int _fboHeight);

    virtual void update() = 0;
    virtual void draw() = 0;

protected:

    int fboWidth, fboHeight;
};


#endif //PMCANCONS_VISUALS_PMBASELAYER_H
