//
//  PMSc8Main.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#include "PMSc8Main.hpp"
#include "PMSongSelector.hpp"


PMSc8Main::PMSc8Main() : PMBaseScene("Scene 8")
{
    setSingleSetup(false);
}

void PMSc8Main::setup()
{
    for(int i=0; i<4; i++){
        PMRendererLayer tempRender = PMRendererLayer(i);
        tempRender.setup();
        switch (i) {
            case 0:
                tempRender.setPosition(ofPoint(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())));
                break;
            case 1:
                tempRender.setPosition(renderers[0].getPosition());
                break;
            case 2:
                tempRender.setPosition(ofPoint(0,0));
                break;
            case 3:
                tempRender.setPosition(ofPoint(ofGetWidth()/2, ofGetHeight()/2));
                break;
            default:
                break;
        }
        renderers.push_back(tempRender);
    }
    
    //Audio device analyzer
    const unsigned int unsigint0=0;
    const unsigned int unsigint1=1;
    vector<unsigned int> audioChanels;
    audioChanels.push_back(0);
    audioChanels.push_back(1);
    cout<<audioChanels.size()<<endl;
    PMDeviceAudioAnalyzer *deviceAudioAnalyzer = PMAudioAnalyzer::getInstance().addDeviceAnalyzer(0, 0,
                                                                                                  2, 0, 44100, 1024, audioChanels);
    
    ofAddListener(deviceAudioAnalyzer->eventPitchChanged, this, &PMSc8Main::pitchChanged);
    ofAddListener(deviceAudioAnalyzer->eventEnergyChanged, this, &PMSc8Main::energyChanged);
//    
//    ofAddListener(deviceAudioAnalyzer->eventSilenceStateChanged, this, &PMScene2::silenceStateChanged);
//    ofAddListener(deviceAudioAnalyzer->eventPauseStateChanged, this, &PMScene2::pauseStateChanged);
//    ofAddListener(deviceAudioAnalyzer->eventOnsetStateChanged, this, &PMScene2::onsetDetected);
//    ofAddListener(deviceAudioAnalyzer->eventShtStateChanged, this, &PMScene2::shtDetected);
//    ofAddListener(deviceAudioAnalyzer->eventMelodyDirection, this, &PMScene2::melodyDirection);
}

void PMSc8Main::update()
{
    //PMMotionExtractor::getInstance().update();
    if(songIsStarted){
        if (!song.isPlaying()) {
            cout<<"song_has_finished"<<endl;
            string sceneToChange="Scene 2";
//            ofNotifyEvent(goToSceneEvent, sceneToChange, this);
        }
    }
    ofSoundUpdate();
    
    for(int i=0; i<renderers.size(); i++){
        renderers[i].update();
    }
    
}

void PMSc8Main::draw()
{
    //ofBackground(255, 35, 32);
    ofSetColor(ofColor::red);
    ofDrawRectangle(0,0, ofGetWidth(), ofGetHeight());
//    PMMotionExtractor::getInstance().draw();
//    KinectInfo* kinectOut=PMMotionExtractor::getInstance().getKinectInfo();
//    ofDrawEllipse(kinectOut->leftHand_joint.x*ofGetWidth(), kinectOut->leftHand_joint.y*ofGetHeight(), 10+5*kinectOut->leftHand_joint.a, 10+5*kinectOut->leftHand_joint.a);
//    ofDrawEllipse(kinectOut->rightHand_joint.x*ofGetWidth(), kinectOut->rightHand_joint.y*ofGetHeight(), 10+5*kinectOut->rightHand_joint.a, 10+5*kinectOut->rightHand_joint.a);
//    ofDrawEllipse(kinectOut->head_joint.x*ofGetWidth(), kinectOut->head_joint.y*ofGetHeight(), 10+7*kinectOut->head_joint.a, 10+7*kinectOut->head_joint.a);
//    ofDrawEllipse(kinectOut->torso_joint.x*ofGetWidth(), kinectOut->torso_joint.y*ofGetHeight(), 10+10*kinectOut->torso_joint.a, 10+10*kinectOut->torso_joint.a);
    ofColor c = ofColor(ofColor::white);
    ofClear(c);
    for(int i=0; i<renderers.size(); i++){
        renderers[i].draw();
    }
}

void PMSc8Main::updateEnter()
{
    PMBaseScene::updateEnter();
    string songPath="songs/"+PMSongSelector::getInstance().getFilename();
    songIsStarted=false;
    loadSong(songPath);
    playSong();
    
    PMAudioAnalyzer::getInstance().start();
}

void PMSc8Main::updateExit()
{
    PMBaseScene::updateExit();
    song.stop();
}

void PMSc8Main::loadSong(string filename){
    song.load(filename);
    song.setVolume(0.75f);
    song.setMultiPlay(false);
}

void PMSc8Main::playSong()
{
    if (!song.isLoaded()){
        cout<<"Error - No loaded Sound!"<<endl;
    }
    song.play();
    songIsStarted=true;
}





//AUDIO struff

void PMSc8Main::pitchChanged(pitchParams &pitchParams)
{
    cout<<pitchParams.midiNote<<endl;
}

void PMSc8Main::energyChanged(energyParams &energyParams)
{
    
}


