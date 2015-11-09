//
//  PMSongSelector.hpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 02/11/15.
//
//

#ifndef PMSongSelector_hpp
#define PMSongSelector_hpp

#include <stdio.h>
#include "ofMain.h"
#include "PMColorContainer.hpp"
#include "PMTextContainer.hpp"
#include "ofxJSON.h"

struct colorPalette{
    string name;
    vector <ofColor> colors;
};

class PMSongSelector
{
public:
    
    static PMSongSelector &getInstance()
    {
        static PMSongSelector instance;
        return instance;
        cout<<"color get instance"<<endl;
    }
    
    void init(ofTrueTypeFont &font, ofTrueTypeFont &boldFont);
    void update();
    void draw();
    
    void getFilename(int index){};
    void checkMousePassed(int x, int y);
    string checkMousePressed(int x, int y);
    
private:
    vector<PMTextContainer > songNamesBox;
    vector<string> songFilenames;
    ofTrueTypeFont *font;
    ofTrueTypeFont *boldFont;
    int indexChoosed;
};

#endif /* PMSongSelector_hpp */