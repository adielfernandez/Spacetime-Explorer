//
//  Idle.cpp
//  Spacetime_Explorer_Statemachine
//
//  Created by Adiel Fernandez on 5/10/14.
//
//

#include "Idle.h"

void Idle::setup(){
    
}

void Idle::update(){
	if (ofGetElapsedTimeMillis() - getSharedData().lastUpdate > 200)
	{
		getSharedData().counter++;
		getSharedData().lastUpdate = ofGetElapsedTimeMillis();
	}
}

void Idle::draw(){
	ofBackground(0, 255, 0);
	ofSetColor(255, 0, 0);
	getSharedData().font.drawString(ofToString(getSharedData().counter), ofGetWidth() >> 1, ofGetHeight() >> 1);
}

string Idle::getName(){
	return "Idle";
}

void Idle::mousePressed(int x, int y, int button){
    
    
    
//	changeState("red");
}
