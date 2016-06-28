//
//  PMSc10Thanks.hpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 30/10/15.
//
//

#ifndef PMSc10Thanks_hpp
#define PMSc10Thanks_hpp

#include "PMBaseScene.hpp"

#endif /* PMSc10Thanks_hpp */

class PMSc10Thanks : public PMBaseScene
{
public:
    
    PMSc10Thanks();
    
    void setup();
    void update();
    void draw();
    void exit();
    void updateEnter() { PMBaseScene::updateEnter(); };
    void updateExit() { PMBaseScene::updateExit(); };
    
    void keyPressed(ofKeyEventArgs &keyargs);
    
    void drawIntoFbo();
    
    void drawRightAlignString(ofTrueTypeFont &font, string s, int x, int y);
    void drawLeftAlignString(ofTrueTypeFont &font, string s, int x, int y);

    
private:
    ofTrueTypeFont  bigFont, smallFont, smallestFont;
    int             originalWidth, originalHeight;
    
    ofFbo           printFbo;
    ofImage         printImage;
	ofImage			small_logo;
	ofImage			plantilla;
	ofImage			facana;
	ofImage			backgroundImage;
    
    string          userName;
    string          songName;
    string          dateName;
    
    ofxTimer        countdown;
    int count;

	ofMatrix4x4 homography;
    
};