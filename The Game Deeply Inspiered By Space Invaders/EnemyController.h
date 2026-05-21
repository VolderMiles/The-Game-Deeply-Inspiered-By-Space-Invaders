#pragma once

#include <vector>

#include "SFML/Graphics.hpp"
#include "Enemy.h"
#include "Constants.h"

#include "IdWithColliderStructure.h"

class EnemyController
{
private:
	sf::Texture m_texture;
	int curEnemy = 0;
	short direction = 1;
	bool is_moving_down = false, is_chunk_of_downmove = false, abort_downmove = false;
	float seconds_since_move = 0, seconds_since_shot = 0;

	std::vector<Enemy*> enemies;

	void HandleEnemySwitching();
	int SetAttackingId(int column);

	static EnemyController* enemy_controller;

	EnemyController(sf::Texture& texture);

public:

	EnemyController(EnemyController const&) = delete;
	void operator = (EnemyController const&) = delete;

	static EnemyController* getEnemyController();

	EnemyController(void) = delete;

	void Update(float time);
	int GetActiveEnemyAmount();

	Enemy* GetEnemy(int id);

	std::vector<sf::Sprite> GetSprites();
	std::vector<IdRectStruct> GetStructs();

	void Reset();
};
