#pragma once

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>

#include "ofMain.h"

class Player {
public:
    ofPoint pos;
	ofRectangle clickable;
    float width, height, speed;
    int lives;
    
	bool is_left_pressed, is_right_pressed, is_down_pressed, is_up_pressed, hit;
    
    void setup(ofImage* _img, ofPoint _pos);
    void update();
    void draw();
    void shoot();
    
    void calculate_movement();
    
    bool check_canshoot();
    
    ofImage* img;
	ofSoundPlayer* laser;
};


#endif /* Player_hpp */
