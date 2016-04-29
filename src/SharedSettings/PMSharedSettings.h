//
// Created by Miquel Àngel Soler on 11/12/15.
//

#ifndef PMCANCONS_VISUALS_PMSHAREDSETTINGS_H
#define PMCANCONS_VISUALS_PMSHAREDSETTINGS_H

#include "ofMain.h"

class PMSharedSettings
{
public:

    static PMSharedSettings &getInstance()
    {
        static PMSharedSettings instance;
        return instance;
    }

    const string &getUserName() const
    {
        return userName;
    }

    void setUserName(const string &userName)
    {
        PMSharedSettings::userName = userName;
    }

private:

    PMSharedSettings() {};

    string userName;
};

//class PMSettingsManager
//{
//public:
//    virtual void write();
//
//    void reload();
//
//protected:
//
//    PMSettingsManager() {};
//    virtual bool load(string filename);
//    virtual void createJSONSettings() = 0;
//
//    bool fileExists(string filename);
//
//    ofxJSONElement  json;
//    string          filename;
//};

#endif //PMCANCONS_VISUALS_PMSHAREDSETTINGS_H
