#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "Particle.h"
#include "ofxMacamPs3Eye.h"
#include "SunParticle.h"
#include "Fragment.h"
#include "Timer.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
    void exit();
		
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
    void drawMarkers();
    
    ofTrueTypeFont instructions;
    float instructionScale;
    ofColor instructCol;
    string instructionA;
    string instructionB;
    
    ofTrueTypeFont status;
    ofTrueTypeFont statusBigger;
    ofColor statusCol;
    string statusA;
    string statusB;
    float statusScale;
    float statusRot;
    
    ofImage handWithBall;
    ofImage handThrowingBall;
    
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
    float narrativeState;
    bool transitionTo2;
    int transitionTo2Timer;
    
    bool transitionTo3;
    int transitionTo3Timer;
    
    bool zooming;
    float zoomSquareWidth;
    float zoomSquareThick;
    ofColor zoomSquareCol;
    
    
    //Narrative States
        //-1 = idle state
        //0 = intro video
        //0.5 = table of contents
        //1 = molecular cloud
        //2 = cloud fragment
        //3 = protostar
        //4 = star
    
    //----------Idle----------
    bool setupStageIdle;
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
    
    
    Timer introTimer;

    
    
    //----------Intro----------
    bool setupStageIntro;
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
    

    //----------Table of Contents----------
    bool setupStageTOC;
    
    ofImage spacetimeThumb;
    ofImage protoThumb;
    ofImage starThumb;
    ofImage comingSoon;
    ofImage stagesThumb;
    
    vector<Timer> tableOfContents;
    vector<int> numBallsInTimers;
    vector<string> TOClabelsA;
    vector<string> TOClabelsB;
    
    float nextStage;
    bool transitionToStage;
    
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
    bool announced2;
    int announcedTimer;
    bool test;
    

    ofVec2f progressBarPos;
    ofVec2f progressBarDim;
    float progress;
    float progressThresh;
    string progressText;
    
    
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
    
    ofSoundPlayer stage3_01_helptheprotostar;
    ofSoundPlayer stage3_023_heatandpressure;
    ofSoundPlayer smallExplosion;

    bool playStage3_01;
    bool playStage3_023;
    
    bool setupStage3;
    ofImage starburst;
    int starburstTimer;
    float starburstSize;
    ofVec2f starburstPos;
    float starburstTrans;
    bool burst;
    int nextBurst;
    
    //-----------Stage 4-----------
    //-------Exploding Star--------
    
    bool playStage4_01;
    ofSoundPlayer stage4_01_wevereachedcritical;

    
    bool setupStage4;
    ofSoundPlayer explosion;
    ofColor sunCol1;
    ofColor sunCol2;
    ofImage glow;
    
    vector<SunParticle> sunPList;
    void createSunSmoke(int numParticles);
    
    float shakeAmplitude;
    
    bool transitionToChoice;
    Timer toTOC;
    Timer toNextStage;
    int numBallTOC;
    int numBallNextStage;
    
    Timer doneWithStar;
    bool useDWStimer;

    
    //-----------Stage 5-----------
    //--------Star Anatomy---------

    bool setupStage5;
    Timer starStageTimer;
    float starSize;
    float goalStarSize;
    ofImage arrow;
    float arrowTrans;
    
    bool showEquilibrium;
    ofColor fusionArrow;
    ofColor gravityArrow;
    int coreTimer;
    int coreCounter;
    int starUseTime;
    bool timeFlag;
    
    //-----------Stage 6-----------
    //-------Fusion Process--------

    
};










