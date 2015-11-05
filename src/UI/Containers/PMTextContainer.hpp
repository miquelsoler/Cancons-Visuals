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
    PMTextContainer(int x, int y, string s, ofTrueTypeFont &font);
    void draw();
    void setFont(ofTrueTypeFont &font);
    
private:
    string s;
    ofTrueTypeFont *font;
};

#endif /* PMTextContainer_hpp */
