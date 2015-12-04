//
// Created by Miquel Àngel Soler on 4/12/15.
//

#ifndef PMCANCONS_VISUALS_PMLAYER4_H
#define PMCANCONS_VISUALS_PMLAYER4_H

#include "PMBaseLayer.h"

class PMLayer4 : public PMBaseLayer
{
public:

    PMLayer4(int _fboWidth, int _fboHeight);

    virtual void update();
    virtual void draw();
};


#endif //PMCANCONS_VISUALS_PMLAYER4_H
