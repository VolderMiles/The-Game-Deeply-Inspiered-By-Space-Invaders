#include "PlayerController.h"

#include "Player.h"
#include "Constants.h"

PlayerController* PlayerController::controller = nullptr;

PlayerController::~PlayerController() {
    delete controller;
}

PlayerController* PlayerController::getPlayerController() {
    if (!controller) {
        controller = new PlayerController();
    }

    return controller;
}

void PlayerController::controllPlayer(Player* player, float time) {
    sf::Vector2f updated_pos = player->getPosition();

    // Movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) &&
        updated_pos.x - PLAYER_SPEED * time >= 0)
        updated_pos.x -= PLAYER_SPEED * time;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) &&
        updated_pos.x + PLAYER_SPEED * time <= SCREEN_WIDTH - ENEMY_X_OFFSET_IN_UNITS * PIXELS_PER_UNIT * SCALE_FACTOR)
        updated_pos.x += PLAYER_SPEED * time;

    player->setPosition(updated_pos);

    //Shooting
    if (player->GetCooldown() <= 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        player->Shoot();
        player->ResetCooldown();
    }
}
