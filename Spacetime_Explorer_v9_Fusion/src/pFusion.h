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
    
    void update(float _speed);
    void setup(ofVec3f _pos, float velAng);
    void draw(ofImage *image);
    

    
    ofVec3f pos, vel, acc;
    ofVec3f collisionPos;

    int type;
    float damping;
    float size;
    float trans;
    float scale;
    float gammaAngle;
    int age;
    
    float bulkSpeed;
    
    float boundary;
    float aspectX, aspectY;
    
    bool fuse;
    bool dead;

};








