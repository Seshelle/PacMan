#include <SFML/Graphics.hpp>
#include "ghost.h"

Ghost::Ghost(char which, double x, double y, sf::Sprite spr){
	dotCounter = 0;
	name = which;
	sprite = spr;
	speed = 0.019;
	setMode('h');
	if (name == 'b'){
		sprite.setTextureRect(sf::IntRect(228, 64, 16, 16));
	}
	else if (name == 'p'){
		sprite.setTextureRect(sf::IntRect(228, 80, 16, 16));
	}
	else if (name == 'i'){
		sprite.setTextureRect(sf::IntRect(228, 96, 16, 16));
	}
	else if (name == 'c'){
		sprite.setTextureRect(sf::IntRect(228, 112, 16, 16));
	}
	sprite.setOrigin(8, 8);
	sprite.setPosition(x, y);
	currentTile = 0;
}

Ghost::Ghost(){

}

void Ghost::setGhost(char which, double x, double y, sf::Sprite spr){
	name = which;
	sprite = spr;
	speed = 0.019;
	mode = 'c';
	sprite.setTextureRect(sf::IntRect(228, 64, 16, 16));
	sprite.setOrigin(8, 8);
	sprite.setPosition(x, y);
}

void Ghost::setMode(char newMode){
	if (mode != newMode){
		mode = newMode;
		if (mode == 'f'){
			sprite.setTextureRect(sf::IntRect(356, 64, 16, 16));
			fright = 20000;
			speed = 0.015;
		}
		if (mode == 'h'){
			dotCounter = 0;
			if (name == 'b'){
				sprite.setTextureRect(sf::IntRect(228, 64, 16, 16));
			}
			else if (name == 'p'){
				sprite.setTextureRect(sf::IntRect(228, 80, 16, 16));
			}
			else if (name == 'i'){
				sprite.setTextureRect(sf::IntRect(228, 96, 16, 16));
			}
			else if (name == 'c'){
				sprite.setTextureRect(sf::IntRect(228, 112, 16, 16));
			}
		}
		reverse();
	}
}

char Ghost::getMode(){
	return mode;
}

void Ghost::move(char face){
	facing = face;
}

void Ghost::reverse(){
	if (facing == 'l'){
		facing = 'r';
	}
	if (facing == 'r'){
		facing = 'l';
	}
	if (facing == 'u'){
		facing = 'd';
	}
	if (facing == 'd'){
		facing = 'u';
	}
}

void Ghost::update(){
	if (mode == 'h'){
		if (name == 'b'){
			sprite.setPosition(14 * 8, (14 * 8) + 4);
			if (dotCounter >= 0){
				sprite.setPosition(14 * 8, (14 * 8) + 4);
				mode = 'c';
			}
		}
		if (name == 'i'){
			sprite.setPosition(12 * 8, 18 * 8);
			if (dotCounter >= 17){
				sprite.setPosition(14 * 8, (14 * 8) + 4);
				mode = 'c';
			}
		}
		if (name == 'p'){
			sprite.setPosition(14 * 8, 18 * 8);
			if (dotCounter >= 7){
				sprite.setPosition(14 * 8, (14 * 8) + 4);
				mode = 'c';
			}
		}
		if (name == 'c'){
			sprite.setPosition(16 * 8, 18 * 8);
			if (dotCounter >= 32){
				sprite.setPosition(14 * 8, (14 * 8) + 4);
				mode = 'c';
			}
		}
	}
	else{
		int xtile = sprite.getPosition().x / 8;
		int ytile = sprite.getPosition().y / 8;

		if (mode == 'f'){
			fright--;
			if (fright < 0){
				mode = 'c';
				speed = 0.019;
				if (name == 'b'){
					sprite.setTextureRect(sf::IntRect(228, 64, 16, 16));
				}
				else if (name == 'p'){
					sprite.setTextureRect(sf::IntRect(228, 80, 16, 16));
				}
				else if (name == 'i'){
					sprite.setTextureRect(sf::IntRect(228, 96, 16, 16));
				}
				else if (name == 'c'){
					sprite.setTextureRect(sf::IntRect(228, 112, 16, 16));
				}
			}
		}

		switch (facing){
		case 'u':
			sprite.move(0, -speed);
			sprite.setPosition((xtile * 8) + 4, sprite.getPosition().y);
			break;
		case 'l':
			sprite.move(-speed, 0);
			sprite.setPosition(sprite.getPosition().x, (ytile * 8) + 4);
			break;
		case 'd':
			sprite.move(0, speed);
			sprite.setPosition((xtile * 8) + 4, sprite.getPosition().y);
			break;
		case 'r':
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
}

int Ghost::getTileX(){
	return (sprite.getPosition().x / 8);
}

int Ghost::getTileY(){
	return (sprite.getPosition().y / 8);
}

void Ghost::setCurrentTile(int tile){
	currentTile = tile;
}

int Ghost::getCurrentTile(){
	return currentTile;
}

char Ghost::getFacing(){
	return facing;
}

char Ghost::getName(){
	return name;
}
void Ghost::add(){
	dotCounter++;
}

sf::Sprite Ghost::getSprite(){
	return sprite;
}