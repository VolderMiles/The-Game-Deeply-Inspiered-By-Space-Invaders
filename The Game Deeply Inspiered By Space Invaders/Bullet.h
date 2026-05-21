#pragma once

#include "Character.h"
#include "IHaveCollision.h"

class Bullet : public Character
{
private:
    sf::Vector2f m_direction;
    bool m_targetPlayer;
    float lifetime = 0, max_lifetime = 5;
public:
    Bullet(void) = delete;
    Bullet(sf::Texture& texture, sf::Vector2f start_pos, sf::Vector2f direction, bool targetPlayer = false);
    ~Bullet();

    void Update(float time) override;

    void RebuildBullet(sf::Vector2f pos, sf::Vector2f dir, bool targetPlayer, sf::Texture texture);

    void Enable() override;

    void CheckCollisions();
};
