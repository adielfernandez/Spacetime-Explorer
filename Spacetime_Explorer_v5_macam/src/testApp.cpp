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
    serial.setup("/dev/tty.usbmodem1411", baud); 
    
    pistonPos = 0;
    pistonSpeed = 120;
    
    // load the texure
	ofDisableArbTex();
	ofLoadImage(texture, "dot.png");
    
    ofEnableArbTex();
    
    // load the shader
    #ifdef TARGET_OPENGLES
        shader.load("shaders_gles/shader");
    #else
        shader.load("shaders/shader");
    #endif
    
    colorscheme.loadImage("gasDesat.jpg");

    
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
    transitionTo2 = false;
    transitionTo2Timer = 0;

    transitionTo3 = false;
    transitionTo3Timer = 0;
    
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
    trans = 0.2;
    pSmall = 15;
    pBig = 80;
    newParticleField(fieldRes);
    
    //UI Stuff
    instructions.loadFont("avenir.ttc", 100, true, true);
    instructions.setLetterSpacing(0.95);
    instructionA = "Help the body acrete mass by";
    instructionB = "pushing the gas cloud to the center";

    instructCol = ofColor(0, 150, 255);

    
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
    zoom.setVolume(1.0f);
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
    
    
    //Narrative States
    //----------Idle----------
    background.loadImage("idleBackground.jpg");
    handWithBall.loadImage("handwithball.png");
    handWithBall.rotate90(2);
    handWithBall.setAnchorPercent(1.0, 0.0);
    
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
    
    
    
    
    debugVisuals = true;
    
    sendSerial(0, 255, 0);
    
}

//----------------------------------------------------------------------------------
//                ___  ___  ________  ________  ________  _________  _______
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
                timeInBox += 4;
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
    
        
        //reset particle counters
        numDead = 0;
        numDisturbed = 0;
        
        //clear out points vector so the only particles in there are ones that are alive 
        points.clear();
        sizes.clear();
        colors.clear();
        
        
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
                points.push_back(partPos);
                
                float s = it -> size;
                sizes.push_back(ofVec3f(s));
                
                ofColor c = it-> col;
                float r = ofNormalize(c.r, 0, 255);
                float g = ofNormalize(c.g, 0, 255);
                float b = ofNormalize(c.b, 0, 255);
                ofFloatColor cF = ofFloatColor(r, g, b, trans);
                colors.push_back(cF);
                
                
            } else {
                //count number of dead particles
                numDead++;
                
                if(pList.size() - numDead < 100){
                    transitionTo2 = true;


                }
                
                
            } //if(particles are alive) statement 

        } //particle for-loop
        
        
        if(transitionTo2 == false){
            
            
            //change attractor size depending on how many particles have been swallowed
            attractorSize = ofLerp(attractorBase, attractorMax, (float)numDead/(float)pList.size());
            
            //update the timer so its current when the transition actually starts
            transitionTo2Timer = ofGetElapsedTimeMillis();
            
            pistonSpeed = 120;

            
            
        }

        
        
        //if we've gathered all the particles, trigger transition

        //--------------------zoom animation--------------------
        
        if(transitionTo2){
           
            //set piston speed to move up quickly
            pistonSpeed = 255;
            
            //play narration clip:
            //"Great job! You've cleared out the neighborhood of all the gas and dust.
            //Lets zoom out to see if we can find more to collect"
            
            //if we're not already playing it
            if(narrate1.getIsPlaying() == false && ofGetElapsedTimeMillis() - transitionTo2Timer < 1000){
                narrate1.play();
            }
            
            //if we're animating...
            if(ofGetElapsedTimeMillis() - transitionTo2Timer > 3500){
                zooming = true;
                
                if(zoom.getIsPlaying() == false){
                    zoom.play();
                }
                
                float fadeSpeed = 0.03;
                
                //change size of attractor
                attractorSize = ofLerp(attractorSize, 20, fadeSpeed);
                
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
            if(ofGetElapsedTimeMillis() - transitionTo2Timer > 9000){
                
                //clear out the particles
                
                
                pList.clear();
                
                newParticleField(6);
                
                narrativeState = 2;
            }

            
            
            
            
            
            
            
        }
        
        
        //upload all the info to the vbo
        int total = (int)points.size();
        vbo.setVertexData(&points[0], total, GL_STATIC_DRAW);
        vbo.setNormalData(&sizes[0], total, GL_STATIC_DRAW);
        vbo.setColorData(&colors[0], total, GL_STATIC_DRAW);

        //send arduino states
        pistonPos = (int)ofClamp(ofMap(attractorSize, attractorBase, attractorMax, 0, 255), 0, 255);

        sendSerial(pistonPos, pistonSpeed, 0);
        
        
        
        
    } else if(narrativeState == 2){
        
        
                    
            
            
            
            
            
            
            
        
    
        

        
        
        
        
    } else if(narrativeState == 3){
        
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

        float rotateSpeed = ofGetElapsedTimef() * 3;
        
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
        ofTranslate(ofGetWindowWidth()/2 + 250, 135);
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
            introStartTime = ofGetElapsedTimeMillis();
            sendSerial(0, 150, 0);
            cvObjectCol = ofColor(255, 0);
            startedIntro = true;
        }
            
        int currentTime = ofGetElapsedTimeMillis() - introStartTime;

        

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
            string rollMessage = "Hold ball here to continue";
            
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
    
        int numLines = 15;
        float lineSpacing = ofGetWindowHeight()/numLines;
        
        ofSetLineWidth(3);
        ofSetColor(255, 255 * 0.2);
        for(int i = 0; i < numLines; i++){
            //horizontal lines
            ofLine(ofGetWindowWidth()/2 - ofGetWindowHeight()/2, i * lineSpacing, ofGetWindowWidth()/2 + ofGetWindowHeight()/2, i * lineSpacing);
            //vertical lines
            ofLine(ofGetWindowWidth()/2 - ofGetWindowHeight()/2 + i * lineSpacing, 0, ofGetWindowWidth()/2 - ofGetWindowHeight()/2 + i * lineSpacing, ofGetWindowHeight());
        }
        
         
        //draw particles
//        for( vector<Particle>::iterator it = pList.begin(); it!=pList.end(); it++){
//            if(it -> dead == false){
//                it -> draw();
//            }
//        }
        
        
        
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
        texture.bind();
        vbo.draw(GL_POINTS, 0, (int)points.size());
        texture.unbind();
        
        shader.end();
        
        ofDisablePointSprites();
        ofDisableBlendMode();
        
        
        ofEnableAlphaBlending();
        
        
        
        
        //Draw Attractor
//        ofSetColor(255, 230, 165, 255*0.09);
        ofColor out = ofColor(255, 240, 200, 80);
        ofColor in = ofColor(255, 212, 100, 80);
        int numBlobs = 100;
        
        for(int i = 0; i < numBlobs; i++){
        
//            ofSetColor(255, 255 - 255 * i/numBlobs, 225 - 225 * i/numBlobs, 255 * 0.08);
            ofColor thisCol = out.lerp(in, 0.01);
            
            ofSetColor(thisCol);
            
            float blobWobble = ofMap(i, 0, numBlobs, 0.6, 0.1);
            perlinBlob(attractorSize - attractorSize * i/numBlobs, blobWobble, 0 + i*2000, 36*i);
      
        
        }
        
        //draw UI
        drawUI();

        
        //draw blob positions
        for(int i = 0; i < contourFinder.blobs.size(); i++){
            
            float mapBlobX = ofMap(contourFinder.blobs[i].centroid.x, 0, camWidth, leftBound, rightBound);
            float mapBlobY = ofMap(contourFinder.blobs[i].centroid.y, 0, camHeight, topBound, bottomBound);
            
            disturbRad = ofMap(contourFinder.blobs[i].area, 30, 500, disturbMin, disturbMax);
            
            ofPushStyle();
            
            ofSetColor(255, 0, 0);
            ofCircle(mapBlobX, mapBlobY, 10);
            ofNoFill();
            ofCircle(mapBlobX, mapBlobY, disturbRad);
            
            ofPopStyle();
        }
        
        
    
    } else if(narrativeState == 2){
        
        
        //draw particles
        for( vector<Particle>::iterator it = pList.begin(); it!=pList.end(); it++){
            if(it -> dead == false){
                it -> draw();
            }
        }
        
        //Draw Attractor
        
        ofColor out = ofColor(255, 255, 255, 100);
        ofColor in = ofColor(255, 0, 0, 100);
        int numBlobs = 100;
        
        for(int i = 0; i < numBlobs; i++){
            ofSetColor(255, 255 - 255 * i/numBlobs, 225 - 225 * i/numBlobs, 255 * 0.08);
//            ofSetColor(in.lerp(out, i/numBlobs));
            
            float blobWobble = ofMap(i, 0, numBlobs, 0.6, 0.1);
            perlinBlob(attractorSize - attractorSize * i/numBlobs, blobWobble, 0 + i*2000, 36*i);
        }
        
        //adds a little shading outside the central circle
        for(int i = 0; i < 5; i++){
            ofSetColor(0, 255 * 0.03);
            perlinBlob(attractorSize - attractorSize * 0.8, 0.6, 0 + i*2000, 36*i);
        }
        
        //draw central red circle
        ofSetColor(255, 0, 0);
        ofCircle(ofGetWindowSize()/2, attractorSize*0.1);
        
        
        
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
            
            ofScale(0.23, 0.23);
            
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
    ofDrawBitmapString("Points vector size: " + ofToString(points.size()), 20, 105);
    
    
    ofDrawBitmapString("Number of blobs detected: " + ofToString(contourFinder.blobs.size()), 20, 120);
    
    if(blobDirection.size() > 0){
        ofDrawBitmapString("Blobs[0] magnitude: " + ofToString(blobDirection[0].length()), 20, 135);
    }
    
    ofDrawBitmapString("pistonPos: " + ofToString(pistonPos), 20, 150);

    
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
        mouseRad = 60;
    } else if(key == '2'){
        mouseRad = 150;
    } else if(key == '3'){
        mouseRad = 300;
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
        transitionTo2 = !transitionTo2;
    }
    
    
    //toggle camera draw
    if(key == 'c' || key == 'C'){
        drawCam = !drawCam;
    }
    
    
    //go to N = 1
    if(key == 'n' || key == 'N'){
        narrativeState = 1;
        sendSerial(0, 255, 0);
    }
    
    
    //piston to top
    if(key == '9'){
        sendSerial(0, 255, 0);
        
    }
    //piston to bottom
    if(key == '0'){
        sendSerial(255, 255, 0);
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
    
    randomPerl = ofRandom(1000);
    
    float perlinScale = 0.005;
    
    sizes.clear();
    
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
                    p.col.a = trans;
                    p.size = ofRandom(pSmall, pBig);
                    pList.push_back(p);
                    
                    ofColor c;
                    c = p.col;
                    float r = ofNormalize(c.r, 0, 255);
                    float g = ofNormalize(c.g, 0, 255);
                    float b = ofNormalize(c.b, 0, 255);
                    ofFloatColor cF = ofFloatColor(r, g, b, trans);
                    colors.push_back(cF);
                    
                    //duplicate positions in point vector and size vector
                    ofVec3f point;
                    point.set(p.pos);
                    points.push_back(point);
                    
                    
                    float s = p.size;
                    //float size = 40;
                    sizes.push_back(ofVec3f(100));
                    
                }
                
                
                
                
                
                
                
            }
        }
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


