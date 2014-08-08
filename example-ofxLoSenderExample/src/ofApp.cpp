#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(0, 0, 150);
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    _camWidth  = 80;
    _camHeight = 60;
    
    _vidGrabber.setDesiredFrameRate(30);
	_vidGrabber.initGrabber(_camWidth,_camHeight);
    
    _videoImage.allocate(_camWidth,_camHeight);
    _grayImage.allocate(_camWidth,_camHeight);
    
    _sender.setup("127.0.0.1", "4000");
}

//--------------------------------------------------------------
void ofApp::update()
{
	_vidGrabber.update();
    
    if(_vidGrabber.isFrameNew())
    {
        _videoImage.setFromPixels(_vidGrabber.getPixels(),_camWidth,_camHeight);
        _grayImage = _videoImage;
	}
}
//--------------------------------------------------------------
void ofApp::draw()
{
    ofSetColor(ofColor::white);
    
    _grayImage.draw(20, 20);
    
    unsigned char* pixels  = _grayImage.getPixels();
    int size = _camWidth*_camHeight;
    
    // send a message with a gray-scale image
    ofxLoMessage m;
    m.setAddress("/blob");
    m.addBlobArg(size, pixels);
    _sender.sendMessage(m);

    ofDrawBitmapString("PRESS 'n' to send int.", 20, 150);
    ofDrawBitmapString("PRESS 'i' to send int.", 20, 150);
    ofDrawBitmapString("PRESS 'f' to send float.", 20, 170);
    ofDrawBitmapString("PRESS 's' to send string.", 20, 190);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if(key == 'i')
	{
		ofxLoMessage m;
		m.setAddress("/int");
		m.addIntArg(199);
		m.addIntArg(1456);
		_sender.sendMessage(m);
	}
	else if(key == 'f')
	{
		ofxLoMessage m;
		m.setAddress("/float");
		m.addFloatArg(1.2222);
		m.addFloatArg(5.1111);
		_sender.sendMessage(m);
	}
	else if(key == 's')
	{
		ofxLoMessage m;
		m.setAddress("/string");
		m.addStringArg("hello");
		m.addStringArg("konnichiwa");
		_sender.sendMessage(m);
	}
    else if(key == 'n')
	{
		ofxLoMessage m;
		m.setAddress("/none");
		_sender.sendMessage(m);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
