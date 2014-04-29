//
//  SunParticle.cpp
//  Algo_Final_v3
//
//  Created by Adiel Fernandez on 12/16/13.
//
//

#include "SunParticle.h"




SunParticle::SunParticle() {

//    damping = ofVec2f( 0.01f );
    damping = 0.99f;
    lifeSpan = ofRandom(ageOfDeath);
    size = 1;
    
    ageOfDeath = 50;
    
    
}

void SunParticle::setParams( ofVec3f _pos, ofVec3f _vel){
    pos.set( _pos );
    vel.set( _vel );
    
}

//void SunParticle::addForce( ofVec2f force ){
//    frc += force;
//}
//
//void SunParticle::addDampingForce() {
//    frc = frc - vel * damping;
//}
//
//void SunParticle::resetForces() {
//    frc.set(0,0);
//}

void SunParticle::update() {
    
    vel *= damping;
    
    
    pos = pos + vel;
    
    lifeSpan++;
    
    
    
    if(lifeSpan > ageOfDeath){
        //reset life counter
        lifeSpan = 0;;
        
        //then give a new random position
        float phi = ofRandom( 0, TWO_PI );
        float costheta = ofRandom( -1.0f, 1.0f );
        
        float rho = sqrt( 1.0f - costheta * costheta );
        float x = rho * cos( phi );
        float y = rho * sin( phi );
        float z = costheta;
        
        ofVec3f randVec(x, y, z);
        pos = randVec * ofRandom( 80.0f, 150.0f );
        pos.x = pos.x + ofGetWindowWidth()/2;
        pos.y = pos.y + ofGetWindowHeight()/2;
        
        
        ofVec3f toCenter = pos - ofVec3f(ofGetWindowSize()/2);
        toCenter.normalize();
        
        vel = toCenter * ofRandom(0.5, 2);
        
        if(size < 80){
            size += 5;
        } else {
            size = 0;
        }
        
    }
    
    
//    resetForces();
    
}

//void SunParticle::draw() {
//
//    
//    ofPushMatrix();
//    
//    ofTranslate(ofGetWindowWidth()/2, ofGetWindowHeight()/2);
//
//    ofSetColor(col, trans);
//    ofCircle(pos.x, pos.y, 20);
//
//    ofPopMatrix();
//
//
//}


