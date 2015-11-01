#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60); //target frame rate.
    ofBackground(66,66,66);
    
    if (useLiveVideoStream) {
        //Init the video grabber
        videoGrabber.setVerbose(false);
        videoGrabber.initGrabber(videoGrabberWidth, videoGrabberHeight);
    } else {
        //Init the video player
        videoPlayer.loadMovie("video.mp4");
        videoPlayer.play();
    }

    //Init the video grabber
    mainFbo.allocate(videoGrabberWidth, videoGrabberHeight);
    
    //init the shader
    shader.load("shaders/shader.vert", "shaders/shader.frag");
    
    plane.set(videoGrabberWidth, videoGrabberHeight, 100, 100);
    plane.mapTexCoordsFromTexture(videoGrabber.getTextureReference());
    
    sphere.setRadius(max(videoGrabberWidth, videoGrabberHeight) / 2.f);
}

//--------------------------------------------------------------
void ofApp::update(){
    if (useLiveVideoStream) {
        videoGrabber.update();
    } else {
        videoPlayer.update();
    }
    
    //calculate noise
    float noiseX = ofMap(mouseX, 0, ofGetWidth(), 0, 0.1);
    float noiseVel = ofGetElapsedTimef();
    float noiseStrength = 1;
    float noiseValue = ofNoise(noiseX, noiseVel) * noiseStrength;
    shader.setUniform1f("programNoise", noiseValue);
}


//-------------------------------------------------------------
void ofApp::draw(){
    if (useLiveVideoStream) {
        videoGrabber.getTextureReference().bind();
    } else {
        videoPlayer.getTextureReference().bind();
    }
    mainFbo.begin();
    ofColor centerColor = ofColor(85, 78, 68);
    ofColor edgeColor(0, 0, 0);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
    
    
    easyCam.begin();
    
    shader.begin();
    shader.setUniform1f("elapsedTime", ofGetElapsedTimef());
    ofPushMatrix();

//    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
    
//    float percentY = mouseY / (float)ofGetHeight();
//    percentY = ofClamp(percentY, 0, 1.f);
//    //map the percent to be between -60 and 60 degrees
//    float angle = ofMap(percentY, 0, 1, -60, 60);
//    ofRotate(angle, 1, 0, 0);
    
    plane.drawWireframe();
    
    ofPopMatrix();
    
    shader.end();
    
//    videoGrabber.draw(0, 0);
    easyCam.end();
    mainFbo.end();
    mainFbo.draw(0, 0);
    
    
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
