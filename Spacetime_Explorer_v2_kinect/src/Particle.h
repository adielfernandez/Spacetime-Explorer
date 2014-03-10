//
//  Particle.h
//  Spacetime_Explorer_v1
//
//  Created by Adiel Fernandez on 3/6/14.
//
//

#ifndef __Spacetime_Explorer_v1__Particle__
#define __Spacetime_Explorer_v1__Particle__

#include <iostream>
#include "ofMain.h"

#pragma once

#endif /* defined(__Spacetime_Explorer_v1__Particle__) */


class Particle{
    
public:
    
    Particle();
    
    void update(ofVec3f _mouse);
    void draw();

    void mouseRepel(ofVec3f _pos, float _radius, float _strength);
    void blobRepel(ofVec3f _pos, float _strength);
    void attract(ofVec3f _pos, float _radius, float _strength);
    void globalAttract(ofVec3f _pos, float _strength);
    
    
    ofVec3f pos, vel, acc;
    ofVec3f mouseDirection;
    ofVec3f blobDir;
    
    ofColor col;

    bool dead;
    bool disturbed;
    
    float damping;
    float size;

    
    
    
};