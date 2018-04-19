#pragma once
#include "ofMain.h"
#include "Canvas.hpp"
#include "Player.hpp"
#include "LevelController.hpp"
#include "uiManager.hpp"
#include "ParticleEmitter.h"
#include <algorithm>
#include <vector>

class Emitter;

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void checkCollisions();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void update_bullets();
	void withinBounds(ofPoint * point);
	void check_bullet_collisions();
	void drawLives();
	void drawScore();
	void resetGame();
	bool isPerfectSquare(int x);
	bool isFibonacci(int n);

	string game_state;
	int score;
	float max_enemy_amplitude;
	float max_enemy_shoot_interval;


	Emitter *player_1Gun, *invaders, *moreInvaders;
	ParticleEmitter* explosion;
	float gameStartTime;
	ofVec3f mouseLast;

	Canvas background;
	Player player_1;
	LevelController level_controller;

	ofPoint player_start;
	ofPoint button_last;

	ofImage player_image;
	ofImage enemy_bullet_image;
	ofImage player_bullet_image;
	ofImage enemy_image;
	ofImage invader_emitter_image;
	ofImage start_screen;
	ofImage end_screen;

	ofSoundPlayer intro_music;
	ofSoundPlayer player_bullet_sound;
	ofSoundPlayer enemy_bullet_sound;

	ofTrueTypeFont score_font;
};