#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(100, 100, 100);
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    _imageWidth  = 80;
    _imageHeight = 60;
    
    _resImage = new ofxCvGrayscaleImage();
    _resImage->allocate(_imageWidth,_imageHeight);
    
    _receiver.setup("4000");
    
    // first, we need to set addresses for setting callback function for Liblo
    //_receiver.addAdress("/none", OFXLO_TYPE_NONE); // ToDo
    _receiver.addAdress("/int", OFXLO_TYPE_INT, 2);
    _receiver.addAdress("/float", OFXLO_TYPE_FLOAT, 2);
    _receiver.addAdress("/string", OFXLO_TYPE_STRING,2);
    _receiver.addAdress("/blob", OFXLO_TYPE_BLOB);
    
    // start server.
    _receiver.start();
}

//--------------------------------------------------------------
void ofApp::update()
{
    while(_receiver.hasWaitingMessages())
    {
    	ofxLoMessage m;
    	_receiver.getNextMessage(&m);
        
    	if(m.getAddress() == "/int")
    	{
    		int i1 = m.getArgAsInt(0);
    		int i2 = m.getArgAsInt(1);
    		
            std::cout << "int param 1: " << i1 << std::endl;
    		std::cout << "int param 2: " << i2 << std::endl;
    	}
    	else if(m.getAddress() == "/float")
    	{
    		float f1 = m.getArgAsFloat(0);
    		float f2 = m.getArgAsFloat(1);
    		
            std::cout << "float param 1: " << f1 << std::endl;
    		std::cout << "float param 2: " << f2 << std::endl;
    	}
    	else if(m.getAddress() == "/string")
    	{
    		std::string s1 = m.getArgAsString(0);
    		std::string s2 = m.getArgAsString(1);
    		
            std::cout << "string param 1: " << s1 << std::endl;
    		std::cout << "string param 2: " << s2 << std::endl;
    	}
    	else if(m.getAddress() == "/blob")
    	{
    		unsigned char* pixels = m.getArgAsPixels(0);
    		_resImage->setFromPixels(pixels, _imageWidth,_imageHeight);
    	}
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    _resImage->draw(20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
