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
    topBound = -22;
    bottomBound = 1115;

    
    disturbRad = 50;
    disturbMin = 50;
    disturbMax = 100;
    
    //Narrative control
    narrativeState = 0;
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
    zoom.loadSound("zoom.mp3");
    zoom.setVolume(1.0f);
    zoom.setSpeed(0.5f);
    zoom.setMultiPlay(false);
    
    pWhoosh.loadSound("whooshShort.mp3");
    pWhoosh.setVolume(0.1f);
    pWhoosh.setSpeed(1.0f);
    pWhoosh.setMultiPlay(true);

    narrate1.loadSound("pops.mp3");
    narrate1.setVolume(0.1f);
    narrate1.setSpeed(1.0f);
    narrate1.setMultiPlay(false);
    
    debugVisuals = true;
    
    sendSerial(0, 255, 0);
    
}

//--------------------------------------------------------------

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
    
    if(narrativeState == 0){
        //introduction
        
        if(lineTrans < 255){
            lineTrans += 1;
        }
        
//        numBallsinBox = 0;
//        
//        if(contourFinder.blobs.size() > 0){
//            for(int i = 0; i < contourFinder.blobs.size(); i++){
//                
//                if(contourFinder.blobs[i].centroid.x > ofGetWindowWidth()/2 + ofGetWindowHeight()/2 - 100 && contourFinder.blobs[i].centroid.x < ofGetWindowWidth()/2 + ofGetWindowHeight()/2 && contourFinder.blobs[i].centroid.y < 100){
//                    numBallsinBox++;
//                
//                }
//            }
//            
//        }
//        
//        if(numBallsinBox > 0){
//            inButton = true;
//        } else {
//            inButton = false;
//        }
//        
//        ofSetColor(255, 0, 0);
//        ofDrawBitmapString(ofToString(numBallsinBox), 100, 100);
//        
//        
//        if(inButton){
//            if(boxTrans < 200){
//                boxTrans += 1;
//            }
//            
//        } else {
//            boxTrans = 0;
//        }
//        
//        numBallsinBox = 0;
//        
//        if(ofGetElapsedTimeMillis() > 10000){
//            sendSerial(255, 255, 0);
//        }
        
        
        
        
        
        
        
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




//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//-----------------------------------------DRAW-----------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void testApp::draw(){
    
    
    
    

    if(narrativeState == 0){
        
        
        
        
        int numLines = 15;
        float lineSpacing = ofGetWindowHeight()/numLines;
        
        ofSetLineWidth(3);
        ofSetColor(255, lineTrans);
        for(int i = 0; i < numLines; i++){
            //horizontal lines
            ofLine(ofGetWindowWidth()/2 - ofGetWindowHeight()/2, i * lineSpacing, ofGetWindowWidth()/2 + ofGetWindowHeight()/2, i * lineSpacing);
            //vertical lines
            ofLine(ofGetWindowWidth()/2 - ofGetWindowHeight()/2 + i * lineSpacing, 0, ofGetWindowWidth()/2 - ofGetWindowHeight()/2 + i * lineSpacing, ofGetWindowHeight());
        }

        
        for(int i = 0; i < contourFinder.blobs.size(); i++){
            float mapBlobX = ofMap(contourFinder.blobs[i].centroid.x, 0, camWidth, leftBound, rightBound);
            float mapBlobY = ofMap(contourFinder.blobs[i].centroid.y, 0, camHeight, topBound, bottomBound);
            
            disturbRad = ofMap(contourFinder.blobs[i].area, 30, 500, disturbMin, disturbMax);
            
            ofPushStyle();
            ofSetColor(0, 150, 255);
            
            ofCircle(mapBlobX, mapBlobY, 10);
            
            ofNoFill();
            ofCircle(mapBlobX, mapBlobY, disturbRad);
            
            ofNoFill();
            ofSetLineWidth(5);
            ofEllipse(mapBlobX, mapBlobY, 50, 50);
            
            
            ofPopStyle();

        }

        
        
        
        //corner control box
//        ofPushMatrix();
//        ofTranslate(ofGetWindowWidth()/2 + ofGetWindowHeight()/2 - 170, 130);
//        ofScale(0.2, 0.2);
//        
//        ofSetColor(instructCol);
//        string corner = "Next Stage";
//        instructions.drawString(corner, 0, 0);
//        
//        ofPopMatrix();
//
//        
//        ofPushStyle();
//
//        ofNoFill();
//        ofSetColor(255);
//        ofRect(ofGetWindowWidth()/2 + ofGetWindowHeight()/2 - 100, 0, 100, 100);
//        
//        ofFill();
//        ofSetColor(0);
//        ofRect(ofGetWindowWidth()/2 + ofGetWindowHeight()/2 - 100, 0, 100, 100);
//        ofSetColor(255, boxTrans);
//        ofRect(ofGetWindowWidth()/2 + ofGetWindowHeight()/2 - 100, 0, 100, 100);
//        
//        
//        ofPopStyle();
        
        
        
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


//--------------------------------------------------UI STUFF--------------------------------------------------

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

//----------------------------------------OTHER FUNCTIONS----------------------------------------

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