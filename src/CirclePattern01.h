//
//  CirclePattern01.hpp
//  CONTACT_VJApp
//
//  Created by 岩城勇磨 on 9/26/17.
//
//


#ifndef CirclePattern01_h
#define CirclePattern01_h

#include <stdio.h>
#include "ofMain.h"
#include "CirclePattern01.h"


class CirclePattern01
{
public:
    int width = 1920 ;
    int height = 1080;

    CirclePattern01(){}
    
    void update()
    {
        ofSetColor(255);
        
        ofFill();
        
        
        ofTranslate(0, 0,-800);
        int l = 50;
        float harlfWidth = width/2;
        for(int k = 0; k < 10; k++)
        {
            
            ofPushMatrix();
            ofRotateZ(360 / 10 * k + ofGetElapsedTimef());
            for(int i = 0; i < l; i ++)
            {
                float x = -harlfWidth + harlfWidth/l * i;
                float y = sin(i * 0.2 + ofGetElapsedTimef()*0.5) * 200;
                y += ofNoise( 0.01 * x + ofGetElapsedTimef()*0.1) * 100;
                float z = cos(ofGetElapsedTimef() * i * 0.07) * (5 * (l-i)*0.1);
                ofDrawCircle(x, y, z+2);
            }
            
            ofPopMatrix();
        }

    }
    
    

    
    void draw()
    {
        
    }
};



#endif /* CirclePattern01_hpp */
