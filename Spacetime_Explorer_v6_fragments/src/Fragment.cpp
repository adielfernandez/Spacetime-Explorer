//
//  Fragment.cpp
//  Spacetime_Explorer_v5_macam
//
//  Created by Adiel Fernandez on 4/27/14.
//
//

#include "Fragment.h"



Fragment::Fragment() {
    
    trans = 0;
    col = ofColor(255);
    size = 1;   //initialize to 1 but will be changed by the createMainFragment() code;
    
    range = ofRandom(20, 100);


    noiseShift = ofRandom(2000);
    noiseSpeed = ofRandom(0.2, 1);
    
}

void Fragment::setParams( ofVec3f _pos){
    basePos.set( _pos );
    
}






void Fragment::update(float _scale) {
    
    scaleFactor = _scale;
    
    
    pos.x = (basePos.x) * scaleFactor + range * ofSignedNoise(ofGetElapsedTimef() * noiseSpeed);
    
    pos.y = (basePos.y) * scaleFactor + range * ofSignedNoise(ofGetElapsedTimef() * noiseSpeed + noiseShift);
//    pos.z = basePos.z + range * ofNoise(ofGetElapsedTimef() * noiseSpeed + noiseShift);
    
    
    
    
    if(trans < 255){
        trans += 2;
    }
    
    
    
    
}

void Fragment::draw() {
    
    
    ofPushMatrix();
    
    ofTranslate(ofGetWindowWidth()/2, ofGetWindowHeight()/2);
    
    ofSetColor(col, trans);
//    ofSetColor(255);
    ofCircle(pos, size);

    ofPopMatrix();
    
    
    
    
}








