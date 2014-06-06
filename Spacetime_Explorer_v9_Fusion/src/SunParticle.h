//
//  SunParticle.h
//  Algo_Final_v3
//
//  Created by Adiel Fernandez on 12/16/13.
//
//

#ifndef __Algo_Final_v3__SunParticle__
#define __Algo_Final_v3__SunParticle__

#include <iostream>

#endif /* defined(__Algo_Final_v3__SunParticle__) */

#pragma once

#include "ofMain.h"

class SunParticle {
public:
    SunParticle();
    
    void update(ofVec3f _mouse);
    void draw();
    
    void setParams( ofVec3f _pos, ofVec3f _vel);
    void addForce( ofVec2f force );
    void addDampingForce();
    void resetForces();
    void resetParticle();
    void mouseRepel(ofVec3f _pos, float _radius, float _strength);
    void blobRepel(ofVec3f _pos, float _strength);
    
    ofVec3f pos;
    ofVec3f vel;
    ofVec3f acc;
    ofVec3f mouseDirection;
    ofVec3f blobDir;
    
    
    float damping;
    
    int lifeSpan;
    float trans;
    ofColor col;
    float size;
    int ageOfDeath;
    bool explode;
    bool dead;
    bool disturbed;
    
    float starSize;
    
    
};