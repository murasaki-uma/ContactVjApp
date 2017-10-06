//
//  DarkBall.hpp
//  CONTACT_VJApp
//
//  Created by 岩城勇磨 on 10/5/17.
//
//

#ifndef DarkBall_hpp
#define DarkBall_hpp

#include <stdio.h>
#include "ofMain.h"

class DarkBall
{
public:
    ofVboMesh ball;
    vector <ofVboMesh> lines;
    float width = 30;
    
    float time = 0.0;
    DarkBall()
    {
        
    }
    
    void setup()
    {
        int vertsNum = 80;
        ball.addVertex(ofVec3f(0,0,0));
        ball.addColor(ofColor(0));
        for(int i = 0; i <= vertsNum; i++)
        {
            float p = PI*2 / vertsNum * i;
            float x = width * cos(p);
            float y = width * sin(p);
            
            ofVec3f point = ofVec3f(x,y,0);
            
            ball.addVertex(point);
            ball.addColor(ofColor(0));
        }
//        
//        ball.addVertex(ball.getVertices()[vertsNum]);
//        ball.addColor(ofColor(0));

        
        ball.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
        
        
        
        for(int j = 0; j < 30; j++){
            ofVboMesh l;
            
            for(int i = 0; i <= vertsNum; i++)
            {
                float p = PI*2 / vertsNum * i;
                float x = width*0.8 * cos(p);
                float y = width*0.8 * sin(p);
                
                ofVec3f point = ofVec3f(x,y,0);
                
                l.addVertex(point);
                l.addColor(ofColor(0));
            }
            l.setMode(OF_PRIMITIVE_LINE_LOOP);
            
            lines.push_back(l);
        }
    }
    
    void update()
    {
        time += 0.01;
        float scale = 0.05;
        float radiusscale = 0.1;
        for(int k = 0; k < lines.size(); k++){
            radiusscale *= 1.1;
            for(int i = 0; i < lines[k].getVertices().size(); i++)
            {
                float kn = ofNoise(k);
                ofVec3f point = lines[k].getVertices()[i];
                float n = ofNoise(k*scale,time);
                float n2 = ofNoise(point.x*scale,point.y*scale,time*scale*k);
                float p = PI*2 / lines[k].getVertices().size() * i;
                
                float x = (width*0.9+6*n2-3+radiusscale) * cos(p+kn);
                float y = (width*0.9+6*n2-3+radiusscale) * sin(p+kn);
                
                lines[k].setVertex(i,ofVec3f(x,y,0));
//                lines[k].addColor(ofColor(0));
            }
        }
        
        
        
        scale = 0.03;
        for(int i = 0; i < ball.getVertices().size(); i++)
        {
            float p = PI*2 / ball.getVertices().size() * i;
            ofVec3f v = ball.getVertices()[i];
            float n = ofNoise(v.x*scale,v.y*scale,time*0.5);
            float x = (width*0.95+6*n-3) * cos(p);
            float y = (width*0.95+6*n-3) * sin(p);
            
            ofVec3f point = ofVec3f(x,y,0);
            
            ball.setVertex(i,point);
//            ball.addColor(ofColor(0));
        }
    }
    
    void draw()
    {
        ofBackground(255);
        ball.draw();
//        ofFill();
//        ofSetColor(0);
        ofSetLineWidth(1);
        
        for(int i = 0; i < lines.size(); i ++)
        {
         lines[i].draw();
        }
        
    }
    
};

#endif /* DarkBall_hpp */
