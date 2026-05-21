#include "Bullet.h"
#include "BulletPool.h"
#include "Constants.h"

#include "Player.h"
#include "EnemyController.h"
#include <vector>

Bullet::Bullet(sf::Texture& texture, sf::Vector2f start_pos, sf::Vector2f direction, bool targetPlayer) :
	Character::Character{ texture, start_pos, 1, 0, sf::Vector2f(0.5, 0.5) },
	m_direction(direction), lifetime(max_lifetime), m_targetPlayer(targetPlayer) { }

Bullet::~Bullet() { }

void Bullet::Update(float time) {
	if (!i_enabled)
		return;
	CheckCollisions();

	sf::Vector2f newPos({ m_pos.x + m_direction.x * BULLET_SPEED * time, m_pos.y + m_direction.y * BULLET_SPEED * time });
	this->setPosition(newPos);

	lifetime -= time;
	if (lifetime <= 0)
		Disable();
}

void Bullet::RebuildBullet(sf::Vector2f pos, sf::Vector2f dir, bool targetPlayer, sf::Texture texture) {
	m_pos = pos;
	m_direction = dir;
	m_targetPlayer = targetPlayer;
	Enable();
}

void Bullet::Enable() {
	Character::Enable();
	lifetime = max_lifetime;
}

void Bullet::CheckCollisions() {
	if (max_lifetime - lifetime <= 0.01)
		return;
	if (m_targetPlayer) {
		Player* player = Player::getPlayer();

		if (IsColliding(player->GetCollider())) {
			Disable();
			player->takeDamage(1);
		}
	}
	else {
		EnemyController* enemy_controller = EnemyController::getEnemyController();
		std::vector<IdRectStruct> structs = enemy_controller->GetStructs();

		for (int i = 0; i < structs.size(); i++) {
			if (IsColliding(structs[i].rect)) {
				enemy_controller->GetEnemy(structs[i].id)->takeDamage(1);
				Disable();
			}
		}
	}
}