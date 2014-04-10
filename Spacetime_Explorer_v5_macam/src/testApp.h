#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "Particle.h"
#include "ofxMacamPs3Eye.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    //Serial connection
    int pistonPos;  //0 = level, 255 = bottom
    int flash;      //0 = off, 1 = light show
    int pistonSpeed;
    void sendSerial(long one, long two, long three);
    ofSerial serial;
    
    
    //CV stuff
    ofxMacamPs3Eye ps3eye;
    
    ofxCvGrayscaleImage grayScale;
    ofxCvColorImage colorImage;
    ofxCvContourFinder contourFinder;
    vector<ofVec2f> oldBlobPos;
    vector<ofVec2f> blobDirection;
    int threshold;
    int disturbRad;
    int camWidth, camHeight;
    float leftBound, rightBound;
    float topBound, bottomBound;
    float disturbMax, disturbMin;
    
    //shader stuff
    ofVbo vbo;
    ofShader shader;
    ofTexture texture;
    vector<ofVec3f> points;
    vector<ofVec3f> sizes;
    vector<ofFloatColor> colors;
    
    //Narrative control
    int narrativeState;
    bool transitionTo2;
    int transitionTo2Timer;

    bool transitionTo3;
    int transitionTo3Timer;
    
    bool zooming;
    float zoomSquareWidth;
    float zoomSquareThick;
    ofColor zoomSquareCol;
    
    
    //Attractor Stuff
    ofVec2f attractorPos;
    int attractorSize;
    int attractorBase;
    int attractionRad;
    float attractStrength;
    int attractorMax;
    //perlin blob
    void perlinBlob(int base, float range, int randSeed, int rot);
    
    
    
    //Particle Stuff
    int numParticles;
    vector<Particle> pList;
    int numDead;
    int numDisturbed;
    ofImage colorscheme;
    float trans;
    int pBig;
    int pSmall;
    
    
    //Particle Field 
    void newParticleField(int res);
    float randomPerl;
    int fieldRes;
    
    
    
    
    //mouse interaction
    ofVec3f mouseDirection;
    ofVec3f oldMousePos;
    ofVec3f mousePos;
    int mouseRad;
    
    
    //UI Elements
    bool debugVisuals;
    bool drawCam;
    void debugVis();
    void drawUI();
    ofTrueTypeFont instructions;
    ofColor instructCol;
    string instructionA;
    string instructionB;
    
    ofTrueTypeFont status;
    ofTrueTypeFont statusBigger;
    ofColor statusCol;
    string statusA;
    string statusB;
    float statusScale;

    
    //Sound Effects
    ofSoundPlayer zoom;
    ofSoundPlayer pWhoosh;
    ofSoundPlayer narrate1;
    
    
};
