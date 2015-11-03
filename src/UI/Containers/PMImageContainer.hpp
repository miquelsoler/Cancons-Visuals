//
//  PMImageContainer.hpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 02/11/15.
//
//

#ifndef PMImageContainer_hpp
#define PMImageContainer_hpp

#include "PMSelectorContainer.hpp"

class PMImageContainer : public PMSelectorContainer
{
public:
    PMImageContainer(ofImage image);
    PMImageContainer(string filename);
    PMImageContainer(int x, int y, int width, int height, ofImage image);
    void draw();
    void setImage(ofImage image);
    void loadImage(string _filename);
    
private:
    ofImage image;
};

#endif /* PMImageContainer_hpp */
