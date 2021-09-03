#ifndef DEF_TEXTURE
#define DEF_TEXTURE

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

/*
	Creer une texture affichable dans une fenetre à partir d'une image
*/

class Textures {
public:
	Textures(std::string file);
	Textures(std::string file, int depX, int depY, int pasX, int pasY);
	Textures(std::string file, sf::IntRect r);

	~Textures();
	void setSpritePosition(int x, int y);
	sf::Vector2f getSpritePosition();
	void drawTexture(sf::RenderTarget& window);
	void setScale(float x, float y);
	sf::IntRect getBounds();

private:
	sf::Texture texture;
	sf::Sprite sprite; // permet d'afficher ma texture dans une fenetre

	void initTexture(std::string file);
	void initSprite();
};

#endif
