//
//  SunParticle.cpp
//  Algo_Final_v3
//
//  Created by Adiel Fernandez on 12/16/13.
//
//

#include "SunParticle.h"




SunParticle::SunParticle() {

    damping = ofVec2f( 0.01f );
    trans = ofRandom(255);
    
    
    
}

void SunParticle::setParams( ofVec3f _pos, ofVec3f _vel){
    pos.set( _pos );
    vel.set( _vel );
    
}

void SunParticle::addForce( ofVec2f force ){
    frc += force;
}

void SunParticle::addDampingForce() {
    frc = frc - vel * damping;
}

void SunParticle::resetForces() {
    frc.set(0,0);
}

void SunParticle::update() {
    vel = vel + frc;
    pos = pos + vel;
    
    trans -= 4;
    
    
    
    if(trans < 0){
        //reset transparency
        trans = 255;
        
        //then give a new random position
        float phi = ofRandom( 0, TWO_PI );
        float costheta = ofRandom( -1.0f, 1.0f );
        
        float rho = sqrt( 1.0f - costheta * costheta );
        float x = rho * cos( phi );
        float y = rho * sin( phi );
        float z = costheta;
        
        ofVec3f randVec(x, y, z);
        pos = randVec * ofRandom( 250.0f, 300.0f );
        
        ofVec3f toCenter = ofVec3f(ofGetWindowSize()/2) - pos;
        toCenter.normalize();
        
        vel = toCenter * ofRandom(1, 5);
        
        
    }
    
    
    resetForces();
    
}

void SunParticle::draw() {

    
    ofPushMatrix();
    
    ofTranslate(ofGetWindowWidth()/2, ofGetWindowHeight()/2, -1000);

    ofSetColor(col, trans);
    ofCircle(pos.x, pos.y, 20);

    ofPopMatrix();


}