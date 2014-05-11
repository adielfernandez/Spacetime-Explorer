//
//  Idle.h
//  Spacetime_Explorer_Statemachine
//
//  Created by Adiel Fernandez on 5/10/14.
//
//

#ifndef __Spacetime_Explorer_Statemachine__Idle__
#define __Spacetime_Explorer_Statemachine__Idle__

#include <iostream>

#endif /* defined(__Spacetime_Explorer_Statemachine__Idle__) */


#pragma once

#include "ofxState.h"
#include "SharedData.h"

class Idle : public itg::ofxState<SharedData>
{
public:

    void setup();
    void update();
	void draw();
	void mousePressed(int x, int y, int button);
	string getName();
};