#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
    ofBackground(0);
    ofSetFrameRate(60);
    ofEnableAlphaBlending();

    //serial connection
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    int baud = 9600;
    serial.setup("/dev/tty.usbmodem1421", baud); 
    
    pistonPos = 0;
    pistonSpeed = 120;
    
    // load the texure
	ofDisableArbTex();
	ofLoadImage(pTex, "dotsmall.png");
	ofLoadImage(sunCrescent, "crescent.png");
	ofLoadImage(sunSmoke, "particleTest2.png");
    
    ofEnableArbTex();
    
    // load the shader
    #ifdef TARGET_OPENGLES
        shader.load("shaders_gles/shader");
    #else
        shader.load("shaders/shader");
    #endif
    
    colorscheme.loadImage("m16.jpg");

    
    //camera stuff
    
    camWidth = 640;
    camHeight = 480;

    ps3eye.listDevices();

    ps3eye.setDesiredFrameRate(60);
    ps3eye.setVerbose(true);
    ps3eye.initGrabber(camWidth,camHeight, true);
    
	ps3eye.setAutoGainAndShutter(false); // otherwise we can't set gain or shutter
	ps3eye.setGain(1.0);
	ps3eye.setShutter(1.0);
	ps3eye.setGamma(0.4);
	ps3eye.setBrightness(0.6);
	ps3eye.setContrast(0.6);
	ps3eye.setHue(0.5);
	
	ps3eye.setFlicker(0);
    
    drawCam = true;
    
    grayScale.allocate(camWidth, camHeight);
    colorImage.allocate(camWidth, camHeight);
    threshold = 150;
    leftBound = 217;
    rightBound = 1721;
    topBound = -47;
    bottomBound = 1097;

    
    disturbRad = 50;
    disturbMin = 50;
    disturbMax = 100;
    
    cvObjectCol = ofColor(0, 255, 0);
    
    
    //Narrative control
    narrativeState = -1;
        //0 = intro video
        //1 = molecular cloud
        //2 = cloud fragment
        //3 = protostar
        //4 = star
    
    
    //view controls
    transitionToNext = false;
    transitionToNextTimer = 0;

    
    zooming = false;
    
    
    
    
    
    lineTrans = 0;
    boxTrans = 0;
    inButton = false;
    
    
    
    
    
    
    //Attractor stuff
    attractorBase = 30;
    attractorSize = 0;
    attractorPos.set(ofGetWindowWidth()/2, ofGetWindowHeight()/2);
    attractionRad = 30;
    attractStrength = 0.6;
    attractorMax = 300;
    mouseRad = 150;
    
    
    //CREATE PARTICLE FIELD
    fieldRes = 8;
    pTrans = 0.0;
    pSmall = 15;
    pBig = 80;

    
    //UI Stuff
    instructions.loadFont("avenir.ttc", 100, true, true);
    instructions.setLetterSpacing(0.95);
    instructionA = "Use the balls to push the";
    instructionB = "gas and dust to the center";

    instructCol = ofColor(255);

    
    status.loadFont("avenir.ttc", 100, true, true);
    statusBigger.loadFont("avenir.ttc", 15, true, true);
    status.setLetterSpacing(0.95);
    statusCol = ofColor(255);
    statusA = "Status: Cloud";
    statusB = "Fragment";
    
    zoomSquareWidth = 1080;
    zoomSquareThick = 10;
    zoomSquareCol = ofColor(255, 0, 0);
    

    

    //Sound Effects
    float top = 1.0f;
    float bottom = -1.0f;
    
    zoom.loadSound("zoom.mp3");
    zoom.setVolume(0.5f);
    zoom.setSpeed(0.5f);
    zoom.setMultiPlay(false);
    zoom.setPan(bottom);
    
    pWhoosh.loadSound("whooshShort.mp3");
    pWhoosh.setVolume(0.1f);
    pWhoosh.setSpeed(1.0f);
    pWhoosh.setMultiPlay(true);
    zoom.setPan(bottom);
    
    narrate1.loadSound("pops.mp3");
    narrate1.setVolume(0.1f);
    narrate1.setSpeed(1.0f);
    narrate1.setMultiPlay(false);
    zoom.setPan(bottom);
    
    
    
    //Narration
        //Idle
    idle.loadSound("narration/idle/idle.mp3");
    idle.setVolume(0.5f);
    idle.setSpeed(1.0f);
    idle.setPan(top);
    
    welcome.loadSound("narration/idle/01welcome.mp3");
    welcome.setVolume(1.0f);
    welcome.setSpeed(1.0f);
    welcome.setPan(top);
    
        //Intro
    Intro01_peoplethink.loadSound("narration/intro/01-peoplethink.mp3");
    Intro01_peoplethink.setVolume(1.0f);
    Intro01_peoplethink.setSpeed(1.0f);
    Intro01_peoplethink.setPan(top);
    
    Intro02_welivein.loadSound("narration/intro/02-welivein4.mp3");
    Intro02_welivein.setVolume(1.0f);
    Intro02_welivein.setSpeed(1.0f);
    Intro02_welivein.setPan(top);
    
    Intro03_whiletime.loadSound("narration/intro/03-whiletime.mp3");
    Intro03_whiletime.setVolume(1.0f);
    Intro03_whiletime.setSpeed(1.0f);
    Intro03_whiletime.setPan(top);
    
    Intro04_thisisspacetime.loadSound("narration/intro/04-thisisspacetime.mp3");
    Intro04_thisisspacetime.setVolume(1.0f);
    Intro04_thisisspacetime.setSpeed(1.0f);
    Intro04_thisisspacetime.setPan(top);
    
    Intro05_thingsthatmove.loadSound("narration/intro/05-thingsthatmove.mp3");
    Intro05_thingsthatmove.setVolume(1.0f);
    Intro05_thingsthatmove.setSpeed(1.0f);
    Intro05_thingsthatmove.setPan(top);
    
    Intro06_rollsomeballs.loadSound("narration/intro/06-rollsomeballs.mp3");
    Intro06_rollsomeballs.setVolume(1.0f);
    Intro06_rollsomeballs.setSpeed(1.0f);
    Intro06_rollsomeballs.setPan(top);
    
    Intro07_nowrollballs.loadSound("narration/intro/07-nowrolltheballs.mp3");
    Intro07_nowrollballs.setVolume(1.0f);
    Intro07_nowrollballs.setSpeed(1.0f);
    Intro07_nowrollballs.setPan(top);
    
    Intro08_easytosee.loadSound("narration/intro/08-easytosee.mp3");
    Intro08_easytosee.setVolume(1.0f);
    Intro08_easytosee.setSpeed(1.0f);
    Intro08_easytosee.setPan(top);
    
    Intro09_thiscurvingof.loadSound("narration/intro/09-thiscurvingof.mp3");
    Intro09_thiscurvingof.setVolume(1.0f);
    Intro09_thiscurvingof.setSpeed(1.0f);
    Intro09_thiscurvingof.setPan(top);
    
    Intro10_wedontnotice.loadSound("narration/intro/10-wedontnotice.mp3");
    Intro10_wedontnotice.setVolume(1.0f);
    Intro10_wedontnotice.setSpeed(1.0f);
    Intro10_wedontnotice.setPan(top);
    
    Intro11_iftheresenough.loadSound("narration/intro/11-iftheresenough.mp3");
    Intro11_iftheresenough.setVolume(1.0f);
    Intro11_iftheresenough.setSpeed(1.0f);
    Intro11_iftheresenough.setPan(top);
    
    Intro12_letssee.loadSound("narration/intro/12-letssee.mp3");
    Intro12_letssee.setVolume(1.0f);
    Intro12_letssee.setSpeed(1.0f);
    Intro12_letssee.setPan(top);
    
        //stage 1
    stage1_01_wearenow.loadSound("narration/stage1/01-wearenow.mp3");
    stage1_01_wearenow.setVolume(1.0f);
    stage1_01_wearenow.setSpeed(1.0f);
    stage1_01_wearenow.setPan(top);

    stage1_02_useyourhands.loadSound("narration/stage1/02-useyourhands.mp3");
    stage1_02_useyourhands.setVolume(1.0f);
    stage1_02_useyourhands.setSpeed(1.0f);
    stage1_02_useyourhands.setPan(top);
    
    stage1_03_seehow.loadSound("narration/stage1/03-seehow.mp3");
    stage1_03_seehow.setVolume(1.0f);
    stage1_03_seehow.setSpeed(1.0f);
    stage1_03_seehow.setPan(top);
    
    stage1_04_keepgathering.loadSound("narration/stage1/04-keepgathering.mp3");
    stage1_04_keepgathering.setVolume(1.0f);
    stage1_04_keepgathering.setSpeed(1.0f);
    stage1_04_keepgathering.setPan(top);
    
    stage1_05_youvecreated.loadSound("narration/stage1/05-youvecreated.mp3");
    stage1_05_youvecreated.setVolume(1.0f);
    stage1_05_youvecreated.setSpeed(1.0f);
    stage1_05_youvecreated.setPan(top);
    
    //stage 2
    stage2_01_useyourhands.loadSound("narration/stage2/01-useyourhands.mp3");
    stage2_01_useyourhands.setVolume(1.0f);
    stage2_01_useyourhands.setSpeed(1.0f);
    stage2_01_useyourhands.setPan(top);
    
    stage2_02_sometimescloud.loadSound("narration/stage2/02-sometimescloud.mp3");
    stage2_02_sometimescloud.setVolume(1.0f);
    stage2_02_sometimescloud.setSpeed(1.0f);
    stage2_02_sometimescloud.setPan(top);
    
    stage2_03_startingtogetwarm.loadSound("narration/stage2/03-startingtogetwarm.mp3");
    stage2_03_startingtogetwarm.setVolume(1.0f);
    stage2_03_startingtogetwarm.setSpeed(1.0f);
    stage2_03_startingtogetwarm.setPan(top);
    
    stage2_04_fragmentprotostar.loadSound("narration/stage2/04-fragmentnowprotostar.mp3");
    stage2_04_fragmentprotostar.setVolume(1.0f);
    stage2_04_fragmentprotostar.setSpeed(1.0f);
    stage2_04_fragmentprotostar.setPan(top);
    
    stage2_05_littlemoremass.loadSound("narration/stage2/05-justalittlemoremass.mp3");
    stage2_05_littlemoremass.setVolume(1.0f);
    stage2_05_littlemoremass.setSpeed(1.0f);
    stage2_05_littlemoremass.setPan(top);
    
    
    
    //Narrative States
    //----------Idle----------
    background.loadImage("idleBackground.jpg");
    handWithBall.loadImage("palmwithballgreen.png");
    handWithBall.rotate90(2);
    handWithBall.setAnchorPercent(0.5, 0.5);
    
    //----------Intro----------
    milkyWay.loadImage("milkyway.jpg");
    milkyWay.setAnchorPercent(0.5, 0.5);
    milkyWayTrans = 0;
    shuttle.loadImage("shuttle.png");
    shuttle.setAnchorPercent(0.5, 0.5);
    shuttle.rotate90(2);
    shuttleDimensions.loadImage("shuttleDimensions.png");
    shuttleDimensions.setAnchorPercent(0.5, 0.5);
    shuttleDimensions.rotate90(2);
    shuttleTrans = 0;
    shuttleDimTrans = 0;
    timeArrow.loadImage("timearrow.png");
    timeArrow.setAnchorPercent(0, 0.5);
    timeArrow.rotate90(2);
    arrowStartX = ofGetWindowWidth()/2 - ofGetWindowHeight()/2 + 1080;
    shuttlePos.set(ofGetWindowWidth()/2, ofGetWindowHeight()/2 + 50);
    gridCam.setDistance(1000);
    bowlingball.loadImage("bowlingball.png");
    bowlingball.setAnchorPercent(0.5, 0.5);
    bowlingballTrans = 0;
    warpedIsGravity.loadImage("warpedisgravity.png");
    warpedIsGravity.setAnchorPercent(0.5, 0.5);
    warpedIsGravity.rotate90(2);
    earth.loadImage("earth.png");
    earth.setAnchorPercent(0.5, 0.5);
    
    
    //----------Stage 1:Cloud Fragment----------
    
    
    //----------Stage 2: Protostar----------
    protoGlow.loadImage("protoGlow.png");
    protoGlow.setAnchorPercent(0.5, 0.5);

    
    
    
    
    
    
    
    
    //----------Stage 4: star----------
    glow.loadImage("glow.png");
    glow.setAnchorPercent(0.5, 0.5);
    
    
  
    
    //Load glowy image for star placeholder
//    glow.loadImage("glow.png");
    
    debugVisuals = true;
    
    sendSerial(0, 255, 0);
    
}

//----------------------------------------------------------------------------------
//                 ___  ___  ________  ________  ________  _________  _______
//                |\  \|\  \|\   __  \|\   ___ \|\   __  \|\___   ___\\  ___ \
//                \ \  \\\  \ \  \|\  \ \  \_|\ \ \  \|\  \|___ \  \_\ \   __/|
//                 \ \  \\\  \ \   ____\ \  \ \\ \ \   __  \   \ \  \ \ \  \_|/__
//                  \ \  \\\  \ \  \___|\ \  \_\\ \ \  \ \  \   \ \  \ \ \  \_|\ \
//                   \ \_______\ \__\    \ \_______\ \__\ \__\   \ \__\ \ \_______\
//                    \|_______|\|__|     \|_______|\|__|\|__|    \|__|  \|_______|
//
//----------------------------------------------------------------------------------





void testApp::update(){

    //------------------------------Computer Vision and app management------------------------------
    
    ps3eye.update();
    
    //if we have a new frame
    if(ps3eye.isFrameNew()){
        
        // load grayscale depth image from the kinect source
        colorImage.setFromPixels(ps3eye.getPixels(), camWidth, camHeight);
        
        grayScale = colorImage;
        
        //go through all the pixels and make them white
        //if they fall between threshold values
        unsigned char * pix = grayScale.getPixels();
        
        int numPixels = grayScale.getWidth() * grayScale.getHeight();

        for(int i = 0; i < numPixels; i++) {
                
            if(pix[i] > threshold) {
                pix[i] = 255;
            } else {
                pix[i] = 0;
            }

        }
        
        // update the cv images
        grayScale.flagImageChanged();
        
        contourFinder.findContours(grayScale, 3, (camWidth * camHeight)/3, 20, false);
        
    }

    

    
    mousePos = ofVec3f(mouseX, mouseY);
    mouseDirection = mousePos - oldMousePos;
    
    //clear out the blob direction vector and allocate the same number of slots as there are blobs
    blobDirection.clear();
    blobDirection.resize(contourFinder.blobs.size());
    
    //update the blob direction vector
    for(int i = 0; i < contourFinder.blobs.size(); i++){
        
        //if we have an old blob to match all the current ones subtract
        //their old position so we get their current direction
        if(i < oldBlobPos.size()){
            blobDirection[i] = contourFinder.blobs[i].centroid - oldBlobPos[i];
            
        } else {
            
            //if we dont have enough old positions to match the current
            //number of blobs, then just make the direction zero
            blobDirection[i].set(0);
        }
        
    }
    
    
    
    
    //------------------------------Interaction stuff------------------------------
    ofSoundUpdate();
    
    
    if(narrativeState == -1){
        
        sendSerial(100,255,0);
        
        
        //Narrator
        if(ofGetElapsedTimeMillis() - idleTimer > 20000 && idle.getIsPlaying() == false){
            idlePlay = true;
        }
        
        if(idlePlay){
            idle.play();
            idlePlay = false;
            
            idleTimer = ofGetElapsedTimeMillis();

        }
        
    
        numBallsinBox = 0;
        
        //Look for blobs and display them
        for(int i = 0; i < contourFinder.blobs.size(); i++){
            float mapBlobX = ofMap(contourFinder.blobs[i].centroid.x, 0, camWidth, leftBound, rightBound);
            float mapBlobY = ofMap(contourFinder.blobs[i].centroid.y, 0, camHeight, topBound, bottomBound);
            
//            disturbRad = ofMap(contourFinder.blobs[i].area, 30, 500, disturbMin, disturbMax);
//            
//            ofPushStyle();
//            ofSetColor(cvObjectCol);
//            ofSetCircleResolution(60);
//            ofCircle(mapBlobX, mapBlobY, 10);
//            
//            ofNoFill();
//            ofSetLineWidth(5);
//            ofEllipse(mapBlobX, mapBlobY, 50, 50);
//            
//            ofPopStyle();
            
            
            //check if any balls are in the circle
            if(ofDistSquared(mapBlobX, mapBlobY, ofGetWindowWidth()/2 + ofGetWindowHeight()/2 - 150, 150) < 100 * 100){
                numBallsinBox++;
            }
            
            
        }

        if(numBallsinBox > 0 || ofDist(mouseX, mouseY, ofGetWindowWidth()/2 + ofGetWindowHeight()/2 - 150, 150) < 100){
            inButton = true;
        } else {
            inButton = false;
        }
        
        
        
        
        if(!inButton){
            timeInBox = 0;
        } else if(inButton && transitionToIntro == false){
            timeInBox += 4;
        } 
        
        
        
        
        idleTimerCol = ofColor(255, 150).lerp(ofColor(cvObjectCol,150), ofMap(timeInBox, 0, 360, 0, 1));
        
        //timer circle
        idleTimerPath.clear();
        idleTimerPath.arc(ofPoint(0,0), 100, 100, 0, timeInBox, true);
        
        idleTimerPath.setStrokeWidth(5);
        
        if(inButton){
            idleTimerPath.setStrokeColor(ofColor(255, 0));
            idleTimerPath.setFilled(true);
                        
            idleTimerPath.setFillColor(idleTimerCol);
            
        } else {

            idleTimerPath.setFilled(false);
            idleTimerPath.setStrokeColor(ofColor(255, 0));
        }
        
        idleTimerPath.setStrokeWidth(3);
        idleTimerPath.setCircleResolution(50);
        
        
        if(timeInBox > 359){
            transitionToIntro = true;
            
            if(welcomePlay == false){
                welcome.play();
                welcomePlay = true;
            }
            
        }
        
        if(transitionToIntro){
            timeInBox = 360;
            
            blackOutTrans += 2;
            
            if(blackOutTrans > 255 && idle.getIsPlaying() == false){
                narrativeState = 0;
                
                
                
            }
            
        }
        
    
    
    } else if(narrativeState == 0){
        //introduction
        
        
        //do detection in timer, other stuff is in the draw loop
        if(useRollTimer){
        
            if(rollTimerTrans < 255){
                rollTimerTrans += 1;
            }
            
            
            
            
            
            rollTimerPos.set(ofGetWindowWidth()/2 + ofGetWindowHeight()/2 - 100, 100);
        
            numBallsinBox = 0;
            
            //Look for blobs and display them
            for(int i = 0; i < contourFinder.blobs.size(); i++){
                float mapBlobX = ofMap(contourFinder.blobs[i].centroid.x, 0, camWidth, leftBound, rightBound);
                float mapBlobY = ofMap(contourFinder.blobs[i].centroid.y, 0, camHeight, topBound, bottomBound);
                
                //check if any balls are in the circle
                if(ofDistSquared(mapBlobX, mapBlobY, rollTimerPos.x, rollTimerPos.y) < rollTimerRad * rollTimerRad){
                    numBallsinBox++;
                }
                
                
            }
            
            if(numBallsinBox > 0 || ofDist(mouseX, mouseY, rollTimerPos.x, rollTimerPos.y) < rollTimerRad){
                inButton = true;
            } else {
                inButton = false;
            }
            
            
            
            
            if(!inButton){
                timeInBox = 0;
            } else if(inButton){
                timeInBox += 2;
            }
            
            
            
            
            rollTimerCol = ofColor(255, 150).lerp(ofColor(cvObjectCol,150), ofMap(timeInBox, 0, 360, 0, 1));
            
            //timer circle
            rollTimerPath.clear();
            rollTimerPath.arc(ofPoint(0,0), rollTimerRad, rollTimerRad, 0, timeInBox, true);
            
            
            if(inButton){
                rollTimerPath.setStrokeColor(ofColor(255, 0));
                rollTimerPath.setFilled(true);
                
                rollTimerPath.setFillColor(ofColor(rollTimerCol, 150));
                
            } else {
                
                rollTimerPath.setFilled(false);
                rollTimerPath.setStrokeColor(ofColor(255, 0));
            }
            
            rollTimerPath.setStrokeWidth(3);
            rollTimerPath.setCircleResolution(50);
        
            
            if(timeInBox > 359){
                
                //go to next part of narrative
                timeInBox = 0;
                useRollTimer = false;

                intro2Timer = ofGetElapsedTimeMillis();
                
                //0 for first part, 1 for part between ball rolls, 2 for last part
                introStage++;
                
                
            }
            
        } else {
            rollTimerTrans = 0;
        }
    


        
        
        
        
        
    } else if(narrativeState == 1){
    
        
        //--------------------CLOUD FRAGMENT UPDATE--------------------
        
        //stage setup
        if(setupStage1 == false){
            fieldRes = 12;
            pList.clear();
            newParticleField(fieldRes);
            
            stageStartTime = ofGetElapsedTimeMillis();
            sendSerial(0, 255, 0);
            cvObjectCol = ofColor(255, 0, 0, 255);
            ballInfluence = false;
            announced = false;
            
            createMainFragment();
            
            setupStage1 = true;
            

            progressCol = ofColor(0, 255, 0);
            
            
            pTrans = 0;
            
        }
        
        if(pTrans < 0.2){
            pTrans += 0.003;
        }
        
        //reset particle counters
        numDead = 0;
        numDisturbed = 0;
        
        //clear out points vector so the only particles in there are ones that are alive 
        pPoints.clear();
        pSizes.clear();
        pColors.clear();
        
        
        //Update particles
        for( vector<Particle>::iterator it = pList.begin(); it!=pList.end(); it++){
            
            //only update non-dead particles
            if(it -> dead == false){
        
                
                //upon first entering stage, fade particles in
                it -> trans = ofLerp(it -> trans, 255, 0.02);
                
                
                //check if inside attractor
                ofVec3f distAttractor = attractorPos - it -> pos;
                if(distAttractor.lengthSquared() < attractorSize * attractorSize){
                
                    //if so, make dead
                    it -> dead = true;
                    it -> vel.set(0, 0);
                    
                }
                
                it -> update(mouseDirection);

                
                //if particle is within mouse radius, count it as disturbed
                ofVec2f distMouse = it -> pos - mousePos;
                
                if(distMouse.lengthSquared() < mouseRad * mouseRad){
                    if(it -> disturbed == false){
                        if(pWhoosh.getIsPlaying() == false){
                            pWhoosh.play();
                        }

                    }
                    
                    it -> disturbed = true;

                    //repulsion from mouse
                    it -> mouseRepel(mousePos, mouseRad, 1.1);
                
                }
                
                if(ballInfluence){
                    //if there are blobs and particle is within radius of blobs, count it as disturbed
                    if(contourFinder.blobs.size() > 0){
                        
                        for(int i = 0; i < contourFinder.blobs.size(); i++){
                        //for( vector<ofxCvBlob>:: iterator thisBlob = contourFinder.blobs.begin(); thisBlob != contourFinder.blobs.end(); thisBlob++){
                            
                            //new mapping with space considerations
                            float mapBlobX = ofMap(contourFinder.blobs[i].centroid.x, 0, camWidth, leftBound, rightBound);
                            float mapBlobY = ofMap(contourFinder.blobs[i].centroid.y, 0, camHeight, topBound, bottomBound);
                            
                            disturbRad = ofMap(contourFinder.blobs[i].area, 30, 500, disturbMin, disturbMax);

                            
                            //subtract position of centroid from position of particle
                            ofVec2f distBlob = (it -> pos) - ofVec2f(mapBlobX, mapBlobY);

                            //count as disturbed if within radius (circular boundary)
                            if(distBlob.lengthSquared() < disturbRad * disturbRad){
                                it -> disturbed = true;
                                
                                //give the direction of the current blob
                                it -> blobDir = blobDirection[i];
                                
                                //then repel away from current blob
                                it -> blobRepel(contourFinder.blobs[i].centroid, 1.0);
                                
                            }
                        
                        }
                        
                    }
                }
            
                //attraction to Attractor due to its own gravitation for particles within
                //the attraction radius
                it -> attract(attractorPos, attractorSize + attractionRad, attractStrength);
                
                //add another gravitational force once particles are disturbed
                if(it -> disturbed){
                    it -> globalAttract(attractorPos, attractStrength);
                    numDisturbed++;
                }
                
                
                //clear out the last positions and add the particle's position to the points vector
                ofVec3f partPos;
                partPos = it -> pos;
                pPoints.push_back(partPos);
                
                float s = it -> size;
                pSizes.push_back(ofVec3f(s));
                
                ofColor c = it-> col;
                float r = ofNormalize(c.r, 0, 500);
                float g = ofNormalize(c.g, 0, 500);
                float b = ofNormalize(c.b, 0, 500);
                float a = ofNormalize(c.a, 0, 255);
                ofFloatColor cF = ofFloatColor(r, g, b, pTrans);
                pColors.push_back(cF);
                
                
            } else {
                //count number of dead particles
                numDead++;
                
                if(pList.size() - numDead < 300){
                    transitionToNext = true;


                }
                
                
            } //if(particles are alive) statement 

        } //particle for-loop
        
        
        
        
        
        
        

        
        
        
        
        
        if(transitionToNext == false){
            
            
            //change attractor size depending on how many particles have been swallowed
            attractorSize = ofLerp(attractorBase, attractorMax, (float)numDead/(float)pList.size());
            attractorLerp = (float)numDead/(float)pList.size();
            
            //update the timer so its current when the transition actually starts
            transitionToNextTimer = ofGetElapsedTimeMillis();
            
            pistonSpeed = 120;

            
            
        }

        
        
        //if we've gathered all the particles, trigger transition

        //--------------------zoom animation--------------------
        
        if(transitionToNext){
           
            //set piston speed to move up quickly
            pistonSpeed = 255;
            
            //play narration clip:
            //"Great job! You've cleared out the neighborhood of all the gas and dust.
            //Lets zoom out to see if we can find more to collect"
            
            //if we're not already playing it
            if(stage1_05_youvecreated.getIsPlaying() == false && ofGetElapsedTimeMillis() - transitionToNextTimer < 1000){
                stage1_05_youvecreated.play();
            }
            
            //if we're animating...
            if(ofGetElapsedTimeMillis() - transitionToNextTimer > 5500){
                zooming = true;
                
                if(zoom.getIsPlaying() == false){
                    zoom.play();
                }
                
                float fadeSpeed = 0.03;
                
                //change size of attractor
                attractorSize = ofLerp(attractorSize, 20, fadeSpeed);
                attractorLerp = ofLerp(attractorLerp, 0.0f, fadeSpeed);
                
                //fade away the status
                if(statusCol.a > 0){
                    statusCol.a -= 5;
                }
                
                //shrink zoom square and fade out color
                zoomSquareWidth = ofLerp(zoomSquareWidth, 50, fadeSpeed);
                zoomSquareThick = ofLerp(zoomSquareThick, 1, fadeSpeed);
                
                
                if(zoomSquareWidth < 55){
                    zoomSquareCol.a = ofLerp(zoomSquareCol.a, 0, fadeSpeed);
                }
                
                //make all particles disturbed
                for( vector<Particle>::iterator it = pList.begin(); it!=pList.end(); it++){
                    it -> disturbed = true;
                }
                
                //if we're ready to move on to the next stage (i.e. narration is done),
                //change narrativeState to 2

            }
            
            
            //if we're ready reset key variables and increment narrativeState
            if(ofGetElapsedTimeMillis() - transitionToNextTimer > 9000){
                
                narrativeState = 2;
            }

            
            
            
            
            
            
            
        }
        
        
        
        
        
        
        
        //upload all the info to the vbo
        int total = (int)pPoints.size();
        particleVBO.setVertexData(&pPoints[0], total, GL_STATIC_DRAW);
        particleVBO.setNormalData(&pSizes[0], total, GL_STATIC_DRAW);
        particleVBO.setColorData(&pColors[0], total, GL_STATIC_DRAW);

        //send arduino states
        pistonPos = (int)ofClamp(ofMap(attractorSize, attractorBase, attractorMax, 0, 255), 0, 255);

        sendSerial(pistonPos, pistonSpeed, 0);
        
        
        
        
    } else if(narrativeState == 2){
        
        
        //--------------------PROTOSTAR UPDATE--------------------
        
        
        //stage setup
        if(setupStage2 == false){
            pList.clear();
            fieldRes = 7;
            newParticleField(fieldRes);
            
            clumpPos.set(ofGetWindowWidth()/2 - ofGetWindowHeight()/2 + 200, 800);
            createClump(clumpPos.x, clumpPos.y, 100, 2000); //args: x, y, rad, num
            locateClump = true;
            
            stageStartTime = ofGetElapsedTimeMillis();
            sendSerial(0, 255, 0);
            cvObjectCol = ofColor(255, 0, 0, 255);
            ballInfluence = false;
            announced = false;
            
            createMainFragment();
            
            statusCol.a = 255;
            statusA = "Status: Protostar";
            statusB = "";
            
            
            setupStage2 = true;
            
            pTrans = 0;
            
        }
        
        if(pTrans < 0.2){
            pTrans += 0.003;
        }
        
        //reset particle counters
        numDead = 0;
        numDisturbed = 0;
        
        //clear out points vector so the only particles in there are ones that are alive
        pPoints.clear();
        pSizes.clear();
        pColors.clear();
        
        
        //Update particles
        for( vector<Particle>::iterator it = pList.begin(); it!=pList.end(); it++){
            
            //only update non-dead particles
            if(it -> dead == false){
                
                
                //upon first entering stage, fade particles in
                it -> trans = ofLerp(it -> trans, 255, 0.02);
                
                
                //check if inside attractor
                ofVec3f distAttractor = attractorPos - it -> pos;
                if(distAttractor.lengthSquared() < attractorSize * attractorSize){
                    
                    //if so, make dead
                    it -> dead = true;
                    it -> vel.set(0, 0);
                    
                }
                
                it -> update(mouseDirection);
                
                
                

                
                ofVec3f distClump = it -> pos - clumpPos;
                if(distClump.lengthSquared() < 75 * 75){
//                    locateClump = false;
                }
                
                
                //if particle is within mouse radius, count it as disturbed
                ofVec2f distMouse = it -> pos - mousePos;
                
                if(distMouse.lengthSquared() < mouseRad * mouseRad){
                    if(it -> disturbed == false){
                        if(pWhoosh.getIsPlaying() == false){
                            pWhoosh.play();
                        }
                        
                    }
                    
                    it -> disturbed = true;
                    
                    //repulsion from mouse
                    it -> mouseRepel(mousePos, mouseRad, 1.1);
                    
                }
                
                if(ballInfluence){
                    //if there are blobs and particle is within radius of blobs, count it as disturbed
                    if(contourFinder.blobs.size() > 0){
                        
                        for(int i = 0; i < contourFinder.blobs.size(); i++){
                            //for( vector<ofxCvBlob>:: iterator thisBlob = contourFinder.blobs.begin(); thisBlob != contourFinder.blobs.end(); thisBlob++){
                            
                            //new mapping with space considerations
                            float mapBlobX = ofMap(contourFinder.blobs[i].centroid.x, 0, camWidth, leftBound, rightBound);
                            float mapBlobY = ofMap(contourFinder.blobs[i].centroid.y, 0, camHeight, topBound, bottomBound);
                            
                            disturbRad = ofMap(contourFinder.blobs[i].area, 30, 500, disturbMin, disturbMax);
                            
                            
                            //subtract position of centroid from position of particle
                            ofVec2f distBlob = (it -> pos) - ofVec2f(mapBlobX, mapBlobY);
                            
                            //count as disturbed if within radius (circular boundary)
                            if(distBlob.lengthSquared() < disturbRad * disturbRad){
                                it -> disturbed = true;
                                
                                //give the direction of the current blob
                                it -> blobDir = blobDirection[i];
                                
                                //then repel away from current blob
                                it -> blobRepel(contourFinder.blobs[i].centroid, 1.0);
                                
                            }
                            
                        }
                        
                    }
                }
                
                //attraction to Attractor due to its own gravitation for particles within
                //the attraction radius
                it -> attract(attractorPos, attractorSize + attractionRad, attractStrength);
                
                //add another gravitational force once particles are disturbed
                if(it -> disturbed){
                    it -> globalAttract(attractorPos, attractStrength);
                    numDisturbed++;
                }
                
                
                //clear out the last positions and add the particle's position to the points vector
                ofVec3f partPos;
                partPos = it -> pos;
                pPoints.push_back(partPos);
                
                float s = it -> size;
                pSizes.push_back(ofVec3f(s));
                
                ofColor c = it-> col;
                //normalize on a 0-400 scales instead of 255 to desaturate
                float r = ofNormalize(c.r, 0, 400);
                float g = ofNormalize(c.g, 0, 400);
                float b = ofNormalize(c.b, 0, 400);
                float a =ofNormalize(c.a, 0, 255);
                ofFloatColor cF = ofFloatColor(r, g, b, pTrans);
                pColors.push_back(cF);
                
                
            } else {
                //count number of dead particles
                numDead++;
                
                if(pList.size() - numDead < 300){
                    transitionToNext = true;
                    
                    
                }
                
                
            } //if(particles are alive) statement
            
        } //particle update for-loop
        

        
        
        if(ofDistSquared(mouseX, mouseY, clumpPos.x, clumpPos.y) < 75 * 75){
            locateClump = false;
        }
        
        
        
        
        
        
        if(transitionToNext == false){
            
            
            //change attractor size depending on how many particles have been swallowed
            attractorSize = ofLerp(attractorBase, attractorMax, (float)numDead/(float)pList.size());
            attractorLerp = (float)numDead/(float)pList.size();
            
            //update the timer so its current when the transition actually starts
            transitionToNextTimer = ofGetElapsedTimeMillis();
            
            pistonSpeed = 120;
            
            
            
        }
        
        
        
        //if we've gathered all the particles, trigger transition
        
        //--------------------zoom animation--------------------
        
        if(transitionToNext){
            
            //set piston speed to move up quickly
            pistonSpeed = 255;
            
            //play narration clip:
            //"Great job! You've cleared out the neighborhood of all the gas and dust.
            //Lets zoom out to see if we can find more to collect"
            
            //if we're not already playing it
            if(stage1_05_youvecreated.getIsPlaying() == false && ofGetElapsedTimeMillis() - transitionToNextTimer < 1000){
                stage1_05_youvecreated.play();
            }
            
            //if we're animating...
            if(ofGetElapsedTimeMillis() - transitionToNextTimer > 5500){
                zooming = true;
                
                if(zoom.getIsPlaying() == false){
                    zoom.play();
                }
                
                float fadeSpeed = 0.03;
                
                //change size of attractor
                attractorSize = ofLerp(attractorSize, 20, fadeSpeed);
                attractorLerp = ofLerp(attractorLerp, 0.0f, fadeSpeed);
                
                //fade away the status
                if(statusCol.a > 0){
                    statusCol.a -= 5;
                }
                
                //shrink zoom square and fade out color
                zoomSquareWidth = ofLerp(zoomSquareWidth, 50, fadeSpeed);
                zoomSquareThick = ofLerp(zoomSquareThick, 1, fadeSpeed);
                
                
                if(zoomSquareWidth < 55){
                    zoomSquareCol.a = ofLerp(zoomSquareCol.a, 0, fadeSpeed);
                }
                
                //make all particles disturbed
                for( vector<Particle>::iterator it = pList.begin(); it!=pList.end(); it++){
                    it -> disturbed = true;
                }
                
                //if we're ready to move on to the next stage (i.e. narration is done),
                //change narrativeState to 2
                
            }
            
            
            //if we're ready reset key variables and increment narrativeState
            if(ofGetElapsedTimeMillis() - transitionToNextTimer > 9000){
                
                narrativeState = 3;
                
            }
            
            
            
            
            
            
            
            
        } 
        

        
        
        //upload all the info to the vbo
        int total = (int)pPoints.size();
        particleVBO.setVertexData(&pPoints[0], total, GL_STATIC_DRAW);
        particleVBO.setNormalData(&pSizes[0], total, GL_STATIC_DRAW);
        particleVBO.setColorData(&pColors[0], total, GL_STATIC_DRAW);
        
        //send arduino states
        pistonPos = (int)ofClamp(ofMap(attractorSize, attractorBase, attractorMax, 0, 255), 0, 255);
        
        sendSerial(pistonPos, pistonSpeed, 0);
            
            
            
            
        
    
        

        
        
        
        
    } else if(narrativeState == 3){
        
        //--------------------PROTOSTAR TO STAR UPDATE--------------------
        
        //stage setup
        if(setupStage3 == false){
            pList.clear();
            fieldRes = 7;
            newParticleField(fieldRes);
            
            stageStartTime = ofGetElapsedTimeMillis();
            sendSerial(0, 255, 0);
            cvObjectCol = ofColor(255, 0, 0, 255);
            ballInfluence = false;
            announced = false;
            
            createMainFragment();
            
            statusCol.a = 255;
            statusA = "Status: Late";
            statusB = "Protostar";
            
            
            setupStage3 = true;
            
            pTrans = 0;
            
        }
        
        if(pTrans < 0.2){
            pTrans += 0.003;
        }
        
        //reset particle counters
        numDead = 0;
        numDisturbed = 0;
        
        //clear out points vector so the only particles in there are ones that are alive
        pPoints.clear();
        pSizes.clear();
        pColors.clear();
        
        
        //Update particles
        for( vector<Particle>::iterator it = pList.begin(); it!=pList.end(); it++){
            
            //only update non-dead particles
            if(it -> dead == false){
                
                
                //upon first entering stage, fade particles in
                it -> trans = ofLerp(it -> trans, 255, 0.02);
                
                
                //check if inside attractor
                ofVec3f distAttractor = attractorPos - it -> pos;
                if(distAttractor.lengthSquared() < attractorSize * attractorSize){
                    
                    //if so, make dead
                    it -> dead = true;
                    it -> vel.set(0, 0);
                    
                }
                
                it -> update(mouseDirection);
                
                
                //if particle is within mouse radius, count it as disturbed
                ofVec2f distMouse = it -> pos - mousePos;
                
                if(distMouse.lengthSquared() < mouseRad * mouseRad){
                    if(it -> disturbed == false){
                        if(pWhoosh.getIsPlaying() == false){
                            pWhoosh.play();
                        }
                        
                    }
                    
                    it -> disturbed = true;
                    
                    //repulsion from mouse
                    it -> mouseRepel(mousePos, mouseRad, 1.1);
                    
                }
                
                if(ballInfluence){
                    //if there are blobs and particle is within radius of blobs, count it as disturbed
                    if(contourFinder.blobs.size() > 0){
                        
                        for(int i = 0; i < contourFinder.blobs.size(); i++){
                            //for( vector<ofxCvBlob>:: iterator thisBlob = contourFinder.blobs.begin(); thisBlob != contourFinder.blobs.end(); thisBlob++){
                            
                            //new mapping with space considerations
                            float mapBlobX = ofMap(contourFinder.blobs[i].centroid.x, 0, camWidth, leftBound, rightBound);
                            float mapBlobY = ofMap(contourFinder.blobs[i].centroid.y, 0, camHeight, topBound, bottomBound);
                            
                            disturbRad = ofMap(contourFinder.blobs[i].area, 30, 500, disturbMin, disturbMax);
                            
                            
                            //subtract position of centroid from position of particle
                            ofVec2f distBlob = (it -> pos) - ofVec2f(mapBlobX, mapBlobY);
                            
                            //count as disturbed if within radius (circular boundary)
                            if(distBlob.lengthSquared() < disturbRad * disturbRad){
                                it -> disturbed = true;
                                
                                //give the direction of the current blob
                                it -> blobDir = blobDirection[i];
                                
                                //then repel away from current blob
                                it -> blobRepel(contourFinder.blobs[i].centroid, 1.0);
                                
                            }
                            
                        }
                        
                    }
                }
                
                //attraction to Attractor due to its own gravitation for particles within
                //the attraction radius
                it -> attract(attractorPos, attractorSize + attractionRad, attractStrength);
                
                //add another gravitational force once particles are disturbed
                if(it -> disturbed){
                    it -> globalAttract(attractorPos, attractStrength);
                    numDisturbed++;
                }
                
                
                //clear out the last positions and add the particle's position to the points vector
                ofVec3f partPos;
                partPos = it -> pos;
                pPoints.push_back(partPos);
                
                float s = it -> size;
                pSizes.push_back(ofVec3f(s));
                
                ofColor c = it-> col;
                //normalize on a 0-400 scales instead of 255 to desaturate
                float r = ofNormalize(c.r, 0, 400);
                float g = ofNormalize(c.g, 0, 400);
                float b = ofNormalize(c.b, 0, 400);
                float a =ofNormalize(c.a, 0, 255);
                ofFloatColor cF = ofFloatColor(r, g, b, pTrans);
                pColors.push_back(cF);
                
                
            } else {
                //count number of dead particles
                numDead++;
                
                if(pList.size() - numDead < 300){
                    transitionToNext = true;
                    
                    
                }
                
                
            } //if(particles are alive) statement
            
        } //particle update for-loop
        
        
        
        
        
        
        
        
        
        if(transitionToNext == false){
            
            
            //change attractor size depending on how many particles have been swallowed
            attractorSize = ofLerp(attractorBase, attractorMax, (float)numDead/(float)pList.size());
            attractorLerp = (float)numDead/(float)pList.size();
            
            //update the timer so its current when the transition actually starts
            transitionToNextTimer = ofGetElapsedTimeMillis();
            
            pistonSpeed = 120;
            
            
            
        }
        
        
        
        //if we've gathered all the particles, trigger transition
        
        //--------------------zoom animation--------------------
        
        if(transitionToNext){
            
            //set piston speed to move up quickly
            pistonSpeed = 255;
            
            //play narration clip:
            //"Great job! You've cleared out the neighborhood of all the gas and dust.
            //Lets zoom out to see if we can find more to collect"
            
            //if we're not already playing it
            if(stage1_05_youvecreated.getIsPlaying() == false && ofGetElapsedTimeMillis() - transitionToNextTimer < 1000){
                stage1_05_youvecreated.play();
            }
            
            //if we're animating...
            if(ofGetElapsedTimeMillis() - transitionToNextTimer > 5500){
                zooming = true;
                
                if(zoom.getIsPlaying() == false){
                    zoom.play();
                }
                
                float fadeSpeed = 0.03;
                
                //change size of attractor
                attractorSize = ofLerp(attractorSize, 20, fadeSpeed);
                attractorLerp = ofLerp(attractorLerp, 0.0f, fadeSpeed);
                
                //fade away the status
                if(statusCol.a > 0){
                    statusCol.a -= 5;
                }
                
                //shrink zoom square and fade out color
                zoomSquareWidth = ofLerp(zoomSquareWidth, 50, fadeSpeed);
                zoomSquareThick = ofLerp(zoomSquareThick, 1, fadeSpeed);
                
                
                if(zoomSquareWidth < 55){
                    zoomSquareCol.a = ofLerp(zoomSquareCol.a, 0, fadeSpeed);
                }
                
                //make all particles disturbed
                for( vector<Particle>::iterator it = pList.begin(); it!=pList.end(); it++){
                    it -> disturbed = true;
                }
                
                //if we're ready to move on to the next stage (i.e. narration is done),
                //change narrativeState to 2
                
            }
            
            
            //if we're ready reset key variables and increment narrativeState
            if(ofGetElapsedTimeMillis() - transitionToNextTimer > 9000){
                
                narrativeState = 4;
                
            }
            
            
            
            
            
            
            
            
        }
        
        
        
        
        //upload all the info to the vbo
        int total = (int)pPoints.size();
        particleVBO.setVertexData(&pPoints[0], total, GL_STATIC_DRAW);
        particleVBO.setNormalData(&pSizes[0], total, GL_STATIC_DRAW);
        particleVBO.setColorData(&pColors[0], total, GL_STATIC_DRAW);
        
        //send arduino states
        pistonPos = (int)ofClamp(ofMap(attractorSize, attractorBase, attractorMax, 0, 255), 0, 255);
        
        sendSerial(pistonPos, pistonSpeed, 0);
        
        
        
        
        
        
        
        
        
        
        
        
    } else if(narrativeState == 4) {
        
        //--------------------STAR UPDATE--------------------
        
        
        //stage setup
        if(setupStage4 == false){

            
            stageStartTime = ofGetElapsedTimeMillis();
//            sendSerial(0, 255, 0);
            cvObjectCol = ofColor(255, 0, 0, 255);
            ballInfluence = false;
            announced = false;

            
            createSunSmoke();
            
            for( vector<SunParticle>::iterator it = sunPList.begin(); it!=sunPList.end(); it++){
                it -> explode = true;
            }

            setupStage4 = true;

            statusA = "Status: Main";
            statusB = "Sequence Star";
            
            
            
        
        }
        
        if(ofGetElapsedTimeMillis() - stageStartTime > 3000){
            for( vector<SunParticle>::iterator it = sunPList.begin(); it!=sunPList.end(); it++){
                it -> explode = false;
            }
            

        }
        
        
        
        
        
    } else if(narrativeState == 5){
        
        
        
        
        
        
    }
    
    
    
    
    
    
    
    //----------------------------------------------------------------------------------//
    //                                                                                  //
    //                                                                                  //
    //                             RESET INDIVIDUAL STAGES                              //
    //                                                                                  //
    //                                                                                  //
    //                                                                                  //
    //----------------------------------------------------------------------------------//
    
    
    if(narrativeState != -1){
        
    }
    
    if(narrativeState != 0){
        
    }
    
    if(narrativeState != 1){
        
        setupStage1 = false;
        transitionToNext = false;
        
        
        
        
    }
    
    if(narrativeState != 2){
        
        
        setupStage2 = false;
        transitionToNext = false;
        
    }
    
    if(narrativeState != 3){

        setupStage3 = false;
        transitionToNext = false;
    }
    
    
    if(narrativeState != 4){
        setupStage4 = false;
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
}



//-------------------------------------------------------------------------------------//
//                    ________   ________   ________  ___       ___                    //
//                    |\   ___ \ |\   __  \|\   __  \|\  \     |\  \                   //
//                     \ \  \_|\ \ \  \|\  \ \  \|\  \ \  \    \ \  \                  //
//                      \ \  \ \\ \ \   _  _\ \   __  \ \  \  __\ \  \                 //
//                       \ \  \_\\ \ \  \\  \\ \  \ \  \ \  \|\__\_\  \                //
//                        \ \_______\ \__\\ _\\ \__\ \__\ \____________\               //
//                         \|_______|\|__|\|__|\|__|\|__|\|____________|               //
//                                                                                     //
//-------------------------------------------------------------------------------------//




void testApp::draw(){
    
    if(narrativeState == -1){
    

        


        
        //Draw background
        ofPushStyle();
        ofPushMatrix();
        ofTranslate(ofGetWindowWidth()/2, ofGetWindowHeight()/2);

        float rotateSpeed = ofGetElapsedTimef() * -3;
        
        ofRotate(rotateSpeed);
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofSetColor(255, 255);
        background.draw(0, 0);
        
        ofSetRectMode(OF_RECTMODE_CORNER);
        
        ofPopStyle();
        ofPopMatrix();
        
        
        

        
        
        drawBlackBars();
        drawGrid(15, 0.2);
        
        //draw timer stuff
        ofPushStyle();
        
        ofNoFill();
        ofSetCircleResolution(30);
        ofSetLineWidth(8);
        
//        ofCircle(ofGetWindowWidth()/2 + ofGetWindowHeight()/2 - 150, 150, 100);
        
        ofPushMatrix();
        ofTranslate(ofGetWindowWidth()/2 + ofGetWindowHeight()/2 - 150, 150);
        ofRotate(90);
        idleTimerPath.draw();
        
        if(inButton){
            ofSetColor(idleTimerCol, 255);
        } else {
            ofSetColor(255, 255);
        }
        
        ofCircle(0,0, 100);
        ofRotate(6);
        ofCircle(0,0, 100);
        ofPopMatrix();
        
        ofPopStyle();

        
        

        ofVec2f handStart = ofPoint(ofGetWindowWidth()/2, ofGetWindowHeight()/2);
        ofVec2f handEnd = ofPoint(ofGetWindowWidth()/2 + ofGetWindowHeight()/2 - 150, 150);
        
        idleHandPos = idleHandPos.interpolate(handEnd, 0.025);

        if(idleHandPos.distance(handEnd) < 5){
            idleHandPos = handStart;

        }
        
        
        //draw moving hand
        ofSetColor(255);
        ofPushMatrix();
        ofTranslate(idleHandPos);

        handWithBall.draw(0,0);
        
        ofPopMatrix();
        
        //draw text
        string idleMessage = "Hold ball here to begin";

        ofPushMatrix();
        ofTranslate(ofGetWindowWidth()/2 + 250, 120);
        ofScale(0.3, 0.3);
        ofRotate(180);
        
        instructions.drawString(idleMessage, 0, 0);
        
        ofPopMatrix();
        
        //draw CV objects
        for(int i = 0; i < contourFinder.blobs.size(); i++){
            float mapBlobX = ofMap(contourFinder.blobs[i].centroid.x, 0, camWidth, leftBound, rightBound);
            float mapBlobY = ofMap(contourFinder.blobs[i].centroid.y, 0, camHeight, topBound, bottomBound);
            
            disturbRad = ofMap(contourFinder.blobs[i].area, 30, 500, disturbMin, disturbMax);
            
            ofPushStyle();
            ofSetColor(cvObjectCol);
            ofSetCircleResolution(60);
            ofCircle(mapBlobX, mapBlobY, 10);
            
            ofNoFill();
            ofSetLineWidth(5);
            ofEllipse(mapBlobX, mapBlobY, 50, 50);
            
            ofPopStyle();

        }
        
        
        
        if(transitionToIntro){
            ofSetColor(0, blackOutTrans);
            ofSetRectMode(OF_RECTMODE_CENTER);
            ofRect(ofGetWindowSize()/2, ofGetWindowHeight(), ofGetWindowHeight());
            ofSetRectMode(OF_RECTMODE_CORNER);
        }
        
        
        
    } else if(narrativeState == 0){
        
        if(startedIntro == false){
            stageStartTime = ofGetElapsedTimeMillis();
            sendSerial(0, 150, 0);
            cvObjectCol = ofColor(255, 0);
            startedIntro = true;
        }
            
        int currentTime = ofGetElapsedTimeMillis() - stageStartTime;

        

        ofSetColor(255, milkyWayTrans);
        milkyWay.draw(ofGetWindowSize()/2);
        
        //fade in milky way
        if(currentTime < 1500 && milkyWayTrans < 255){
            milkyWayTrans += 2;
        }
        
        
        
        
        //play first narration clip
        if(currentTime > 1000 && currentTime < 1500 && !Intro01_peoplethink.getIsPlaying()){
            playIntro01 = true;
        }
        
        if(playIntro01){
            Intro01_peoplethink.play();
            playIntro01 = false;
        }
        
        //play second narration clip
        if(currentTime > 9500 && currentTime < 10000 && !Intro02_welivein.getIsPlaying()){
            playIntro02 = true;
        }
        
        if(playIntro02){
            Intro02_welivein.play();
            playIntro02 = false;
        }
        
        
        //fade the shuttle in
        if(shuttleTrans < 255 && currentTime > 7000 && currentTime < 9000){
            shuttleTrans += 4;
        }
        

        //if we're in the middle, fade overlay in
        if(shuttleDimTrans < 255 && currentTime > 11000 && currentTime < 13000){
            shuttleDimTrans += 5;
        }
        
        //if we're at the end of the middle, fade overlay out
        if(shuttleDimTrans > 0 && currentTime > 16200 && currentTime < 19000){
            shuttleDimTrans -= 4;
        }


        //play third narration clip
        if(currentTime > 17000 && currentTime < 17500 && !Intro03_whiletime.getIsPlaying()){
            playIntro03 = true;
        }
        
        if(playIntro03){
            Intro03_whiletime.play();
            playIntro03 = false;
        }
        
        //move in time arrow and move out shuttle
        if(currentTime > 17000 && currentTime < 24000){
            
            if(arrowStartX > ofGetWindowWidth()/2 - ofGetWindowHeight()/2 + 300 && currentTime < 21000){
                arrowStartX -= 4;
            }
            
            if(currentTime > 21000){
                arrowStartX -= 8;
                shuttlePos.x -= 6;
                shuttlePos.y += 3;
                
            }
            
            
        }
        
        
        
        
        //draw space shuttle and images 
        float shuttleSize = 0.75;
        ofSetColor(255, shuttleTrans);
        shuttle.draw(shuttlePos, shuttle.width * shuttleSize, shuttle.height * shuttleSize);
        
        ofSetColor(255, shuttleDimTrans);
        shuttleDimensions.draw(shuttlePos, shuttleDimensions.width * shuttleSize, shuttleDimensions.height * shuttleSize);
        
        ofPushMatrix();
        ofTranslate(arrowStartX, 200);
        ofSetColor(255, 255);
        timeArrow.draw(0,0);
        ofPopMatrix();
        
        
        //play fourth narration clip
        if(currentTime > 24000 && currentTime < 24500 && !Intro04_thisisspacetime.getIsPlaying()){
            playIntro04 = true;
        }
        
        if(playIntro04){
            Intro04_thisisspacetime.play();
            playIntro04 = false;
        }
        
        
        

        //create 3D grid
        if(currentTime > 24000 && currentTime < 24500 && gridTrans < 255){
            gridTrans += 2;
        }
        
        if(currentTime > 34000 && gridTrans > 0){
            gridTrans -= 2;
        }
        
        gridCam.begin();
        
        int gridUnit = 200;
        int gridLength = 1200;
        
        
        for(int z = 0; z < gridLength; z += gridUnit){
            for(int y = 0; y < gridLength; y += gridUnit){
                for(int x = 0; x < gridLength; x += gridUnit){
                    float u = gridUnit/2;
                    
                    ofPushMatrix();
                    
                    if(currentTime > 25000){
                        ofRotate(gridRot, 1, 0.5, 0);
                        gridRot += 0.001;
                    }
                    ofTranslate(-gridLength/2, -gridLength/2, -gridLength/2);
                    ofSetLineWidth(2);
                    ofSetColor(255, gridTrans);
                    //XY - z
                    ofLine(x - u, y - u, z - u, x - u, y + u, z - u);
                    ofLine(x - u, y + u, z - u, x + u, y + u, z - u);
                    ofLine(x + u, y + u, z - u, x + u, y - u, z - u);
                    ofLine(x + u, y - u, z - u, x - u, y - u, z - u);
                    //XY + z
                    ofLine(x - u, y - u, z + u, x - u, y + u, z + u);
                    ofLine(x - u, y + u, z + u, x + u, y + u, z + u);
                    ofLine(x + u, y + u, z + u, x + u, y - u, z + u);
                    ofLine(x + u, y - u, z + u, x - u, y - u, z + u);
                    //Z lines
                    ofLine(x - u, y - u, z + u, x - u, y - u, z - u);
                    ofLine(x - u, y + u, z + u, x - u, y + u, z - u);
                    ofLine(x + u, y + u, z + u, x + u, y + u, z - u);
                    ofLine(x + u, y - u, z + u, x + u, y - u, z - u);
                    ofPopMatrix();
                }
            }
        }
        
        gridCam.end();
        
        if(currentTime > 34000 && flatGridTrans < 150){
            //drawGrid(15, flatGridTrans);
            
            flatGridTrans += 1;
        }
        
        //play fifth narration clip
        if(currentTime > 36000 && currentTime < 36500 && !Intro05_thingsthatmove.getIsPlaying()){
            playIntro05 = true;
            cvObjectCol = ofColor(0,255,0);
        }
        
        if(playIntro05){
            Intro05_thingsthatmove.play();
            playIntro05 = false;
        }
        
        //and immediately play the next clip
        if(currentTime > 41000 && currentTime < 41500 && !Intro05_thingsthatmove.getIsPlaying() && !Intro06_rollsomeballs.getIsPlaying()){
            playIntro06 = true;
        }
        
        if(playIntro06){
            Intro06_rollsomeballs.play();
            playIntro06 = false;

        }

        //if it has been a few seconds, present timer option to move on
        if(currentTime > 45000 && currentTime < 45500){
            useRollTimer = true;
        }
        
        
        //draw flat grid
        drawGrid(15, flatGridTrans/255);

        //draw roll timer
        if(useRollTimer){
            //draw timer stuff
            ofPushStyle();
            
            ofNoFill();
            ofSetCircleResolution(30);
            ofSetLineWidth(8);
            
            ofPushMatrix();
            ofTranslate(rollTimerPos);
            ofRotate(90);
            rollTimerPath.draw();
            
            if(inButton){
                ofSetColor(rollTimerCol, rollTimerTrans);
            } else {
                ofSetColor(255, rollTimerTrans);
            }
            
            ofCircle(0,0, rollTimerRad);
            ofRotate(6);
            ofCircle(0,0, rollTimerRad);
            ofPopMatrix();
            
            ofPopStyle();
            
            //draw text
            string rollMessage = "Hold ball here for next stage";
            
            ofPushMatrix();
            ofTranslate(ofGetWindowWidth()/2 + 325, rollTimerPos.y - 10);
            ofScale(0.3, 0.3);
            ofRotate(180);
            ofSetColor(255, rollTimerTrans);
            instructions.drawString(rollMessage, 0, 0);
            
            ofPopMatrix();

            
            
        }

        //second stage of intro after flat ball roll
        if(introStage == 1){
            
            stage2Time = ofGetElapsedTimeMillis() - intro2Timer;
            
            if(stage2Time > 1000 && stage2Time < 1500 && !Intro07_nowrollballs.getIsPlaying()){
                playIntro07 = true;
            }
            
            if(playIntro07){
                Intro07_nowrollballs.play();
                playIntro07 = false;
                
            }
            
            if(stage2Time > 3000 && stage2Time < 7000){
                if(bowlingballTrans < 255){
                    bowlingballTrans += 2;
                } else if(bowlingballTrans > 200){
                    sendSerial(255, 255, 0);
                }

            }
            
            if(stage2Time > 8000){
                useRollTimer = true;
            }
            

            

        } else if(introStage == 2){
            
            stage2Time = ofGetElapsedTimeMillis() - intro2Timer;
            
            //play clip 8
            if(stage2Time > 1000 && stage2Time < 1500 && !Intro08_easytosee.getIsPlaying()){
                playIntro08 = true;
                
            }
            
            if(playIntro08){
                Intro08_easytosee.play();
                playIntro08 = false;
                
            }
            
            if(stage2Time > 4000 && stage2Time < 6500){
                
                if(warpedIsGravityTrans < 255){
                    warpedIsGravityTrans += 2;
                }
                
                //set initial position for sign
                warpedGravPos.set(0, ofGetWindowHeight()/2 - 200);
            }

            if(stage2Time > 10000 && stage2Time < 14000){
                if(earthSwitchScale < 2.0){
                    earthSwitchScale += 0.01;
                }
            }
            
            
            if(stage2Time > 13000 && stage2Time < 17000){
                
                //make it spiral into the center
                warpedRot += 2;
                if(warpedSize < 1.0){
                    warpedSize += 0.005;
                }
                
                warpedGravPos.set(warpedGravPos.x, warpedGravPos.y - 1);
                

                
            }
            
            
            //play clip 9
            if(stage2Time > 6000 && stage2Time < 6500 && !Intro09_thiscurvingof.getIsPlaying()){
                playIntro09 = true;
            }
            
            if(playIntro09){
                Intro09_thiscurvingof.play();
                playIntro09 = false;
                
            }
            
            
            
            
            //draw sign
            ofSetColor(255, warpedIsGravityTrans);

            ofPushMatrix();
            ofTranslate(ofGetWindowSize()/2);
            ofRotate(warpedRot);
            ofTranslate(warpedGravPos);
            
            ofScale(1.0f - warpedSize, 1.0f - warpedSize);
            
            
            warpedIsGravity.draw(0, 0);
            ofPopMatrix();
            
            
            //play clip 10
            if(stage2Time > 13000 && stage2Time < 13500 && !Intro10_wedontnotice.getIsPlaying()){
                playIntro10 = true;
            }
            
            if(playIntro10){
                Intro10_wedontnotice.play();
                playIntro10 = false;
                
            }
            
            
            //play clip 11
            if(stage2Time > 22000 && stage2Time < 22500 && !Intro11_iftheresenough.getIsPlaying()){
                playIntro11 = true;
            }
            
            if(playIntro11){
                Intro11_iftheresenough.play();
                playIntro11 = false;
                
            }
            
            if(stage2Time > 23000 && stage2Time < 25000){
                lightArcAngle += 1;
            }
            
            if(stage2Time > 25000){
                if(lightArcTrans > 1){
                    lightArcTrans -= 2;
                }
            }
            
            
            //play last clip
            if(stage2Time > 30000 && stage2Time < 30500 && !Intro12_letssee.getIsPlaying()){
                playIntro12 = true;
            }
            
            if(playIntro12){
                Intro12_letssee.play();
                playIntro12 = false;
                
            }
            
            
            if(stage2Time > 37000){
                narrativeState = 1;
            }
            
            
        }
        
        
        
        ofSetColor(255, bowlingballTrans);
        ofPushMatrix();
        ofTranslate(ofGetWindowSize()/2);

        ofScale(ofClamp(1.0f - earthSwitchScale, 0, 1), ofClamp(1.0f - earthSwitchScale, 0, 1));
        bowlingball.draw(0, 0, bowlingball.width * 0.4, bowlingball.height * 0.4);
        
        
        ofPopMatrix();
        
        //draw Earth over bowling ball
        ofSetColor(255);
        ofPushMatrix();
        ofTranslate(ofGetWindowSize()/2);
        ofScale(ofClamp(earthSwitchScale - 1.0f, 0, 1), ofClamp(earthSwitchScale - 1.0f, 0, 1));
        earth.draw(0, 0, earth.width * 0.4, earth.height * 0.4);
        
        
        ofPopMatrix();
        
        ofPushMatrix();
        
        lightArc.clear();
        lightArc.arc(ofPoint(0,0), 2400, 2400, lightArcAngle - 180, lightArcAngle, true);
        lightArc.setStrokeWidth(10);
        lightArc.setStrokeColor(ofColor(255, 255, 0, lightArcTrans));
        lightArc.setFilled(false);
        lightArc.setCircleResolution(180);

        ofTranslate(ofGetWindowWidth()/2 - ofGetWindowHeight()/2 - 1000, -1000);
        
        lightArc.draw(0,0);
        ofRotate(1);
        lightArc.draw(0,0);
        
        ofPopMatrix();
        
        ofPushMatrix();
        
        lightArc.clear();
        lightArc.arc(ofPoint(0,0), 2850, 2850, lightArcAngle - 90, lightArcAngle + 90, true);
        lightArc.setStrokeWidth(10);
        lightArc.setStrokeColor(ofColor(255, 255, 0, lightArcTrans));
        lightArc.setFilled(false);
        lightArc.setCircleResolution(180);
        
        ofTranslate(ofGetWindowWidth()/2 + 2500, ofGetWindowHeight()/2);
        
        lightArc.draw(0,0);
        ofRotate(1);
        lightArc.draw(0,0);
        
        ofPopMatrix();
        
        
        

        
        
        
        
        
        
        
        
        
        
        for(int i = 0; i < contourFinder.blobs.size(); i++){
            float mapBlobX = ofMap(contourFinder.blobs[i].centroid.x, 0, camWidth, leftBound, rightBound);
            float mapBlobY = ofMap(contourFinder.blobs[i].centroid.y, 0, camHeight, topBound, bottomBound);
            
            disturbRad = ofMap(contourFinder.blobs[i].area, 30, 500, disturbMin, disturbMax);
            
            ofPushStyle();
            ofSetColor(cvObjectCol);
            
            ofCircle(mapBlobX, mapBlobY, 10);
            
            ofNoFill();
            ofCircle(mapBlobX, mapBlobY, disturbRad);
            
            ofNoFill();
            ofSetLineWidth(5);
            ofEllipse(mapBlobX, mapBlobY, 50, 50);
            
            
            ofPopStyle();

        }

        ofPushStyle();
        ofSetColor(cvObjectCol);
        
        ofCircle(mouseX, mouseY, 10);
                
        ofNoFill();
        ofSetLineWidth(5);
        ofEllipse(mouseX, mouseY, 50, 50);
        
        
        ofPopStyle();
        
        
        
        drawBlackBars();
        ofSetColor(255);
        ofDrawBitmapString("currentTime: " + ofToString(currentTime), 1600, 30);
        
        ofDrawBitmapString("stage 2 time: " + ofToString(stage2Time), 1600, 50);
        ofDrawBitmapString("intro Stage: " + ofToString(introStage), 1600, 70);
        
        
        
    } else if(narrativeState == 1){
        
        //-------------------STAGE 1: CLOUD FRAGMENT--------------------------
    

        
        
        int currentTime = ofGetElapsedTimeMillis() - stageStartTime;

        
        //play audio clips
        if(currentTime > 2000 && currentTime < 2500 && !stage1_01_wearenow.getIsPlaying()){
            playStage1_01 = true;
    
        }

        
        if(playStage1_01){
            stage1_01_wearenow.play();
            playStage1_01 = false;
        }
        
        
        if(currentTime > 11500 && currentTime < 12000 && !stage1_02_useyourhands.getIsPlaying()){
            playStage1_02 = true;
        }
        
        if(playStage1_02){
            stage1_02_useyourhands.play();
            playStage1_02 = false;
            cvObjectCol = ofColor(0, 255, 0);
            ballInfluence = true;

        }
        
        
        if(numDead > 5000 && announced == false && !stage1_03_seehow.getIsPlaying()){
            playStage1_03 = true;
            announced = true;
            cout << "play narration" << endl;
        }
        
        if(playStage1_03){
            stage1_03_seehow.play();
            announcedTimer = ofGetElapsedTimeMillis();
            playStage1_03 = false;
        }
        
        
        //CHANGE THIS START TIME TO SOMETHING THAT WORKS SO IT DOESNT PLAY UNLESS THE PREVIOUS ONE HAS
        if(ofGetElapsedTimeMillis() - announcedTimer > 9000 && ofGetElapsedTimeMillis() - announcedTimer < 9500){
            playStage1_04 = true;
            test = true;
        }
        
        if(playStage1_04){
            stage1_04_keepgathering.play();
            playStage1_04 = false;
        }

//        if(test){
//            ofPushStyle();
//            
//            ofSetColor(255, 0, 0);
//            ofCircle(300, 300, 100);
//            
//            ofPopStyle();
//        }
        
        
        drawGrid(15, 0.2);
        
        
        
        
         
        //draw particles
//        for( vector<Particle>::iterator it = pList.begin(); it!=pList.end(); it++){
//            if(it -> dead == false){
//                it -> draw();
//            }
//        }
        
        
                
        
        //----------draw Cloud Fragment----------
        
        
        
        
        
  
        float scaleFactor = ofMap(attractorLerp, 0.0, 1.0, 0, 250);
        
        //clear vectors for VBO of old data
        //update the cloud fragment particles
        //push them to vectors
  
        
        fragPoints.clear();
        fragSizes.clear();
        fragColors.clear();
        
        int numFragsDrawn = int(ofMap(attractorLerp, 0.0, 1.0, 10, 2000));//mainFragment.size()));
        
        for( int i = 0; i < numFragsDrawn; i++){
            mainFragment[i].update(scaleFactor);
//            mainFragment[i].draw();
        
            
            //first color
            ofColor c;
            c = mainFragment[i].col;
            //normalize them to a much larger range so we desaturate them and the blob is less white
            float r = ofClamp(ofNormalize(c.r, 0, 600), 0.0f, 1.0f);
            float g = ofNormalize(c.g, 0, 600);
            float b = ofNormalize(c.b, 0, 600);
            float a =ofNormalize(c.a, 0, 255);
            ofFloatColor cF = ofFloatColor(r, g, b, pTrans);
            fragColors.push_back(cF);


            //now for the points and size vectors
            ofVec3f point;
            point.set(mainFragment[i].pos);
            fragPoints.push_back(point);
            
            
            float s = mainFragment[i].size;
            //float size = 40;
            fragSizes.push_back(ofVec3f(100));
        
        }
        
        //upload all the info to the vbo
        int total = (int)fragPoints.size();
        fragmentVBO.setVertexData(&fragPoints[0], total, GL_STATIC_DRAW);
        fragmentVBO.setNormalData(&fragSizes[0], total, GL_STATIC_DRAW);
        fragmentVBO.setColorData(&fragColors[0], total, GL_STATIC_DRAW);
        
        
        //shader stuff to place images where particles are
    	glDepthMask(GL_FALSE);
        
        //ofSetColor(255);
        
        // this makes everything look glowy :)
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        ofEnablePointSprites();
        
//        ofDisableBlendMode();
        
        
        // bind the shader and camera
        // everything inside this function
        // will be effected by the shader/camera
        shader.begin();
        
        // bind the texture so that when all the points
        // are drawn they are replace with our dot image
        pTex.bind();
        
        particleVBO.draw(GL_POINTS, 0, (int)pPoints.size());
        
        ofPushMatrix();
        ofTranslate(ofGetWindowSize()/2);
//        fragmentVBO.draw(GL_POINTS, 0, (int)fragPoints.size());
        ofPopMatrix();
        

        pTex.unbind();
        
        
        shader.end();
        
        ofDisablePointSprites();

        
        
        ofEnableAlphaBlending();
        
        ofEnableDepthTest();
        




        float progress = (float)numDead/(float)pList.size();
        drawProgress(progress);
       
        
        
        
        
        
        
        
        
        //draw UI
        drawUI();

        
        //draw blob positions
        for(int i = 0; i < contourFinder.blobs.size(); i++){
            
            float mapBlobX = ofMap(contourFinder.blobs[i].centroid.x, 0, camWidth, leftBound, rightBound);
            float mapBlobY = ofMap(contourFinder.blobs[i].centroid.y, 0, camHeight, topBound, bottomBound);
            
            disturbRad = ofMap(contourFinder.blobs[i].area, 30, 500, disturbMin, disturbMax);
            
            ofPushStyle();
            
            ofSetColor(cvObjectCol);
            ofCircle(mapBlobX, mapBlobY, 10);
            ofNoFill();
            ofCircle(mapBlobX, mapBlobY, disturbRad);
            
            ofPopStyle();
        }
        
        
    
    } else if(narrativeState == 2){

        
        
        //-------------------STAGE 2: PROTOSTAR--------------------------
        

        
        
        int currentTime = ofGetElapsedTimeMillis() - stageStartTime;
        
        
        //play first clip: "help the fragment gather more gas"
        if(currentTime > 2000 && currentTime < 2500 && !stage2_01_useyourhands.getIsPlaying()){
            playStage2_01 = true;
            
        }
        
        
        if(playStage2_01){
            stage2_01_useyourhands.play();
            playStage2_01 = false;
        }
        
        
        
        
        //trigger second clip and create a new fragment
        if(currentTime > 6000 && currentTime < 6500 && !stage2_02_sometimescloud.getIsPlaying()){
            playStage2_02 = true;
        }
        
        if(playStage2_02){
            stage2_02_sometimescloud.play();
            playStage2_02 = false;
            cvObjectCol = ofColor(0, 255, 0);
            ballInfluence = true;
            
        }
        
        
        if(numDead > 5000 && announced == false && !stage1_03_seehow.getIsPlaying()){
            playStage1_03 = true;
            announced = true;
            cout << "play narration" << endl;
        }
        
        if(playStage1_03){
            stage1_03_seehow.play();
            announcedTimer = ofGetElapsedTimeMillis();
            playStage1_03 = false;
        }
        
        if(ofGetElapsedTimeMillis() - announcedTimer > 9000 && ofGetElapsedTimeMillis() - announcedTimer < 9500){
            playStage1_04 = true;
            test = true;
        }
        
        if(playStage1_04){
            stage1_04_keepgathering.play();
            playStage1_04 = false;
        }
        
        drawGrid(15, 0.2);
        

        
        
        
        
        //draw particles
//        for( vector<Particle>::iterator it = pList.begin(); it!=pList.end(); it++){
//            if(it -> dead == false){
//                it -> draw();
//            }
//        }
        
        
        //----------draw Protostar----------
        
        
        float scaleFactor = ofMap(attractorLerp, 0.0, 1.0, 0, 250);

        
        //clear vectors for VBO of old data
        //update the cloud fragment particles
        //push them to vectors
        
        fragPoints.clear();
        fragSizes.clear();
        fragColors.clear();
        
        int numFragsDrawn = int(ofMap(attractorLerp, 0.0, 1.0, 10, 2000));//mainFragment.size()));
        
        for( int i = 0; i < numFragsDrawn; i++){
            mainFragment[i].update(scaleFactor);
            //            mainFragment[i].draw();
            
            
            //first color
            ofColor c;
            c = mainFragment[i].col;
            float r = ofClamp(ofNormalize(c.r, 0, 600) + attractorLerp, 0.0f, 1.0f);
            float g = ofNormalize(c.g, 0, 600);
            float b = ofNormalize(c.b, 0, 600);
            float a =ofNormalize(c.a, 0, 255);
            ofFloatColor cF = ofFloatColor(r, g, b, pTrans);
            fragColors.push_back(cF);
            
            
            //now for the points and size vectors
            ofVec3f point;
            point.set(mainFragment[i].pos);
            fragPoints.push_back(point);
            
            
            float s = mainFragment[i].size;
            //float size = 40;
            fragSizes.push_back(ofVec3f(100));
            
        }
        
        //upload all the info to the vbo
        int total = (int)fragPoints.size();
        fragmentVBO.setVertexData(&fragPoints[0], total, GL_STATIC_DRAW);
        fragmentVBO.setNormalData(&fragSizes[0], total, GL_STATIC_DRAW);
        fragmentVBO.setColorData(&fragColors[0], total, GL_STATIC_DRAW);

        
        
        
        //shader stuff to place images where particles are
    	glDepthMask(GL_FALSE);
        
        //ofSetColor(255);
        
        // this makes everything look glowy :)
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        ofEnablePointSprites();
        
        // bind the shader and camera
        // everything inside this function
        // will be effected by the shader/camera
        shader.begin();
        
        // bind the texture so that when all the points
        // are drawn they are replace with our dot image
        pTex.bind();
        particleVBO.draw(GL_POINTS, 0, (int)pPoints.size());
        
        ofPushMatrix();
        ofTranslate(ofGetWindowSize()/2);
        fragmentVBO.draw(GL_POINTS, 0, (int)fragPoints.size());
        ofPopMatrix();

        
        pTex.unbind();
        
        shader.end();
        
        ofDisablePointSprites();
        ofDisableBlendMode();
        
        
        //ofEnableAlphaBlending();
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        
        //draw background glow
        ofColor clear = ofColor(255, 0, 0, 50);
        ofColor red = ofColor(255, 0, 0, 100);
        float lerpColVal = 0.5f + 0.5f * sin(ofGetElapsedTimef() * 6);
        ofColor currentCol = clear.getLerped(red, lerpColVal);
        
        
        
        ofSetColor(currentCol);
        protoGlow.draw(ofGetWindowSize()/2, scaleFactor*4, scaleFactor*4);
        
        
        
        
        
        float progress = (float)numDead/(float)pList.size();
        drawProgress(progress);
        
        
        

        
        
        if(locateClump){
            
            ofPushStyle();
            ofSetColor(0, 0, 255);
            ofSetLineWidth(3);
            ofNoFill();
            
            ofSetCircleResolution(60);
            
            float amplitude = 20;
            float indicateRad = 120 + amplitude * sin(ofGetElapsedTimef() * 5);
            
            ofCircle(clumpPos, indicateRad);
            
            ofPopStyle();
            
        }
        
        
        
        
        
        //draw UI
        drawUI();
        
        
        //draw blob positions
        for(int i = 0; i < contourFinder.blobs.size(); i++){
            
            float mapBlobX = ofMap(contourFinder.blobs[i].centroid.x, 0, camWidth, leftBound, rightBound);
            float mapBlobY = ofMap(contourFinder.blobs[i].centroid.y, 0, camHeight, topBound, bottomBound);
            
            disturbRad = ofMap(contourFinder.blobs[i].area, 30, 500, disturbMin, disturbMax);
            
            ofPushStyle();
            
            ofSetColor(cvObjectCol);
            ofCircle(mapBlobX, mapBlobY, 10);
            ofNoFill();
            ofCircle(mapBlobX, mapBlobY, disturbRad);
            
            ofPopStyle();
        }
        

        

        
        
    } else if(narrativeState == 3) {

        
        //--------------------PROTOSTAR TO SUN DRAW--------------------
        
        
        
        int currentTime = ofGetElapsedTimeMillis() - stageStartTime;
        
            cvObjectCol = ofColor(0, 255, 0);
            ballInfluence = true;

        
        
        //play first clip: "help the fragment gather more gas"
//        if(currentTime > 2000 && currentTime < 2500 && !stage2_01_useyourhands.getIsPlaying()){
//            playStage2_01 = true;
//            
//        }
//        
//        
//        if(playStage2_01){
//            stage2_01_useyourhands.play();
//            playStage2_01 = false;
//        }
//        
//        
//        
//        
//        //trigger second clip and create a new fragment
//        if(currentTime > 11500 && currentTime < 12000 && !stage1_02_useyourhands.getIsPlaying()){
//            playStage1_02 = true;
//        }
//        
//        if(playStage1_02){
//            stage1_02_useyourhands.play();
//            playStage1_02 = false;
//            cvObjectCol = ofColor(0, 255, 0);
//            ballInfluence = true;
//            
//        }
//        
//        
//        if(numDead > 5000 && announced == false && !stage1_03_seehow.getIsPlaying()){
//            playStage1_03 = true;
//            announced = true;
//            cout << "play narration" << endl;
//        }
//        
//        if(playStage1_03){
//            stage1_03_seehow.play();
//            announcedTimer = ofGetElapsedTimeMillis();
//            playStage1_03 = false;
//        }
//        
//        if(ofGetElapsedTimeMillis() - announcedTimer > 9000 && ofGetElapsedTimeMillis() - announcedTimer < 9500){
//            playStage1_04 = true;
//            test = true;
//        }
//        
//        if(playStage1_04){
//            stage1_04_keepgathering.play();
//            playStage1_04 = false;
//        }
        
        drawGrid(15, 0.2);
        
        
        
        
        

//draw particles
//        for( vector<Particle>::iterator it = pList.begin(); it!=pList.end(); it++){
//            if(it -> dead == false){
//                it -> draw();
//            }
//        }
        
        
        //----------draw Protostar----------
        
        
        float scaleFactor = ofMap(attractorLerp, 0.0, 1.0, 0, 250);
        
        
        //clear vectors for VBO of old data
        //update the cloud fragment particles
        //push them to vectors
        
        fragPoints.clear();
        fragSizes.clear();
        fragColors.clear();
        
        int numFragsDrawn = int(ofMap(attractorLerp, 0.0, 1.0, 10, 2000));//mainFragment.size()));
        
        for( int i = 0; i < numFragsDrawn; i++){
            mainFragment[i].update(scaleFactor);
            //            mainFragment[i].draw();
            
            
            //first color
            ofColor c;
            c = mainFragment[i].col;
            float r = ofClamp(ofNormalize(c.r, 0, 600) + attractorLerp, 0.0f, 1.0f);
            float g = ofNormalize(c.g, 0, 600);
            float b = ofNormalize(c.b, 0, 600);
            float a =ofNormalize(c.a, 0, 255);
            ofFloatColor cF = ofFloatColor(r, g, b, pTrans);
            fragColors.push_back(cF);
            
            
            //now for the points and size vectors
            ofVec3f point;
            point.set(mainFragment[i].pos);
            fragPoints.push_back(point);
            
            
            float s = mainFragment[i].size;
            //float size = 40;
            fragSizes.push_back(ofVec3f(100));
            
        }
        
        //upload all the info to the vbo
        int total = (int)fragPoints.size();
        fragmentVBO.setVertexData(&fragPoints[0], total, GL_STATIC_DRAW);
        fragmentVBO.setNormalData(&fragSizes[0], total, GL_STATIC_DRAW);
        fragmentVBO.setColorData(&fragColors[0], total, GL_STATIC_DRAW);
        
        
        
        
        //shader stuff to place images where particles are
    	glDepthMask(GL_FALSE);
        
        //ofSetColor(255);
        
        // this makes everything look glowy :)
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        ofEnablePointSprites();
        
        // bind the shader and camera
        // everything inside this function
        // will be effected by the shader/camera
        shader.begin();
        
        // bind the texture so that when all the points
        // are drawn they are replace with our dot image
        pTex.bind();
        particleVBO.draw(GL_POINTS, 0, (int)pPoints.size());
        
        ofPushMatrix();
        ofTranslate(ofGetWindowSize()/2);
        fragmentVBO.draw(GL_POINTS, 0, (int)fragPoints.size());
        ofPopMatrix();
        
        
        pTex.unbind();
        
        shader.end();
        
        ofDisablePointSprites();
        ofDisableBlendMode();
        
        
        //ofEnableAlphaBlending();
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        
        //draw background glow
        ofColor clear = ofColor(255, 0, 0, 50);
        ofColor red = ofColor(255, 0, 0, 100);
        float lerpColVal = 0.5f + 0.5f * sin(ofGetElapsedTimef() * 6);
        ofColor currentCol = clear.getLerped(red, lerpColVal);
        
        
        
        ofSetColor(currentCol);
        protoGlow.draw(ofGetWindowSize()/2, scaleFactor*4, scaleFactor*4);
        
        
        
        
        
        float progress = (float)numDead/(float)pList.size();
        drawProgress(progress);
        
        
        
        

        
        
        
        
        
        //draw UI
        drawUI();
        
        
        //draw blob positions
        for(int i = 0; i < contourFinder.blobs.size(); i++){
            
            float mapBlobX = ofMap(contourFinder.blobs[i].centroid.x, 0, camWidth, leftBound, rightBound);
            float mapBlobY = ofMap(contourFinder.blobs[i].centroid.y, 0, camHeight, topBound, bottomBound);
            
            disturbRad = ofMap(contourFinder.blobs[i].area, 30, 500, disturbMin, disturbMax);
            
            ofPushStyle();
            
            ofSetColor(cvObjectCol);
            ofCircle(mapBlobX, mapBlobY, 10);
            ofNoFill();
            ofCircle(mapBlobX, mapBlobY, disturbRad);
            
            ofPopStyle();
        }
        

        
        
    } else if(narrativeState == 4){
        

        
        
        
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);

        drawGrid(15, 0.2);

        ofSetColor(sunCol1);
        ofCircle(ofGetWindowWidth()/2, ofGetWindowHeight()/2, attractorSize/2);
        
        ofEnableBlendMode(OF_BLENDMODE_ADD);

        ofSetColor(sunCol1);
        ofCircle(ofGetWindowWidth()/2, ofGetWindowHeight()/2, attractorSize/2);

        //place glow image on top of star
        ofPushMatrix();

        ofTranslate(ofGetWindowSize()/2);

        ofSetCircleResolution(50);
        ofSetColor(255, 220, 50, 255);
        ofCircle(0, 0, 250);
        glow.draw(0, 0, 550, 550);
        glow.draw(0, 0, 550, 550);
        
        ofPopMatrix();

        
        

        
        

//        //update sun particles
//        for( vector<SunParticle>::iterator it = sunPList.begin(); it != sunPList.end(); it++){
//            it -> update();
//            it -> draw();
//            
//        }
        
        
        
        
        //clear vectors for VBO of old data
        //update the particles
        //push them to VBO vectors
        
        pPoints.clear();
        pSizes.clear();
        pColors.clear();
        
        
        for( int i = 0; i < sunPList.size(); i++){
            
            sunPList[i].update();
            
            
            //first color
            ofColor c;
            c = sunPList[i].col;
            float r = ofNormalize(c.r, 0, 400);
            float g = ofNormalize(c.g, 0, 400);
            float b = ofNormalize(c.b, 0, 400);
            float a = ofNormalize(c.a, 0, 255);
            ofFloatColor cF = ofFloatColor(r, g, b, 0.5);
            pColors.push_back(cF);
            
            
            //now for the points and size vectors
            ofVec3f point;
            point.set(sunPList[i].pos);
            pPoints.push_back(point);
            
            
            float s = sunPList[i].size;
            //float size = 40;

            pSizes.push_back(ofVec3f(s));
            
        }
        
        //upload all the info to the vbo
        int total = (int)pPoints.size();
        particleVBO.setVertexData(&pPoints[0], total, GL_STATIC_DRAW);
        particleVBO.setNormalData(&pSizes[0], total, GL_STATIC_DRAW);
        particleVBO.setColorData(&pColors[0], total, GL_STATIC_DRAW);
        
        
        
        
        //shader stuff to place images where particles are
    	glDepthMask(GL_FALSE);
        
        //ofSetColor(255);
        
        // this makes everything look glowy :)
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        ofEnablePointSprites();
        
        // bind the shader and camera
        // everything inside this function
        // will be effected by the shader/camera
        shader.begin();
        
        // bind the texture so that when all the points
        // are drawn they are replace with our dot image
        sunSmoke.bind();

        particleVBO.draw(GL_POINTS, 0, (int)pPoints.size());
        
        sunSmoke.unbind();
        
        shader.end();
        
        ofDisablePointSprites();
        ofDisableBlendMode();
        
        //draw UI
        
        instructionA = "End of Play Testing";
        instructionB = "Thank You for Playing";
        instructCol = ofColor(255, 0, 0);
        attractorSize = 400;
        
        drawUI();
        
        
        
        
        
    } else if(narrativeState == 5){
        
        
        
        
        
        
        
    }
    

    
    

    
    
    //Show all the debugging visuals
    if(debugVisuals){
        debugVis();
    }
   
    
    
    //----------after everything else is done----------
    //lets take note of the old mouse position
    oldMousePos.set(mouseX, mouseY);
    
    
    //Also, keep track of old blob positions and directions
    
    //start by clearing out the vectors
    oldBlobPos.clear();
    
    //if there are blobs then lets allocate the same number of slots as there are blobs
    if(contourFinder.blobs.size() > 0){
        oldBlobPos.resize(contourFinder.blobs.size());
    }
    
    //then lets fill it with the positions of all the blobs
    for(int i = 0; i < oldBlobPos.size(); i++){
        oldBlobPos[i].set(contourFinder.blobs[i].centroid);
    }
    
    
}
















//--------------------------------------------------UI STUFF------------------------------------------

void testApp::drawUI(){
    
    int borderPadding = 60;
    
    
    ofPushMatrix();{
        ofTranslate(ofGetWindowSize()/2);
        
        
        //INSTRUCTIONS
        for(int i = 0; i < 1; i++){

            ofPushMatrix();
            ofRotate(i*180);
            ofTranslate(0, ofGetWindowHeight()/2 - borderPadding);
            ofRotate(180);
            
            ofScale(0.3, 0.3);
            
            //draw bounding boxes
            ofSetColor(0, 255 * 0.4);
            ofRectangle A = instructions.getStringBoundingBox(instructionA, -instructions.stringWidth(instructionA)/2, 0);
            ofRect(A.x, A.y, A.width, A.height);

            ofRectangle B = instructions.getStringBoundingBox(instructionB, -instructions.stringWidth(instructionB)/2, instructions.getLineHeight());
            ofRect(B.x, B.y, B.width, B.height);
            
            //draw text
            ofSetColor(instructCol);
            instructions.drawString(instructionA, -instructions.stringWidth(instructionA)/2, 0);
            instructions.drawString(instructionB, -instructions.stringWidth(instructionB)/2, instructions.getLineHeight());
            ofPopMatrix();
        }
        
        //STATUS

        int num;
        if(attractorSize < 100){
            num = 2;
        } else if(attractorSize < 200){
            num = 3;
        } else {
            num = 4;
        }
        
        for(int i = 0; i < num; i++){
            ofPushMatrix();
            ofRotate(360/num * i + (ofGetElapsedTimef() * 10));
            ofTranslate(0, attractorSize + attractorSize * 0.1);
            
            statusScale = ofMap(attractorSize, 0, 300, 0.08, 0.23);
            
            ofScale(statusScale, statusScale);
            
            //draw text
            ofSetColor(statusCol);
            status.drawString(statusA, -status.stringWidth(statusA)/2, 0);
            status.drawString(statusB, -status.stringWidth(statusB)/2, status.getLineHeight());
            
            ofPopMatrix();
        }
        
        
        //ZOOM STUFF
        if(zooming){
            
            ofPushStyle();
            ofSetRectMode(OF_RECTMODE_CENTER);
            ofSetColor(zoomSquareCol);
            ofNoFill();
            ofSetLineWidth(zoomSquareThick);
            ofRect(0, 0, zoomSquareWidth, zoomSquareWidth);
            
            ofPopStyle();

        }
        
        
    
    }ofPopMatrix();
    
}


void testApp::debugVis(){
    ofPushStyle();
    ofSetColor(255);
    ofNoFill();
    ofRect(ofGetWindowWidth()/2 - ofGetWindowHeight()/2, 0, ofGetWindowHeight(), ofGetWindowHeight());
    
    ofSetColor(255, 0, 0);
    ofDrawBitmapString("Framerate: " + ofToString(ofGetFrameRate()), 20, 30);
    ofDrawBitmapString("Number of Particles: " + ofToString(pList.size()), 20, 45);
    ofDrawBitmapString("Disturbed not dead: " + ofToString(numDisturbed), 20, 60);
    ofDrawBitmapString("Dead Particles: " + ofToString(numDead), 20, 75);
    ofDrawBitmapString("Attractor Size: " + ofToString(attractorSize), 20, 90);
    ofDrawBitmapString("Points vector size: " + ofToString(pPoints.size()), 20, 105);
    
    
    ofDrawBitmapString("Number of blobs detected: " + ofToString(contourFinder.blobs.size()), 20, 120);
    
    ofDrawBitmapString("pistonPos: " + ofToString(pistonPos), 20, 135);
    ofDrawBitmapString("mainFragment size: " + ofToString(mainFragment.size()), 20, 150);
    
    
    ofPopStyle();
    
    //draw camera stuff
    //contourFinder.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    
    if(drawCam){
        ps3eye.draw(0, 500, 260, 195);
    }
    

    

    
}






//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    //change mouse radius
    if(key == '1'){
        narrativeState = -1;        //welcome screen
    } else if(key == '2'){
        narrativeState = 0;         //intro video
    } else if(key == '3'){
        narrativeState = 1;         //gas cloud (first interactive stage
    } else if(key == '4'){
        narrativeState = 2;         //protostar stage
    } else if(key == '5'){
        narrativeState = 3;         //protostar reactions
    } else if(key == '6'){
        narrativeState = 4;         //star birth
    }
    
    
    //toggle debug info
    if(key == 'd' || key == 'D'){
        debugVisuals = !debugVisuals;
    }
    
    
    //disturb all particles on keypress
    if(key == ' '){
        for( vector<Particle>::iterator it = pList.begin(); it!=pList.end(); it++){
            it -> disturbed = true;
        }
    }
    
    
    //toggle zoom animation
    if(key == 'z' || key == 'Z'){
        transitionToNext = !transitionToNext;
    }
    
    
    //toggle camera draw
    if(key == 'c' || key == 'C'){
        drawCam = !drawCam;
    }
    
    

    
    
    //piston to top
    if(key == '9'){
        sendSerial(0, 255, 0);
        cout << "piston up" << endl;
        
    }
    //piston to bottom
    if(key == '0'){
        sendSerial(255, 255, 0);
        cout << "piston down" << endl;
    }
    
}



//----------------------------------------OTHER FUNCTIONS-------------------------------
void testApp::drawBlackBars(){
    ofPushStyle();
    
    //left bar
    ofSetColor(0);
    ofRect(0,0, (ofGetWindowWidth() - ofGetWindowHeight())/2, ofGetWindowHeight());
    //right bar
    ofRect(ofGetWindowWidth()/2 + ofGetWindowHeight()/2,0, (ofGetWindowWidth() - ofGetWindowHeight())/2, ofGetWindowHeight());
    
    ofPopStyle();
}

void testApp::drawGrid(int num, float trans){
    float lineSpacing = ofGetWindowHeight()/num;
    
    ofSetLineWidth(3);
    ofSetColor(255, 255 * trans);
    for(int i = 0; i < num; i++){
        //horizontal lines
        ofLine(ofGetWindowWidth()/2 - ofGetWindowHeight()/2, i * lineSpacing, ofGetWindowWidth()/2 + ofGetWindowHeight()/2, i * lineSpacing);
        //vertical lines
        ofLine(ofGetWindowWidth()/2 - ofGetWindowHeight()/2 + i * lineSpacing, 0, ofGetWindowWidth()/2 - ofGetWindowHeight()/2 + i * lineSpacing, ofGetWindowHeight());
    }
}

void testApp::drawProgress(float progress){
    
    //draw progress bar
    progressBarDim.set(500, 50);
    progressBarPos.set(ofGetWindowWidth()/2 - progressBarDim.x/2, ofGetWindowHeight() - 170);
    

    
    ofPushStyle();
    
    //draw inside
    ofSetColor(progressCol);
    ofRect(progressBarPos.x, progressBarPos.y, progressBarDim.x - progressBarDim.x * progress, progressBarDim.y);
    
    //draw border
    ofSetColor(255);
    ofSetLineWidth(2);
    ofNoFill();
    ofRect(progressBarPos, progressBarDim.x, progressBarDim.y);
    
    ofPopStyle();
    
    
    
    ofPushMatrix();
    
    ofTranslate(ofGetWindowSize()/2);
    ofRotate(180);
    ofTranslate(0, -ofGetWindowHeight()/2 + 155);
    
    ofScale(0.2, 0.2);
    
    
    
    //draw text
    progressText = "Gas Left to Collect: " + ofToString(100 - floor(progress*100)) + "%";
    
    ofSetColor(255);
    instructions.drawString(progressText, -instructions.stringWidth(progressText)/2, 0);
    ofPopMatrix();

    
}


void testApp::perlinBlob(int base, float range, int randSeed, int rot){
    
    float speed = 0.2;
    float fringeWidth = base * range;
    
    ofPushMatrix();{
        ofTranslate( ofGetWindowSize() / 2);
        ofRotate(rot);
        
        ofBeginShape();
        for (int i = 0; i < 100; i++){
            
            //Code borrowed from Charley Whitney (Algorithmic Animations Fall 2013)
            float add = ofNoise(i/20.0f, ofGetElapsedTimef() * speed + randSeed);
            
            //this will draw a circle with a min radius of the incoming value
            //plus the fringe value
            ofVertex( (base - fringeWidth * add) * cos((i/100.0)*TWO_PI),
                     (base - fringeWidth * add) * sin((i/100.0)*TWO_PI));
            
        }
        
        //ofVertex(firstX, firstY);
        
        ofEndShape();
        
    }ofPopMatrix();
    
}


void testApp::newParticleField(int res){
    int particleResolution = res;
    int randomScatter = 30;
    
    ofSeedRandom(ofRandom(1000));
    randomPerl = ofRandom(1000);
    
    float perlinScale = 0.005;
    
    pList.clear();
    pSizes.clear();
    pPoints.clear();
    
    for(int y = 0; y < ofGetWindowHeight(); y += particleResolution){
        for(int x = ofGetWindowWidth()/2 - ofGetWindowHeight()/2; x < ofGetWindowWidth()/2 + ofGetWindowHeight()/2; x += particleResolution){
            
            //calculate point distance from attractor
            float distSq = ofDistSquared(x, y, attractorPos.x, attractorPos.y);
            
            //create new points only if outside attractor
            if(distSq > (attractorSize + attractionRad) * (attractorSize + attractionRad)){
                float noiseVal = ofNoise(x * perlinScale + randomPerl, y * perlinScale + randomPerl);
                
                if(noiseVal > 0.5){
                    Particle p;
                    p.pos.set(x + ofRandom(-randomScatter, randomScatter), y + ofRandom(-randomScatter, randomScatter));
                    
                    p.col = colorscheme.getColor(x, y);
                    p.col.a = 0;
                    p.size = ofRandom(pSmall, pBig);
                    pList.push_back(p);
                    
                    ofColor c;
                    c = p.col;
                    float r = ofNormalize(c.r, 0, 255);
                    float g = ofNormalize(c.g, 0, 255);
                    float b = ofNormalize(c.b, 0, 255);
                    ofFloatColor cF = ofFloatColor(r, g, b, pTrans);
                    pColors.push_back(cF);
                    
                    //duplicate positions in point vector and size vector
                    ofVec3f point;
                    point.set(p.pos);
                    pPoints.push_back(point);
                    
                    
                    float s = p.size;
                    //float size = 40;
                    pSizes.push_back(ofVec3f(100));
                    
                }
                
                
                
                
                
                
                
            }
        }
    }
}

void testApp::createClump(int _x, int _y, float _rad, int num){
    
    for(int i = 0; i < num; i++){
        
        //Circle distribution code from Charlie Whitney (flocking sketch - algo - fall 2013)
        
        float phi = ofRandom( 0, TWO_PI );
        float costheta = ofRandom( -1.0f, 1.0f );
        
        float rho = sqrt( 1.0f - costheta * costheta );
        float x = rho * cos( phi );
        float y = rho * sin( phi );
        float z = costheta;
        
        ofVec3f randVec(x, y, z);
        
        ofVec3f pos = randVec * ofRandom( _rad/2 , _rad );

        Particle p;
        p.pos.set(pos.x + _x, pos.y + _y);
        
        p.col = colorscheme.getColor(ofRandom(colorscheme.width), ofRandom(colorscheme.height));
        p.col.a = 0;
        p.size = ofRandom(pSmall, pBig);
        pList.push_back(p);
        
    }

    
    
}

void testApp::createSunSmoke(){
    
    sunPList.clear();
    
    
    for (int i = 0; i < 2500; i++){
        
        //Circle distribution code from Charlie Whitney (flocking sketch - algo - fall 2013)
        
        float phi = ofRandom( 0, TWO_PI );
        float costheta = ofRandom( -1.0f, 1.0f );
        
        float rho = sqrt( 1.0f - costheta * costheta );
        float x = rho * cos( phi );
        float y = rho * sin( phi );
        float z = costheta;
        
        ofVec3f randVec(x, y, z);
        
//        ofVec3f pos = randVec;
        ofVec3f pos = ofVec3f(ofGetWindowSize()/2);
        
        ofVec3f vel = ofVec3f(ofRandom(-10, 10), ofRandom(-10, 10), ofRandom(0, 20));
        
        SunParticle s;
        s.setParams(pos, vel);
        
        sunCol1 = ofColor(255, 255, 100);
        sunCol2 = ofColor(255, 200, 20);
        s.col = sunCol1.lerp(sunCol2, ofRandom(0,1));
        s.size = ofRandom(pSmall, pBig);
        sunPList.push_back(s);
        

        
        
    }
    

    
    
    
    
    
}


void testApp::createMainFragment(){     //make sure to only call after newParticleField()

    
    mainFragment.clear();

    
    for (int i = 0; i < 5000; i++){

        //Circle distribution code from Charlie Whitney (flocking sketch - algo - fall 2013)

        float phi = ofRandom( 0, TWO_PI );
        float costheta = ofRandom( -1.0f, 1.0f );

        float rho = sqrt( 1.0f - costheta * costheta );
        float x = rho * cos( phi );
        float y = rho * sin( phi );
        float z = costheta;

        ofVec3f randVec(x, y, z);

        ofVec3f pos = randVec; // * ofRandom( 0.5f, 1.0f );
//        ofVec3f vel(ofRandom(-10, 10),ofRandom(-10, 10),ofRandom(-10, 10));

//        pos.set(0, 0);
        Fragment f;
        f.setParams(pos);
        f.col = colorscheme.getColor(ofRandom(colorscheme.width), ofRandom(colorscheme.height));
        f.col.a = 0;
//        f.col = ofColor(255);
        f.size = ofRandom(pSmall/10, pBig/10);
//        f.size = ofRandom(10, 11);
        mainFragment.push_back(f);
        


        
    }
    
    

}

//--------------------------------------------------------------

//package data into a string and send via serial
//borrowed from Kyle McDonald https://github.com/openframeworks/openFrameworks/issues/279
void testApp::sendSerial(long one, long two, long three){
    
    //package ints as a string separated by commas and with a newline ending
    string outgoing = ofToString(one) + "," + ofToString(two) + "," + ofToString(three) + "\n";
    
    //serial can't handle strings so we turn the string into a char array
    unsigned char* outgoingCharArray = new unsigned char[outgoing.size()];
    memcpy(outgoingCharArray, outgoing.c_str(), outgoing.size());
    
    //send the char array out via serial
    serial.writeBytes(outgoingCharArray, outgoing.size());
    
    //delete the char array for memory management
    delete [] outgoingCharArray;
    
    
}


