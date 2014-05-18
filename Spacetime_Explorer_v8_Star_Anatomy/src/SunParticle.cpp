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
    damping = 0.97f;
    lifeSpan = ofRandom(ageOfDeath);
    size = 1;
    
    ageOfDeath = 50;
    explode = true;
    acc.set(0);
    
    dead = false;
    starSize = 250;
    
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



void SunParticle::mouseRepel(ofVec3f _pos, float _radius, float _strength){
    
    
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

void SunParticle::blobRepel(ofVec3f _pos, float _strength){
    
    
    
    ofVec2f diff = pos - _pos;
    
    float pct = ofClamp(1 - diff.length()/1000, 0.3, 1);
    diff.normalize();
    
    
    acc.x += blobDir.x/6 * pct * _strength;
    acc.y += blobDir.y/6 * pct * _strength;
    
    
    
}

void SunParticle::resetParticle(){
    
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
    pos = randVec * ofRandom( 80.0f, starSize );
    pos.x = pos.x + ofGetWindowWidth()/2;
    pos.y = pos.y + ofGetWindowHeight()/2;
    
    
    ofVec3f toCenter = pos - ofVec3f(ofGetWindowSize()/2);
    toCenter.normalize();
    
    vel = toCenter * ofRandom(0.5, 5);
    
    if(explode){
        pos = ofVec3f(ofGetWindowSize()/2);
        vel = ofVec3f(ofRandom(-20, 20), ofRandom(-20, 20), ofRandom(0, 20));
        
    }
    
    if(size < 100){
        size += 5;
    } else {
        size = 0;
    }

    
}


void SunParticle::update(ofVec3f _mouse) {
    
    mouseDirection = _mouse;
    
    vel *= damping;
    
    vel += acc;
    pos += vel;
    
    
    
    lifeSpan++;
    
    
    acc.set(0);
    
    
    if(lifeSpan > ageOfDeath){
        
//        if(disturbed == false){
        
            resetParticle();
            
//        } else {
//            dead = true;
//        }
        
    }
    

    
}

//------------------------------LEGACY CODE: NOT ACTUALLY CALLED------------------------------
//But we still need to call the functions above so the positions are updated
//before they are passed to the VBO then to the shader


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


