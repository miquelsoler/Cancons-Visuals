//
// Created by Miquel Àngel Soler on 10/12/15.
//

#ifndef PMCANCONS_VISUALS_PMUICANVASLAYERS_H
#define PMCANCONS_VISUALS_PMUICANVASLAYERS_H

#include "PMBaseUICanvas.h"

class PMUICanvasLayers : public PMBaseUICanvas
{
public:

    PMUICanvasLayers(string title, int headerFontSize);

    virtual void init(int posX, int posY, bool autosize = true, int width = 0, int height = 0);
    virtual void clear();

    virtual void handleEvents(ofxUIEventArgs &e);

protected:

    void            loadPreset(int presetNumber = 0);
    void            savePreset(int presetNumber = 0);

private:

};


#endif //PMCANCONS_VISUALS_PMUICANVASLAYERS_H
