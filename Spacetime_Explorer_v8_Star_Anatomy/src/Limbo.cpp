//
//  Limbo.cpp
//  Spacetime_Explorer_v5_macam
//
//  Created by Adiel Fernandez on 4/24/14.
//
//

#include "Limbo.h"

//
//
//if(starCreated == false){
//    for (int i = 0; i < 1000; i++){
//        
//        sunCol1 = ofColor(255, 255, 150);
//        sunCol2 = ofColor(255, 100, 20);
//        starCreated = true;
//        
//        //Circle distribution code from Charlie Whitney (flocking sketch - algo - fall 2013)
//        
//        float phi = ofRandom( 0, TWO_PI );
//        float costheta = ofRandom( -1.0f, 1.0f );
//        
//        float rho = sqrt( 1.0f - costheta * costheta );
//        float x = rho * cos( phi );
//        float y = rho * sin( phi );
//        float z = costheta;
//        
//        ofVec3f randVec(x, y, z);
//        
//        ofVec3f pos = randVec * ofRandom( 25.0f, 50.0f );
//        ofVec3f vel(ofRandom(-10, 10),ofRandom(-10, 10),ofRandom(-10, 10));
//        
//        
//        SunParticle s;
//        s.setParams(pos, vel);
//        s.col = sunCol1.lerp(sunCol2, ofRandom(0,1));
//        
//        sunList.push_back(s);
//        
//    }
//    
//    
//}
//
//
//ofSetColor(sunCol1);
//ofCircle(ofGetWindowWidth()/2, ofGetWindowHeight()/2, attractorSize);
//
////place glow image on top of star
//ofPushMatrix();
//
//ofTranslate(ofGetWindowSize()/2);
//ofSetRectMode(OF_RECTMODE_CENTER);
//ofSetCircleResolution(50);
//ofSetColor(255, 220, 50, 255 * 0.9);
//ofCircle(0, 0, 150);
//glow.draw(0, 0, 350, 350);
//
//ofSetRectMode(OF_RECTMODE_CORNER);
//
//ofPopMatrix();
//
//
////update sun particles
//for( vector<SunParticle>::iterator it = sunList.begin(); it != sunList.end(); it++){
//    it -> update();
//    it -> draw();
//    
//}
//
