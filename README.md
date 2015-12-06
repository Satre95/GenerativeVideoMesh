# GenerativeVideoMesh
An art project to perform hardware accelerated generative drawing on a video based mesh. Built with openFrameworks

There are two components to this project, openCV powered face detection and the generative distortion performed using GLSL.
The openCV library detects frontal faces, and filters the rect within which they lie from the video stream captured by the video grabber.
This rect is then applied to an `ofImage` texture, upon which a GLSL shader is run to produce a generative, pseudo-random based distortion.
Finally, the distorted image frame is drawn to the screen as a wireframe, in the region relative to the source video stream that it orignated from.
The program supports multiple simulataneous face detection and drawing, up to the threshold defined in `ofApp.h`.

Please note that run time performance can vary greatly depending on your system, as much of the project uses hardware-accelerated features.

## Setup
1. Clone this repo to a location of your choice.
2. Import the project into your system's project generator to update it to use your `OF_PATH`. 

Note: I wrote this project to run on Mac OS X, but all the underlying code can easily be ported to Windows or Linux.

## Dependencies
This project requires the following addons:
- ofxCV
- ofxOpenCV


