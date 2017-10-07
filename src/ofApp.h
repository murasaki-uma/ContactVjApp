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


class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void drawFboTest();
	void drawFboTrailsTest();

	void setupGui();
	void drawGui(ofEventArgs & args);

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
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
	int width = 1920 * 2;
	int height = 1080;

	ofEasyCam camera;

	LogoMotion l;
	CirclePattern01 circle01;

	WaveLines wavelines;
	NoiseLine noiseline;
	NoiseLine noiseline02;
	AudioReactiveLine arline;
	AudioReactiveLine arline02;
	DarkBall darkball;
	NoiseWalker noisewalker;
	NoiseField field;



	// gui

	ofxOscParameterSync sync;
	ofParameter<bool> fullScreen;
	ofParameter<ofVec2f> fboWH;
	ofParameter<float> fboYposition;
    ofParameter<float> fboXposition;
	ofParameter<float> fboMainZposition;
	ofParameter<float> fboAlphaZposition;
	ofParameter<bool> fboMain;
	ofParameter<bool> fboAlpha;
	ofParameter<bool> drawLogo;
	ofParameter<bool> drawRipple;
	ofParameter<bool> drawLineParticle;
	ofParameter<bool> drawAudioLine;
	ofParameter<bool> drawLineParticle02;
	ofParameter<bool> drawDarkball;
	ofParameter<bool> drawField;
	ofParameter<bool> drawWaveLine;
	ofParameter<bool> drawNoiseWalker;
	ofParameter<int> clearAlpha;
	ofParameter<int> mainAlpha;
	ofParameter<int> alphaAlpha;

	ofParameter<bool> logoRotate;
	ofParameter<bool> logoStart;
	ofParameter<bool> drawNoReactLine;

	ofVec3f mainFboPos = ofVec3f(0, 0, 0);
	ofVec3f alphaFboPos = ofVec3f(0, 0, 0);
ofParameter<float> volField;
    ofParameter<float> volLine;




	//    ofxOscParameterSync sync;


	ofParameterGroup parameters_fbo;
	ofParameterGroup parameters_main;
	ofParameterGroup parameters_alpha;
	ofParameterGroup animationSettings;
	ofParameterGroup parameters;
	ofxPanel gui;

};
