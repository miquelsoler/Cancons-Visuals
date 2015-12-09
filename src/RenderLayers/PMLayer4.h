//
// Created by Miquel Àngel Soler on 4/12/15.
//

#ifndef PMCANCONS_VISUALS_PMLAYER4_H
#define PMCANCONS_VISUALS_PMLAYER4_H

#include "PMBaseLayer.h"

class PMLayer4 : public PMBaseLayer
{
public:

    PMLayer4(int fboWidth, int fboHeight, KinectNodeType kinectNodeType);

    void setup(ofPoint initialPosition);
    void update();
    void draw();

private:
    bool            didShake;
    float           beginShakeTime;
    deque<ofPoint>  directionHistory;
    
    float           shootSizeDecrement;
    float           shootSpeedDecrement;
    int             shootMargin;
};


#endif //PMCANCONS_VISUALS_PMLAYER4_H
