//
//  PMSc6Main.cpp
//  PMConcertParaules
//
//  Created by Miquel Àngel Soler on 7/10/15.
//
//

#include "PMSc6Main.hpp"
void PMSc6Main::setup()
{
    songIsStarted=false;
    loadSong("songs/Com_Balles_Tu.mp3");
    playSong();
}

void PMSc6Main::update()
{
    //PMMotionExtractor::getInstance().update();
    if(songIsStarted){
        if (!song.isPlaying()) {
            cout<<"song_has_finished"<<endl;
        }
    }
    ofSoundUpdate();
}

void PMSc6Main::draw()
{
    ofBackground(255, 35, 32);
//    PMMotionExtractor::getInstance().draw();
//    KinectInfo* kinectOut=PMMotionExtractor::getInstance().getKinectInfo();
//    ofDrawEllipse(kinectOut->leftHand_joint.x*ofGetWidth(), kinectOut->leftHand_joint.y*ofGetHeight(), 10+5*kinectOut->leftHand_joint.a, 10+5*kinectOut->leftHand_joint.a);
//    ofDrawEllipse(kinectOut->rightHand_joint.x*ofGetWidth(), kinectOut->rightHand_joint.y*ofGetHeight(), 10+5*kinectOut->rightHand_joint.a, 10+5*kinectOut->rightHand_joint.a);
//    ofDrawEllipse(kinectOut->head_joint.x*ofGetWidth(), kinectOut->head_joint.y*ofGetHeight(), 10+7*kinectOut->head_joint.a, 10+7*kinectOut->head_joint.a);
//    ofDrawEllipse(kinectOut->torso_joint.x*ofGetWidth(), kinectOut->torso_joint.y*ofGetHeight(), 10+10*kinectOut->torso_joint.a, 10+10*kinectOut->torso_joint.a);
}

void PMSc6Main::loadSong(string filename){
    song.load(filename);
    song.setVolume(0.75f);
    song.setMultiPlay(false);
}

void PMSc6Main::playSong()
{
    if (!song.isLoaded()){
        cout<<"Error - No loaded Sound!"<<endl;
    }
    song.play();
    songIsStarted=true;
}