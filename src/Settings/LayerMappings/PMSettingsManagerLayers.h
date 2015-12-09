//
// Created by Miquel Àngel Soler on 7/12/15.
//

#ifndef PMCANCONS_VISUALS_PMLAYERMAPPINGS_H
#define PMCANCONS_VISUALS_PMLAYERMAPPINGS_H

#include "PMSettingsManager.h"

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

    float getSaturationScaleFactor(int layerID);

    float getBrightnessScaleFactor(int layerID);

    float getAlphaMin(int layerID);
    float getAlphaMax(int layerID);
    float getAlphaScaleFactor(int layerID);

//    float getBandMaxEnergy(int layerID);
//    float getMinAlpha(int layerID);
//    float getMaxAlpha(int layerID);
//    float getMinSize(int layerID);
//    float getMaxSize(int layerID);
//    float getMinBrightness(int layerID);
//    float getMaxBrightness(int layerID);

private:

    int getIndexOfLayerWithID(int layerID);
};


#endif //PMCANCONS_VISUALS_PMLAYERMAPPINGS_H
