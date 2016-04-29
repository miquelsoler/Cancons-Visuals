//
// Created by Miquel Àngel Soler on 4/12/15.
//

#ifndef PMCANCONS_VISUALS_PMLAYER2_H
#define PMCANCONS_VISUALS_PMLAYER2_H

#include "PMBaseLayer.h"

class PMLayer2 : public PMBaseLayer
{
public:

    PMLayer2(int fboWidth, int fboHeight, KinectNodeType kinectNodeType);

    void setup(ofPoint initialPosition);
    void update();
    void draw();
};


#endif //PMCANCONS_VISUALS_PMLAYER2_H
