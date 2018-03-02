#pragma once
//----------------------------------------------------------------------------------
//
// Basic Sprite Emitter Class
//
//
//  Kevin M. Smith - CS 134 SJSU

#include "Sprite.h"


//  General purpose Emitter class for emitting sprites
//  This works similar to a Particle emitter
//
class Emitter : public BaseObject {
public:
	Emitter(SpriteSystem *);
	void draw();
	void start();
	void stop();
	void setLifespan(float);    // in milliseconds
	void setVelocity(ofVec3f);  // pixel/sec
	void setChildImage(ofImage);
	void setChildSound(ofSoundPlayer);
	void setChildSize(float w, float h) { childWidth = w; childHeight = h; }
	void setImage(ofImage);
	void setSound(ofSoundPlayer);
	void setRate(float);
	float maxDistPerFrame();
	void update();
	SpriteSystem *sys;
	float rate;
	ofVec3f velocity;
	float lifespan;
	bool started;
	float lastSpawned;
	ofImage childImage;
	ofImage image;
	ofSoundPlayer childSound;
	ofSoundPlayer sound;
	ofPoint pos;
	bool drawable;
	bool haveChildImage;
	bool haveImage;
	bool haveChildSound;
	bool haveSound;
	float width, height;
	float childWidth, childHeight;
};
