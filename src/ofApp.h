#pragma once

#include "ofMain.h"
#include "LogoMotion.h"
#include "CirclePattern01.h"
#include "WaveLines.h"
#include "NoiseLine.h"
#include "AudioReactiveLine.h"
#include "DarkBall.h"
#include "NoiseWalker.h"
#include "NoiseField.h"
#include "ofxGui.h"
#include "ofxOscParameterSync.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void drawFboTest();
        void drawFboTrailsTest();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	void audioIn(float * input, int bufferSize, int nChannels);
    ofSoundStream soundStream;
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    
    int 	bufferCounter;
    int 	drawCounter;
    
    float smoothedVol;
    float scaledVol;
    
    
    ofFbo mainFbo;
    ofFbo rgbaFboFloat;
    int width = 1920*2 ;
    int height = 1080;
    
    ofEasyCam camera;
    
    LogoMotion l;
    CirclePattern01 circle01;
    
    WaveLines wavelines;
    NoiseLine noiseline;
    AudioReactiveLine arline;
    DarkBall darkball;
    NoiseWalker noisewalker;
    NoiseField field;
    
    
    
    // gui
    
    ofxOscParameterSync sync;
    ofParameter<float> fboYposition;
    ofParameter<float> fboMainZposition;
    ofParameter<float> fboAlphaZposition;
    ofParameter<bool> fboMain;
    ofParameter<bool> fboAlpha;
    ofParameter<bool> drawLogo;
    ofParameter<bool> drawRipple;
    ofParameter<bool> drawLineParticle;
    ofParameter<bool> drawAudioLine;
    ofParameter<bool> drawDarkball;
    ofParameter<bool> drawField;
    ofParameter<bool> drawWaveLine;
    ofParameter<bool> drawNoiseWalker;
    ofParameter<int> clearAlpha;
    ofParameter<int> mainAlpha;
    ofParameter<int> alphaAlpha;
    
    ofParameter<bool> logoRotate;
    ofParameter<bool> logoStart;
    
    ofVec3f mainFboPos = ofVec3f(0,0,0);
    ofVec3f alphaFboPos = ofVec3f(0,0,0);
    
    
    

    
//    ofxOscParameterSync sync;
    
    
    ofParameterGroup parameters_fbo;
    ofParameterGroup parameters_main;
    ofParameterGroup parameters_alpha;
    ofParameterGroup animationSettings;
    ofParameterGroup parameters;
    ofxPanel gui;
    
};
