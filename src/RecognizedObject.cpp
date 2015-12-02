//
//  RecognizedObject.cpp
//  GenerativeVideoMesh
//
//  Created by Siddharth Atre on 11/22/15.
//
//

#include "RecognizedObject.h"
#include "ofApp.h"

using namespace ofxCv;
using namespace cv;


RecognizedObject:: RecognizedObject(ofShader shader) {
    objectImage.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
    plane.set(objectImage.getWidth(), objectImage.getHeight(), COLUMN_RESOLUTION, ROW_RESOLUTION);
    plane.mapTexCoordsFromTexture(objectImage.getTexture());
    
    this->shader = shader;
}

RecognizedObject:: RecognizedObject(const string vertexShaderPath, const string fragmentShaderPath) {
    objectImage.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
    plane.set(objectImage.getWidth(), objectImage.getHeight(), COLUMN_RESOLUTION, ROW_RESOLUTION);
    plane.mapTexCoordsFromTexture(objectImage.getTexture());
    
    shader.load(vertexShaderPath, fragmentShaderPath);
}

void RecognizedObject::updateImageWithObjectRectFromCamera(cv::Rect &objectRect, cv::Mat &camMat) {
    this->objectRect = objectRect;
    this->camMat = camMat;
    Mat croppedCamMat(camMat, objectRect);
    
    resize(croppedCamMat, objectImage);
    objectImage.update();
    plane.set(objectRect.width, objectRect.height);
    
    float mouseX = ((ofApp *)ofGetAppPtr())->mouseX;
    
    float noiseX = ofMap(mouseX, 0, ofGetWidth(), 0, 0.1);
    float noiseVel = ofGetElapsedTimef();
    float noiseStrength = 1;
    float noiseValue = ofNoise(noiseX, noiseVel) * noiseStrength;
    shader.setUniform1f("programNoise", noiseValue);
}

void RecognizedObject::draw() {
    objectImage.getTexture().bind();
    float x = objectRect.x;
    float y = objectRect.y;
    float width = objectRect.width;
    float height = objectRect.height;
    
    ofPushMatrix();
    ofTranslate(x, y);
    objectImage.draw(0, 0, width, height);
//    plane.drawWireframe();
    ofPopMatrix();
}

void RecognizedObject::drawWithShader() {
    objectImage.getTexture().bind();
    float x = objectRect.x;
    float y = objectRect.y;
    float width = objectRect.width;
    float height = objectRect.height;
    
    shader.begin();
    shader.setUniform1f("elapsedTime", ofGetElapsedTimef());
    float scale = ((ofApp *) ofGetAppPtr())->scale;
    shader.setUniform1f("scale", scale);
    
    ofPushMatrix();
    ofTranslate(x, y);
    //    objectImage.draw(0, 0, width, height);
    plane.drawWireframe();
//    plane.drawFaces();
    ofPopMatrix();
    shader.end();
}



/*
RecognizedObject::RecognizedObject(cv::Rect & objectRect, cv::Mat & camMat ){
    objectImage.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
    
    this->objectRect = objectRect;
    this->camMat = camMat;
    Mat croppedCamMat(camMat, objectRect);
    
    resize(croppedCamMat, objectImage);
    objectImage.update();
    
    plane.set(objectImage.getWidth(), objectImage.getHeight(), COLUMN_RESOLUTION, ROW_RESOLUTION);
    plane.mapTexCoordsFromTexture(objectImage.getTexture());
}
 */
