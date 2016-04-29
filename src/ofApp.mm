#include "ofApp.h"
#include "global.h"
bool globalBounce;
bool globalFriction;
ofTrueTypeFont fuente;
//--------------------------------------------------------------
void ofApp::setup(){
//    sound1.setMultiPlay(true);
    
    //sample.load(ofToDataPath("audio/PVCW1.wav"));
    //printf("Summary:\n%s", sample.getSummary());//get info on samples if you like.
//    
//    sound2.load("audio/PVC4.mp3");
    volume1=volume2=speed1=speed2=1;
    for(int a=0; a<tri.size();a++){
        tri[a].setup();
        
        tri[a].position(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()));
    }
    for(int a=0;a<4;a++){
        Button tbut;
        tbut.setup(a);
        but.push_back(tbut);
    }
    
    gravity=false;
    phase = 0;
    ofSoundStreamSetup(2, 0); // 2 output channels (stereo), 0 input channels
    ofxAccelerometer.setup();
    fuente.load("Arial.ttf",50);
}

//--------------------------------------------------------------
void ofApp::update(){
    accelerometer = ofxAccelerometer.getForce();
    accelerometer.y*=-1;
    for(int a=0; a<tri.size();a++){
        tri[a].update();
        if(gravity)
        tri[a].speed+=accelerometer;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int a=0; a<tri.size();a++){
        tri[a].draw();
    }
    for(int a=0; a<but.size();a++){
        but[a].draw();
    }
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch){
    
    int isButton=-1;
    for(int a=0; a<but.size();a++){
        if(but[a].touch(touch,touch.id)){
            isButton=a;
        }
    }
    if(isButton!=-1){
        buttonPressed(isButton);
    }else{
        bool isDrag=false;
        int oneDead=-1;
        for(int a=0; a<tri.size();a++){
            isDrag|=tri[a].touch(touch,touch.id);
            if(!tri[a].alive)
                oneDead=a;
        }
        Triangle newt;
        newt.setup();
        newt.position(touch);
        newt.touch(touch,touch.id);
        if(!isDrag){
            
            if(tri.size()>3&&oneDead!=-1){
                tri[oneDead]=newt;
            }else{
                if(tri.size()>8){
                    tri[0]=newt;
                }
                tri.push_back(newt);
                
            }
        }
    }
    
}
void ofApp::buttonPressed(int which){
    if(which==0){
        gravity=!gravity;
        but[0].toggled=gravity;
    }else if(which==1){
        bool are=but[1].toggled;
        globalBounce=!are;
        but[1].toggled=!are;
    }else if(which==2){
        bool are=but[2].toggled;
        globalFriction=!are;
        but[2].toggled=!are;
    }else if(which==3){
        while(tri.size()>0){
            tri.pop_back();
        }
    }
}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch){
    for(int a=0; a<tri.size();a++){
        tri[a].drag(touch,touch.id);
    }

}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch){
    for(int a=0; a<tri.size();a++){
        tri[a].touchup(touch,touch.id);
    }
}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void ofApp::lostFocus(){

}

//--------------------------------------------------------------
void ofApp::gotFocus(){

}

//--------------------------------------------------------------
void ofApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void ofApp::deviceOrientationChanged(int newOrientation){
    
}

void ofApp::audioOut( float * output, int bufferSize, int nChannels ) {
    int maxVoices=256;
    for(int i = 0; i < bufferSize * nChannels; i += 2) {
        ofVec2f val;
        val.x=0;
        val.y=0;
        for(int a=0; a<tri.size()&&a<maxVoices;a++){
            val+=tri[a].getSample()*0.1/tri.size();
        }
        
        output[i] = val.x; // writing to the left channel
        output[i+1] = val.y; // writing to the right channel
        
    }
}


