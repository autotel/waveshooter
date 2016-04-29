#pragma once

#include "ofxiOS.h"
#include "Triangle.h"
#include "Button.h"



class ofApp : public ofxiOSApp {
	
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    void touchDoubleTap(ofTouchEventArgs & touch);
    void touchCancelled(ofTouchEventArgs & touch);
    void lostFocus();
    void gotFocus();
    void gotMemoryWarning();
    void deviceOrientationChanged(int newOrientation);
    void audioOut( float * output, int bufferSize, int nChannels );
    void buttonPressed(int which);
    int startSound();


    int triangles=24;
    vector <Triangle> tri;
    vector <Button> but;
    float volume1, volume2, speed1, speed2;
    ofVec2f screenSize, accelerometer;
    bool gravity;
    double phase;

};


