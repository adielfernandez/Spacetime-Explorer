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
    inButton =  false;
    hideImage = false;
    hideTrans = 200;
    
    trans = 0;
    
    rad = 100;
    disableTiming = false;
}

void Timer::update(){
    
    //fade in outline
    if(trans < 254){
        trans += 2;
    }
    
    
    
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
            
            //if we're disabling the timer, make it count
            //faster so the outline turns red quicker
            if(disableTiming){
                time += 6;
            } else {
                time += 2;
                
            }
            
            
        } else {
            
            //mark as triggered but only if this isnt a disabled timer
            if(disableTiming == false){
                triggered = true;
            }
            
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
    
    ofSetCircleResolution(30);
    ofSetLineWidth(strokeThick);
    
    
    ofPushMatrix();
    
    ofTranslate(pos);
    
    
    ofRotate(90);
    
    
    if(disableTiming == false){
        timerPath.draw();
    }
    
    
    
    
    if(inButton){
        ofSetColor(col, 255);
        
        if(hideTrans > 0){
            hideTrans -= 6;
        }
        
    } else {
        
        


        if(hideTrans < 200){
            hideTrans += 8;
        }
        
        //make the outlines white if we're not in the timer
        ofSetColor(255, trans);
        
    }
    
    //only draw transparent dark circle if the particular wants it
    if(hideImage == false){
        hideTrans = 0;
    }
    
    
    //if we want to hide a thumbnail image underneath,
    //add a dark transparent circle over the timer
    ofPushStyle();
    ofFill();
    ofSetColor(0, hideTrans);
    ofCircle(0,0, rad);
    ofPopStyle();
    
    
    
    ofNoFill();
    ofCircle(0,0, rad);
    ofRotate(6);
    ofCircle(0,0, rad);
    ofPopMatrix();
    
    ofPopStyle();
    
    
    
}


