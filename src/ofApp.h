#pragma once

#include "ofMain.h"
#include "LogoMotion.h"
#include "CirclePattern01.h"
#include "WaveLines.h"
#include "NoiseLine.h"
#include "AudioReactiveLine.h"

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
    int width = 1920 ;
    int height = 1080;
    
    ofEasyCam camera;
    
    LogoMotion l;
    CirclePattern01 circle01;
    
    WaveLines wavelines;
    NoiseLine noiseline;
    AudioReactiveLine arline;
};
