//
// Created by Miquel Àngel Soler on 4/12/15.
//

#ifndef PMCANCONS_VISUALS_PMLAYER3_H
#define PMCANCONS_VISUALS_PMLAYER3_H

#include "PMBaseLayer.h"

class PMLayer3 : public PMBaseLayer
{
public:

    PMLayer3(int fboWidth, int fboHeight, KinectNodeType kinectNodeType);

    void setup(ofPoint initialPosition);
    void update();
    void draw();

private:

    bool            didShake;
    float           beginShakeTime;
    deque<ofPoint>  directionHistory;
};


#endif //PMCANCONS_VISUALS_PMLAYER3_H
