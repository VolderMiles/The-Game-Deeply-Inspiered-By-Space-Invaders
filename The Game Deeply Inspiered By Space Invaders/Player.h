#pragma once

#include "Character.h"
#include "BulletPool.h"
#include "IHaveCollision.h"

class PlayerController;

class Player : public Character {
private:
    PlayerController* m_controller;
    BulletPool* m_pool;
    float cooldown = 0;

    static Player* player;

public:

    Player(Player const&) = delete;
    void operator = (Player const&) = delete;
    ~Player();

    static Player* getPlayer();

    Player(void) = delete;
    Player(sf::Texture& texture, sf::Vector2f start_pos, int health = 3);

    void Update(float time) override;

    float GetCooldown();
    void ResetCooldown();
    void Shoot();

    void takeDamage(float damage) override;

    void Reset();
};
