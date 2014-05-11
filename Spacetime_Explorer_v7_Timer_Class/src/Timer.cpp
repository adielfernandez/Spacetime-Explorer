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
    triggered = false;
    inButton = false;
    rad = 100;
    
}

void Timer::update(){
    
    col = ofColor(255, 150).lerp(ofColor(cvObjectCol,150), ofMap(time, 0, 360, 0, 1));
    
    
    //timer circle
    timerPath.clear();
    timerPath.arc(ofPoint(0,0), rad, rad, 0, time, true);
    
    timerPath.setStrokeWidth(5);
    
    if(inButton){
//        timerPath.setStrokeColor(ofColor(255, 0));
        timerPath.setFilled(true);
        
        timerPath.setFillColor(col);
        
        if(time < 360){
            time += 2;
        } else {
            triggered = true;
        }
        
    } else {
        
        timerPath.setFilled(false);
        timerPath.setStrokeColor(ofColor(255, 0));
        
        time = 0;
        
    }
    
    timerPath.setStrokeWidth(3);
    timerPath.setCircleResolution(50);
    

    
    
    
    
    
    
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
        ofSetColor(col, 255);
    } else {
        ofSetColor(255, 255);
    }
    
    ofCircle(0,0, rad);
    ofRotate(6);
    ofCircle(0,0, rad);
    ofPopMatrix();
    
    ofPopStyle();
    
    
    
}


