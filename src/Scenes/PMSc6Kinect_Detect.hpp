//
//  PMSc6Kinect_Detect.hpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 30/10/15.
//
//

#ifndef PMSc6Kinect_Detect_hpp
#define PMSc6Kinect_Detect_hpp

#include <stdio.h>
#include "PMBaseScene.hpp"

#endif /* PMSc6Kinect_Detect_hpp */

class PMSc6Kinect_Detect : public PMBaseScene
{
public:
    
    PMSc6Kinect_Detect();
    
    void setup();
    void update();
    void draw();
    void exit(){};
    void updateEnter(){PMBaseScene::updateEnter();};
    void updateExit(){PMBaseScene::updateExit();};

    
    
protected:
    
private:

	ofImage backgroundImage;
    
};