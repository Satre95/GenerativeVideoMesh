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
