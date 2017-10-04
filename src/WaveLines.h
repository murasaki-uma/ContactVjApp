//
//  WaveLines.hpp
//  CONTACT_VJApp
//
//  Created by 岩城勇磨 on 9/28/17.
//
//

#ifndef WaveLines_hpp
#define WaveLines_hpp

#include <stdio.h>
#include "ofMain.h"
//#include Wave

class WaveLines {
public:
    WaveLines()
    {
        
    }
    
    vector<ofVboMesh> waves;
    vector<ofVec3f> translatePos;
    float radius = 0;
    float maxRadius = 30;
    float time = 0.0;
    int lineNum = 40;
    void init()
    {
        
        
        for(int n = 0; n < lineNum; n++)
        {
            
            ofVboMesh vbomesh;
            
            
            for(int i = 0; i < 50; i ++)
            {            //            float tp;
                
//                float s = ofN
                float step = 0.1 + ofNoise(n*0.1)*0.3;
                vbomesh.addVertex(ofVec3f( sin(i*step) * maxRadius/2, ofMap(i,0,50, -100,100), sin(i*step) * maxRadius/3));
                
                float color = sin(PI/50*i);
                vbomesh.addColor(ofFloatColor(color,color,color));
            }
            
            vbomesh.setMode(OF_PRIMITIVE_LINE_STRIP);
            translatePos.push_back(ofVec3f(ofMap(n,0,lineNum,-300,300), 0,0));
            
            waves.push_back(vbomesh);

        }
        
        
        
        
    }
    void update()
    
    {
        
        time += 0.002+ofNoise(time)*0.01;
        
        for(int n = 0; n < lineNum; n++)
        {
            
            for(int i = 0; i < 50; i ++)
            {
                //                float s = ofN
                
                float scale = ofNoise(time);
                scale = ofMap(scale,0.0,1.0,0.3,1.2);
                float step = 0.1 + ofNoise(n*0.1 + time)*0.3;
                waves[n].setVertex(i, ofVec3f( sin(i*step+cos(time*0.3)*0.05) * maxRadius/2*scale, ofMap(i,0,50, -80,80), sin(i*step) * maxRadius/3));
//                waves[n].setVertex(n, ofFloatColor(1,1,1));
            
//            vbomesh.setMode(OF_PRIMITIVE_LINE_STRIP);
            }
//            waves.push_back(vbomesh);
            
            translatePos[n].x += 0.3;
            if(translatePos[n].x >= 300)
            {
                translatePos[n].x = -300;
            }
            
        }

        
    }
    
    void draw()
    {
        ofSetLineWidth(4);
        ofPushMatrix();
        ofRotate(sin(time*0.1)*180.0, sin(time), cos(time), cos(time*1.5));
        
            for(int i = 0; i < waves.size(); i++)
            {
                ofPushMatrix();
                ofTranslate(translatePos[i]);
                waves[i].draw();
                ofPopMatrix();
            }
        
//        }
        ofPopMatrix();
        
    }
    
    
private:
    
};

#endif /* WaveLines_hpp */
