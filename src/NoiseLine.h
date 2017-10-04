//
//  NoiseLine.hpp
//  CONTACT_VJApp
//
//  Created by 岩城勇磨 on 10/3/17.
//
//

#ifndef NoiseLine_hpp
#define NoiseLine_hpp
#include <stdio.h>
#include "ofMain.h"

class NoiseLine
{
public:
    ofVboMesh points;
    ofVboMesh points_orgin;
    float width = 1920;
    float height = 1080;
    float xSize =20;
    float xstep = 10;
    float ystep = 6;
    float ySize = 20;
    float time = 0;
    vector<float> dists;
    NoiseLine()
    {
        
    }
    
    void setup()
    {
        
        for(int x = 0; x < xSize; x++)
        {
            for(int y = 0; y < ySize; y++)
            {
                for(int i = 0; i < 2; i++)
                {
                    ofVec3f p =ofVec3f(x*xstep-xSize*xstep/2,y*ystep-ySize*ystep/2,0);
                    points.addVertex(p);
                    points_orgin.addVertex(p);
                    points.addColor(ofFloatColor(1.0));
                    points_orgin.addColor(ofFloatColor(1.0));
                    dists.push_back(0.0);
                }
                
            }
        }
        
        points.setMode(OF_PRIMITIVE_LINES);
//        points_origin. = points;
    }
    
    void update()
    {
        
        time += 0.001;
        for(int i = 0; i < points.getVertices().size(); i+=2)
        {
            
            ofVec3f p = points.getVertices()[i];
            ofVec3f p_o = points_orgin.getVertices()[i];
            float scale = 0.01;
            ofVec3f n = ofVec3f(
                                ofNoise((p.x)*scale)-0.5,
                                ofNoise(p.y*scale)-0.5,
//                                ofNoise(time*4.0)-0.5
                                ofNoise(time)
                                );
            p+= n*0.5;
            points.setVertex(i,p);
            float distance = ofDist(p.x, p.y, p.z,p_o.x,p_o.y,p_o.z);
            if(distance > 30)
            {
                points.setVertex(i,points_orgin.getVertices()[i]);
                p = p_o;
                dists[i+1] = 0.0;
            }
            
            if(distance < 15)
            {
                dists[i+1] += 0.1;

            } else
            {
                dists[i+1] -= 0.1;

            }
            
            float d = ofNoise(ofVec3f(p.x*scale,p.y*scale,time));

            float center_d = ofMap(ofDist(p.x, p.y, p.z,0,0,0),0,100,0,3.0);
            p += n*dists[i+1]*center_d;
            
           
            points.setVertex(i+1,p);
            points.setColor(i,ofFloatColor(0,0,0));
            points_orgin.setColor(i+1,ofFloatColor(ofNoise(time),ofNoise(time),ofNoise(time)));
            
            
            
        }
    }
    
    void draw()
    {
        ofSetLineWidth(2);
        ofPushMatrix();
        ofRotate(sin(time)*90.0, sin(time), cos(time), cos(time*1.5));
//        ofTranslate(-xSize*xstep/2, -ySize*ystep/2);
        glPointSize(4);
        points.draw();
        ofPopMatrix();
    }
private:
};

#endif /* NoiseLine_hpp */
