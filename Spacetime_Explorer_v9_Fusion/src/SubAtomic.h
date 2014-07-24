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
    void setup(ofVec3f _pos, ofImage *image);
    void globalAttract(ofVec3f _pos, float _strength);
    
    ofVec3f pos, vel, acc;
    float damping;
    float size;
    float trans;
    float scale;
    int age;
    
    ofImage *sharedImage;
    int type;
    
    int deutSlot;
    

    
};