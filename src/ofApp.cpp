#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60); //target frame rate.
    ofBackground(66,66,66);
    
    //Init the video grabber
    videoGrabber.setVerbose(false);
    videoGrabber.initGrabber(videoGrabberWidth, videoGrabberHeight);

    //Init the video grabber
    mainFbo.allocate(videoGrabberWidth, videoGrabberHeight);
    
    //init the shader
    shader.load("shaders/shader.vert", "shaders/shader.frag");
    
    plane.set(videoGrabberWidth, videoGrabberHeight, 500, 500);
    plane.mapTexCoordsFromTexture(videoGrabber.getTextureReference());
}

//--------------------------------------------------------------
void ofApp::update(){
    videoGrabber.update();
}

//-------------------------------------------------------------
void ofApp::draw(){
    videoGrabber.getTextureReference().bind();
    
    shader.begin();
    
    ofPushMatrix();
    
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
    float percentY = mouseY / (float)ofGetHeight();
    percentY = ofClamp(percentY, 0, 1.f);
    //map the percent to be between -60 and 60 degrees
    float angle = ofMap(percentY, 0, 1, -60, 60);
    ofRotate(angle, 1, 0, 0);
    
    plane.drawWireframe();
    
    ofPopMatrix();
    shader.end();
    
//    videoGrabber.draw(0, 0);

    
    //Show the FPS
    ofSetColor(255);
    string msg = "fps: " + ofToString(ofGetFrameRate(), 2);
    ofDrawBitmapString(msg, 10, 20);
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
