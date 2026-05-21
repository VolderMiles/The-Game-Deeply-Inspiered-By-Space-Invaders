#include "Enemy.h"

#include "Constants.h"
#include "ScoreHandler.h"

Enemy::Enemy(sf::Texture& texture, sf::Vector2f start_pos, float health, int sprite_in_spritesheet, int score) :
    Character::Character{texture, start_pos, health, sprite_in_spritesheet}, m_score(score) { }

Enemy::~Enemy() { }

void Enemy::Update(float time) {
    m_sprite.setPosition(m_pos);
}

void Enemy::takeDamage(float damage) {
    Character::takeDamage(damage);
    if (m_health <= 0) {
        ScoreHandler::getScoreHandler()->IncraeseScore(m_score);
        Disable();
    }
}