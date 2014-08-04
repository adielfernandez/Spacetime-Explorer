//
//  pFusion.h
//  Spacetime_Explorer_v9_Fusion
//
//  Created by Adiel Fernandez on 8/4/14.
//
//

#ifndef __Spacetime_Explorer_v9_Fusion__pFusion__
#define __Spacetime_Explorer_v9_Fusion__pFusion__

#include <iostream>
#include "ofMain.h"

#endif /* defined(__Spacetime_Explorer_v9_Fusion__pFusion__) */




#pragma once

class pFusion{
    
public:
    
    pFusion();
    
    void update();
    void draw();
    
    void setup(ofVec3f _pos, float velAng, ofImage *image);

    
    ofVec3f pos, vel, acc;
    ofVec3f collisionPos;

    int type;
    float damping;
    float size;
    float trans;
    int age;
    
    ofImage *sharedImage;
    
    
    
};