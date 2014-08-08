#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxLoSender.h"

class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
private:
    
    unsigned char * 	videoInverted;
    ofTexture			videoTexture;
    
    
    int _camWidth;
    int _camHeight;
    
    ofVideoGrabber _vidGrabber;
    
    ofxCvColorImage _videoImage;
    ofxCvGrayscaleImage _grayDiff;
    ofxCvGrayscaleImage _grayBG;
    ofxCvGrayscaleImage _grayImage;
    
    ofxLoSender _sender;
};
