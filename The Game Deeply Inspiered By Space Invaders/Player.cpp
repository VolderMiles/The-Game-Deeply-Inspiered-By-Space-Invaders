#include "Player.h"

#include "PlayerController.h"
#include "Constants.h"
#include "Bullet.h"

Player* Player::player = nullptr;

Player::~Player() {
    delete player;
}

Player* Player::getPlayer() {
    if (!player) {
        sf::Texture sample_texture = sf::Texture("../Assets/Textures/player.png");
        player = new Player(sample_texture, sf::Vector2f((SCREEN_WIDTH + SCALE_FACTOR*PIXELS_PER_UNIT)/2, PLAYER_START_Y), 3);
    }

    return player;
}

Player::Player(sf::Texture& texture, sf::Vector2f start_pos, int health) :
    Character::Character {texture, start_pos, health, 0} {
    m_controller = PlayerController::getPlayerController();
    m_pool = BulletPool::getPool();

    SetCollider(m_pos, m_size);
}

void Player::Update(float time) {
    if (cooldown > 0)
        cooldown -= time;

    m_controller->controllPlayer(this, time);

    m_sprite.setPosition(m_pos);
}

float Player::GetCooldown() {
    return cooldown;
}
void Player::ResetCooldown() {
    cooldown = PLAYER_COOLDOWN;
}
void Player::Shoot() {
    Bullet* bul = m_pool->GetBulletFromPool();

    bul->RebuildBullet(m_pos, sf::Vector2f(0, -1), false, sf::Texture("../Assets/Textures/bullet.png"));
}

void Player::takeDamage(float damage) {
    Character::takeDamage(damage);
}

void Player::Reset() {
    sf::Vector2f new_pos = sf::Vector2f((SCREEN_WIDTH + SCALE_FACTOR * PIXELS_PER_UNIT) / 2, PLAYER_START_Y);
    setPosition(new_pos);
    m_health = PLAYER_START_HP;
}
