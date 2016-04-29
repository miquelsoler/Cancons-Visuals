//
// Created by Miquel Àngel Soler on 7/12/15.
//

#ifndef PMCANCONS_VISUALS_PMLAYERMAPPINGS_H
#define PMCANCONS_VISUALS_PMLAYERMAPPINGS_H

#include "../PMSettingsManager.h"

class PMSettingsManagerLayers : public PMSettingsManager
{
public:

    static PMSettingsManagerLayers &getInstance()
    {
        static PMSettingsManagerLayers instance;
        return instance;
    }

    PMSettingsManagerLayers();
    void createJSONSettings() {};

    float getEnergyMin(int layerID);
    float getEnergyMax(int layerID);

    unsigned int getSizeMin(int layerID);
    unsigned int getSizeMax(int layerID);

    float getHueScaleFactor(int layerID);
    float getHueVariation(int layerID);

    float getSaturationScaleFactor(int layerID);
    float getSaturationVariation(int layerID);

    float getBrightnessScaleFactor(int layerID);
    float getBrightnessVariation(int layerID);

    float getAlphaMin(int layerID);
    float getAlphaMax(int layerID);
    float getAlphaScaleFactor(int layerID);
    
    float getSizeEnergyFactor(int layerID);
    float getSizeAccelerationFactor(int layerID);
    float getSizeZFactor(int layerID);
    
    float getAlphaEnergyFactor(int layerID);
    float getAlphaVelocityFactor(int layerID);
    float getAlphaZFactor(int layerID);
    
    //behavoiur
    float getSpeed(int layerID);
    float getCurveSize(int layerID);
    
    //shoot behavoiur
    float getShootInitialSpeed(int layerID);
    float getShootInitialSize(int layerID);
    float getShootSpeedDecrement(int layerID);
    float getShootSizeDecrement(int layerID);
    float getShootCurveAmount(int layerID);
    
    
private:

    int getIndexOfLayerWithID(int layerID);
};


#endif //PMCANCONS_VISUALS_PMLAYERMAPPINGS_H
