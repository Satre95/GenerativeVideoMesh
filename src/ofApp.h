#pragma once

#include "ofMain.h"
#include "ofxFX.h"

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
    
    ofVboMesh videoMesh;
    ofEasyCam easyCam;
    ofVideoGrabber videoGrabber;
    
    const int videoGrabberWidth = 1920;
    const int videoGrabberHeight = 1080;
    
    const float meshScaleX = 0.25;
    const float meshScaleY = 0.25;
    
    ofShader shader;
    
    ofFbo mainFbo;
    
    ofPlanePrimitive plane;
    ofSpherePrimitive sphere;
    ofVideoPlayer videoPlayer;
    
    bool useLiveVideoStream = true;
    
};
