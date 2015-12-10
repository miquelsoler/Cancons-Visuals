//
//  PMBrushesSelector.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 02/11/15.
//
//

#include "PMBrushesSelector.hpp"
#include <dirent.h>

void PMBrushesSelector::init()
{
    selectedPaletteIndex = 0;

    DIR *dpdf;
    DIR *dpdf2;
    struct dirent *epdf;
    struct dirent *epdf2;

    string slash = "/";

    int i = 0;
    brushesXpalette = 0;

    dpdf = opendir(ofToDataPath("brushes/", true).c_str());
    if (dpdf == NULL) return;

    while ((epdf = readdir(dpdf)))
    {
        if (epdf->d_type != 0x8)
        {
            string foldername = string(epdf->d_name);
            if (foldername[0] != '.')
            {
                dpdf2 = opendir(ofToDataPath("brushes/" + foldername + slash, true).c_str());

                while ((epdf2 = readdir(dpdf2)))
                {
                    string brushname = epdf2->d_name;
                    if (brushname[0] != '.') {
                        PMImageContainer tempContainer("brushes/" + foldername + slash + brushname);
                        brushes.push_back(tempContainer);
                        i++;
                    }
                }

                if (brushesXpalette == 0)
                {
                    brushesXpalette = i;
                }
                else
                {
                    if (brushesXpalette != i)
                        cout << "ERROR_Palettes not the same size" << endl;
                }

                i = 0;
            }
        }
    }

    setInitialState();

//    int index=0;
//    int x,y;
//    int width,height;
//    for(int i=1; i<=brushes.size()/brushesXpalette; i++){
//        y=(((ofGetHeight()-150)*i/((brushes.size()/brushesXpalette)+1))+150);
//        for(int j=0; j<brushesXpalette; j++){
//            x=(ofGetWidth()*(j+1)/(brushesXpalette+1));
//            width=((ofGetWidth()/(brushesXpalette*2))-1);
//            height=width;
//            brushes[index].update(x, y, width, height);
//            index++;
//        }
//    }
//    
//    for(int i=0; i<brushes.size(); i=i+brushesXpalette){
//        int x=ofGetWidth()/2;
//        int y=brushes[i].getY();
//        int width=ofGetWidth()-(2*brushes[i].getX()-brushes[i].getWidth())+20;
//        int height=brushes[i].getHeight()+20;
//        rectSelector.push_back(PMColorContainer(x, y, width, height, ofColor(127)));
//    }
}

void PMBrushesSelector::setInitialState()
{
    int index = 0;
    int x, y;
    int width, height;
    for (int i = 1; i <= brushes.size() / brushesXpalette; i++) {
        y = (((ofGetHeight() - 150) * i / ((brushes.size() / brushesXpalette) + 1)) + 150);
        for (int j = 0; j < brushesXpalette; j++) {
            x = (ofGetWidth() * (j + 1) / (brushesXpalette + 1));
            width = ((ofGetWidth() / (brushesXpalette * 2)) - 1);
            height = width;
            brushes[index].update(x, y, width, height);
            index++;
        }
    }

    for (int i = 0; i < brushes.size(); i = i + brushesXpalette)
    {
        int x = ofGetWidth() / 2;
        int y = brushes[i].getY();
        int width = ofGetWidth() - (2 * brushes[i].getX() - brushes[i].getWidth()) + 20;
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
