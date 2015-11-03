//
//  PMColorsSelector.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 02/11/15.
//
//

#include "PMColorsSelector.hpp"

void PMColorsSelector::init()
{
    json.open("colors/Colors.json");
    for(int i=0; i<6; i++){
        tempPalette.name=json["Colors"][i]["Name"].asString();
        for(int j=1; j<=5; j++){
            ofColor tempColor=ofColor::fromHex(ofHexToInt(json["Colors"][i][ofToString(j)].asString()));
            tempPalette.colors.push_back(tempColor);
        }
        colorPalettes.push_back(tempPalette);
        tempPalette.colors.clear();
    }
    
    int rows=colorPalettes.size();
    int columns=colorPalettes[0].colors.size();
    int x,y;
    int width,height;
    for(int i=0; i<rows; i++){
        y=(((ofGetHeight()-150)*(i+1)/((rows)+1))+150);
        for(int j=0; j<columns; j++){
            x=(ofGetWidth()*(j+1)/(columns+1));
            width=((ofGetWidth()/(columns*2))-1);
            height=width;
            PMColorContainer tempContainer(x, y, width, height, colorPalettes[i].colors[j]);
            colorContainers.push_back(tempContainer);
        }
    }
}

void PMColorsSelector::update()
{
    
}

void PMColorsSelector::draw()
{
    for(int i=0; i<colorContainers.size(); i++){
        colorContainers[i].draw();
    }
}