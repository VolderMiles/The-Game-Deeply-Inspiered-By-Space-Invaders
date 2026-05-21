#pragma once

#include <SFML/Graphics.hpp>

#include "IHaveCollision.h"

class Character : public IHaveCollision {
protected:
	int m_sprite_in_spritesheet;
	int m_health;
	sf::Vector2f m_size;
	sf::Vector2f m_pos;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	bool i_enabled = false;

	sf::Vector2f m_colliderAxes;

public:
	Character(void) = delete;
	Character(sf::Texture& texture, sf::Vector2f start_pos, int health = 1, int sprite_in_spritesheet = 0, sf::Vector2f colliderAxes = sf::Vector2f(1, 1));
	virtual ~Character();

	virtual void Update(float time) = 0;
	virtual void takeDamage(float damage);

	void setPosition(sf::Vector2f& pos);

	int getHP() const;
	sf::Vector2f getSize() const;
	sf::Vector2f getPosition() const;
	sf::Sprite getSprite() const;

	virtual void Enable();
	virtual void Disable();
	bool isEnabled();
};
