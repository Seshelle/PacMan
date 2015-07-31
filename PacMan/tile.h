#include <SFML/Graphics.hpp>

class Tile{
private:
	double xpos;
	double ypos;
	sf::Sprite sprite;
	int id;
	char item;//(d)ot, (e)nergizer, (n)othing, (c)herry, (s)trawberry, (p)each, (a)pple, (g)rapes, gala(x)ian, (b)ell, (k)ey
	bool visible;
public:
	Tile(double x, double y, bool passable, char what, int number, sf::Sprite spr);
	Tile();
	void setTile(char what, sf::Sprite spr);
	void setTile(char what);
	void resetTile();
	void setLocationID(double x, double y, int number);
	int getID();
	int eatTile();
	bool isLegal();
	bool isVisible();
	sf::Sprite getSprite();
};