#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "Particle.h"
#include "ofxMacamPs3Eye.h"
#include "SunParticle.h"
#include "Fragment.h"

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
    ofShader shader;
    ofTexture pTex;
    ofTexture sunSmoke;
    ofTexture sunCrescent;

    ofVbo particleVBO;
    vector<ofVec3f> pPoints;
    vector<ofVec3f> pSizes;
    vector<ofFloatColor> pColors;
    
    ofVbo fragmentVBO;
    vector<ofVec3f> fragPoints;
    vector<ofVec3f> fragSizes;
    vector<ofFloatColor> fragColors;
    

    
    
    
    
    

    
    
    
    
    
    //Attractor Stuff
    ofVec2f attractorPos;
    int attractorSize;
    float attractorLerp;
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
    float pTrans;
    int pBig;
    int pSmall;
    
    
    //Particle Field 
    void newParticleField(int res);
    float randomPerl;
    int fieldRes;
    void createClump(int _x, int _y, float _rad, int num);
    
    
    
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
    void drawProgress(float progress);
    
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
    
    
    
    //Narrative control
    int narrativeState;
    bool transitionToNext;
    int transitionToNextTimer;
    
    
    bool zooming;
    float zoomSquareWidth;
    float zoomSquareThick;
    ofColor zoomSquareCol;
    
    
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
    int stageStartTime;
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
    
    //----------Stage 1----------
    //-------Cloud Fragment------
    
    bool setupStage1;
    
    vector<Fragment> mainFragment;
    
    void createMainFragment();
    
    ofSoundPlayer stage1_01_wearenow;
    ofSoundPlayer stage1_02_useyourhands;
    ofSoundPlayer stage1_03_seehow;
    ofSoundPlayer stage1_04_keepgathering;
    ofSoundPlayer stage1_05_youvecreated;
    
    bool playStage1_01;
    bool playStage1_02;
    bool playStage1_03;
    bool playStage1_04;
    bool playStage1_05;
    
    bool ballInfluence;
    bool announced;
    int announcedTimer;
    bool test;
    

    ofVec2f progressBarPos;
    ofVec2f progressBarDim;
    string progressText;
    ofColor progressCol;
    
    
    
    //----------Stage 2----------
    //---------Protostar---------

    bool setupStage2;
    
    ofSoundPlayer stage2_01_useyourhands;
    ofSoundPlayer stage2_02_sometimescloud;
    ofSoundPlayer stage2_03_startingtogetwarm;
    ofSoundPlayer stage2_04_fragmentprotostar;
    ofSoundPlayer stage2_05_littlemoremass;
    
    bool playStage2_01;
    bool playStage2_02;
    bool playStage2_03;
    bool playStage2_04;
    bool playStage2_05;
    

    ofVec3f clumpPos;
    bool locateClump;
    ofImage protoGlow;
    
    
    //----------Stage 3----------
    //-----Protostar to star-----
    
    bool setupStage3;
    

    //----------Stage 4----------
    //-----Protostar to star-----
    
    bool setupStage4;

    
    ofColor sunCol1;
    ofColor sunCol2;
    ofImage glow;
    
    vector<SunParticle> sunPList;
    void createSunSmoke();
    
    
    
    
};










