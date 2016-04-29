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
#include "../UI/Containers/PMColorContainer.hpp"
#include "../UI/Containers/PMTextContainer.hpp"
#include "ofxJSON.h"
#include "ofxAppUtils.h"

//struct colorPalette{
//    string name;
//    vector <ofColor> colors;
//};

class PMSongSelector
{
public:
    
    static PMSongSelector &getInstance()
    {
        static PMSongSelector instance;
        return instance;
    }
    
    void init(ofTrueTypeFont &font);
    void update();
    void draw();
    
    string getFilename(){return songFilenames[indexChoosed];};
    string getSongname(){return songNamesBox[indexChoosed].getString();};
    void checkMousePassed(int x, int y);
    bool checkMousePressed(int x, int y);
    void resetSize();
    
private:
    
    vector<PMTextContainer > songNamesBox;
    vector<string> songFilenames;
    ofTrueTypeFont *font;
    int indexChoosed;
    vector<ofxTimer> timers;
    vector<float> textScales;
    vector<bool> selectedText;
    
    int originalWidth, originalHeight;
    
};

#endif /* PMSongSelector_hpp */