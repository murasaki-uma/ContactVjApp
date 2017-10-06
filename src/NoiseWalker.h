//
//  NoiseWarker.hpp
//  CONTACT_VJApp
//
//  Created by 岩城勇磨 on 10/6/17.
//
//

#ifndef NoiseWalker_hpp
#define NoiseWalker_hpp

#include <stdio.h>
#include "ofMain.h"
class NoiseWalker {
public:
    int vertsNum = 200;
    ofVboMesh walker;
    float time = 0.0;
    float width = 30;
    vector<ofVec3f> baseVec;
    ofVec3f restartPos;
    
    NoiseWalker()
    {
        
    }
    
    void setup()
    {
        for(int x = 0; x < vertsNum; x++)
        {
            for(int i = 0; i < 2; i++)
            {
                float rad = ofRandom(PI*2);
                ofVec3f p =ofVec3f(cos(rad) * width, sin(rad) * width, 0 );
                walker.addVertex(p);
                walker.addVertex(p);
                walker.addColor(ofFloatColor(1.0));
                walker.addColor(ofFloatColor(1.0));
                baseVec.push_back(p.normalize());
            }
        }
        
        
        walker.setMode(OF_PRIMITIVE_LINES);
        restartPos = ofVec3f(0,0,0);
    }
    
    void update()
    {
        time += 0.01;
        float scale= 0.1;
        
        restartPos.x = width*cos(time);
        restartPos.y = width*sin(time);
        for(int i = 0; i < walker.getVertices().size(); i+=2)
        {
            float rad = ofRandom(PI*2);
            ofVec3f p = walker.getVertices()[i];
            
            ofVec3f _p = p;
            
            float nx = ofNoise(p.x*scale,p.y*scale,time);
            float ny = ofNoise(p.y*scale,p.x*scale,time);
            ofVec3f noiseVec = ofVec3f(nx,ny,0).normalize();
            
            ofVec3f vec = (baseVec[i/2] * noiseVec)*ofNoise(p.x,p.y);
            p +=  vec;
            p.x += p.x*0.01;
            
            
            ofVec3f nextVec = p - _p;
            nextVec.normalize();
            
            
            float d= ofDist(p.x,p.y,0,0);
            if(d > 200)
            {
                
                float rad = ofRandom(PI*2);
                p =ofVec3f(cos(rad) * width, sin(rad) * width, 0 );
                nextVec = p;
                nextVec.normalize();
                baseVec[i/2] =nextVec;
            }
            
            
            walker.setVertex(i,p);
            walker.setVertex(i+1, p+nextVec*ofMap(d,0,100,0,4.0));
            
            
            
        }
        
        
    }
    
    void draw()
    
    {
        
        ofSetLineWidth(1);
        walker.draw();
    }
};
#endif /* NoiseWarker_hpp */
