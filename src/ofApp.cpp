#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60); //target frame rate.
    ofBackground(66,66,66);
    
    videoGrabberHeight = ofGetHeight();
    videoGrabberWidth = ofGetWidth() / 2;
    

    //Init the video grabber
    videoGrabber.setVerbose(false);
    videoGrabber.initGrabber(videoGrabberWidth, videoGrabberHeight);

    //Init the video grabber
    planeFbo.allocate(ofGetWidth(), ofGetHeight());
    sphereFbo.allocate(videoGrabberWidth, videoGrabberHeight);
    //init the shader
    shader.load("shaders/shader.vert", "shaders/shader.frag");
    
    plane.set(videoGrabberWidth, videoGrabberHeight,80, 80);
    plane.mapTexCoordsFromTexture(videoGrabber.getTexture());
    
    sphere.setRadius(max(videoGrabberWidth , videoGrabberHeight) / 2.0f);
    sphere.setResolution(600);
    sphere.mapTexCoordsFromTexture(videoGrabber.getTexture());
    
    vector <ofSerialDeviceInfo> deviceList = serialPort.getDeviceList();
//    serialPort.setup(deviceList[0].getDeviceName(), 9600);
//    serialPort.flush();
    
    arduino.connect(deviceList[0].getDeviceName());
    ofLogNotice() << "Arduino Initialized: " << arduino.isInitialized();
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    videoGrabber.update();
    
    scale = readScaleFromSerialPort();
    
    //calculate noise
    float noiseX = ofMap(mouseX, 0, ofGetWidth(), 0, 0.1);
    float noiseVel = ofGetElapsedTimef();
    float noiseStrength = 1;
    float noiseValue = ofNoise(noiseX, noiseVel) * noiseStrength;
    shader.setUniform1f("programNoise", noiseValue);
}


//-------------------------------------------------------------
void ofApp::draw(){
    drawPlaneMesh();
//    drawSphereMesh();
    
    //Show the FPS
    ofSetColor(255);
    string msg = "FPS: " + ofToString(ofGetFrameRate(), 2);
    ofDrawBitmapString(msg, 10, 20);
}

void ofApp::drawPlaneMesh() {
    planeFbo.begin();
    videoGrabber.getTexture().bind();

    ofClear(0, 0, 0);
    ofColor centerColor = ofColor(85, 78, 68);
    ofColor edgeColor(0, 0, 0);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
    
    
    easyCam.begin();
    
    shader.begin();
    
    shader.setUniform1f("elapsedTime", ofGetElapsedTimef());
    float constrainedScale = ofClamp(scale, 1, 1023);
    float mappedScale = ofMap(constrainedScale, 1, 1023, 1, 100);
    shader.setUniform1f("scale", mappedScale);
    
//    plane.drawWireframe();
//    plane.drawVertices();
    plane.drawFaces();
    
    shader.end();
    
    //    videoGrabber.draw(0, 0);
    
    easyCam.end();
    planeFbo.end();
//    planeFbo.draw(0, 0, ofGetWidth() / 2, ofGetHeight());
    planeFbo.draw(0, 0);
}

void ofApp::drawSphereMesh() {
    sphereFbo.begin();

    videoGrabber.getTexture().bind();
    
    
    ofClear(0, 0, 0);
    ofColor centerColor = ofColor(85, 78, 68);
    ofColor edgeColor(0, 0, 0);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);
    
    
    easyCam.begin();
    
    shader.begin();
    
    shader.setUniform1f("elapsedTime", ofGetElapsedTimef());
    
    sphere.drawVertices();
//    sphere.drawWireframe();
    
    
    shader.end();
    
    //    videoGrabber.draw(0, 0);
    
    easyCam.end();
    //    planeFbo.draw(0, 0, ofGetWidth() / 2, ofGetHeight() / 2);
    sphereFbo.end();
    sphereFbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's' || key == 'S') {
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
    }
    
}

int ofApp::readScaleFromSerialPort() {
//    float scale = serialPort.readByte();
//    ofLogNotice() << "Scale: " << scale << "\n";
//    return scale;
    
    if (arduino.isArduinoReady()) {
        arduino.update();
        int currScale = arduino.getAnalog(0);
        ofLogNotice() << "Scale: " << currScale << "\n";
        return currScale;
    }
    
    return 1;
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
