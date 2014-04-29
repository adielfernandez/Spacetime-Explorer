//
//  Fragment.h
//  Spacetime_Explorer_v5_macam
//
//  Created by Adiel Fernandez on 4/27/14.
//
//

#ifndef __Spacetime_Explorer_v5_macam__Fragment__
#define __Spacetime_Explorer_v5_macam__Fragment__

#include <iostream>
#include "ofMain.h"

#pragma once

#endif /* defined(__Spacetime_Explorer_v5_macam__Fragment__) */


class Fragment {
public:
    Fragment();
    
    void setParams( ofVec3f _pos);
    void update(float _scale);
    void draw();
    
    ofVec3f basePos;
    ofVec3f pos;
    float size;
    
    float scaleFactor;
    
    ofColor col;
    float trans;
    
    float range;
    
    float noiseShift;
    float noiseSpeed;
    
};