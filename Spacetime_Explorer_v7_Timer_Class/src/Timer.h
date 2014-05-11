//
//  Timer.h
//  Spacetime_Explorer_v7_Timer_Class
//
//  Created by spacetime explorer on 5/9/14.
//
//

#ifndef __Spacetime_Explorer_v7_Timer_Class__Timer__
#define __Spacetime_Explorer_v7_Timer_Class__Timer__

#include <iostream>

#endif /* defined(__Spacetime_Explorer_v7_Timer_Class__Timer__) */

#include "ofMain.h"
#pragma once


class Timer{
    
public:
    
    Timer();
    
    void update();
    void draw();
    
    ofPath timerPath;
    float size;
    ofVec3f pos;
    float time;
    float rad;
    
    float strokeThick;
    ofColor idleCol;
    ofColor col;
    ofColor cvObjectCol;
    
    
    
    bool inButton;
    bool triggered;

    
};