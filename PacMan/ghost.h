#include <SFML/Graphics.hpp>

class Ghost{
private:
	double speed;
	char name;//(i)nky, (b)linky, (c)lyde, (p)inky
	char mode;//(c)hase, (s)catter, (h)ome, (f)rightened
	int targetTile;
	int currentTile;
	char facing;
	int dotCounter;
	int fright;
	sf::Sprite sprite;
public:
	Ghost(char which, double x, double y, sf::Sprite spr);
	Ghost();
	void setGhost(char which, double x, double y, sf::Sprite spr);
	void setMode(char newMode);
	char getMode();
	void move(char face);
	void reverse();
	void update();
	int getTileX();
	int getTileY();
	void setCurrentTile(int tile);
	int getCurrentTile();
	char getFacing();
	char getName();
	void add();
	sf::Sprite getSprite();
};