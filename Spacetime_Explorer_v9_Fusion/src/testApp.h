#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "Particle.h"
#include "ofxMacamPs3Eye.h"
#include "SunParticle.h"
#include "Fragment.h"
#include "Timer.h"
#include "SubAtomic.h"

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
    string instructionC;
    string instructionD;
    
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

    //timing
    int currentTime;

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
    
    int handTrans;

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

    ofSoundPlayer stage5_01_thestarhasbecome;
    ofSoundPlayer stage5_02_waveaball;
    ofSoundPlayer stage5_03_hydrogenatomsarejoined;
    //ofSoundPlayer stage5_04_starsconstantbalance;
    
    
    bool playStage5_01;
    bool playStage5_02;
    bool playStage5_03;
    
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
    bool starEquilibriumSetup;

    //-----------Stage 6-----------
    //-------Fusion Intro--------
    
    bool setupStage6;
    
    ofSoundPlayer stage6_01_fusionIsThe;
    bool playStage6_01;
    
    
    
    ofImage fusionFull;
    ofImage fusionStage1;
    ofImage fusionStage2;
    ofImage fusionStage3;
    
    ofVec3f reactant1pos, reactant2pos;
    ofVec3f deutPos, trinoPos, posiPos;
    ofVec3f collision;
    
    float reactantTrans, productTrans, explosionTrans;
    float titleTrans;

    float fullDiagTrans;
    float stage1DiagTrans;

    float highlighterX;
    float highlighterY;
    float highlighterHeight;
    float highlighterTrans;
    
    //-----------Stage 7-----------
    //-------Fusion Stage 1--------

    bool setupStage7;
    
    ofSoundPlayer stage7_01_theFirstStep;
    ofSoundPlayer stage7_02_youveMadeDeuterium;
    ofSoundPlayer stage7_03_greatJobFeelFree;
    
    bool playStage7_00;
    bool playStage7_01;
    bool playStage7_02;
    bool playStage7_03;
    
    bool playedSecondClip;
    bool playedThirdClip;
    
    ofImage hydrogen;
    ofImage hydroBank;
    
    ofImage neutron;
    
    ofImage deuterium;
    ofImage deuteriumSlot;
    ofImage deuteriumOutline;
    
    ofImage helium3;
    ofImage helium3Slot;
    ofImage helium3Bank;
    
    ofImage helium4;
    ofImage helium4Slot;
    
    ofImage neutrino;
    ofImage positron;
    ofImage gammaRay;
    ofImage gammaLabel;
    
    ofImage key1;
    ofImage key2;
    ofImage key3;
    
    ofSoundPlayer fusionPop1;
    ofSoundPlayer fusionPop2;
    ofSoundPlayer fusionPop3;
    
    Timer continueFusion;
    bool useContinueTimer;
    
    bool blobCollision;
    int collisionTimer;
    float colDist;
    ofVec3f collisionPos;
    int noColZoneRad;
    float particleScale;
    float collisionBurstTrans;
    float collisionBurstSize;
    int numBankSlot;
    ofVec3f bankSlot1;
    ofVec3f bankSlot2;
    int endStageTimer;
    int audioDelayTimer;
    
    vector<SubAtomic> fusorList;
    
    
    //-----------Stage 8-----------
    //-------Fusion Stage 2 INTRO--------
    
    bool setupStage8;
    
    ofSoundPlayer stage8_01_theNextStep;
    
    bool playStage8_01;
    
    ofVec3f hel3Pos, gammaPos;
    float stage2DiagTrans;
    int stage2TextShift;
    
    
    //-----------Stage 9-----------
    //-------Fusion Stage 2--------
    
    bool setupStage9;
    
    ofSoundPlayer stage9_01_hitTheFloatingDeut;
    ofSoundPlayer stage9_02_youveMadeHelium3;
    ofSoundPlayer stage9_03_weNowHaveTwo;
    
    bool playStage9_01;
    bool playStage9_02;
    bool playStage9_03;
    
    
    int floatDeutTimer;
    vector<SubAtomic> floatDeut;
    
    
    
    //-----------Stage 10-----------
    //-------Fusion Stage 3 INTRO--------
    
    bool setupStage10;

    ofSoundPlayer stage10_01_theLastStepIs;
    
    bool playStage10_01;
    
    
    ofVec3f proton1Pos, proton2Pos, hel4Pos;
    ofVec3f stage3TextPos, stage3TextEndPos;
    float stage3DiagTrans;
    float stageTextScale;
    
    
    
    
    
    
    //-----------Stage 11-----------
    //-------Fusion Stage 3--------
    
    bool setupStage11;

    ofSoundPlayer stage11_01_collideTwoBallsAndSee;
    ofSoundPlayer stage11_02_youveMadeHel4TryAnother;
    ofSoundPlayer stage11_03_aHelium4emc2;
    ofSoundPlayer stage11_04_inFusionlittleMassLotEnergy;
    
    bool playStage11_01;
    bool playStage11_02;
    bool playStage11_03;
    bool playStage11_04;
    
    
    
    
    //-----------Stage 12-----------
    //-------Fusion Stage 4--------
    
    bool setupStage12;
    
    ofSoundPlayer stage12_01_thisIsPoolOfHydrogen;
    ofSoundPlayer stage12_02_noticeHowSpeedingUp;
    ofSoundPlayer stage12_03_allHydrogenFused;
    
    bool playStage12_01;
    bool playStage12_02;
    bool playStage12_03;
    
    
    
    
    
    
    
    
    
    
    
};











