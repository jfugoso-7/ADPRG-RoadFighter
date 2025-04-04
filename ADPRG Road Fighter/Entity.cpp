#include "Entity.h"
#include "TextureManager.h"

Entity::Entity(const sf::Texture& texture)
	: mTexture(&texture), mSprite(texture) // directly construct mSprite
{
}

void Entity::setTexture(sf::Texture& texture) {
	mTexture = &texture;
	mSprite.setTexture(*mTexture);
}

sf::Sprite* Entity::getSprite() {
	return &mSprite;
}

void Entity::update() {
	if (clock.getElapsedTime().asMilliseconds() > 100) {
		std::string key = rootTexName + std::to_string(ctr);
		sf::Texture* texture = TextureManager::getInstance()->getTexture(key);
		setTexture(*texture); // now uses reference

		ctr++;
		ctr %= frames;
		clock.restart();
	}
}