#pragma once

#include "Character.h"

class Enemy : public Character {
private:
    int m_score = 0;
public:
    Enemy(void) = delete;
    Enemy(sf::Texture& texture, sf::Vector2f start_pos, float health = 1, int spritesheet_x_offset = 0, int score = 100);
    ~Enemy();

    void Update(float time) override;
    void takeDamage(float damage) override;
};
