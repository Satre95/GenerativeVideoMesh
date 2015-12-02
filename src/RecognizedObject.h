//
//  RecognizedObject.h
//  GenerativeVideoMesh
//
//  Created by Siddharth Atre on 11/22/15.
//
//

#ifndef __GenerativeVideoMesh__RecognizedObject__
#define __GenerativeVideoMesh__RecognizedObject__

#include "ofMain.h"
#include "ofxCv.h"

/**
Class is used to encapsulate information about a contour object that has been recognized by openCV. Each instance stores references to plane primitive being used to draw to screen as well as native openCV object being used.
*/
class RecognizedObject{

public:
    const static int COLUMN_RESOLUTION = 80;
    const static int ROW_RESOLUTION = 80;
    
//    RecognizedObject(cv::Rect & objectRect, cv::Mat & );
    RecognizedObject(ofShader shader);
    RecognizedObject(const string vertexShaderPath, const string fragmentShaderPath);
    void updateImageWithObjectRectFromCamera( cv:: Rect & objectRect, cv:: Mat & camMat);
    void draw();
    void drawWithShader();
    
    ofPlanePrimitive imagePlane;
    cv::Rect objectRect;
    cv::Mat camMat;
    
    ofImage objectImage;
    ofPlanePrimitive plane;
    ofShader shader;
	
protected:

};

#endif /* defined(__GenerativeVideoMesh__RecognizedObject__) */
