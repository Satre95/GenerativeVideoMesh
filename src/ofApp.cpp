#include "ofApp.h"

using namespace ofxCv;
using namespace cv;


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60); //target frame rate.
    ofBackground(66,66,66);
    
    videoGrabberHeight = ofGetHeight();
    videoGrabberWidth = ofGetWidth();
    

    //Init the video grabber
    videoGrabber.setVerbose(false);
    videoGrabber.initGrabber(videoGrabberWidth, videoGrabberHeight);

    //Load the default image, used in the case that videograbber doesn't work correctly.
    defaultImage.load("defaultImage.jpg");
    
    //Init the video grabber
    cvObjectsFbo.allocate(ofGetWidth(), ofGetHeight());
    
    //init the shader
    shader.load("shaders/shader.vert", "shaders/shader.frag");
    
    
    faceFinder.setup("haarcascade_frontalface_default.xml");
//    faceFinder.setup("haarcascade_lowerbody.xml");
    faceFinder.setPreset(ObjectFinder::Fast);
    faceImage.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
    
    //Set up the array of recognized objects that will be drawn.
    for (int i = 0; i < MAX_NUMBER_OF_RECOGNIZED_OBJECTS; i++) {
        recognizedObjects.push_back(RecognizedObject("shaders/shader.vert", "shaders/shader.frag"));
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    videoGrabber.update();
    if (videoGrabber.isFrameNew()) {
        faceFinder.update(videoGrabber);
        if (faceFinder.size() > 0) {
            for( int i = 0; i < faceFinder.size(); i++ ) {
                cv::Rect roi = toCv(faceFinder.getObject(i));
                Mat camMat = toCv(videoGrabber);
                recognizedObjects[i].updateImageWithObjectRectFromCamera(roi, camMat);
            }
            
        }
    }

    
    numberOfRecognizedObjects = faceFinder.size();
    ofLogNotice() << "Recognized Objects: " << numberOfRecognizedObjects << "\n";
    
//    scale = readScaleFromSerialPort();
    
    //calculate noise
    float noiseX = ofMap(mouseX, 0, ofGetWidth(), 0, 0.1);
    float noiseVel = ofGetElapsedTimef();
    float noiseStrength = 1;
    float noiseValue = ofNoise(noiseX, noiseVel) * noiseStrength;
    shader.setUniform1f("programNoise", noiseValue);
}


//-------------------------------------------------------------
void ofApp::draw(){

    cvObjectsFbo.begin();
    ofClear(0, 0, 0);
    ofColor centerColor = ofColor(85, 78, 68);
    ofColor edgeColor(0, 0, 0);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);

//    videoGrabber.draw(0, 0, ofGetWidth(), ofGetHeight());


//    faceFinder.draw();
//    faceImage.draw(0, 0);
    for (int i = 0; i < numberOfRecognizedObjects; i++) {
//        recognizedObjects[i].draw();
        recognizedObjects[i].drawWithShader();
    }
    cvObjectsFbo.end();
    
    cvObjectsFbo.draw(0, 0);
    
    
    //Show the FPS
    ofSetColor(255);
    string msg = "FPS: " + ofToString(ofGetFrameRate(), 2);
    ofDrawBitmapString(msg, 10, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's' || key == 'S') {
        ofPixels pixels1;
        cvObjectsFbo.readToPixels(pixels1);
        ofImage image1;
        image1.setFromPixels(pixels1);
        image1.save("RecognizedObjects.png", OF_IMAGE_QUALITY_BEST);
        
        /*
        ofPixels pixels1;
        planeFbo.readToPixels(pixels1);
        ofImage image1;
        image1.setFromPixels(pixels1);
        image1.save("Plane.png", OF_IMAGE_QUALITY_BEST);
        
        
        ofPixels pixels2;
        sphereFbo.readToPixels(pixels2);
        ofImage image2;
        image2.setFromPixels(pixels2);
        image2.save("Sphere.png", OF_IMAGE_QUALITY_BEST);
         */
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
