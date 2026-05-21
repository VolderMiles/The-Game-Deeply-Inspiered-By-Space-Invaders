#include "BulletPool.h"

BulletPool* BulletPool::bullet_pool = nullptr;

BulletPool* BulletPool::getPool() {
	if (!bullet_pool) {
		bullet_pool = new BulletPool();
	}

	return bullet_pool;
}

Bullet* BulletPool::CreateNewBullet() {
	Bullet* bul = new Bullet(sample_texture, sf::Vector2f(0, 0), sf::Vector2f(0, 0));
	pool.emplace_back(bul);
	return bul;
}

Bullet* BulletPool::GetBulletFromPool() {

	for (int i = 0; i < pool.size(); i++) {
		if (!pool[i]->isEnabled())
			return pool[i];
	}

	return CreateNewBullet();
}

void BulletPool::Update(float time) {
	for (int i = 0; i < pool.size(); i++) {
		if (pool[i]->isEnabled())
			pool[i]->Update(time);
	}
}

std::vector<sf::Sprite> BulletPool::GetSprites() {
	std::vector<sf::Sprite> sprs;
	for (int i = 0; i < pool.size(); i++) {
		if (pool[i]->isEnabled())
			sprs.emplace_back(pool[i]->getSprite());
	}
	return sprs;
}
void BulletPool::Reset() {
	for (int i = 0; i < pool.size(); i++) {
		pool[i]->Disable();
	}
}
