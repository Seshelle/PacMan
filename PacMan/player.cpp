#include "player.h"
#include <SFML/Graphics.hpp>

Player::Player(sf::Sprite spr){
	sprite = spr;
	animation = 225;
	sprite.setTextureRect(sf::IntRect(animation, 0, 16, 16));
	sprite.setOrigin(8, 8);
	sprite.setPosition(112, 212);
	facing = 'n';
	speed = 0.02;
	timePass = 0;
}

void Player::move(char direction){
	facing = direction;
}

void Player::update(){
	timePass++;
	if (timePass >= 70){
		timePass = 0;
		animation = animation + 16;
		if (animation > 257){
			animation = 225;
		}
		sprite.setTextureRect(sf::IntRect(animation, 0, 16, 16));
	}
	int xtile;
	int ytile;
	xtile = sprite.getPosition().x / 8;
	ytile = sprite.getPosition().y / 8;
	switch (facing){
	case 'u':
		sprite.setRotation(270);
		sprite.move(0, -speed);
		sprite.setPosition((xtile * 8) + 4, sprite.getPosition().y);
		break;
	case 'l':
		sprite.setRotation(180);
		sprite.move(-speed, 0);
		sprite.setPosition(sprite.getPosition().x, (ytile * 8) + 4);
		break;
	case 'd':
		sprite.setRotation(90);
		sprite.move(0, speed);
		sprite.setPosition((xtile * 8) + 4, sprite.getPosition().y);
		break;
	case 'r':
		sprite.setRotation(0);
		sprite.move(speed, 0);
		sprite.setPosition(sprite.getPosition().x, (ytile * 8) + 4);
		break;
	default:
		break;
	}
	if (xtile == 27){
		sprite.setPosition(8, sprite.getPosition().y);
	}
	else if (xtile == 0){
		sprite.setPosition(215, sprite.getPosition().y);
	}
}

double Player::getXPos(){
	return sprite.getPosition().x;
}

double Player::getYPos(){
	return sprite.getPosition().y;
}

sf::Sprite Player::getSprite(){
	return sprite;
}

char Player::getFacing(){
	return facing;
}

int Player::getTileX(){
	return ((getXPos()) / 8);
}

int Player::getTileY(){
	return ((getYPos()) / 8);
}

void Player::die(){
	sprite.setPosition(112, 212);
}

/*int Player::kludgeUp(){
	return ((getYPos() + 5) / 8);
}

void Player::fixUp(){
	sprite.move(0, speed / 2);
}

int Player::kludgeDown(){
	return ((getYPos() + 3) / 8);
}

void Player::fixDown(){
	sprite.move(0, -speed / 2);
}*/