#include "Character.h"
#include "Constants.h"

Character::Character(sf::Texture& texture, sf::Vector2f start_pos, int health, int sprite_in_spritesheet, sf::Vector2f colliderAxes) :
    m_pos(start_pos),
    m_health(health),
    m_texture(texture),
    m_sprite_in_spritesheet(sprite_in_spritesheet),
    m_sprite(m_texture),
    m_colliderAxes(colliderAxes) {
    m_sprite.setPosition(m_pos);

    m_size = sf::Vector2f(SCALE_FACTOR * PIXELS_PER_UNIT, SCALE_FACTOR * PIXELS_PER_UNIT);
    m_sprite.scale({ SCALE_FACTOR, SCALE_FACTOR });
    m_sprite.setTextureRect(sf::IntRect({ PIXELS_PER_UNIT * m_sprite_in_spritesheet, 0 }, { PIXELS_PER_UNIT, PIXELS_PER_UNIT }));

    SetCollider(m_pos, sf::Vector2f(m_colliderAxes.x * m_size.x, m_colliderAxes.y * m_size.y));
}

Character::~Character() {}

void Character::takeDamage(float damage) {
    m_health -= damage;
}

void Character::setPosition(sf::Vector2f& pos) {
    m_pos = pos;
    m_sprite.setPosition(m_pos);
    SetCollider(m_pos, sf::Vector2f(m_colliderAxes.x * m_size.x, m_colliderAxes.y * m_size.y));
}

int Character::getHP() const {
    return m_health;
}

sf::Vector2f Character::getSize() const {
    return m_size;
}

sf::Vector2f Character::getPosition() const {
    return m_pos;
}

sf::Sprite Character::getSprite() const {
    return m_sprite;
}

void Character::Enable() {
    i_enabled = true;
}
void Character::Disable() {
    i_enabled = false;
}

bool Character::isEnabled() {
    return i_enabled;
}