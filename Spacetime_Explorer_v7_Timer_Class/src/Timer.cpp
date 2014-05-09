//
//  Timer.cpp
//  Spacetime_Explorer_v7_Timer_Class
//
//  Created by spacetime explorer on 5/9/14.
//
//

#include "Timer.h"



Timer::Timer(){
    
    //initialize to 0,0
    pos.set(0,0);
    time = 0;
    
    strokeThick = 8;
    
    
    
}

void Timer::update(){
    
//    timerCol = ofColor(255, 150).lerp(ofColor(cvObjectCol,150), ofMap(time, 0, 360, 0, 1));
//    
//    
//    //timer circle
//    idleTimerPath.clear();
//    idleTimerPath.arc(ofPoint(0,0), 100, 100, 0, timeInBox, true);
//    
//    idleTimerPath.setStrokeWidth(5);
//    
//    if(inButton){
//        idleTimerPath.setStrokeColor(ofColor(255, 0));
//        idleTimerPath.setFilled(true);
//        
//        idleTimerPath.setFillColor(idleTimerCol);
//        
//    } else {
//        
//        idleTimerPath.setFilled(false);
//        idleTimerPath.setStrokeColor(ofColor(255, 0));
//    }
//    
//    idleTimerPath.setStrokeWidth(3);
//    idleTimerPath.setCircleResolution(50);
//    
//    
//    if(timeInBox > 359){
//        transitionToIntro = true;
//        
//        if(welcomePlay == false){
//            welcome.play();
//            welcomePlay = true;
//        }
//    
//    }

    
    
    
    
}


void Timer::draw(){
    
    
    //draw timer stuff
    ofPushStyle();
    
    ofNoFill();
    ofSetCircleResolution(30);
    ofSetLineWidth(strokeThick);
    
    
    ofPushMatrix();
    
    ofTranslate(pos);
    
    
    ofRotate(90);
    
    timerPath.draw();
    
    if(inButton){
        //ofSetColor(idleTimerCol, 255);
    } else {
        ofSetColor(255, 255);
    }
    
    ofCircle(0,0, 100);
    ofRotate(6);
    ofCircle(0,0, 100);
    ofPopMatrix();
    
    ofPopStyle();
    
    
    
}


