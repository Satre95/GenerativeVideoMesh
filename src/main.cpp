#include "ofMain.h"
#include "ofApp.h"
#include "ofGLProgrammableRenderer.h"

//========================================================================
int main( ){
    ofGLWindowSettings settings;
    settings.setGLVersion(4, 0);
    ofCreateWindow(settings);   // <-------- setup the GL context

	ofRunApp(new ofApp());

}
