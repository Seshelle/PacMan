#include <SFML/Graphics.hpp>

class Player{
private:
	float speed;
	char facing;
	int timePass;
	int animation;
	sf::Sprite sprite;
	bool isDead;
public:
	Player(sf::Sprite spr);
	void move(char direction);
	void update();
	double getXPos();
	double getYPos();
	sf::Sprite getSprite();
	char getFacing();
	int getTileX();
	int getTileY();
	int kludgeUp();
	void fixUp();
	int kludgeDown();
	void fixDown();
	void die();
};