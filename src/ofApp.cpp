#include "ofApp.hpp"
#include "ofMain.h"


void ofApp::setup() {
    game_state = "start";
    score = 0;

	background.setup();

	ofBackground(255, 100, 100); 
    
    max_enemy_amplitude = 3.0;
    max_enemy_shoot_interval = 1.5;
    
    player_image.load("images/player.png");
    enemy_image.load("images/enemy.png");
    enemy_bullet_image.load("images/enemy_bullet.png");
    player_bullet_image.load("images/player_bullet.png");
    
	intro_music.load("sounds/intro_music.wav");
    player_bullet_sound.load("sounds/laser.wav");
	enemy_bullet_sound.load("sounds/Ror_laser.wav");
    
    player_start.set(ofGetWidth() / 2, ofGetHeight() / 2);
    player_1.setup(&player_image, player_start);
    
    start_screen.load("images/start_screen.png");
    end_screen.load("images/end_screen.png");
	score_font.load("fonts/steelworks_vintage.otf", 48);
}

//--------------------------------------------------------------
void ofApp::update(){
    if (game_state == "start") {
        
    } else if (game_state == "game") {
        player_1.update();
        withinBounds(&player_1.pos);
        update_bullets();
        
		for (auto e = enemies.begin(); e != enemies.end(); ++e) {
            e->update();
            if (e->time_to_shoot()) {
                Bullet b;
                b.setup(false, e->pos, e->speed, &enemy_bullet_image, &enemy_bullet_sound);
                bullets.push_back(b);
				enemy_bullet_sound.play();
            }
        }
        
        if (level_controller.should_spawn() == true) {
            Enemy e;
            e.setup(true, max_enemy_amplitude, max_enemy_shoot_interval, &enemy_image);
            enemies.push_back(e);
			//UI_Enemy.addItem(e);
        }
    } else if (game_state == "end") { 
        
    }
               
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (game_state == "start") {
        start_screen.draw(0, 0);
		// intro_music.play();
    } else if (game_state == "game") {
		//ofEnableAlphaBlending();
		background.draw();
		//ofDisableAlphaBlending();


		for (auto it = enemies.begin(); it != enemies .end(); ++it) {
			if (it->isVisible) 
				it->draw();
		}
		 
		for (auto it = bullets.begin(); it != bullets.end(); ++it) {
			it->draw();
		}
        player_1.draw();
        
        drawScore();
        drawLives();
    } else if (game_state == "end") {
        end_screen.draw(0, 0);
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
            Bullet b;
            b.setup(true, player_1.pos, player_1.speed, &player_bullet_image, &player_bullet_sound);
            bullets.push_back(b);
            player_bullet_sound.play();
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

void ofApp::update_bullets() {
    for (int i = 0; i < bullets.size(); i+=1) {
        bullets[i].update();
        if (bullets[i].pos.y - bullets[i].width/2 < 0 || bullets[i].pos.y + bullets[i].width/2 > ofGetHeight()) {
            bullets.erase(bullets.begin() + i);
        }
    }
    check_bullet_collisions();
}

void ofApp::withinBounds(ofPoint* point) {

	Player* p = &player_1;
    
    if (0 > point->x) {
        point->x = 0;
    }
    if (point->x > ofGetWidth() - p->img->getWidth()) {
        point->x = ofGetWidth() - p->img->getWidth();
    }
    if (0 > point->y) {
        point->y = 0;
    }
    if (point->y > ofGetWindowHeight() - p->img->getHeight()) {
        point->y = ofGetWindowHeight() - p->img->getHeight();
    }
	delete p;
}

void ofApp::check_bullet_collisions() {
    for (size_t i = 0; i < bullets.size(); i++) {
        if (bullets[i].from_player) {
            for (int e = enemies.size()-1; e >= 0; e--) {
                if (ofDist(bullets[i].pos.x, bullets[i].pos.y, enemies[e].pos.x, enemies[e].pos.y) < (enemies[e].width + bullets[i].width)/2) {
                    enemies.erase(enemies.begin()+e);
                    bullets.erase(bullets.begin()+i);
                    score+=10;
                }
            }
        } else {
            if (ofDist(bullets[i].pos.x, bullets[i].pos.y, player_1.pos.x, player_1.pos.y) < (bullets[i].width+player_1.width)/2) {
                bullets.erase(bullets.begin()+i);
                player_1.lives--;
                
                if (player_1.lives <= 0) {
                    game_state = "end";
                }
            }
        }
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

template <typename T>
void remove(vector<T>& vec, size_t pos)
{
	std::vector<T>::iterator it = vec.begin();
	std::advance(it, pos);
	vec.erase(it);
}