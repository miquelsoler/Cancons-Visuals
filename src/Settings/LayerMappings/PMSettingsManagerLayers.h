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

    float getBandMaxEnergy(int layerID);
    float getMinAlpha(int layerID);
    float getMaxAlpha(int layerID);
    float getMinSize(int layerID);
    float getMaxSize(int layerID);
    float getMinBrightness(int layerID);
    float getMaxBrightness(int layerID);

private:

    int getIndexOfLayerWithID(int layerID);
};


#endif //PMCANCONS_VISUALS_PMLAYERMAPPINGS_H
