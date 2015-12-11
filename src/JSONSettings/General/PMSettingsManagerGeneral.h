//
// Created by Miquel Àngel Soler on 29/10/15.
//

#pragma once

#ifndef PMCONCERTPARAULES_PMSETTINGSMANAGERGENERAL_H
#define PMCONCERTPARAULES_PMSETTINGSMANAGERGENERAL_H

#include "PMSettingsManager.h"

class PMSettingsManagerGeneral : public PMSettingsManager
{
public:

    static PMSettingsManagerGeneral &getInstance()
    {
        static PMSettingsManagerGeneral instance;
        return instance;
    }

    PMSettingsManagerGeneral();
    void createJSONSettings() {};

    bool getDebugShowFPS();
    bool getDebugShowGUIScene8();
    unsigned int getDebugScene7CountdownTime();
    bool getReleaseShowFPS();
    bool getReleaseShowGUIScene8();
    unsigned int getReleaseScene7CountdownTime();
};

#endif //PMCONCERTPARAULES_PMSETTINGSMANAGERGENERAL_H
