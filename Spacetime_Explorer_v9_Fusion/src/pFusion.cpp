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
    
    dead = false;
    
    boundary = 900;
    
    age = 0;
    damping = 1.0;
    trans = 255;
    size = 1.0;
    
    aspectX = 1920;
    aspectY = 1080;
    
    bulkSpeed = 0;
    
}


void pFusion::setup(ofVec3f _pos, float velAng){
    
    
    pos = _pos;

    
    //-----give random velocity-----
    //first get unit vector
    vel = ofVec3f(1, 0, 0);
    
    //then rotate by random amount
    //    vel.rotate(ofRandom(360), ofVec3f(0, 0, 1));
    vel.rotate(velAng, ofVec3f(0, 0, 1));
    
    //scale by random amount
    vel.scale(bulkSpeed);
    
}






void pFusion::update(float _speed){
    
    bulkSpeed = _speed;
    
    vel.normalize();
    vel.scale(_speed);
    

    
    //bounce off walls but only if we're hydrogen, deuterium or helium 3 or 4
    
    if(type >= 1 && type <= 4 && fuse == false){
        
        //circular boundary (with correct bouncing)
        ofVec3f toCenter = ofGetWindowSize()/2;
        float distSq = ofDistSquared(toCenter.x, toCenter.y, pos.x, pos.y);
        
        if(distSq > (boundary/2 - 15) * (boundary/2 - 15)){
            
            //get the vector perpendicular to circle tangent
            ofVec3f perp = toCenter - pos;
            
            //then get the angle between the perpendicular and the velocity
            float angle = vel.angle(perp);
            
            //find the cross product of velocity and perpendicular
            //we need this to determine which way to rotate our speed (orientation of bounce)
            ofVec3f cross = vel.getCrossed(perp);
            
            if(cross.z > 1){

                vel.rotate(180 + angle*2, ofVec3f(0, 0, 1));
                
            } else if(cross.z < 1){
            
                vel.rotate(180 - angle*2, ofVec3f(0, 0, 1));
//                size = 2.0f;
                
            } else {
                vel *= -1;
            }
            
            //and also move the position toward the center so
            //we dont get weird boundary cases
            pos = pos + (perp * 0.01);
            
            
            
        }

        
    } else {
        
        //if we're a positron, neutrino or gamma ray, check if we're out off screen so we can delete
        
        //square boundary
        if(pos.x < aspectX/2 - aspectY/2 || pos.x > aspectX/2 + aspectY/2 || pos.y < 0 || pos.y > aspectY){
            
            dead = true;
        
        
        }
        
        vel.normalize();
        vel.scale(4);
        
        
    }
    

    
    vel *= damping;
    
    vel += acc;
    
    pos += vel;
    
    acc.set(0);
    
    age++;
    
    
}

void pFusion::draw(ofImage *image){
    
    ofPushStyle();
    
    

    
    //draw particle
    if(type == 0 || type >= 5){

        float trans = ofMap(age, 0, 150, 255, 0, true);
        ofSetColor(255, trans);
        ofSetLineWidth(2);
        ofLine(collisionPos.x, collisionPos.y, pos.x, pos.y);

    }

    
    
    ofPushMatrix();
    ofTranslate(pos);
    
//    if(type == 0){
//        ofRotate(gammaAngle);
//    }

    
    
    
    
    ofScale(size, size);
    
    
    ofSetColor(255);
    image -> draw(0, 0);


    //rotate and draw if its a gamma ray
//    if(type == 0){
//        ofRotate(velAngle + 180);
//        sharedImage2 -> draw(0, 0, sharedImage2 -> width * scale, sharedImage2 -> height * scale);
//    }
    
        
        
        
    
    
    
    ofPopMatrix();
    
    ofPopStyle();
    

    
    
}
