//
//  LogoMotion.hpp
//  CONTACT_VJApp
//
//  Created by 岩城勇磨 on 9/26/17.
//
//

#ifndef LogoMotion_h
#define LogoMotion_h

#include <stdio.h>
#include "ofMain.h"
#include "LogoMotion.h"


class LogoMotion
{
public:
    
    float maxRadius = 30;
    float radius = 0;
    float radius02 = 0;
    float radius03 = 0;
    float linePi = -PI/2;
    int width = 1920 ;
    int height = 1080;
    bool isAnimationStart = false;
    
    
    float halfCircleMoveDist = 0;
    float midCircleMoveDist = 0;
    
    ofVboMesh waveLine;
//    ofVboMesh halfCircleBottomMesh;
    vector<ofVboMesh> circleMeshs;
    ofImage img_wave;
    ofVboMesh midCirleMesh;
    bool isRotate = false;
    float tween_rotate = 0.0;

    float pointsize = 1.0;
    float time = 0;
    bool isRipple = false;

    int cirleVertsNum = 100;
    int trailCircleNum = 3;
    vector<float> trailCircleScales;
    LogoMotion(){
        
        
    }
    
    void init()
    {
        
        img_wave.load("wave.png");
        
        
        for(int n = 0; n < trailCircleNum; n++)
        {
            ofVboMesh m;
            
            
            for(int i = 0; i < cirleVertsNum; i ++)
            {
                float p = PI*2/cirleVertsNum * i;
                m.addVertex(ofVec3f( cos(p) * maxRadius , sin(p) * maxRadius, 0 ));
                m.addColor(ofFloatColor(1,1,1));
                
            }
            
            trailCircleScales.push_back(0);
            
            m.setMode(OF_PRIMITIVE_LINE_LOOP);
            circleMeshs.push_back(m);
        }
        
        for(int i = 0; i < 51; i ++)
        {
            float p = PI*2/50 * i;
//            m.addVertex(ofVec3f( cos(p) * maxRadius , sin(p) * maxRadius, 0 ));
//            m.addColor(ofFloatColor(1,1,1));
//            
            
            midCirleMesh.addVertex(ofVec3f( cos(p) * maxRadius*0.65 , sin(p) * maxRadius*0.65, 0 ));
            midCirleMesh.addColor(ofFloatColor(1,1,1));
            
        
//            float tp;
            if(i <= 25)
            {
                float tp = PI/2 - i* (PI/25);
                waveLine.addVertex(ofVec3f( cos(tp) * radius/2 , maxRadius/2 + sin(tp) * maxRadius/2,0 ));
                waveLine.addColor(ofFloatColor(1,1,1));
            }
            
            if(i >= 25)
            {
                float tp = PI/2 + (i-25)* (PI/25);
                waveLine.addVertex(ofVec3f( cos(tp) * radius/2 , -maxRadius/2 +sin(tp) * maxRadius/2,0 ));
                waveLine.addColor(ofFloatColor(1,1,1));
            }
        }
        
        
        
        
        
        midCirleMesh.setMode(OF_PRIMITIVE_LINE_LOOP);
        waveLine.setMode(OF_PRIMITIVE_LINE_STRIP);
        
    }
    
    void update()
    {
        
        
        
        float trailsScaleTiming = 1.0/trailCircleScales.size();
        
        if(isRotate)
        {
            tween_rotate += (1.0-tween_rotate) * 0.02;
            time += 0.004;
        }
        
        if(isAnimationStart)
        {
            
            
            radius +=(maxRadius - radius) * 0.05;
            radius02 +=(maxRadius - radius02) * 0.03;
            radius03 +=(maxRadius - radius03) * 0.04;
            
            
            
            
            for(int i = 0; i < circleMeshs.size(); i++)
            {

                if(i == 0)
                {
                    if(time > trailsScaleTiming){
                        trailCircleScales[i] += 0.005;
                    };
                
                } else
                {
                    if(trailCircleScales[i-1] > trailsScaleTiming){
                        trailCircleScales[i] += 0.005;
                    };
                    
                }
                
                if(trailCircleScales[i] > 1.0)
                {
                    trailCircleScales[i] = 0.0;
                }
                
                for(int k = 0; k < cirleVertsNum; k ++)
                {
                    float p = PI*2/cirleVertsNum * k;
                    float r = maxRadius + maxRadius*0.1 * (ofNoise(k*0.1+i,time)*ofMap(time,0.0,1.0,0.0,1.0));
                    circleMeshs[i].setVertex(k, ofVec3f( cos(p) * r , sin(p) * r, 0 ));
                }
                
            }
            
            
            
            
            
            for(int i = 0; i < 51; i ++)
            {
                
                //            float tp;
                if(i <= 25)
                {
                    float tp = PI/2 - i* (PI/25);
                    waveLine.setVertex(i,ofVec3f( cos(tp) * radius02/2 , maxRadius/2 + sin(tp) * maxRadius/2,0 ));
//                    waveLine.setVertex(ofFloatColor(1,1,1));
                }
                
                if(i >= 25)
                {
                    float tp = PI/2 + (i-25)* (PI/25);
                    waveLine.setVertex(i,ofVec3f( cos(tp) * radius02/2 , -maxRadius/2 +sin(tp) * maxRadius/2,0 ));
//                    waveLine.addColor(ofFloatColor(1,1,1));
                }
            }
  
        }
        
        time = fmod(time,PI*4);
    }
    
    
    void click()
    {
        isAnimationStart = !isAnimationStart;
    }
    
    void draw()
    {
        
        ofSetLineWidth(4);
        
        

        ofSetColor(255);
        
        ofDrawCircle(0,0,pointsize);
        
        ofPushMatrix();
        
        ofRotateZ(time * -90);
        
        ofDrawLine(cos(linePi)*radius,sin(linePi)*radius,cos(linePi+PI)*radius,sin(linePi+PI)*radius);
        ofDrawCircle(cos(linePi)*radius,sin(linePi)*radius,pointsize);
        ofDrawCircle(cos(linePi+PI)*radius,sin(linePi+PI)*radius,pointsize);
        ofPopMatrix();
        
        ofPushMatrix();
        ofRotateZ(time * -55);
        ofRotateZ(-45*radius/maxRadius);
        
        ofDrawLine(cos(linePi)*radius,sin(linePi)*radius,cos(linePi+PI)*radius,sin(linePi+PI)*radius);
        ofDrawCircle(cos(linePi)*radius,sin(linePi)*radius,pointsize);
        ofDrawCircle(cos(linePi+PI)*radius,sin(linePi+PI)*radius,pointsize);
        ofPopMatrix();
        
        ofNoFill();
        ofPushStyle();
        ofScale((radius/maxRadius),(radius/maxRadius));
//        ofNofill();
        ofDrawCircle(0,0,0,maxRadius);
        ofPopStyle();
        
        ofPushMatrix();
        ofRotateZ(time * -90);
        ofRotateZ(-45*radius/maxRadius);
//        ofTranslate(0,radius/2);
        waveLine.draw();
        ofPopMatrix();
        
        
        
        ofPushMatrix();
        ofScale((radius/maxRadius),(radius/maxRadius));
        ofRotateZ(time * -100);
        ofTranslate(0,-maxRadius*0.35);
        midCirleMesh.draw();
        ofPopMatrix();
        

    }
    
    void drawRipple()
    
    {
        
        
//        for(int k = 0; k < 10; k++)
//        {
        ofPushMatrix();
        ofScale((radius/maxRadius),(radius/maxRadius));
//        
//            of
            for(int i = 0; i < circleMeshs.size(); i++)
            {
                
                ofPushMatrix();
                float s = 1;
                float t_s = trailCircleScales[i];
                ofScale(s+t_s,s+t_s);
                circleMeshs[i].draw();
                ofPopMatrix();
            }
        ofPopMatrix();
        
    }
};
#endif /* LogoMotion_hpp */