//
//  PMSelectorContainer.hpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 02/11/15.
//
//

#ifndef PMSelectorContainer_hpp
#define PMSelectorContainer_hpp

#include <stdio.h>
#include "ofMain.h"

class PMSelectorContainer
{
public:
    PMSelectorContainer();
    PMSelectorContainer(int x, int y, int width, int height);
    void update(int x, int y);
    void update(int x, int y, int width, int height);
    bool isInside(int x, int y);
    
protected:
    int x;
    int y;
    int width;
    int height;
};

#endif /* PMSelectorContainer_hpp */
