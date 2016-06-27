//
//  PMSc10Thanks.cpp
//  PMCancons_Visuals
//
//  Created by Eduard Frigola on 30/10/15.
//
//

#include "PMSc10Thanks.hpp"
#include "PMSongSelector.hpp"
#include "PMSharedSettings.h"
#include "PMMotionExtractor.hpp"

const static int COUNTDOWN_TIME = 2;

PMSc10Thanks::PMSc10Thanks() : PMBaseScene("Scene Thanks")
{
    bigFont.load("fonts/NeutraTextTF-Book.otf", 29, true, true, false, 0.3, 72);
    smallFont.load("fonts/NeutraTextTF-Light.otf", 28, true, true, false, 0.3, 72);
    smallestFont.load("fonts/NeutraTextTF-Light.otf", 22, true, true, false, 0.3, 72);
	small_logo.load("assets/urban_art.png");
    originalWidth = DESIGN_WIDTH;
    originalHeight = DESIGN_HEIGHT;
    setSingleSetup(false);
    songName = "Blade Runner";
    dateName = "30/06/2016, 22:13";
    userName = "Interpretat per Susanna Mitjà";

	//facana.load("assets/facana.tiff");
	facana.load("assets/print_background.png");
	plantilla.load("assets/print_plantilla.png");
	//ofSetWindowShape(1772, 1181);
	//homography.set(0.579811573, 0.220885843, 0, 0.000285788818,
	//	0.00508813839, 0.338972956, 0, 0.000000268133908,
	//	0, 0, 1, 0,
	//	166.0, 358.0, 0, 1);

	//Homography for new plantilla
	/*
	homography.set(0.592777908, 0.223622605, 0, 0.000294847618,
		0.000365242478, 0.339181930, 0, -0.000000268133908,
		0, 0, 1, 0,
		168.0, 349.0, 0, 1);
	*/

	//Homography for new fbo resolution
	homography.set(0.599193573, 0.226636082, 0, 0.000300306710,
		0.00733219925, 0.544999719, 0, 8.78107676e-06,
		0, 0, 1, 0,
		166.0, 350.0, 0, 1);
}

void PMSc10Thanks::setup()
{
	ofSetWindowShape(1772, 1181);
    //Primer ha de pillar el nom, sino No es pot generar l'fbo
    songName = PMSongSelector::getInstance().getSongname();
    userName = "Interpretat per " + PMSharedSettings::getInstance().getUserName();
    dateName = ofGetTimestampString("%d/%m/%Y, %H:%M");
    //carrega la imatge, alloca el fbo i genera fbo
    ofClear(0, 0, 0);
    printImage.load("TempRender.tiff");
    printFbo.allocate(1772, 1181, GL_RGB);
    drawIntoFbo();
    //exportem fbo i el guardem
    ofPixels pix;
    printFbo.readToPixels(pix);
//    ofSaveImage(pix, "toPrint.png", OF_IMAGE_QUALITY_BEST);
    ofStringReplace(songName, " ", "_");
    ofStringReplace(userName, " ", "_");
    ofStringReplace(dateName, " ", "_");
    ofStringReplace(dateName, "/", "_");
//    string saveFilename= "exports/toprint/"+songName+"-"+userName+"_"+dateName+".png";
//    cout<<songName<<"     "<<userName<<"       "<<dateName<<"         "<<saveFilename<<endl;
	string simpleSaveFilename = "toPrint_" + ofGetTimestampString() + ".png";
	string saveFilename = "exports/toprint/" + simpleSaveFilename;
    ofSaveImage(pix, saveFilename, OF_IMAGE_QUALITY_BEST);

    //imprimir fbo.

#if ENABLE_PRINTING
    //string c = "lp -o media=Custom.4x6in -o page-left=0 -o page-right=0 -o page-top=0 -o page-bottom=0 " + ofToDataPath(saveFilename);
	string imagePath = ofToDataPath("exports\\toprint\\" + simpleSaveFilename, true);
	ofStringReplace(imagePath, "/", "\\");
	string s = "\"c:\\Program Files (x86)\\IrfanView\\i_view32.exe\" " + imagePath + " /silent /print=Printer01";
	system(s.c_str());
#endif

    countdown.set();
    countdown.setAlarm(COUNTDOWN_TIME * 1000);
    
    count=0;
}

void PMSc10Thanks::exit()
{
//    printFbo.unbind();
}

void PMSc10Thanks::update()
{
    if (countdown.alarm()) {
        countdown.resetAlarm();
        string toScene = "Scene 2";
        //ofNotifyEvent(goToSceneEvent, toScene, this);
    }
}

void PMSc10Thanks::draw()
{
    PMBaseScene::draw();
    ofPushMatrix();
    float scaleX = (float) ofGetWidth() / (float) originalWidth;
    float scaleY = (float) ofGetHeight() / (float) originalHeight;
    ofScale(scaleX, scaleY);
    ofSetColor(ofColor::white);
	///plantilla.draw(0, 0, ofGetWidth(), ofGetHeight());
    drawCenteredFont(bigFont, "Imprimint", originalWidth / 2, 462);
    drawCenteredFont(bigFont, "Moltes gràcies!", originalWidth / 2, 508);
    drawCenteredFont(bigFont, "Cançons Visuals", originalWidth / 2, 938);
    drawCenteredFont(smallFont, "www.xavibove.com", originalWidth / 2, 988);
    ofPopMatrix();
    printFbo.draw(0,0, ofGetWidth(), ofGetHeight());
	if (ofGetKeyPressed(OF_KEY_SHIFT))
		plantilla.draw(0,0);

    //printFbo.draw(0,0);
}


void PMSc10Thanks::drawIntoFbo()
{
    printFbo.begin();
    {
        ofClear(255);

		//Draw tempRender image in its position
		ofSetColor(255);
		ofPushMatrix();
		ofMultMatrix(homography);
		printImage.draw(0, 0);
		ofPopMatrix();

		//Draw facade image;
		//facana.draw(69, 59, 1628, 961);
		facana.draw(0, 0);

		//Draw strings
        ofSetColor(ofColor::black);
        //drawRightAlignString(bigFont, "\"" + songName + "\"", 1693, 1046);
        //drawRightAlignString(smallFont, userName, 1693, 1081);
        //drawRightAlignString(smallFont, dateName, 1693, 1116);
        //drawLeftAlignString(smallestFont, "Centre Cívic Fort Pienc", 70, 1042);
		//drawLeftAlignString(smallestFont, "www.fortpienc.org", 70, 1064);

		drawLeftAlignString(bigFont, "\"" + songName + "\"", 67, 1046-2);
		drawLeftAlignString(smallFont, userName, 67, 1081-2);
		drawLeftAlignString(smallFont, dateName, 67, 1116-2);
    }
    printFbo.end();
}


void PMSc10Thanks::drawRightAlignString(ofTrueTypeFont &font, string s, int x, int y)
{
    int halfStringHeight = font.stringHeight(s) / 2;
    int stringWidth = font.stringWidth(s);
    font.drawString(s, x - stringWidth, y + halfStringHeight);
}

void PMSc10Thanks::drawLeftAlignString(ofTrueTypeFont &font, string s, int x, int y)
{
    int halfStringHeight = font.stringHeight(s) / 2;
    font.drawString(s, x, y + halfStringHeight);
}

void PMSc10Thanks::keyPressed(ofKeyEventArgs &keyargs){
#ifdef OF_DEBUG
    if(keyargs.key == ' '){
        string sceneToChange = "Scene 2";
        ofNotifyEvent(goToSceneEvent, sceneToChange, this);
    }
#endif
}