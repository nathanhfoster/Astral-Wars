#include "ofApp.hpp"
#include "ofMain.h"
#include "Emitter.h"

void ofApp::setup() {
	ofSetVerticalSync(true);
    game_state = "start";
    score = 0;

	player_image.load("images/player.png");
	enemy_image.load("images/enemy.png");
	enemy_bullet_image.load("images/enemy_bullet.png");
	invader_emitter_image.load("images/death_star.png");
	player_bullet_image.load("images/player_bullet.png");

	intro_music.load("sounds/intro_music.wav");
	player_bullet_sound.load("sounds/laser.wav");
	player_bullet_sound.setMultiPlay(true);
	enemy_bullet_sound.load("sounds/Ror_laser.wav");
	

	player_start.set(ofGetWidth() / 2, ofGetHeight() / 2);
	player_1.setup(&player_image, player_start);

	start_screen.load("images/start_screen.png");
	end_screen.load("images/end_screen.png");
	score_font.load("fonts/steelworks_vintage.otf", 48);

	// Record when the game starts - game will run for 20 sec
	gameStartTime = ofGetElapsedTimeMillis();

	// Create and setup emitters  (you can play with parameters
	// I have another example program that creates a GUI for these
	// so with that you can get an idea of velocity/rate effects.
	//
	player_1Gun = new Emitter(new SpriteSystem());
		// Set up some reasonable parameters for the gun/missile launcher
	// Remember that "Y" decreases as we move toward teh top of the 
	// window, so we set a negative velocity of -1000;
	// We also don't want the missiles to live forever, so we set
	// a lifespan of 500 ms.
	//
	player_1Gun->setPosition(ofPoint(player_1.pos));
	player_1Gun->setVelocity(ofVec3f(0, -1000, 0));
	player_1Gun->setRate(1);
	player_1Gun->setLifespan(1000);
	player_1Gun->setChildImage(player_bullet_image);
	player_1Gun->setChildSound(player_bullet_sound);

	invaders = new Emitter(new SpriteSystem());
	invaders->setImage(invader_emitter_image);
	invaders->setChildImage(enemy_image);

	// Set up some reasonable parameters for the invader spirtes
	// Remember that "Y" decreases as we move toward the bottom of
	// the window, so we set a negative velocity of 400.
	// We also don't want the invaders to live forever, so we set
	// a lifespan of 5000 ms.  they are traveling much slower
	// than the missiles, so they need to live longer
	//
	invaders->setPosition(ofVec3f(ofGetWindowWidth() / 2, 50, 0));
	invaders->velocity.set(0, 400, 0);
	invaders->setLifespan(5000);
	invaders->setRate(1);
	invaders->setChildSize(20, 20);


	moreInvaders = new Emitter(new SpriteSystem());

	moreInvaders->setImage(invader_emitter_image);
	moreInvaders->setChildImage(enemy_image);
	moreInvaders->setPosition(ofVec3f(ofGetWindowWidth() / 2, 200, 0));
	moreInvaders->velocity.set(0, 600, 0);
	moreInvaders->setRate(10);
	moreInvaders->setLifespan(5000);
	moreInvaders->setChildSize(20, 20);
	moreInvaders->start();


	explosion = new ParticleEmitter();
	explosion->setDamping(1);

	explosion->setOneShot(true);
	explosion->setEmitterType(RadialEmitter);
	explosion->setGroupSize(10);
	explosion->setLifespan(1);
	explosion->setVelocity(ofVec3f(1000, 0, 0));
	explosion->setParticleRadius(4);


	// start them up

	invaders->start();
	player_1Gun->start();

	background.setup();

	ofBackground(0, 0, 0); 
}

//--------------------------------------------------------------
void ofApp::update(){
    if (game_state == "start") {
        
    } else if (game_state == "game") {
		//  call the emitter's update function to create new sprites
		//  as needed
		player_1Gun->update();
		player_1Gun->setPosition(ofPoint(player_1.pos));
		invaders->update();
		if (score > 200)
			moreInvaders->update();

	// check for collisions between missles and invaders
	//  
	checkCollisions();
	explosion->update();

	// we will randomize initial velocity so that not the invaders
	// are going at the same speed just to make it a little harder/interesting
	// to play
	//
	ofVec3f v = invaders->velocity;
	invaders->setVelocity(ofVec3f(ofRandom(-v.y /2, v.y /2), v.y, v.z));
	moreInvaders->setVelocity(ofVec3f(ofRandom(-v.y / 2, v.y / 2), v.y, v.z));
	

	// game runs for 20 seconds; check to see if over and stop
	// emitters.  We are computing in milleseconds so we need
	// to multiply seconds by 1000 to convert to ms.

	/*float t = ofGetElapsedTimeMillis();
	if ((t - gameStartTime > (20 * 1000))) {
		game_state = "end";
		gun->stop();
		invaders->stop();
	}*/

	if (score > 5) { invaders->setRate(2); player_1Gun->setRate(2); }
	if (score > 10) { invaders->setRate(3); }
	if (score > 20) { invaders->setRate(4); player_1Gun->setRate(3);}
	if (score > 30) { invaders->setRate(5); }
	if (score > 40) { invaders->setRate(6); player_1Gun->setRate(4); }
	if (score > 50) { invaders->setRate(7); }
	if (score > 60) { invaders->setRate(8); }
	if (score > 70) { invaders->setRate(9); player_1Gun->setRate(5); }
	if (score > 80) { invaders->setRate(10); }
	if (score > 90) { invaders->setRate(11); }
	if (score > 100) { invaders->setRate(12); player_1Gun->setRate(6); }
	if (score > 200) { invaders->setRate(14); player_1Gun->setRate(7); }
	
		
	player_1.update();
    withinBounds(&player_1.pos);
    } else if (game_state == "end") { 
        
    }
               
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (game_state == "start") {
        start_screen.draw(0, 0);
		// intro_music.play();
    } else if (game_state == "game") {
		player_1Gun->draw();
		invaders->draw();
		if (score > 200)
			moreInvaders->draw();
		//ofEnableAlphaBlending();
		//background.draw();
		//ofDisableAlphaBlending();

        player_1.draw();
		explosion->draw();
		
        drawScore();
        drawLives();
    } else if (game_state == "end") {
        end_screen.draw(0, 0);
    }
}

//  This is a simple O(M x N) collision check
//  For each missle check to see which invaders you hit and remove them
//
void ofApp::checkCollisions() {

	// find the distance at which the two sprites (missles and invaders) will collide
	// detect a collision when we are within that distance.
	//
	float collisionDist = player_1Gun->childHeight / 2 + invaders->childHeight / 2;
	float nearPlayer = player_1.img->getHeight() / 2 + invaders->childHeight / 2;
	float nearPlayer2 = player_1.img->getHeight() / 2 + moreInvaders->childHeight / 2;
	vector<Sprite>::iterator i = invaders->sys->sprites.begin();


	// Loop through all the missiles, then remove any invaders that are within
	// "collisionDist" of the missiles.  the removeNear() function returns the
	// number of missiles removed.
	//
	for (auto g = player_1Gun->sys->sprites.begin(); g != player_1Gun->sys->sprites.end(); ++g) {
		int n = invaders->sys->removeNear(g->trans, collisionDist) + moreInvaders->sys->removeNear(g->trans, collisionDist);
		if (n > 0) {
			score += n;
			explosion->setPosition(g->trans);
			explosion->start();
		}
	}

	for (int i = 0; i < invaders->sys->sprites.size(); i++) {
		int n = invaders->sys->removeNear(player_1.pos, nearPlayer) + moreInvaders->sys->removeNear(player_1.pos, nearPlayer2);
		if (n > 0) {
			player_1.lives -= n;
			explosion->setPosition(player_1.pos);
			explosion->start();
		}
		if (player_1.lives == 0) {
			game_state = "end";
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (game_state == "game") {
        if (key == OF_KEY_LEFT)
            player_1.is_left_pressed = true;
        if (key == OF_KEY_RIGHT)
            player_1.is_right_pressed = true; 
        if (key == OF_KEY_UP)
            player_1.is_up_pressed = true;
        if (key == OF_KEY_DOWN)
            player_1.is_down_pressed = true;
        if (key == ' ') {
           /* Bullet b;
            b.setup(true, player_1.pos, player_1.speed, &player_bullet_image, &player_bullet_sound);
            bullets.push_back(b);
            player_bullet_sound.play();*/
			
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (game_state == "start" && key == ' ') {
        game_state = "game";
        level_controller.setup(ofGetElapsedTimeMillis());
    } else if (game_state == "game") {
        if (key == OF_KEY_LEFT)
            player_1.is_left_pressed = false;
        if (key == OF_KEY_RIGHT)
            player_1.is_right_pressed = false;
        if (key == OF_KEY_UP)
            player_1.is_up_pressed = false;
        if (key == OF_KEY_DOWN)
            player_1.is_down_pressed = false;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {
	button_last = ofPoint(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	ofPoint mouse_cur = ofPoint(x, y);

	if (this->player_1.clickable.inside(x, y)) {
		ofVec2f delta = (mouse_cur - button_last);
		player_1.pos += delta;
		button_last = mouse_cur;
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::withinBounds(ofPoint* point) {
    
    if (0 > point->x) {
        point->x = 0;
    }
    if (point->x > ofGetWidth()) {
        point->x = ofGetWidth();
    }
    if (0 > point->y) {
        point->y = 0;
    }
    if (point->y > ofGetWindowHeight()) {
        point->y = ofGetWindowHeight();
    }
}

void ofApp::drawLives() {
    for (int i = 0; i < player_1.lives; i++) {
        player_image.draw(ofGetWidth() - (i * player_image.getWidth()) - 100, 30);
    }
}

void ofApp::drawScore() {
    if (game_state == "game") {
        score_font.drawString(ofToString(score), 30, 72);
    } else if (game_state == "end") {
        float w = score_font.stringWidth(ofToString(score));
        score_font.drawString(ofToString(score), ofGetWidth()/2 - w/2, ofGetHeight()/2 + 100);
    }
}

void ofApp::resetGame() {
    
}

bool ofApp::isPerfectSquare(int x) {
	int s = sqrt(x);
	return (s*s == x);
}

bool ofApp::isFibonacci(int n) {
	// n is Fibinacci if one of 5*n*n + 4 or 5*n*n - 4 or both
	// is a perferct square
	return isPerfectSquare(5 * n*n + 4) ||
		isPerfectSquare(5 * n*n - 4);
}