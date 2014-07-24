//
//  SubAtomic.cpp
//  Spacetime_Explorer_v9_Fusion
//
//  Created by Adiel Fernandez on 7/22/14.
//
//

#include "SubAtomic.h"


SubAtomic::SubAtomic(){
    
    //Particle type:
    //0 = gamma ray
    //1 = hydrogen (proton)
    //2 = deuterium
    //3 = helium 3
    //4 = helium 4
    //5 = neutrino
    //6 = positron
    
    type = 1;
    
    //-----give random velocity-----
    //first get unit vector
    vel = ofVec3f(1, 0, 0);
    
    //then rotate by random amount
    vel.rotate(ofRandom(360), ofVec3f(0, 0, 1));
    
    //scale by random amount
    vel.scale(ofRandom(10, 20));
    
    
    
    age = 0;
    damping = 0.94;
    trans = 255;
    size = 1.0;
    
    //use deutSlot to keep track if it should go to the deuterium slot
    //0 means none, 1 means first slot, 2 means second slot;
    deutSlot = 0;
    
    
}


void SubAtomic::setup(ofVec3f _pos, ofImage *image){
    
    sharedImage = image;
    
    pos = _pos;
    
}

void SubAtomic::globalAttract(ofVec3f _pos, float _strength){
    
    
    ofVec2f diff = pos - _pos;
    

    //increase damping if we're close to the target position but only for
    //deuterium headed for the slot
    damping = ofMap(diff.length(), 0, 500, 0.8, 0.999, true);
    
    //make damping 0 if we're really close
    if(diff.length() < 4){
        vel.set(0);
    }
    
    float pct = ofClamp(1 - diff.length()/1000, 0.3, 1);
    diff.normalize();
    
    acc.x -= diff.x * pct * _strength;
    acc.y -= diff.y * pct * _strength;
    
    
    
    
}

void SubAtomic::update(){
    
    vel *= damping;
    
    vel += acc;
    
    pos += vel;
    
    acc.set(0);
    
    age++;
    
    //fade transparency if we're not in the deuterium slot
    if(deutSlot == 0){
        
        trans = ofMap(age, 0, 200, 255, 0, true);

    }

    //bounce off walls
    if(pos.x < ofGetWindowHeight()/2){
        vel.x *= -1;
        pos.x = ofGetWindowHeight()/2 + 2;
    } else if(pos.x > ofGetWindowWidth()/2 + ofGetWindowHeight()/2){
        vel.x *= -1;
        pos.x = ofGetWindowWidth()/2 + ofGetWindowHeight()/2 - 2;
    }
    
    if(pos.y < 0){
        vel.y *= -1;
        pos.y = 2;
    } else if(pos.y > ofGetWindowHeight()){
        vel.y *= -1;
        pos.y = ofGetWindowHeight() - 2;
    }
    
    
    
}

void SubAtomic::draw(){
    
    ofPushMatrix();
    ofTranslate(pos);
    ofRotate(180);
    ofSetColor(255, trans);
    sharedImage -> draw(0, 0, sharedImage -> width * scale, sharedImage -> height * scale);
    
    ofPopMatrix();
    
}











