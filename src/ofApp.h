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
    void drawPlaneMesh();
    void drawSphereMesh();
    
    ofVboMesh videoMesh;
    ofEasyCam easyCam;
    ofVideoGrabber videoGrabber;
    
    int videoGrabberWidth = 800;
    int videoGrabberHeight = 800;
    
    const float meshScaleX = 0.25;
    const float meshScaleY = 0.25;
    
    ofShader shader;
    
    ofFbo planeFbo;
    ofFbo sphereFbo;
    
    ofPlanePrimitive plane;
    ofSpherePrimitive sphere;
    ofVideoPlayer videoPlayer;
    
    bool useLiveVideoStream = true;
    
};
