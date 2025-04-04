#include <SFML/Graphics.hpp>

class Entity {
public:
	Entity(const sf::Texture& texture);
	void setTexture(sf::Texture& texture);
	sf::Sprite* getSprite();
	void update();

	std::string rootTexName;
	int frames;

private:
	const sf::Texture* mTexture = nullptr; // make it a const pointer
	sf::Sprite mSprite;
	sf::Clock clock;
	int ctr = 0;
};