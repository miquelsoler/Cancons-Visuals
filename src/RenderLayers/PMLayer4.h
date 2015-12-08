//
// Created by Miquel Àngel Soler on 4/12/15.
//

#ifndef PMCANCONS_VISUALS_PMLAYER4_H
#define PMCANCONS_VISUALS_PMLAYER4_H

#include "PMBaseLayer.h"

static const int MARGIN = 50;
static const int INITIAL_SHAKE_SPEED = 30;
static const float SPEED_DECREMENT = 0.5;
static const float SIZE_DECREMENT = 0.2f;
static const int INITIAL_SHAKE_SIZE = BRUSH_MAX_SIZE*4;

class PMLayer4 : public PMBaseLayer
{
public:

    PMLayer4(int fboWidth, int fboHeight, KinectNodeType kinectNodeType);

    void setup();
    void update() override;
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
    
private:
    bool        isShaked;
    float       beginShakeTime;
};


#endif //PMCANCONS_VISUALS_PMLAYER4_H
