#pragma once
#include "ofMain.h"
#include "Canvas.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Life.hpp"
#include "Enemy.hpp"
#include "LevelController.hpp"
#include "uiManager.hpp"
#include <algorithm>
#include <vector>

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

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

	string game_state;
	int score;
	float max_enemy_amplitude;
	float max_enemy_shoot_interval;

	uiManager<Enemy> UI_Enemy;
	uiManager<Bullet> UI_Bullet;

	Canvas background;
	Player player_1;
	vector<Bullet> bullets;
	vector<Enemy> enemies;
	LevelController level_controller;

	ofPoint player_start;
	ofPoint button_last;

	ofImage player_image;
	ofImage enemy_bullet_image;
	ofImage player_bullet_image;
	ofImage enemy_image;
	ofImage start_screen;
	ofImage end_screen;

	ofSoundPlayer intro_music;
	ofSoundPlayer player_bullet_sound;
	ofSoundPlayer enemy_bullet_sound;

	ofTrueTypeFont score_font;
};