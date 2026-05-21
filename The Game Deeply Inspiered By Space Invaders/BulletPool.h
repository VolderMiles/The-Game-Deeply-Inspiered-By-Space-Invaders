#pragma once

#include <vector>

#include "SFML/Graphics.hpp"
#include "Bullet.h"
#include "Constants.h"

class BulletPool
{
private:
	sf::Texture sample_texture = sf::Texture("../Assets/Textures/bullet.png");

	Bullet* CreateNewBullet();
	std::vector<Bullet*> pool;

	BulletPool() = default;

	static BulletPool* bullet_pool;

public:

	BulletPool(BulletPool const&) = delete;
	void operator = (BulletPool const&) = delete;

	static BulletPool* getPool();

	Bullet* GetBulletFromPool();

	void Update(float time);

	std::vector<sf::Sprite> GetSprites();

	void Reset();
};
