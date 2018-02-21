#pragma once
// Code used from: https://forum.openframeworks.cc/t/setting-an-image-as-canvass-background/16960/2

#ifndef Canvas_hpp
#define Canvas_hpp

#include <stdio.h>
#include "ofMain.h"

class Canvas {

public:



	ofFbo fbo;
	ofFbo fbo2;
	ofImage fundo; //background
	Canvas() {}
	void setup();
	void draw();
};
#endif