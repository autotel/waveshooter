#pragma once
#include "global.h"
class Triangle{
public:
    float rotation, rotationSpeed,radius,volume;
    int dragging,samplesPerUpdate,samplesCount,envelopeTimer;
    ofVec2f pos,speed,prevPos,prevSpeed,posportion,screenSize;
    ofSoundPlayer sample;
    double phase, speedValue;
    bool alive,friction,harmonize;
    int name;
    
    void setup(){//ofSoundPlayer tsample
        //sample.load(ofToDataPath("audio/PVCW1344.wav"));//load in your samples. Provide the full path to a wav file.
        phase=0;
        rotation=0;
        rotationSpeed=ofRandom(4);
        radius=32;
        pos.x=0;
        pos.y=0;
        speed.x=0;
        speed.y=0;
        prevPos.x=0;
        prevPos.y=0;
        dragging=-1;
        //sample=tsample;
        //sample.play();
        alive=true;
        //count how many audio samples happen between each update
        samplesPerUpdate=1;
        samplesCount=0;
        envelopeTimer=0;
        screenSize.x=ofGetWidth();
        screenSize.y=ofGetHeight();
        //globalBounce;
        friction=true;
        harmonize=false;
        volume=1;
        
    }
    void update(){
        samplesPerUpdate=samplesCount;
        samplesCount=0;
        if(dragging==-1){
            pos+=speed;
        }
        posportion.x=pos.x/screenSize.x;
        posportion.y=pos.y/screenSize.y;
       // alive=!(abs(speed.x)<0.01&&dragging==-1);
        alive=(abs(speed.x)>0.01&&volume>0.001)||dragging!=-1;
        prevSpeed=speed;
        //printf("\nAlive:%d, vol:%f",alive,volume);

        speed=pos-prevPos;
        speedValue=speed.length();
//        sample.setSpeed(speed.x*4-1);
        //float h=ofGetHeight();
        //printf("\npan:%f",(pos.y-h/2)/h);
        //would be awesome to disphaze the l and r channels to make doppler space.
        //sample.setPan((pos.y-h/2)/h);
        prevPos=pos;
        if(globalBounce){
            if(pos.x>ofGetWidth()){
                speed.x=-1*speed.x;
            }else if(pos.x<0){
                speed.x=-1*speed.x;
            }
            if(pos.y>ofGetHeight()){
                speed.y=-1*speed.y;
            }else if(pos.y<0){
                speed.y=-1*speed.y;
            }
        }
        volume=2*max(0.00,1-max(abs(posportion.x-0.5),abs(posportion.y-0.5)));//a fake and lighter pithagorean distance
    }
    void draw(){
        //if it is being held under finger
        if(dragging!=-1){
            ofSetColor(240);
            position(pos);
        }else{
            ofSetColor(255);
        }
        if(!alive){
            ofSetColor(0);
        }
        ofPushMatrix();
        ofTranslate(pos.x,pos.y);
        ofRotate(rotation);
        ofSetCircleResolution(7);
        ofDrawCircle(0, 0, radius);
        
        ofPopMatrix();
        
    }
    void position(int posx,int posy){
        ofVec2f npos;
        npos.x=posx;
        npos.y=posy;
        position(npos);
        
    };
    void position(ofVec2f npos){
        pos=npos;
    };
    bool touch(ofVec2f touch,int n){
        if(dragging==-1){
            if(ofDist(touch.x,touch.y,pos.x,pos.y)<radius*2){
                dragging=n;
                return true;
            }else{
                dragging=-1;
                return false;
            }
        }else{
            return false;
            
        }
    };
    void drag(ofVec2f touch, int n){
        if(dragging==n)
            position(touch);
    };
    void touchup(ofVec2f touch, int n){
        if(dragging==n)
            dragging=-1;
    };
    ofVec2f getSample(){
        ofVec2f  sample;

        
            volume*=min(100,envelopeTimer)/100.00;
            
            sample.x=sin(phase+(posportion.y-1))*(posportion.y-1)*volume;
            sample.y=sin(phase+(posportion.y))*(posportion.y)*volume;
            if(dragging==-1){
                envelopeTimer++;
                if(harmonize) {
                    phase += pow(round(speedValue)/96,2);
                    //phase += pow(2,floor(speedValue*12)/1200)*80;
                    
                }else{
                    phase += pow(speedValue/96,2);
                    //phase+=0.1;
                }
            }
            if(globalFriction){
                speed=speed*0.99999;
            }
            //now I can interpolate speed for a better dragging freq change
            //speed=prevSpeed/samplesPerUpdate;
            
            samplesCount++;
        return sample;
        
    }
};