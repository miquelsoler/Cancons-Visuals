//
//  PMBrushesSelector.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 02/11/15.
//
//

#include "PMBrushesSelector.hpp"

void PMBrushesSelector::init()
{
    originalHeight= DESIGN_HEIGHT;
    originalWidth= DESIGN_WIDTH;
    
    selectedPaletteIndex = 0;
    brushesXpalette = 0;
    
    ofDirectory dir;
    ofDirectory subDir;
    dir.listDir("brushes/");
    dir.sort();
    for(int i = 0; i < (int)dir.size(); i++){
        subDir.listDir(dir.getPath(i));
        for(int i = 0; i < (int)subDir.size(); i++){
            PMImageContainer tempContainer(subDir.getPath(i));
            brushes.push_back(tempContainer);
        }
        if (brushesXpalette == 0)
        {
            brushesXpalette = subDir.size();
        }
        else
        {
            if (brushesXpalette != subDir.size())
                cout << "ERROR_Palettes not the same size" << endl;
        }
    }
 
    setInitialState();
}

void PMBrushesSelector::setInitialState()
{
    int index = 0;
    int x, y;
    int width, height;
    for (int i = 1; i <= brushes.size() / brushesXpalette; i++) {
        y = (((originalHeight - 150) * i / ((brushes.size() / brushesXpalette) + 1)) + 150);
        for (int j = 0; j < brushesXpalette; j++) {
            x = (originalWidth * (j + 1) / (brushesXpalette + 1));
            width = ((originalWidth / (brushesXpalette * 2)) - 1);
            height = width;
            brushes[index].update(x, y, width, height);
            index++;
        }
    }

    for (int i = 0; i < brushes.size(); i = i + brushesXpalette)
    {
        int x = originalWidth / 2;
        int y = brushes[i].getY();
        int width = originalWidth - (2 * brushes[i].getX() - brushes[i].getWidth()) + 20;
        int height = brushes[i].getHeight() + 20;
        rectSelector.push_back(PMColorContainer(x, y, width, height, ofColor(127)));
    }
}

void PMBrushesSelector::update()
{
}

void PMBrushesSelector::draw()
{
    for (int i = 0; i < rectSelector.size(); i++) {
        rectSelector[i].draw();
    }

    for (int i = 0; i < brushes.size(); i++) {
        brushes[i].draw();
    }
}

PMImageContainer *PMBrushesSelector::getBrush(int layer)
{
    int index = (selectedPaletteIndex * brushesXpalette) + layer;
    return &brushes[index];
}


void PMBrushesSelector::checkMousePassed(int x, int y)
{
    for (int i = 0; i < rectSelector.size(); i++) {
        int x1 = rectSelector[i].getX() - rectSelector[i].getWidth() / 2;
        int x2 = rectSelector[i].getX() + rectSelector[i].getWidth() / 2;
        int y1 = rectSelector[i].getY() - rectSelector[i].getHeight() / 2;
        int y2 = rectSelector[i].getY() + rectSelector[i].getHeight() / 2;
        if (x >= x1 && x <= x2 && y >= y1 && y <= y2) {
//            cout<<"index choosed: "<<i<<"----"<<ofGetTimestampString()<<endl;
        } else {
            //rectSelector[i].setFont(*font);
        }
    }
}

bool PMBrushesSelector::checkMousePressed(int x, int y)
{
    for (int i = 0; i < rectSelector.size(); i++)
    {
        int x1 = rectSelector[i].getX() - rectSelector[i].getWidth() / 2;
        int x2 = rectSelector[i].getX() + rectSelector[i].getWidth() / 2;
        int y1 = rectSelector[i].getY() - rectSelector[i].getHeight() / 2;
        int y2 = rectSelector[i].getY() + rectSelector[i].getHeight() / 2;
        if (x >= x1 && x <= x2 && y >= y1 && y <= y2) {
            selectedPaletteIndex = i;
            return true;
        }
    }
    return false;
}
