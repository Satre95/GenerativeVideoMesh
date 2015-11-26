//
//  RecognizedObject.cpp
//  GenerativeVideoMesh
//
//  Created by Siddharth Atre on 11/22/15.
//
//

#include "RecognizedObject.h"

using namespace ofxCv;
using namespace cv;


RecognizedObject:: RecognizedObject() {
    objectImage.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);
    plane.set(objectImage.getWidth(), objectImage.getHeight(), COLUMN_RESOLUTION, ROW_RESOLUTION);
    plane.mapTexCoordsFromTexture(objectImage.getTexture());
    
    
}

void RecognizedObject::updateImageWithObjectRect(cv::Rect &objectRect, cv::Mat &camMat) {
    this->objectRect = objectRect;
    this->camMat = camMat;
    Mat croppedCamMat(camMat, objectRect);
    
    resize(croppedCamMat, objectImage);
    objectImage.update();
    plane.set(objectRect.width, objectRect.height);
}

void RecognizedObject::draw() {
    float x = objectRect.x;
    float y = objectRect.y;
    float width = objectRect.width;
    float height = objectRect.height;
    
    ofPushMatrix();
    ofTranslate(x, y);
    objectImage.draw(0, 0, width, height);
    plane.drawFaces();
    ofPopMatrix();
    
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
