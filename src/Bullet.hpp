#pragma once

#ifndef Bullet_hpp
#define Bullet_hpp

#include <stdio.h>
#include "ofMain.h"

class Bullet {
public:
    ofPoint pos;
    float speed;
    float width;
    bool from_player;
    
    void setup(bool f_p, ofPoint p, float s, ofImage* bullet_image, ofSoundPlayer* bullet_sound);
    void update();
    void draw();
    
    ofImage * img;
	ofSoundPlayer* sound;
};

#endif /* Bullet_hpp */
