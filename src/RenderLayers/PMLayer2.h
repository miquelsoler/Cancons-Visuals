//
// Created by Miquel Àngel Soler on 4/12/15.
//

#ifndef PMCANCONS_VISUALS_PMLAYER2_H
#define PMCANCONS_VISUALS_PMLAYER2_H

#include "PMBaseLayer.h"

//static const float Z_SIZE_OFFSET  = 1;
//static const float Z_SIZE_FACTOR = 10;

class PMLayer2 : public PMBaseLayer
{
public:

    PMLayer2(int fboWidth, int fboHeight, KinectNodeType kinectNodeType);

    void setup(ofPoint initialPosition);
    void update();
    void draw();

    //Audio listeners
    void pitchChanged(pitchParams &pitchParams) override;
    void energyChanged(energyParams &energyParams) override;
    void silenceStateChanged(silenceParams &silenceParams) override;
    void pauseStateChanged(pauseParams &_auseParams) override;
    void onsetDetected(onsetParams &onsetParams) override;
    void shtDetected(shtParams &shtParams) override;
    void melodyDirection(melodyDirectionParams &melodyDirectionParams) override;
    void melBandsChanged(melBandsParams &melBandsParams) override;
};


#endif //PMCANCONS_VISUALS_PMLAYER2_H
