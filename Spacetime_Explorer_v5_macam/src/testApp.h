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
    
    ofColor cvObjectCol;
    
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
    void drawBlackBars();
    void drawGrid(int num, float trans);
    
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

    ofImage handWithBall;
    
    //Sound Effects
    ofSoundPlayer zoom;
    ofSoundPlayer pWhoosh;
    ofSoundPlayer narrate1;
    
    //Narrator clips
    //Idle state
    ofSoundPlayer idle;
    ofSoundPlayer welcome;
    
    //Intro video
    ofSoundPlayer Intro01_peoplethink;
    ofSoundPlayer Intro02_welivein;
    ofSoundPlayer Intro03_whiletime;
    ofSoundPlayer Intro04_thisisspacetime;
    ofSoundPlayer Intro05_thingsthatmove;
    ofSoundPlayer Intro06_rollsomeballs;
    ofSoundPlayer Intro07_nowrollballs;
    ofSoundPlayer Intro08_easytosee;
    ofSoundPlayer Intro09_thiscurvingof;
    ofSoundPlayer Intro10_wedontnotice;
    ofSoundPlayer Intro11_iftheresenough;
    ofSoundPlayer Intro12_letssee;
    
    //Narrative States
    //----------Idle----------
    int idleTimer = 0;
    bool idlePlay = false;
    bool welcomePlay = false;
    ofImage background;
    
    float lineTrans;
    float boxTrans;
    bool inButton;
    int numBallsinBox;
    float timeInBox = 0;
    ofPath idleTimerPath;
    bool idleHand;
    float idleHandLerp = 0;
    ofVec2f idleHandPos;
    ofColor idleTimerCol;
    float blackOutTrans = 0;
    bool transitionToIntro;
    
    //----------Intro----------
    bool startedIntro;
    int introStartTime;
    bool playIntro01;
    bool playIntro02;
    bool playIntro03;
    bool playIntro04;
    bool playIntro05;
    bool playIntro06;
    bool playIntro07;
    bool playIntro08;
    bool playIntro09;
    bool playIntro10;
    bool playIntro11;
    bool playIntro12;
    
    
    ofImage milkyWay;
    float milkyWayTrans;
    ofImage shuttle;
    ofVec2f shuttlePos;
    ofImage shuttleDimensions;
    float shuttleTrans;
    float shuttleDimTrans;
    ofImage timeArrow;
    float arrowStartX;
    
    ofEasyCam gridCam;
    float gridTrans;
    float flatGridTrans;
    float gridRot;
    ofPath rollTimerPath;
    float rollTimer;
    ofColor rollTimerCol;
    bool useRollTimer;
    int intro2Timer;
    int introStage;
    ofImage bowlingball;
    float bowlingballTrans;
    float bowlingballScale;
    float rollTimerRad = 75;
    ofPoint rollTimerPos;
    int stage2Time;
    float rollTimerTrans;
    
    ofImage warpedIsGravity;
    float warpedIsGravityTrans;
    ofVec2f warpedGravPos;
    float warpedRot;
    float warpedSize;
    
    ofImage earth;
    float earthSwitchScale;
    
    ofPath lightArc;
    ofPoint lightArcCenter;
    float lightArcRad;
    float lightArcAngle;
    float lightArcTrans = 255;
    
};










