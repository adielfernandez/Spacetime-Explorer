//
//  pFusion.cpp
//  Spacetime_Explorer_v9_Fusion
//
//  Created by Adiel Fernandez on 8/4/14.
//
//

#include "pFusion.h"


pFusion::pFusion(){
    
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


void pFusion::setup(ofVec3f _pos, float velAng, ofImage *image){
    
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






void pFusion::update(){
    
    vel *= damping;
    
    vel += acc;
    
    pos += vel;
    
    acc.set(0);
    
    

    
    

    
    
    
}

void pFusion::draw(){
    
    ofPushStyle();
    
    ofSetColor(255, trans);
    

    
    //draw particle
    ofPushMatrix();
    ofTranslate(pos);
    
    //always draw first two deuteriums full transparency
    if(bankSlot != 0){
        ofSetColor(255);
    }
    
    sharedImage -> draw(0, 0, sharedImage -> width * scale, sharedImage -> height * scale);
    
    
        
    //rotate and draw if its a gamma ray
    if(type == 0){
        ofRotate(velAngle + 180);
        sharedImage2 -> draw(0, 0, sharedImage2 -> width * scale, sharedImage2 -> height * scale);
    }
    
        
        
        
    
    
    
    ofPopMatrix();
    
    ofPopStyle();
    
    
    
    
    
}
