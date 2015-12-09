//
// Created by Miquel Àngel Soler on 7/12/15.
//

#include "PMSettingsManagerLayers.h"

static const string FILENAME = "settings/layers.json";

static const string STR_LAYERS                  = "Layers";
static const string STR_LAYER_ID                = "ID";
static const string STR_ENERGY                  = "Energy";
static const string STR_ENERGY_MIN              = "Min (N)";
static const string STR_ENERGY_MAX              = "Max (N)";
static const string STR_SIZE                    = "Size";
static const string STR_SIZE_MIN                = "Min";
static const string STR_SIZE_MAX                = "Max";
static const string STR_SIZE_ENERGY_FACTOR      = "Scale Energy Factor";
static const string STR_SIZE_ACCELERATION_FACTOR= "Scale Acceleration Factor";
static const string STR_SIZE_Z_FACTOR           = "Scale Z Factor";
static const string STR_HUE                     = "Hue";
static const string STR_HUE_SCALE_FACTOR        = "Scale Factor";
static const string STR_HUE_VARIATION           = "Variation";
static const string STR_SATURATION              = "Saturation";
static const string STR_SATURATION_SCALE_FACTOR = "Scale Factor";
static const string STR_SATURATION_VARIATION    = "Variation";
static const string STR_BRIGHTNESS              = "Brightness";
static const string STR_BRIGHTNESS_SCALE_FACTOR = "Scale Factor";
static const string STR_BRIGHTNESS_VARIATION    = "Variation";
static const string STR_ALPHA                   = "Alpha";
static const string STR_ALPHA_MIN               = "Min (N)";
static const string STR_ALPHA_MAX               = "Max (N)";
static const string STR_ALPHA_SCALE_FACTOR      = "Scale Factor";
static const string STR_ALPHA_ENERGY_FACTOR     = "Scale Energy Factor";
static const string STR_ALPHA_VELOCITY_FACTOR   = "Scale Velocity Factor";
static const string STR_ALPHA_Z_FACTOR          = "Scale Z Factor";


PMSettingsManagerLayers::PMSettingsManagerLayers() : PMSettingsManager()
{
    filename = FILENAME;

    bool parserResult = load(filename);
    if (!parserResult)
    {
        string msg = "BAD FORMAT IN " + FILENAME + ". Now quitting...";
        ofLog(OF_LOG_ERROR, msg);
        std::exit(EXIT_FAILURE);
    }
}

float PMSettingsManagerLayers::getEnergyMin(int layerID)
{
    int index = getIndexOfLayerWithID(layerID);
    Json::Value jsonLayer = json[STR_LAYERS][index][STR_ENERGY];
    return jsonLayer[STR_ENERGY_MIN].asFloat();
}

float PMSettingsManagerLayers::getEnergyMax(int layerID)
{
    int index = getIndexOfLayerWithID(layerID);
    Json::Value jsonLayer = json[STR_LAYERS][index][STR_ENERGY];
    return jsonLayer[STR_ENERGY_MAX].asFloat();
}

unsigned int PMSettingsManagerLayers::getSizeMin(int layerID)
{
    int index = getIndexOfLayerWithID(layerID);
    Json::Value jsonLayer = json[STR_LAYERS][index][STR_SIZE];
    return jsonLayer[STR_SIZE_MIN].asUInt();
}

unsigned int PMSettingsManagerLayers::getSizeMax(int layerID)
{
    int index = getIndexOfLayerWithID(layerID);
    Json::Value jsonLayer = json[STR_LAYERS][index][STR_SIZE];
    return jsonLayer[STR_SIZE_MAX].asUInt();
}

float PMSettingsManagerLayers::getHueScaleFactor(int layerID)
{
    int index = getIndexOfLayerWithID(layerID);
    Json::Value jsonLayer = json[STR_LAYERS][index][STR_HUE];
    return jsonLayer[STR_HUE_SCALE_FACTOR].asFloat();
}

float PMSettingsManagerLayers::getHueVariation(int layerID)
{
    int index = getIndexOfLayerWithID(layerID);
    Json::Value jsonLayer = json[STR_LAYERS][index][STR_HUE];
    return jsonLayer[STR_HUE_VARIATION].asFloat();
}

float PMSettingsManagerLayers::getSaturationScaleFactor(int layerID)
{
    int index = getIndexOfLayerWithID(layerID);
    Json::Value jsonLayer = json[STR_LAYERS][index][STR_SATURATION];
    return jsonLayer[STR_SATURATION_SCALE_FACTOR].asFloat();
}

float PMSettingsManagerLayers::getSaturationVariation(int layerID)
{
    int index = getIndexOfLayerWithID(layerID);
    Json::Value jsonLayer = json[STR_LAYERS][index][STR_SATURATION];
    return jsonLayer[STR_SATURATION_VARIATION].asFloat();
}

float PMSettingsManagerLayers::getBrightnessScaleFactor(int layerID)
{
    int index = getIndexOfLayerWithID(layerID);
    Json::Value jsonLayer = json[STR_LAYERS][index][STR_BRIGHTNESS];
    return jsonLayer[STR_BRIGHTNESS_SCALE_FACTOR].asFloat();
}

float PMSettingsManagerLayers::getBrightnessVariation(int layerID)
{
    int index = getIndexOfLayerWithID(layerID);
    Json::Value jsonLayer = json[STR_LAYERS][index][STR_BRIGHTNESS];
    return jsonLayer[STR_BRIGHTNESS_VARIATION].asFloat();
}

float PMSettingsManagerLayers::getAlphaMin(int layerID)
{
    int index = getIndexOfLayerWithID(layerID);
    Json::Value jsonLayer = json[STR_LAYERS][index][STR_ALPHA];
    return jsonLayer[STR_ALPHA_MIN].asFloat();
}

float PMSettingsManagerLayers::getAlphaMax(int layerID)
{
    int index = getIndexOfLayerWithID(layerID);
    Json::Value jsonLayer = json[STR_LAYERS][index][STR_ALPHA];
    return jsonLayer[STR_ALPHA_MAX].asFloat();
}

float PMSettingsManagerLayers::getAlphaScaleFactor(int layerID)
{
    int index = getIndexOfLayerWithID(layerID);
    Json::Value jsonLayer = json[STR_LAYERS][index][STR_ALPHA];
    return jsonLayer[STR_ALPHA_SCALE_FACTOR].asFloat();
}

#pragma mark Size variation parameters

float PMSettingsManagerLayers::getSizeEnergyFactor(int layerID)
{
    int index = getIndexOfLayerWithID(layerID);
    Json::Value jsonLayer = json[STR_LAYERS][index][STR_SIZE];
    return jsonLayer[STR_SIZE_ENERGY_FACTOR].asFloat();
}

float PMSettingsManagerLayers::getSizeAccelerationFactor(int layerID)
{
    int index = getIndexOfLayerWithID(layerID);
    Json::Value jsonLayer = json[STR_LAYERS][index][STR_SIZE];
    return jsonLayer[STR_SIZE_ACCELERATION_FACTOR].asFloat();
}

float PMSettingsManagerLayers::getSizeZFactor(int layerID)
{
    int index = getIndexOfLayerWithID(layerID);
    Json::Value jsonLayer = json[STR_LAYERS][index][STR_SIZE];
    return jsonLayer[STR_ALPHA_ENERGY_FACTOR].asFloat();
}

#pragma mark Alpha variation parameters

float PMSettingsManagerLayers::getAlphaEnergyFactor(int layerID)
{
    int index = getIndexOfLayerWithID(layerID);
    Json::Value jsonLayer = json[STR_LAYERS][index][STR_ALPHA];
    return jsonLayer[STR_ALPHA_ENERGY_FACTOR].asFloat();
}

float PMSettingsManagerLayers::getAlphaVelocityFactor(int layerID)
{
    int index = getIndexOfLayerWithID(layerID);
    Json::Value jsonLayer = json[STR_LAYERS][index][STR_ALPHA];
    return jsonLayer[STR_ALPHA_VELOCITY_FACTOR].asFloat();
}

float PMSettingsManagerLayers::getAlphaZFactor(int layerID)
{
    int index = getIndexOfLayerWithID(layerID);
    Json::Value jsonLayer = json[STR_LAYERS][index][STR_ALPHA];
    return jsonLayer[STR_ALPHA_Z_FACTOR].asFloat();
}

int PMSettingsManagerLayers::getIndexOfLayerWithID(int layerID)
{
    int result = -1;

    bool found = false;
    for (int i=0; i<json[STR_LAYERS].size() && !found; ++i)
    {
        found = json[STR_LAYERS][i][STR_LAYER_ID].asInt() == layerID;
        if (found) result = i;
    }

    return result;
}

