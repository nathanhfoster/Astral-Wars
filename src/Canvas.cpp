#include "Canvas.hpp"

// Code used from: https://forum.openframeworks.cc/t/setting-an-image-as-canvass-background/16960/2

void Canvas::setup() {
	ofSetBackgroundAuto(true);
	fundo.loadImage("images/background.jpg");


	fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	fbo2.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);

	fbo2.begin();
	ofClear(255, 255, 255, 0);
	fbo2.end();

	fbo.begin();
	ofClear(255, 255, 255, 0);
	fbo.end();

}

void Canvas::draw() {
	fbo.begin();
	fundo.draw(0, 0, 540, 960);
	ofPushStyle();
	ofSetColor(0);
	string message = "fps: " + ofToString(ofGetFrameRate());
	ofDrawBitmapString(message, 10, 20);
	ofPopStyle();

	fbo.end();


	fbo2.begin();

	//ofPushStyle();
	//ofFill();
	//ofSetColor(255, 255, 0);
	//ofCircle(ofGetMouseX(), ofGetMouseY(), 10);
	ofPopStyle();
	fbo2.end();

	fbo.draw(0, 0);
	fbo2.draw(0, 0);

}