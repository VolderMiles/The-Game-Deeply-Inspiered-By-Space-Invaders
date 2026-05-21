#pragma once

#include "SFML/Graphics.hpp"

class IHaveCollision
{
protected:
	void SetCollider(sf::Vector2f pos, sf::Vector2f size);
private:
	sf::FloatRect collider;
public:
	bool IsColliding(sf::FloatRect other);
	sf::FloatRect GetCollider();
};
