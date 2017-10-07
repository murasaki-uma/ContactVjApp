#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    
    parameters_fbo.setName("fbo settings");
    parameters_fbo.add(fboMain.set("main",true));
    parameters_fbo.add(fboAlpha.set("alpha",true));
    parameters_fbo.add(fboYposition.set("Y",300,0,ofGetHeight()));
    parameters_fbo.add(fboMainZposition.set("main Z",0,-200,200));
    parameters_fbo.add(fboAlphaZposition.set("alpha Z",0,-200,200));
    parameters_fbo.add(clearAlpha.set("clear alpha",15,0,255));
    parameters_fbo.add(mainAlpha.set("main alpha",15,0,255));
    parameters_fbo.add(alphaAlpha.set("alpha alpha",15,0,255));
    
    parameters_main.setName("main fbo");
    parameters_main.add(drawLogo.set("drawLogo",true));
    parameters_main.add(drawAudioLine.set("drawAudioLine",false));
    parameters_main.add(drawDarkball.set("drawDarkball",false));
    parameters_main.add(drawField.set("drawField",false));
    
    parameters_alpha.setName("alpha fbo");
    parameters_alpha.add(drawRipple.set("drawRipple",false));
    parameters_alpha.add(drawLineParticle.set("drawLineParticle",true));
    parameters_alpha.add(drawWaveLine.set("drawWaveLine",false));
    parameters_alpha.add(drawNoiseWalker.set("drawNoiseWalker",false));
//    parameters_fbo.add(drawField.set("drawField",false));
    
    animationSettings.setName("animation");
    animationSettings.add(logoRotate.set("logo rotate",false));
    animationSettings.add(logoStart.set("logo start",false));
    
    parameters.setName("settings");
    parameters.add(parameters_fbo);
    parameters.add(parameters_main);
    parameters.add(parameters_alpha);
    parameters.add(animationSettings);
    
    gui.setup(parameters);
    
    sync.setup((ofParameterGroup&)gui.getParameter(),6666,"localhost",6667);
    
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
    darkball.setup();
    noisewalker.setup();
    field.setup();
    
    
    
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
    
    sync.update();
    scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
    
    if(logoRotate)
    {
        l.isRotate = !l.isRotate;
        l.time = 0.0;
        
        logoRotate = false;
    }
    
    if(logoStart)
    {
        l.click();
        logoStart = false;
    }
    
    //lets record the volume into an array
    volHistory.push_back( scaledVol );
    
    //if we are bigger the the size we want to record - lets drop the oldest value
    if( volHistory.size() >= 400 ){
        volHistory.erase(volHistory.begin(), volHistory.begin()+1);
    }

    darkball.update();
    
    l.update();
    wavelines.update();
    noiseline.update();
    arline.update(float(scaledVol)*70.0);
    noisewalker.update();
    field.update(float(scaledVol)*1.0);
    
    mainFbo.begin();
    drawFboTest();
    mainFbo.end();
    
    rgbaFboFloat.begin();
    drawFboTrailsTest();
    rgbaFboFloat.end();
    
    
    mainFboPos += (ofVec3f(0,0,fboMainZposition)-mainFboPos) * 0.01;
    alphaFboPos += (ofVec3f(0,0,fboAlphaZposition)-alphaFboPos) * 0.01;
    
 
}

//--------------------------------------------------------------
void ofApp::drawFboTest(){
    
    
    camera.begin();
    ofPushMatrix();
    ofTranslate(mainFboPos);
    ofSetColor(0,0,0,255);
    ofDrawRectangle(-width/2,-height/2,width,height);
   
//    ofSetColor(0,0,0,0);
//    ofDrawRectangle(-width/2,-height/2,width,height);

    //    l.draw();
//    noiseline.draw();
//    if(drawField) 
    if(drawAudioLine) arline.draw();
//    if()
    if(drawDarkball) darkball.draw();
    if(drawField) field.draw();
    if(drawLogo) l.draw();
    ofPopMatrix();
    camera.end();
    
//    l.update();
    
}


void ofApp::drawFboTrailsTest(){
    camera.begin();
    ofPushMatrix();
    ofTranslate(alphaFboPos);
    ofSetColor(0,0,0, clearAlpha);
    ofDrawRectangle(-width/2,-height/2,width,height);
    ofNoFill();
    ofSetColor(255,255,255);

    if(drawRipple) l.drawRipple();
    if(drawWaveLine) wavelines.draw();
    if(drawNoiseWalker) noisewalker.draw();
    if(drawLineParticle)noiseline.draw();
    
//    l.drawRipple();
//    wavelines.draw();
//    noisewalker.draw();
    ofPopMatrix();
    camera.end();
    
    //    l.update();
    
}



//--------------------------------------------------------------
void ofApp::draw(){


    
    
    ofPushMatrix();
    ofTranslate(0, fboYposition);
//    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    
    
  
    
  
    
    
    if(fboMain)
    {
        //        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        ofSetColor(255,255,255,mainAlpha);
        mainFbo.draw(0,0,ofGetWidth(),ofGetHeight()/2);
    }
    
    
    if(fboAlpha)
    {
        ofSetColor(255,255,255,alphaAlpha);
        rgbaFboFloat.draw(0,0,ofGetWidth(),ofGetHeight()/2);
    }
    
    
    
    ofPopMatrix();
    
    
    gui.draw();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    
    
    
    
    if(key == 's') {
        gui.saveToFile("settings.xml");
    }
    if(key == 'l') {
        gui.loadFromFile("settings.xml");
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
