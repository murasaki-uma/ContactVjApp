//
//  AudioReactiveLine.hpp
//  CONTACT_VJApp
//
//  Created by 岩城勇磨 on 10/4/17.
//
//

#ifndef AudioReactiveLine_hpp
#define AudioReactiveLine_hpp
#include <stdio.h>
#include "ofMain.h"

class AudioReactiveLine{
public:
    
    vector<ofVboMesh> lines;
	vector<ofVboMesh> noreactLines;
    float width = 1920;
    float height = 1080;
    float xSize =200;
    float xstep = 2;
    float ystep = 6;
    float ySize = 20;
    float time = 0;

    AudioReactiveLine()
    {
        
    }
    
    void setup()
    {
        
        for(int i = 0; i < 6; i++)
        {
            ofVboMesh l;
            
            for(int x = 0; x <= xSize; x++)
            {
                ofVec3f p =ofVec3f(x*xstep-xSize*xstep/2,0,0);
                l.addVertex(p);
                l.addColor(ofFloatColor(1.0));
            }
            
            l.setMode(OF_PRIMITIVE_LINE_STRIP);
            
            lines.push_back(l);
			noreactLines.push_back(l);
        }
    }
    
    void update(float volume)
    {
        time += 0.01;
        
        for(int i = 0; i < lines.size(); i++)
        {
			
            for(int k = 0; k < lines[i].getVertices().size(); k++)
            {
				
                ofVec3f p = lines[i].getVertices()[k];
                
				float dist = ofMap( ofDist(p.x,p.y,p.z,0,0,0),0,100,5,0);
                float scale = 0.01;
                ofVec3f n = ofVec3f(
                                    ofNoise((p.x)*scale)-0.5,
                                    ofNoise(p.x*scale,time, i*0.4)-0.5,
                                    ofNoise(p.x*scale,time*0.8, i*0.6)-0.5
                                    );
                
                lines[i].setVertex(k,ofVec3f(p.x,n.y*dist*volume,n.z*dist));
   
            }
       
		}
        
    }
    
    void draw(bool noreactlines)
    {
        ofPushStyle();
        ofSetLineWidth(3);
        
        for(int i = 0; i < lines.size(); i++)
        {
            ofPushMatrix();
            cout << i*10-25 << endl;
            ofTranslate(0,i*10-20);
			if (noreactlines) {
				noreactLines[i].draw();
			}
            lines[i].draw();
            ofPopMatrix();
        }
        ofPopStyle();
    }
};

#endif /* AudioReactiveLine_hpp */
