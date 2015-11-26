#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "ofxCv.h"
#include "RecognizedObject.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void drawPlaneMesh();
    void drawSphereMesh();
    
    ofVboMesh videoMesh;
    ofEasyCam easyCam;
    ofVideoGrabber videoGrabber;
    
    int videoGrabberWidth = 1920;
    int videoGrabberHeight = 1080;
    
    const float meshScaleX = 0.25;
    const float meshScaleY = 0.25;
    
    ofShader shader;
    
    ofFbo planeFbo;
    ofFbo sphereFbo;
    
    ofPlanePrimitive plane;
    ofSpherePrimitive sphere;
    
    bool useLiveVideoStream = true;
    int scale;
    
    ofSerial serialPort;
    ofArduino arduino;
    
    const string forecastURL = "https://api.forecast.io/forecast/6d5469fb52edef1548f96fa095fb2c7c/";
    string latitude = "42.375374";
    string longitude = "-71.055414";
    
    //--------------------
    //Open CV stuff
    ofxCv::ObjectFinder faceFinder;
    ofImage faceImage;
    vector<RecognizedObject> recognizedObjects;
    static const int MAX_NUMBER_OF_RECOGNIZED_OBJECTS = 10;
    int numberOfRecognizedObjects = 0;
    
    
    
private:
    const string forecastAPIKey = "6d5469fb52edef1548f96fa095fb2c7c";
};
