//
//  SubAtomic.h
//  Spacetime_Explorer_v9_Fusion
//
//  Created by Adiel Fernandez on 7/22/14.
//
//

#ifndef __Spacetime_Explorer_v9_Fusion__SubAtomic__
#define __Spacetime_Explorer_v9_Fusion__SubAtomic__

#include <iostream>
#include "ofMain.h"

#endif /* defined(__Spacetime_Explorer_v9_Fusion__SubAtomic__) */

#pragma once

class SubAtomic{
    
public:
    
    SubAtomic();
    
    void update();
    void draw();
    
    void setup(ofVec3f _pos, float velAng, ofImage *image);
    void setup(ofVec3f _pos, float velAng, ofImage *image, ofImage *image2);

    void globalAttract(ofVec3f _pos, float _strength);
    
    ofVec3f pos, vel, acc;
    float velAngle;
    ofVec3f collisionPos;
    float damping;
    float size;
    float trans;
    float scale;
    int age;
    
    ofImage *sharedImage;
    ofImage *sharedImage2;
    int type;
    
    int bankSlot;
    
    bool floating;
    bool twoImages;
    
    
};