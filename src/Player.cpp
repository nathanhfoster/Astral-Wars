#include "Player.hpp"
#include "ofApp.hpp"

//--------------------------------------------------------------
void Player::setup(ofImage * _img, ofPoint _pos){
    img = _img;
    height = img->getHeight();
    width = img->getWidth();
    pos.set(_pos);
    speed = 1;
    lives = 5;
}

//--------------------------------------------------------------
void Player::update(){
    if (is_up_pressed)
        pos.y -= speed;
    if (is_down_pressed)
        pos.y += speed;
    if (is_left_pressed)
        pos.x -= speed;
    if (is_right_pressed)
        pos.x += speed;
}

//--------------------------------------------------------------
void Player::draw(){
    img->draw(pos.x-width/2, pos.y-height/2);
	clickable.set(pos.x - width / 2, pos.y - height / 2, img->getWidth(), img->getHeight());
}

//--------------------------------------------------------------
void Player::shoot(){
}