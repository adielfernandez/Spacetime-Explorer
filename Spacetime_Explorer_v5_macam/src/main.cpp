#include "ofMain.h"
#include "testApp.h"

//========================================================================
int main( ){

	ofSetupOpenGL(1920,1080, OF_FULLSCREEN);			// <-------- setup the GL context
//    ofSetWindowPosition(0, -1080);
    
    
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}
