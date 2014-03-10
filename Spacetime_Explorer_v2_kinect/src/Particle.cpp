//
//  Particle.cpp
//  Spacetime_Explorer_v1
//
//  Created by Adiel Fernandez on 3/6/14.
//
//

#include "Particle.h"


Particle::Particle(){
    
    damping = 0.99;
    
//    col = (255, 255, 255);
    col = (255, 230, 165);
//    col.a = ofRandom(20, 150);
    disturbed = false;
    dead = false;
//    size = ofRandom(0.8, 3);
    size = 1.5;
    
    
    
}



void Particle::repel(ofVec3f _pos, float _radius, float _strength){
    
    
    ofVec2f diff = pos - _pos;
    
    if( diff.lengthSquared() < _radius * _radius){
        float pct = diff.length()/_radius;

        // "1 - " makes particles closer to mouse repel more.
        //remove to make repulsion proportional to distace
        diff.normalize();
        
        //force to center of screen
        //        ofVec2f toCenter;
        //        toCenter =  ofVec2f(ofGetWindowWidth()/2, ofGetWindowHeight()/2) - pos;
        //        toCenter.normalize();
        //
        //
        //        acc.x += toCenter.x * pct * strength;
        //        acc.y += toCenter.y * pct * strength;
        
        
        //force away from mouse
        //        acc.x += diff.x * pct * strength;
        //		acc.y += diff.y * pct * strength;
        
        
        
        //force with mouse
        acc.x += mouseDirection.getNormalized().x * pct * _strength;
		acc.y += mouseDirection.getNormalized().y * pct * _strength;
        
        
        
    }
    

    
    
    
}

void Particle::attract(ofVec3f _pos, float _radius, float _strength){
 

    
    ofVec2f diff = pos - _pos;
    
    if( diff.lengthSquared() < _radius * _radius){
        float pct = 1 - diff.length()/_radius;
        diff.normalize();
        
        acc.x -= diff.x * pct * _strength;
        acc.y -= diff.y * pct * _strength;
    }
    
    
    
    
}

void Particle::globalAttract(ofVec3f _pos, float _strength){
    
    ofVec2f diff = pos - _pos;
    
    float pct = ofClamp(1 - diff.length()/1000, 0.3, 1);
    diff.normalize();
    
    acc.x -= diff.x * pct * _strength;
    acc.y -= diff.y * pct * _strength;
    
    
    
    
}


//------------------------------UPDATE------------------------------
void Particle::update(ofVec3f _mouse){
    
    pos += vel;
    vel += acc;
    
    vel *= damping;
    
    
    acc.set(0);
    
    mouseDirection = _mouse;
    
    
}

//------------------------------DRAW HERE------------------------------
void Particle::draw(){
    
    ofPushStyle();
    
        ofSetColor(col);
        ofRect(pos, size, size);
        //ofCircle(pos, 20);
    
    ofPopStyle();
    
}



