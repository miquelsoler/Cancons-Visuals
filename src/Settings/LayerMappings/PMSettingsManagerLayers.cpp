//
// Created by Miquel Àngel Soler on 7/12/15.
//

#include "PMSettingsManagerLayers.h"

static const string FILENAME = "settings/layers.json";

static const string STR_LAYERS                  = "Layers";
static const string STR_LAYER_ID                = "ID";
static const string STR_LAYER_BAND_MAX_ENERGY   = "Band Max Energy (N)";
static const string STR_LAYER_MIN_ALPHA         = "Brush Min Alpha (N)";
static const string STR_LAYER_MAX_ALPHA         = "Brush Max Alpha (N)";
static const string STR_LAYER_MIN_SIZE          = "Brush Min Size";
static const string STR_LAYER_MAX_SIZE          = "Brush Max Size";
static const string STR_LAYER_MIN_BRIGHTNESS    = "Brush Min Brightness (N)";
static const string STR_LAYER_MAX_BRIGHTNESS    = "Brush Max Brightness (N)";


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

float PMSettingsManagerLayers::getBandMaxEnergy(int layerID)
{
    int index = getIndexOfLayerWithID(layerID);
    Json::Value jsonLayer = json[STR_LAYERS][index];
    return jsonLayer[STR_LAYER_BAND_MAX_ENERGY].asFloat();
}

float PMSettingsManagerLayers::getMinAlpha(int layerID)
{
    int index = getIndexOfLayerWithID(layerID);
    Json::Value jsonLayer = json[STR_LAYERS][index];
    return jsonLayer[STR_LAYER_MIN_ALPHA].asFloat();
}

float PMSettingsManagerLayers::getMaxAlpha(int layerID)
{
    int index = getIndexOfLayerWithID(layerID);
    Json::Value jsonLayer = json[STR_LAYERS][index];
    return jsonLayer[STR_LAYER_MAX_ALPHA].asFloat();
}

float PMSettingsManagerLayers::getMinSize(int layerID)
{
    int index = getIndexOfLayerWithID(layerID);
    Json::Value jsonLayer = json[STR_LAYERS][index];
    return jsonLayer[STR_LAYER_MIN_SIZE].asFloat();
}

float PMSettingsManagerLayers::getMaxSize(int layerID)
{
    int index = getIndexOfLayerWithID(layerID);
    Json::Value jsonLayer = json[STR_LAYERS][index];
    return jsonLayer[STR_LAYER_MAX_SIZE].asFloat();
}

float PMSettingsManagerLayers::getMinBrightness(int layerID)
{
    int index = getIndexOfLayerWithID(layerID);
    Json::Value jsonLayer = json[STR_LAYERS][index];
    return jsonLayer[STR_LAYER_MIN_BRIGHTNESS].asFloat();
}

float PMSettingsManagerLayers::getMaxBrightness(int layerID)
{
    int index = getIndexOfLayerWithID(layerID);
    Json::Value jsonLayer = json[STR_LAYERS][index];
    return jsonLayer[STR_LAYER_MAX_BRIGHTNESS].asFloat();
}

int PMSettingsManagerLayers::getIndexOfLayerWithID(int layerID)
{
    int result = -1;

    bool found = false;
    for (int i=0; i<json[STR_LAYERS].size(); ++i)
    {
        found = json[STR_LAYERS][i][STR_LAYER_ID].asInt() == layerID;
        if (found) result = i;
    }

    return result;
}
