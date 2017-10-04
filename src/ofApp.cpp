#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    mainFbo.allocate(width, height, GL_RGBA);
    rgbaFboFloat.allocate(width, height, GL_RGBA );
    
    mainFbo.begin();
    ofClear(255,255,255, 0);
    mainFbo.end();
    
    
    rgbaFboFloat.begin();
    ofClear(255,255,255, 0);
    rgbaFboFloat.end();
    
    ofEnableDataPath();
    ofEnableSmoothing();
    ofSetCircleResolution(50);
    camera.setDistance(100);

    l.init();
    wavelines.init();
    
    noiseline.setup();
    arline.setup();
    
    
    
    
    soundStream.printDeviceList();
    
    //if you want to set a different device id
    //soundStream.setDeviceID(0); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
    
    int bufferSize = 256;
    
    
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    volHistory.assign(400, 0.0);
    
    bufferCounter	= 0;
    drawCounter		= 0;
    smoothedVol     = 0.0;
    scaledVol		= 0.0;
    
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    
    //lets record the volume into an array
    volHistory.push_back( scaledVol );
    
    //if we are bigger the the size we want to record - lets drop the oldest value
    if( volHistory.size() >= 400 ){
        volHistory.erase(volHistory.begin(), volHistory.begin()+1);
    }

    
    
    l.update();
    wavelines.update();
    noiseline.update();
    arline.update(float(scaledVol)*70.0);
    
    mainFbo.begin();
    drawFboTest();
    mainFbo.end();
    
    rgbaFboFloat.begin();
    drawFboTrailsTest();
    rgbaFboFloat.end();
    
 
}

//--------------------------------------------------------------
void ofApp::drawFboTest(){
    
    
    camera.begin();
    ofSetColor(0,0,0,255);
    ofDrawRectangle(-width/2,-height/2,width,height);
    ofSetColor(0,0,0,0);
    ofDrawRectangle(-width/2,-height/2,width,height);
//    l.draw();
//    noiseline.draw();
    arline.draw();
//    l.draw();

    camera.end();
    
//    l.update();
    
}


void ofApp::drawFboTrailsTest(){
    camera.begin();
    ofSetColor(0,0,0, 15);
    ofDrawRectangle(-width/2,-height/2,width,height);
    ofNoFill();
    ofSetColor(255,255,255);

    
//    l.drawRipple();
//    wavelines.draw();
    
    camera.end();
    
    //    l.update();
    
}



//--------------------------------------------------------------
void ofApp::draw(){


    ofSetColor(255,255,255);
    mainFbo.draw(0,0,ofGetWidth(),ofGetHeight());
    rgbaFboFloat.draw(0,0,ofGetWidth(),ofGetHeight());
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if(key == 'r')
    {
        l.isRotate = true;
        l.time = 0.0;
    }
}

void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    float curVol = 0.0;
    
    // samples are "interleaved"
    int numCounted = 0;
    
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (int i = 0; i < bufferSize; i++){
        left[i]		= input[i*2]*0.5;
        right[i]	= input[i*2+1]*0.5;
        
        curVol += left[i] * left[i];
        curVol += right[i] * right[i];
        numCounted+=2;
    }
    
    //this is how we get the mean of rms :)
    curVol /= (float)numCounted;
    
    // this is how we get the root of rms :)
    curVol = sqrt( curVol );
    
    smoothedVol *= 0.93;
    smoothedVol += 0.07 * curVol;
    
    bufferCounter++;
    
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    l.click();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
