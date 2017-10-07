//
//  NoiseField.hpp
//  CONTACT_VJApp
//
//  Created by 岩城勇磨 on 10/6/17.
//
//

#ifndef NoiseField_hpp
#define NoiseField_hpp

#include <stdio.h>

#include "ofMain.h"

class NoiseField {
public:
    int num  = 100;
    ofVboMesh field;
    float width = 400;
    float time = 0.0;
    
    float height = 150;
    NoiseField()
    {
        for(int x =0; x < num; x++)
        {
            for(int y = 0; y < num; y++)
            {
                float _x = float(x)/float(num) * width-width/2;
                float _y = float(y)/float(num) * height-height/2;
                ofVec3f p = ofVec3f(_x,_y,0);
                field.addVertex(p);
                field.addColor(ofColor(255));
            }
        }
        
        field.setMode(OF_PRIMITIVE_POINTS);
    }
    
    void setup()
    {
        
    }
    
    void update(float volume)
    {
        time += 0.001+volume;
        float scalex = sin(ofGetElapsedTimef()*0.05)*0.03;
        float scaley = cos(ofGetElapsedTimef()*0.05)*0.03;
        for(int i= 0; i < field.getVertices().size(); i++)
        {
            ofVec3f p = field.getVertices()[i];
            float n = ofNoise(p.x*scalex,p.y*scaley,time);
            
            field.setColor(i,ofFloatColor(n));
        }
    }
    
    void draw()
    {
        glPointSize(10);
        field.draw();
        
    }
};
#endif /* NoiseField_hpp */
