#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
    ofBackground(0);
    ofSetFrameRate(60);
    ofEnableAlphaBlending();

    
    //Kinect stuff
    kinect.setRegistration();
    kinect.init();
    kinect.open();
    
    grayScale.allocate(kinect.width, kinect.height);
    nearThreshold = 240;
    farThreshold = 223;
    
    disturbRad = 200;
    
    
    //Narrative control
        //0 = intro video
        //1 = molecular cloud
        //2 = cloud fragment
        //3 = protostar
        //4 = star
    narrativeState = 1;
    
    
    
    //Attractor stuff
    attractorBase = 30;
    attractorSize = 0;
    attractorPos.set(ofGetWindowWidth()/2, ofGetWindowHeight()/2);
    attractionRad = 30;
    attractStrength = 0.6;
    attractorMax = 175;
    
    mouseRad = 150;
    
    
    //CREATE PARTICLE FIELD
    fieldRes = 5;
    newParticleField(fieldRes);

    
    
    
    //UI Stuff
    instructions.loadFont("avenirNext.ttc", 20, true, true);
    instructions.setLetterSpacing(0.95);
    instructionA = "Help the body acrete mass by";
    instructionB = "pushing the gas cloud to the center";
    instructCol = ofColor(0, 150, 255);
    
    status.loadFont("avenir.ttc", 15, true, true);
    statusBigger.loadFont("avenir.ttc", 15, true, true);
    status.setLetterSpacing(0.95);
    statusCol = ofColor(255);
    statusA = "Status: Cloud";
    statusB = "Fragment";
    
    debugVisuals = true;
    
}

//--------------------------------------------------------------
void testApp::update(){

    //Computer Vision Stuff
    kinect.update();
    
    //if we have a new frame
    if(kinect.isFrameNew()){
        
        // load grayscale depth image from the kinect source
		grayScale.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
        
        //go through all the pixels and make them white
        //if they fall between threshold values
        unsigned char * pix = grayScale.getPixels();
        
        int numPixels = grayScale.getWidth() * grayScale.getHeight();
        for(int i = 0; i < numPixels; i++) {
            if(pix[i] < nearThreshold && pix[i] > farThreshold) {
                pix[i] = 255;
            } else {
                pix[i] = 0;
            }
        }
        
        // update the cv images
		grayScale.flagImageChanged();
        
        contourFinder.findContours(grayScale, 10, (kinect.width * kinect.height)/3, 20, false);
        
    }
    
    
    
    
    
    //------------------------------Interaction stuff------------------------------
    
    if(narrativeState == 0){
        
        
    } else if(narrativeState == 1){
    
    
    mousePos = ofVec3f(mouseX, mouseY);
    mouseDirection = mousePos - oldMousePos;


    
    //reset particle counter
    numDead = 0;
    
    //Update particles
    for( vector<Particle>::iterator it = pList.begin(); it!=pList.end(); it++){
        
        //only update non-dead particles
        if(it -> dead == false){
            
            //check if inside attractor
            ofVec3f distAttractor = attractorPos - it -> pos;
            if(distAttractor.lengthSquared() < attractorSize * attractorSize){
            
                //if so, add to attractor and make dead
                accretionCounter += 1;
                it -> dead = true;
                it -> vel.set(0, 0);
                
            }
            
            it -> update(mouseDirection);

            
            //if particle is within mouse radius, count it as disturbed
            ofVec2f distMouse = it -> pos - mousePos;
            
            if(distMouse.lengthSquared() < mouseRad * mouseRad){
                it -> disturbed = true;

                //repulsion from mouse
                it -> repel(mousePos, mouseRad, 1.1);
            
            }
            
            
            //if there are blobs and particle is within radius of blobs, count it as disturbed
            if(contourFinder.blobs.size() > 0){
                
//                for( vector<ofxCvBlob>:: iterator thisBlob = contourFinder.blobs.begin(); thisBlob != contourFinder.blobs.end(); thisBlob++){
//                    
//                    //map the position of the blob to the screen size
//                    float mapBlobX = ofMap(thisBlob -> centroid.x, 0, kinect.width, 0, ofGetWindowWidth());
//                    float mapBlobY = ofMap(thisBlob -> centroid.y, 0, kinect.height, 0, ofGetWindowHeight());
//                    
//                    //subtract position of centroid from position of particle
//                    ofVec2f distBlob = (it -> pos) - ofVec2f(mapBlobX, mapBlobY);
//
//                    //count as disturbed if within radius (circular boundary)
//                    if(distBlob.lengthSquared() < disturbRad * disturbRad){
//                        it -> disturbed = true;
//                    }
//
//                    
//                    
//                }
                
                
                for(int i = 0; i < contourFinder.blobs.size(); i++){
                    
                    if(pointInPolygon(i, it -> pos.x, it -> pos.y)){
                        it -> disturbed = true;
                    }
                    
                }
                
            }
            
            //attraction to Attractor due to its own gravitation for particles within
            //the attraction radius
            it -> attract(attractorPos, attractorSize + attractionRad, attractStrength);
            
            //add another gravitational force once particles are disturbed
            if(it -> disturbed){
                it -> globalAttract(attractorPos, attractStrength);
            }
            
            
            
            
        } else {
            //count number if dead particles
            numDead++;
            
        }
    }
    
    
    
    attractorSize = attractorBase + accretionCounter/120;
    } else if(narrativeState == 2){
        
        
        
        
        
        
        
        
        
        
        
        
        
    }
    
}

//-----JUST A TEST-----
bool testApp::pointInPolygon(int pno,int x, int y){
    
    int j = contourFinder.blobs[pno].pts.size()-1;
    
    bool oddNodes= false;
    
    for (int i = 0; i<contourFinder.blobs[pno].pts.size(); i++) {
        
        if ((contourFinder.blobs[pno].pts[i].y < y && contourFinder.blobs[pno].pts[j].y >= y) || (contourFinder.blobs[pno].pts[j].y < y && contourFinder.blobs[pno].pts[i].y>=y)){
            
            if (contourFinder.blobs[pno].pts[i].x + (y-contourFinder.blobs[pno].pts[i].y)/(contourFinder.blobs[pno].pts[j].y - contourFinder.blobs[pno].pts[i].y) * (contourFinder.blobs[pno].pts[j].x - contourFinder.blobs[pno].pts[i].x) < x) {
                
                oddNodes=!oddNodes;
            }
            
        }
        
        j=i;
        
    }
    
    return oddNodes;
    
}


//--------------------------------------------------------------
void testApp::draw(){

    
    //draw particles
    for( vector<Particle>::iterator it = pList.begin(); it!=pList.end(); it++){
        if(it -> dead == false){
            it -> draw();
        }
    }
    
    
    
    
    
    
    
    
    //Draw Attractor
//    ofSetColor(255, 230, 165, 255*0.09);
    ofColor out = ofColor(255, 255, 255, 100);
    ofColor in = ofColor(255, 0, 0, 100);
    int numBlobs = 100;
    
    for(int i = 0; i < numBlobs; i++){
    
        ofSetColor(255, 255 - 255 * i/numBlobs, 225 - 225 * i/numBlobs, 255 * 0.08);
//        ofSetColor(in.lerp(out, i/numBlobs));
        
        float blobWobble = ofMap(i, 0, numBlobs, 0.6, 0.1);
        perlinBlob(attractorSize - attractorSize * i/numBlobs, blobWobble, 0 + i*2000, 36*i);
  
    
    }
    
    for(int i = 0; i < 5; i++){
        
        ofSetColor(0, 255 * 0.03);
        perlinBlob(attractorSize - attractorSize * 0.8, 0.6, 0 + i*2000, 36*i);
        
        
    }
    
    ofSetColor(255, 0, 0);
    ofCircle(ofGetWindowSize()/2, attractorSize*0.1);
    
    //    ofSetCircleResolution(100);
    //    ofCircle(attractorPos, attractorSize);
    
    
    //draw UI
    drawUI();
    
    
    //Show all the debugging visuals 
    if(debugVisuals){
        debugVis();
    }
    
    
    
    oldMousePos.set(mouseX, mouseY);

}


//--------------------------------------------------UI STUFF--------------------------------------------------

void testApp::drawUI(){
    
    int borderPadding = 60;
    
    
    ofPushMatrix();{
        ofTranslate(ofGetWindowSize()/2);
        
        
        //INSTRUCTIONS
        for(int i = 0; i < 4; i++){

            ofPushMatrix();
            ofRotate(i*90);
            ofTranslate(0, ofGetWindowHeight()/2 - borderPadding);
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
            
            //draw text
            ofSetColor(statusCol);
            status.drawString(statusA, -status.stringWidth(statusA)/2, 0);
            status.drawString(statusB, -status.stringWidth(statusB)/2, status.getLineHeight());
            
            ofPopMatrix();
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
    ofDrawBitmapString("Dead Particles: " + ofToString(numDead), 20, 60);
    ofDrawBitmapString("Attractor Size: " + ofToString(attractorSize), 20, 75);

    ofDrawBitmapString("Number of blobs detected: " + ofToString(contourFinder.blobs.size()), 20, 90);
    
    
    
    ofPopStyle();
    
    //draw kinect stuff
    contourFinder.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    
//    for(int i = 0; i < contourFinder.blobs.size(); i++){
//        ofPushStyle();
//        ofSetColor(255, 0, 0);
//        float thisX = ofMap(contourFinder.blobs[i].centroid.x, 0, kinect.width, 0, ofGetWindowWidth());
//        float thisY = ofMap(contourFinder.blobs[i].centroid.y, 0, kinect.height, 0, ofGetWindowHeight());
//        ofCircle(thisX, thisY, 10);
//        
////        ofNoFill();
////        ofCircle(thisX, thisY, disturbRad);
//        
//        
//        ofPopStyle();
//    }
    
    
    
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
    float randomScatter = 30;
    
    randomPerl = ofRandom(1000);
    
    float perlinScale = 0.005;
    
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
                    
                    //add to x pos to center them in window
//                    p.pos.x += ofGetWindowWidth()/2 - ofGetWindowHeight()/2;
                    pList.push_back(p);
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