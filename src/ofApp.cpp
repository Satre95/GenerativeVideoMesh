#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60); //target frame rate.
    ofBackground(66,66,66);
    
    //Init the video grabber
    videoGrabber.setVerbose(true);
    videoGrabber.initGrabber(videoGrabberWidth, videoGrabberHeight);
    
    //iterate over the video pixels, creating a new spot for each one.
    cout << videoGrabber.getWidth() << "\n";
    cout << videoGrabber.getHeight() << "\n";
    
    for (int y = 0; y < videoGrabberHeight; y+= meshScaleY) {
        for (int x = 0; x < videoGrabberWidth; x+= meshScaleX) {
            //get the vertex at the pixel point
            ofVec3f tempVertex = ofVec3f(x * (1 / meshScaleX), y * (1 / meshScaleY), 0);
            videoMesh.addVertex(tempVertex);
            
            //get the color of the pixel
            
            ofFloatColor sampleColor(0, 0, 0);
            videoMesh.addColor(sampleColor);
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    videoGrabber.update();
    
    
    if (videoGrabber.isFrameNew()) {
        for (int i = 0; i < videoGrabberHeight * videoGrabberWidth; i++) {
            ofFloatColor sampleColor(videoGrabber.getPixels()[i*3]/255.f * (1 / meshScaleY) * (1 / meshScaleX),				// r
                                     videoGrabber.getPixels()[i*3+1]/255.f * (1 / meshScaleY) * (1 / meshScaleX),			// g
                                     videoGrabber.getPixels()[i*3+2]/255.f * (1 / meshScaleY) * (1 / meshScaleX));			// b
            
            //now we get the vertex aat this position
            ofVec3f tmpVec = videoMesh.getVertex(i);
            videoMesh.setVertex(i, tmpVec); //so far this is redundant, but it will not be soon.
            
            videoMesh.setColor(i, sampleColor);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    camera.begin();
    
    //    ofDisableDepthTest();
    //    videoGrabber.draw(0, -videoGrabberHeight);
    //    ofEnableDepthTest();
    
    videoMesh.drawWireframe();
    //    videoMesh.drawFaces();
    
    camera.end();
    
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
