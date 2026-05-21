#include "EnemyController.h"

#include "BulletPool.h"
#include "Resetter.h"

EnemyController* EnemyController::enemy_controller = nullptr;

EnemyController* EnemyController::getEnemyController() {
	if (!enemy_controller) {
		sf::Texture sample_texture = sf::Texture("../Assets/Textures/enemies.png");
		enemy_controller = new EnemyController(sample_texture);
	}

	return enemy_controller;
}

EnemyController::EnemyController(sf::Texture& texture) :
	m_texture(texture) {

	for (int x = ENEMY_RAWS-1; x > -1; x--) {
		for (int y = 0; y < ENEMY_COLUMNS; y++) {
			enemies.emplace_back(new Enemy(texture, sf::Vector2f((1 + ENEMY_GAP_IN_UNITS) * PIXELS_PER_UNIT * SCALE_FACTOR * (ENEMY_X_OFFSET_IN_UNITS + y),
				(1 + ENEMY_GAP_IN_UNITS) * PIXELS_PER_UNIT * SCALE_FACTOR * (ENEMY_Y_OFFSET_IN_UNITS + x)), 1, 3 - x, (4 - x)*100));
		}
	}
}

int EnemyController::GetActiveEnemyAmount() {
	int a = 0;
	for (int i = 0; i < enemies.size(); i++)
		a++;
	return a;
}

void EnemyController::HandleEnemySwitching() {
	curEnemy++;
	if (curEnemy >= enemies.size()) {
		curEnemy -= enemies.size();
		if ((is_moving_down != is_chunk_of_downmove) && !abort_downmove) {
			is_moving_down = is_chunk_of_downmove;
			direction *= -1;
		}
		else {
			if (abort_downmove) {
				if (is_chunk_of_downmove) direction *= -1;
				abort_downmove = false;
			}
			is_moving_down = false;
			is_chunk_of_downmove = false;
		}
	}
}

void EnemyController::Update(float time) {
	if (GetActiveEnemyAmount() == 0)
		return;

	// Moving
	seconds_since_move += time;
	if (seconds_since_move >= ENEMY_SECONDS_TO_MOVE) {
		seconds_since_move -= ENEMY_SECONDS_TO_MOVE;

		while (!enemies[curEnemy]->isEnabled()) {
			HandleEnemySwitching();
		}

		sf::Vector2f cur_pos = enemies[curEnemy]->getPosition();
		if (!is_moving_down) {
			float new_x_pos = cur_pos.x + PIXELS_PER_UNIT * SCALE_FACTOR * ENEMY_X_STEP_IN_UNITS * direction;

			sf::Vector2f nvp = sf::Vector2f(new_x_pos, cur_pos.y);
			enemies[curEnemy]->setPosition(nvp);

			if (new_x_pos > SCREEN_WIDTH - (1 + ENEMY_X_OFFSET_IN_UNITS) * PIXELS_PER_UNIT * SCALE_FACTOR ||
				new_x_pos < ENEMY_X_OFFSET_IN_UNITS * PIXELS_PER_UNIT * SCALE_FACTOR) {
				is_chunk_of_downmove = true;
			}
			if (!abort_downmove)
				abort_downmove = cur_pos.y + PIXELS_PER_UNIT * SCALE_FACTOR * ENEMY_Y_STEP_IN_UNITS >= ENEMY_BOTTOM_PIXEL;
		}
		else {
			float new_y_pos = cur_pos.y + PIXELS_PER_UNIT * SCALE_FACTOR * ENEMY_Y_STEP_IN_UNITS;

			sf::Vector2f nvp = sf::Vector2f(cur_pos.x, new_y_pos);
			enemies[curEnemy]->setPosition(nvp);
		}

		HandleEnemySwitching();
	}
	// Shooting
	seconds_since_shot += time;
	if (seconds_since_shot >= ENEMY_COOLDOWN) {
		seconds_since_shot -= ENEMY_COOLDOWN;

		int attackingColumn = rand() % ENEMY_COLUMNS;
		int attId = SetAttackingId(attackingColumn);

		BulletPool* pool = BulletPool::getPool();
		Bullet* bul = pool->GetBulletFromPool();

		bul->RebuildBullet(enemies[attId]->getPosition(), sf::Vector2f(0, 1), true, sf::Texture("../Assets/Textures/bullet.png"));
	}
}

int EnemyController::SetAttackingId(int column) {
	int id = -1;
	for (int y = 0; y < ENEMY_COLUMNS; y++) {
		bool flag = false;
		for (int x = 0; x < ENEMY_RAWS; x++) {
			if (!enemies[x + y * ENEMY_RAWS]->isEnabled())
				continue;
			id = x + y * ENEMY_RAWS;
			if (id >= column * ENEMY_RAWS && id < (column + 1) * ENEMY_RAWS) {
				flag = true;
				break;
			}
			break;
		}
		if (flag) break;
	}
	return id;
}

Enemy* EnemyController::GetEnemy(int id) {
	if (id < 0 || id >= enemies.size())
		return nullptr;
	return enemies[id];
}

std::vector<sf::Sprite> EnemyController::GetSprites() {
	std::vector<sf::Sprite> sprs;

	for (int y = 0; y < ENEMY_COLUMNS; y++) {
		for (int x = 0; x < ENEMY_RAWS; x++) {
			if (enemies[x + y * ENEMY_RAWS]->isEnabled())
				sprs.emplace_back(enemies[x + y * ENEMY_RAWS]->getSprite());
		}
	}

	return sprs;
}

std::vector<IdRectStruct> EnemyController::GetStructs() {
	std::vector<IdRectStruct> list;
	for (int i = 0; i < enemies.size(); i++) {
		if (!enemies[i]->isEnabled())
			continue;
		IdRectStruct temp = { i, enemies[i]->GetCollider() };
		list.emplace_back(temp);
	}
	return list;
}

void EnemyController::Reset() {
	for (int x = 0; x < ENEMY_RAWS; x++) {
		for (int y = 0; y < ENEMY_COLUMNS; y++) {
			sf::Vector2f new_pos = sf::Vector2f((1 + ENEMY_GAP_IN_UNITS) * PIXELS_PER_UNIT * SCALE_FACTOR * (ENEMY_X_OFFSET_IN_UNITS + y),
				(1 + ENEMY_GAP_IN_UNITS) * PIXELS_PER_UNIT * SCALE_FACTOR * (ENEMY_Y_OFFSET_IN_UNITS + x));
			enemies[ENEMY_RAWS*ENEMY_COLUMNS - 1 - y - x * ENEMY_COLUMNS]->setPosition(new_pos);
			enemies[ENEMY_RAWS * ENEMY_COLUMNS - 1 - y - x * ENEMY_COLUMNS]->Enable();
		}
	}
}