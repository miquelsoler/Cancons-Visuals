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
    DIR *dpdf;
    DIR *dpdf2;
    struct dirent *epdf;
    struct dirent *epdf2;
    
    string slash="/";
    
    int i=0;
    brushesXpalette=0;
    
    dpdf = opendir(ofToDataPath("brushes/", true).c_str());
    if(dpdf == NULL){
        return false;
    }
    while((epdf = readdir(dpdf))){
        if (epdf->d_type!= 0x8){
            string foldername=string(epdf->d_name);
            if (foldername[0]!='.'){
                dpdf2 = opendir(ofToDataPath("brushes/"+foldername+slash, true).c_str());
                while((epdf2 = readdir(dpdf2))){
                    string brushname=epdf2->d_name;
                    if(brushname[0]!='.'){
                        cout<<"brushes/"+foldername+slash+brushname<<endl;
                        //tempImage.load("brushes/"+foldername+slash+brushname);
                        PMImageContainer tempContainer("brushes/"+foldername+slash+brushname);
                        //brushes.push_back(tempImage);
                        brushes.push_back(tempContainer);
                        i++;
                    }
                }
                if(brushesXpalette==0){
                    brushesXpalette=i;
                }else{
                    if(brushesXpalette!=i){
                        cout<<"ERROR_Palettes not the same size"<<endl;
                    }
                }
                i=0;
            }
        }
    }
    int index=0;
    int x,y;
    int width,height;
    for(int i=1; i<=brushes.size()/brushesXpalette; i++){
        y=(((ofGetHeight()-150)*i/((brushes.size()/brushesXpalette)+1))+150);
        for(int j=0; j<brushesXpalette; j++){
            x=(ofGetWidth()*(j+1)/(brushesXpalette+1));
            width=((ofGetWidth()/(brushesXpalette*2))-1);
            height=width;
            brushes[index].update(x, y, width, height);
            cout<<x<<" "<<y<<endl;
            index++;
        }
    }
}

void PMBrushesSelector::update()
{
    
}

void PMBrushesSelector::draw()
{
//    int x,y;
//    int width,height;
//    for(int i=1; i<=brushes.size()/brushesXpalette; i++){
//        y=(((ofGetHeight()-150)*i/((brushes.size()/brushesXpalette)+1))+150);
//        for(int j=0; j<brushesXpalette; j++){
//            x=(ofGetWidth()*(j+1)/(brushesXpalette+1));
//            width=((ofGetWidth()/(brushesXpalette*2))-1);
//            //width=40;
//            height=width;
//            ofSetRectMode(OF_RECTMODE_CENTER);
//            ofSetColor(255);
//            ofDrawRectRounded(x, y, width, height, 2);
//        }
//    }
    for(int i=0; i<brushes.size(); i++){
        brushes[i].draw();
    }
}
