//
//  PMTextContainer.hpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 02/11/15.
//
//

#ifndef PMTextContainer_hpp
#define PMTextContainer_hpp

#include "PMSelectorContainer.hpp"

class PMTextContainer : public PMSelectorContainer
{
public:
    PMTextContainer(int x, int y, string s, ofTrueTypeFont &font, float scale);
    PMTextContainer(int x, int y, string s, ofTrueTypeFont &font);
    //PMTextContainer(int x, int y, string s, ofTrueTypeFont &font, float scale);
    void draw();
    void draw(float scale);
    void setFont(ofTrueTypeFont &font);
    void setScale(float _scale);
    string getString(){return s;};
    
private:
    string s;
    ofTrueTypeFont *font;
    float scale;
    float scaledWidth, scaledHeight;
};

#endif /* PMTextContainer_hpp */
