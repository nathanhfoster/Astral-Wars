#include "ofMain.h"
#include "ofApp.hpp"

//Inspired from: http://openframeworks.cc/ofBook/chapters/game_design.html

int main( ){
	ofSetupOpenGL(540, 960, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}
