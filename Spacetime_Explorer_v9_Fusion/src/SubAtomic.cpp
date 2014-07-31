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
    
    
    floating = false;
    twoImages = false;
    
    
    
    age = 0;
    damping = 0.93;
    trans = 255;
    size = 1.0;
    
    //use deutSlot to keep track if it should go to the deuterium slot
    //0 means none, 1 means first slot, 2 means second slot;
    bankSlot = 0;
    
    
}


void SubAtomic::setup(ofVec3f _pos, float velAng, ofImage *image){
    
    sharedImage = image;
    
    pos = _pos;
    collisionPos = _pos;
    
    //-----give random velocity-----
    //first get unit vector
    vel = ofVec3f(1, 0, 0);
    
    //then rotate by random amount
    //    vel.rotate(ofRandom(360), ofVec3f(0, 0, 1));
    vel.rotate(velAng, ofVec3f(0, 0, 1));
    
    //scale by random amount
    vel.scale(ofRandom(10, 20));
    
}


//overload setup() for loading second image for gamma ray
void SubAtomic::setup(ofVec3f _pos, float velAng, ofImage *image, ofImage *image2){
    
    sharedImage = image;
    sharedImage2 = image2;
    velAngle = velAng;
    
    pos = _pos;
    collisionPos = _pos;
    
    //-----give random velocity-----
    //first get unit vector
    vel = ofVec3f(1, 0, 0);
    
    //then rotate by random amount
    //    vel.rotate(ofRandom(360), ofVec3f(0, 0, 1));
    vel.rotate(velAngle, ofVec3f(0, 0, 1));
    
    //scale by random amount
    vel.scale(ofRandom(10, 20));
    
}

void SubAtomic::globalAttract(ofVec3f _pos, float _strength){
    
    
    ofVec2f diff = pos - _pos;
    

    //increase damping if we're close to the target position but only for
    //deuterium headed for the slot
    damping = ofMap(diff.length(), 0, 500, 0.8, 0.999, true);
    
    //make velocity 0 if we're really close
    if(diff.length() < 3){
        vel.set(0);
        pos.set(_pos);
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
    
    
    //fade transparency with time
    if(floating){
        
        if(trans < 254){
            trans += 3;
        }

    } else {
        
        age++;
        trans = ofMap(age, 0, 350, 255, 0, true);
        
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
    
    ofPushStyle();
    
    ofSetColor(255, trans);
    
    //draw connecting lines
    if(floating == false){
        ofSetLineWidth(1);
        ofLine(pos, collisionPos);
    }
    
    //draw particle
    ofPushMatrix();
    ofTranslate(pos);
    
    //always draw first two deuteriums full transparency
    if(bankSlot != 0){
        ofSetColor(255);
    }

    sharedImage -> draw(0, 0, sharedImage -> width * scale, sharedImage -> height * scale);
    
    
    //if we're drawing two images for one particle...
    if(twoImages){

        //rotate and draw if its a gamma ray
        if(type == 0){
            ofRotate(velAngle + 180);
            sharedImage2 -> draw(0, 0, sharedImage2 -> width * scale, sharedImage2 -> height * scale);
        }
        
        //dont rotate and flash if its a deuterium outline
        if(type == 2){
            
            
//            if(ofGetElapsedTimeMillis() % 500 < 250){
            
                float sineTrans = 255/2 + 255/2 * sin(ofGetElapsedTimef() * 5);
                
                ofSetColor(255, sineTrans);
                sharedImage2 -> draw(0, 0, sharedImage2 -> width * scale, sharedImage2 -> height * scale);
                
//            }
            
        }
        
        
        
    }
    

    ofPopMatrix();

    ofPopStyle();





}











