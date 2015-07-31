#include "tile.h"
#include <SFML/Graphics.hpp>

Tile::Tile(double x, double y, bool passable, char what, int number, sf::Sprite spr){
	xpos = x;
	ypos = y;
	item = what;//(d)ot, (e)nergizer, (n)othing, (c)herry, (s)trawberry, (p)each, (a)pple, (g)rapes, gala(x)ian, (b)ell, (k)ey, (w)all
	id = number;
	sprite = spr;
}

Tile::Tile(){

}

void Tile::setLocationID(double x, double y, int number){
	xpos = x;
	ypos = y;
	sprite.setPosition(xpos, ypos);
	id = number;
	resetTile();
}

void Tile::resetTile(){
	//create symmetry
	double tempx = xpos;
	if (xpos > (13 * 8)){
		double diff = (xpos - (13 * 8));
		xpos = (13 * 8) - ((diff - 8));
	}

	item = 'd';

	//left and right wall
	if (xpos <= 0 && ypos != (17 * 8)){
		item = 'w';
	}
	//top and bottom walls
	if (ypos <= (3 * 8) || ypos >= (33 * 8)){
		item = 'w';
	}
	//upper outer box
	if (xpos >= (2 * 8) && xpos <= (5 * 8) && ypos >= (5 * 8) && ypos <= (7 * 8)){
		item = 'w';
	}
	//upper box
	if (xpos >= (7 * 8) && xpos <= (11 * 8) && ypos >= (5 * 8) && ypos <= (7 * 8)){
		item = 'w';
	}
	//upper middle wall
	if (xpos == (13 * 8) && ypos <= (7 * 8)){
		item = 'w';
	}
	//upper H
	if (xpos >= (7 * 8) && xpos <= (8 * 8) && ypos >= (9 * 8) && ypos <= (16 * 8)){
		item = 'w';
	}
	if (ypos >= (12 * 8) && ypos <= (13 * 8) && xpos >= (9 * 8) && xpos <= (11 * 8)){
		item = 'w';
	}
	//upper T
	if (ypos >= (9 * 8) && ypos <= (10 * 8) && xpos >= (10 * 8) && xpos <= (17 * 8)){
		item = 'w';
	}
	if (xpos == (13 * 8) && ypos >= (9 * 8) && ypos <= (13 * 8)){
		item = 'w';
	}
	//little upper boxes
	if (xpos >= (2 * 8) && xpos <= (5 * 8) && ypos >= (9 * 8) && ypos <= (10 * 8)){
		item = 'w';
	}
	//wall above tunnel
	if (ypos >= (12 * 8) && ypos <= (16 * 8) && xpos <= (5 * 8)){
		item = 'w';
	}
	//wall below tunnel
	if (ypos >= (18 * 8) && ypos <= (22 * 8) && xpos <= (5 * 8)){
		item = 'w';
	}
	//ghost house
	if (xpos >= (10 * 8) && xpos <= (17 * 8) && ypos >= (15 * 8) && ypos <= (19 * 8)){
		item = 'w';
	}
	//lower T
	if (xpos >= (10 * 8) && xpos <= (17 * 8) && ypos >= (21 * 8) && ypos <= (22 * 8)){
		item = 'w';
	}
	if (xpos == (13 * 8) && ypos >= (21 * 8) && ypos <= (25 * 8)){
		item = 'w';
	}
	//little side boxes near middle
	if (xpos >= (7 * 8) && xpos <= (8 * 8) && ypos >= (18 * 8) && ypos <= (22 * 8)){
		item = 'w';
	}
	//side nubs
	if (xpos <= (2 * 8) && ypos >= (27 * 8) && ypos <= (28 * 8)){
		item = 'w';
	}
	//lower tetromino
	if (xpos >= (2 * 8) && xpos <= (5 * 8) && ypos >= (24 * 8) && ypos <= (25 * 8)){
		item = 'w';
	}
	if (xpos >= (4 * 8) && xpos <= (5 * 8) && ypos >= (26 * 8) && ypos <= (28 * 8)){
		item = 'w';
	}
	//lower small boxes
	if (xpos >= (7 * 8) && xpos <= (11 * 8) && ypos >= (24 * 8) && ypos <= (25 * 8)){
		item = 'w';
	}
	//bottom T
	if (xpos >= (10 * 8) && xpos <= (17 * 8) && ypos >= (27 * 8) && ypos <= (28 * 8)){
		item = 'w';
	}
	if (xpos == (13 * 8) && ypos >= (29 * 8) && ypos <= (31 * 8)){
		item = 'w';
	}
	//big bottom weird thing
	if (xpos >= (2 * 8) && xpos <= (11 * 8) && ypos >= (30 * 8) && ypos <= (31 * 8)){
		item = 'w';
	}
	if (xpos >= (7 * 8) && xpos <= (8 * 8) && ypos >= (27 * 8) && ypos <= (30 * 8)){
		item = 'w';
	}

	//remove dots from empty spaces
	if (xpos <= (9 * 8) && xpos != (6 * 8) && ypos == (17 * 8)){
		item = 'n';
	}
	if (xpos == (9 * 8) && ypos >= (14 * 8) && ypos <= (22 * 8)){
		item = 'n';
	}
	if (xpos >= (9 * 8) && xpos <= (18 * 8) && ypos == (14 * 8)){
		item = 'n';
	}
	if (xpos >= (9 * 8) && xpos <= (18 * 8) && ypos == (20 * 8)){
		item = 'n';
	}
	if (xpos == (12 * 8) && ypos >= (12 * 8) && ypos <= (13 * 8)){
		item = 'n';
	}
	if (xpos == (13 * 8) && ypos == (26 * 8)){
		item = 'n';
	}

	if (item == 'n' || item == 'w'){
		visible = false;
	}
	else{
		visible = true;
	}

	xpos = tempx;
}

void Tile::setTile(char what, sf::Sprite spr){
	item = what;//(d)ot, (e)nergizer, (n)othing, (c)herry, (s)trawberry, (p)each, (a)pple, (g)rapes, gala(x)ian, (b)ell, (k)ey, (w)all
	sprite = spr;
	sprite.setPosition(xpos, ypos);

	if (item == 'n' || item == 'w'){
		visible = false;
	}
	else{
		visible = true;
		if (item == 'd'){
			sprite.setTextureRect(sf::IntRect(444, 240, 8, 8));
		}
		else if (item == 'e'){
			sprite.setTextureRect(sf::IntRect(436, 240, 8, 8));
		}
	}
}

int Tile::getID(){
	return id;
}

bool Tile::isLegal(){
	return (item != 'w');
}

int Tile::eatTile(){
	int score;
	switch (item){
	case 'd':
		score = 10;
		break;
	case 'e':
		score = 50;
		break;
	case 'c':
		score = 100;
		break;
	case 's':
		score = 300;
		break;
	case 'p':
		score = 500;
		break;
	case 'a':
		score = 700;
		break;
	case 'g':
		score = 1000;
		break;
	case 'x':
		score = 2000;
		break;
	case 'b':
		score = 3000;
		break;
	case 'k':
		score = 5000;
		break;
	default:
		score = 0;
		break;
	}
	item = 'n';
	visible = false;
	return score;
}

void Tile::setTile(char what){
	item = what;
}

bool Tile::isVisible(){
	return visible;
}

sf::Sprite Tile::getSprite(){
	return sprite;
}