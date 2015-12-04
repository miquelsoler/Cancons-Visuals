//
// Created by Miquel Àngel Soler on 4/12/15.
//

#ifndef PMCANCONS_VISUALS_PMLAYER1_H
#define PMCANCONS_VISUALS_PMLAYER1_H

#include "PMBaseLayer.h"

class PMLayer1 : public PMBaseLayer
{
public:

    PMLayer1(int _fboWidth, int _fboHeight);

    virtual void update();
    virtual void draw();
};


#endif //PMCANCONS_VISUALS_PMLAYER1_H
