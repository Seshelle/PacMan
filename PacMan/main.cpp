#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <stdlib.h>
#include <windows.h>

#include "player.h"
#include "tile.h"
#include "ghost.h"

//written by Sebastian Shelley

int main(){

	//The game map is 224 x 288
	//28 x 36 tiles of 8 pixels square
	
	//spritesheet is 452 x 248

	sf::SoundBuffer introb;

	introb.loadFromFile("pacman_beginning.wav");
	sf::Sound intro;
	intro.setBuffer(introb);

	sf::SoundBuffer nomgb;
	nomgb.loadFromFile("pacman_eatghost.wav");
	sf::Sound nomGhost;
	nomGhost.setBuffer(nomgb);

	sf::SoundBuffer wakab;
	wakab.loadFromFile("pacman_chomp.wav");
	sf::Sound waka;
	waka.setBuffer(wakab);

	sf::SoundBuffer dieb;
	dieb.loadFromFile("pacman_death.wav");
	sf::Sound deathNoise;
	deathNoise.setBuffer(dieb);

	bool started = false;
	bool godMode = true;
	int addScore = 0;
	int score = 0;
	int dots = 0;
	int lives = 2;
	int locationID;
	double targetX;
	double targetY;
	double distance;
	double lastDistance;
	char nextDirection;

	int random;
	srand(100);

	sf::RenderWindow window(sf::VideoMode(224, 288), "SFML Application");

	sf::Texture spriteSheet;
	spriteSheet.loadFromFile("Pac Man Map.png");

	sf::Sprite mazeSprite;
	mazeSprite.setTexture(spriteSheet);
	mazeSprite.setPosition(0, 24);

	//create pacman
	sf::Sprite player;
	player.setTexture(spriteSheet);
	Player pacMan(player);

	sf::Sprite life1;
	sf::Sprite life2;
	life1.setTexture(spriteSheet);
	life2.setTexture(spriteSheet);
	life1.setTextureRect(sf::IntRect(225, 0, 16, 16));
	life2.setTextureRect(sf::IntRect(225, 0, 16, 16));
	life1.setPosition(2 * 8, 34 * 8);
	life2.setPosition(4 * 8, 34 * 8);

	Tile tileSet[28][36];
	//give each tile a location and unique ID
	int ID = 0;
	for (int i = 0; i < 28; i++){
		for (int j = 0; j < 36; j++){
			tileSet[i][j].setTile('d', mazeSprite);
			tileSet[i][j].setLocationID(i * 8, j * 8, ID);
			ID++;
		}
	}

	tileSet[1][6].setTile('e', mazeSprite);
	tileSet[26][6].setTile('e', mazeSprite);
	tileSet[1][26].setTile('e', mazeSprite);
	tileSet[26][26].setTile('e', mazeSprite);

	//create ghosts
	//(i)nky, (b)linky, (c)lyde, (p)inky
	Ghost blinky('b', 110, (14 * 8) + 4, mazeSprite);
	Ghost pinky('p', 100, 100, mazeSprite);
	Ghost inky('i', 100, 100, mazeSprite);
	Ghost clyde('c', 120, 100, mazeSprite);

	Ghost enemies[4] = {blinky, pinky, inky, clyde};

	double inkyX;
	double inkyY;

	while (window.isOpen()){

		sf::Event event;
		while (window.pollEvent(event)){

			if (event.type == sf::Event::Closed)
				window.close();
		}

		//change PacMan's facing to direction pressed if direction valid
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			if (tileSet[pacMan.getTileX() - 1][pacMan.getTileY()].isLegal() == true){
				pacMan.move('l');
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			if (tileSet[pacMan.getTileX() + 1][pacMan.getTileY()].isLegal() == true){
				pacMan.move('r');
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			if (tileSet[pacMan.getTileX()][pacMan.getTileY() - 1].isLegal() == true){
				pacMan.move('u');
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			if (tileSet[pacMan.getTileX()][pacMan.getTileY() + 1].isLegal() == true){
				pacMan.move('d');
			}
		}

		//move PacMan forward if there is no wall in front of him
		if (pacMan.getFacing() == 'u' && tileSet[pacMan.getTileX()][pacMan.getTileY() - 1].isLegal() == true ||
			pacMan.getFacing() == 'd' && tileSet[pacMan.getTileX()][pacMan.getTileY() + 1].isLegal() == true ||
			pacMan.getFacing() == 'l' && tileSet[pacMan.getTileX() - 1][pacMan.getTileY()].isLegal() == true ||
			pacMan.getFacing() == 'r' && tileSet[pacMan.getTileX() + 1][pacMan.getTileY()].isLegal() == true){
			pacMan.update();
		}
		
		//eat whatever is in current tile, add to score, and apply effects
		addScore = tileSet[pacMan.getTileX()][pacMan.getTileY()].eatTile();
		score = score + addScore;
		if (addScore == 10){
			waka.play();
			dots++;
			for (int i = 0; i < 4; i++){
				enemies[i].add();
			}
			if (dots == 254){
				printf("all dots eaten");
				for (int j = 0; j < 4; j++){
					enemies[j].setMode('h');
				}
				pacMan.die();
				for (int k = 0; k < 28; k++){
					for (int l = 0; l < 36; l++){
						tileSet[k][l].resetTile();
					}
				}
				tileSet[1][6].setTile('e', mazeSprite);
				tileSet[26][6].setTile('e', mazeSprite);
				tileSet[1][26].setTile('e', mazeSprite);
				tileSet[26][26].setTile('e', mazeSprite);
				started = false;
			}
		}
		else if (addScore == 50){
			for (int i = 0; i < 4; i++){
				enemies[i].setMode('f');
				dots++;
				for (int i = 0; i < 4; i++){
					enemies[i].add();
				}
				if (dots == 254){
					printf("all dots eaten");
					for (int j = 0; j < 4; j++){
						enemies[j].setMode('h');
					}
					pacMan.die();
					for (int k = 0; k < 28; k++){
						for (int l = 0; l < 36; l++){
							tileSet[k][l].resetTile();
						}
					}
					tileSet[1][6].setTile('e', mazeSprite);
					tileSet[26][6].setTile('e', mazeSprite);
					tileSet[1][26].setTile('e', mazeSprite);
					tileSet[26][26].setTile('e', mazeSprite);
					started = false;
				}
			}
		}

		for (int i = 0; i < 4; i++){
			//find pacmans's tile and compare to ghost's tile, if same eat or die
			locationID = tileSet[pacMan.getTileX()][pacMan.getTileY()].getID();
			if (tileSet[enemies[i].getTileX()][enemies[i].getTileY()].getID() == locationID){
				if (enemies[i].getMode() == 'f'){
					enemies[i].setMode('h');
					nomGhost.play();
				}
				else if (godMode == false){
					deathNoise.play();
					Sleep(2000);
					for (int j = 0; j < 4; j++){
						enemies[j].setMode('h');
					}
					pacMan.die();
					lives--;
					if (lives < 0){
						score = 0;
						for (int k = 0; k < 28; k++){
							for (int l = 0; l < 36; l++){
								tileSet[k][l].resetTile();
							}
						}
						tileSet[1][6].setTile('e', mazeSprite);
						tileSet[26][6].setTile('e', mazeSprite);
						tileSet[1][26].setTile('e', mazeSprite);
						tileSet[26][26].setTile('e', mazeSprite);
						started = false;
					}
					break;
				}

			}

			//check if each ghost is in a new tile, break if false
			if (tileSet[enemies[i].getTileX()][enemies[i].getTileY()].getID() != enemies[i].getCurrentTile()){
				//set up target tile

				//chase mode different for each ghost
				if (enemies[i].getName() == 'b' && enemies[i].getMode() == 'c'){
					targetX = pacMan.getTileX();
					targetY = pacMan.getTileY();
				}

				if (enemies[i].getName() == 'p' && enemies[i].getMode() == 'c'){
					if (pacMan.getFacing() == 'l'){
						targetX = pacMan.getTileX() - 3;
						targetY = pacMan.getTileY();
					}
					if (pacMan.getFacing() == 'r'){
						targetX = pacMan.getTileX() + 3;
						targetY = pacMan.getTileY();
					}
					if (pacMan.getFacing() == 'u'){
						//this is wrong intentionally, it is a bug in the original version of PacMan
						targetX = pacMan.getTileX() - 3;
						targetY = pacMan.getTileY() - 3;
					}
					if (pacMan.getFacing() == 'd'){
						targetX = pacMan.getTileX();
						targetY = pacMan.getTileY() + 3;
					}
				}

				if (enemies[i].getName() == 'i' && enemies[i].getMode() == 'c'){
					if (pacMan.getFacing() == 'l'){
						inkyX = pacMan.getTileX() - 3;
						inkyY = pacMan.getTileY();
					}
					if (pacMan.getFacing() == 'r'){
						inkyX = pacMan.getTileX() + 3;
						inkyY = pacMan.getTileY();
					}
					if (pacMan.getFacing() == 'u'){
						//this is wrong intentionally, it is a bug in the original version of PacMan
						inkyX = pacMan.getTileX() - 3;
						inkyY = pacMan.getTileY() - 3;
					}
					if (pacMan.getFacing() == 'd'){
						inkyX = pacMan.getTileX();
						inkyY = pacMan.getTileY() + 3;
					}

					targetX = inkyX + (inkyX - enemies[0].getTileX());
					targetY = inkyY + (inkyY - enemies[0].getTileY());
				}

				if (enemies[i].getName() == 'c' && enemies[i].getMode() == 'c'){
					targetX = pacMan.getTileX();
					targetY = pacMan.getTileY();

					if (sqrt((enemies[i].getTileX() - targetX) * (enemies[i].getTileX() - targetX)
						+ (pacMan.getTileY() - enemies[i].getTileY()) * (pacMan.getTileY() - enemies[i].getTileY())) < 8){
						targetX = 0;
						targetY = 34;
					}
				}

				//set target to home corner in scatter mode
				if (enemies[i].getMode() == 's'){
					if (enemies[i].getName() == 'b'){
						targetX = 26;
						targetY = 0;
					}
					if (enemies[i].getName() == 'p'){
						targetX = 2;
						targetY = 0;
					}
					if (enemies[i].getName() == 'i'){
						targetX = 27;
						targetY = 34;
					}
					if (enemies[i].getName() == 'c'){
						targetX = 0;
						targetY = 33;
					}
				}

				//check each tile in order around ghost, except for behind, for closest tile to target
				//right down left up order

				if (enemies[i].getMode() == 'c' || enemies[i].getMode() == 's'){
					lastDistance = -1;
					if (tileSet[enemies[i].getTileX() + 1][enemies[i].getTileY()].isLegal() == true && enemies[i].getFacing() != 'l'){
						nextDirection = 'r';
						lastDistance = (sqrt((enemies[i].getTileX() + 1 - targetX) * (enemies[i].getTileX() + 1 - targetX)
							+ (pacMan.getTileY() - enemies[i].getTileY()) * (pacMan.getTileY() - enemies[i].getTileY())));
						//printf("R");
					}
					if (tileSet[enemies[i].getTileX()][enemies[i].getTileY() + 1].isLegal() == true && enemies[i].getFacing() != 'u'){
						distance = (sqrt((enemies[i].getTileX() - targetX) * (enemies[i].getTileX() - targetX)
							+ (enemies[i].getTileY() + 1 - targetY) * (enemies[i].getTileY() + 1 - targetY)));
						if (distance <= lastDistance || lastDistance == -1){
							nextDirection = 'd';
							lastDistance = distance;
						}
						//printf("D");
					}
					if (tileSet[enemies[i].getTileX() - 1][enemies[i].getTileY()].isLegal() == true && enemies[i].getFacing() != 'r'){
						distance = (sqrt((enemies[i].getTileX() - 1 - targetX) * (enemies[i].getTileX() - 1 - targetX)
							+ (enemies[i].getTileY() - targetY) * (enemies[i].getTileY() - targetY)));
						if (distance <= lastDistance || lastDistance == -1){
							nextDirection = 'l';
							lastDistance = distance;
						}
						//printf("L");
					}
					if (tileSet[enemies[i].getTileX()][enemies[i].getTileY() - 1].isLegal() == true && enemies[i].getFacing() != 'd'){
						distance = (sqrt((enemies[i].getTileX() - targetX) * (enemies[i].getTileX() - targetX)
							+ (enemies[i].getTileY() - 1 - targetY) * (enemies[i].getTileY() - 1 - targetY)));
						if (distance <= lastDistance || lastDistance == -1){
							nextDirection = 'u';
						}
						//printf("U");
					}
				}
				else if (enemies[i].getMode() == 'f'){
					random = rand() % 4;
					for (int j = 0; j < 4; j++){
						if (tileSet[enemies[i].getTileX()][enemies[i].getTileY() - 1].isLegal() == true && enemies[i].getFacing() != 'd'){
							if (random == 0){
								nextDirection = 'u';
								random--;
							}
							else{ random--; }
						}
						if (tileSet[enemies[i].getTileX() - 1][enemies[i].getTileY()].isLegal() == true && enemies[i].getFacing() != 'r'){
							if (random == 0){
								nextDirection = 'l';
								random--;
							}
							else{ random--; }
						}
						if (tileSet[enemies[i].getTileX()][enemies[i].getTileY() + 1].isLegal() == true && enemies[i].getFacing() != 'u'){
							if (random == 0){
								nextDirection = 'd';
								random--;
							}
							else{ random--; }
						}
						if (tileSet[enemies[i].getTileX() + 1][enemies[i].getTileY()].isLegal() == true && enemies[i].getFacing() != 'l'){
							if (random == 0){
								nextDirection = 'r';
								random--;
							}
							else{ random--; }
						}
					}
				}

				//if that tile is closer to target than last, face towards that one
				enemies[i].move(nextDirection);

				//set new currentTile
				enemies[i].setCurrentTile(tileSet[enemies[i].getTileX()][enemies[i].getTileY()].getID());
			}

			enemies[i].update();
		}

		window.clear();
		window.draw(mazeSprite);

		for (int i = 0; i < 28; i++){
			for (int j = 0; j < 36; j++){
				if (tileSet[i][j].isVisible() == true){
					window.draw(tileSet[i][j].getSprite());
				}
			}
		}
		window.draw(pacMan.getSprite());
		window.draw(enemies[0].getSprite());
		window.draw(enemies[1].getSprite());
		window.draw(enemies[2].getSprite());
		window.draw(enemies[3].getSprite());
		if (lives > 0){
			window.draw(life1);
		}
		if (lives > 1){
			window.draw(life2);
		}
		window.display();

		if (started == false){
			started = true;
			intro.play();
			Sleep(4000);
		}
		
	}

}