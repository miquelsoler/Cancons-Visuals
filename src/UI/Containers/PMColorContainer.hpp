//
//  PMColorContainer.hpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 02/11/15.
//
//

#ifndef PMColorContainer_hpp
#define PMColorContainer_hpp

#include "PMSelectorContainer.hpp"

class PMColorContainer :public PMSelectorContainer
{
public:
    PMColorContainer(int x, int y, int width, int height, ofColor color);
    void draw();
    void setColor(ofColor color);

private:
    ofColor color;
};

#endif /* PMColorContainer_hpp */
