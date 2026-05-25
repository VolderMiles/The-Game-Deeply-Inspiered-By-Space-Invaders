#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>

#include "Constants.h"
#include "Player.h"
#include "EnemyController.h"
#include "BulletPool.h"
#include "ScoreHandler.h"

#include "Resetter.h"

Player* player = Player::getPlayer();
EnemyController* enemyController = EnemyController::getEnemyController();
BulletPool* bullet_pool = BulletPool::getPool();
ScoreHandler* scoreHandler = ScoreHandler::getScoreHandler();
Resetter* resetter = Resetter::getResetter();

int game_state = 1;
// default - normal game state
// 1 - welcome screen
// 2 - game over

int main() {
    sf::RenderWindow window(sf::VideoMode({ SCREEN_WIDTH, SCREEN_HEIGHT }), "The Game Deeply Inspiered By Space Invaders");

    sf::Font font;
    font.openFromFile("../Assets/Fonts/MonogramExtended.ttf");
    // Common Texts
    sf::Text score_text = sf::Text(font, "Score: ");
    sf::Text hi_score_text = sf::Text(font, "Hi-Score: ");
    sf::Text press_enter_text = sf::Text(font, "Press Enter To Start");

    score_text.setPosition(sf::Vector2f(SCREEN_WIDTH / 8, 0));
    hi_score_text.setPosition(sf::Vector2f(SCREEN_WIDTH * 5 / 8, 0));
    press_enter_text.setPosition(sf::Vector2f(SCREEN_WIDTH / 3, SCREEN_HEIGHT - press_enter_text.getCharacterSize()));
    // Game Texts
    sf::Text fps_text = sf::Text(font, "FPS: ");
    sf::Text hp_text = sf::Text(font, "Hp: ");

    hp_text.setPosition(sf::Vector2f(0, SCREEN_HEIGHT - hp_text.getCharacterSize()));
    // Welcome Screen
    sf::Text how_to_play_text = sf::Text(font, "A/D to move left/right\nSpace to shoot\n0 HP = defeat\nGood luck");
    sf::Text points_text = sf::Text(font, "- 100 points\n\n- 200 points\n\n- 300 points\n\n- 400 points");
    float flashing_time = 0.75, cur_flashing_time = 0; // flashing_time - half period
    sf::Texture texture("../Assets/Textures/enemies.png");

    std::vector<sf::Sprite> welcome_sprites;

    how_to_play_text.setPosition(sf::Vector2f(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 8));
    points_text.setPosition(sf::Vector2f(SCREEN_WIDTH * 3.75 / (float)8, SCREEN_HEIGHT / 3));

    for (int i = 0; i < 4; i++) {
        welcome_sprites.emplace_back(sf::Sprite(texture));
        welcome_sprites.back().scale({ SCALE_FACTOR, SCALE_FACTOR });
        welcome_sprites.back().setTextureRect(sf::IntRect({ PIXELS_PER_UNIT * i, 0 }, { PIXELS_PER_UNIT, PIXELS_PER_UNIT }));
        welcome_sprites.back().setPosition(sf::Vector2f(points_text.getPosition().x - SCALE_FACTOR * PIXELS_PER_UNIT*1.5, points_text.getPosition().y + i * SCALE_FACTOR * PIXELS_PER_UNIT*1.5));
    }
    // Game Over Screen
    sf::Text game_over_text = sf::Text(font, "Game Over");

    game_over_text.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.2, SCREEN_HEIGHT / 10));

    sf::Clock clock;

    resetter->Reset();
    scoreHandler->LoadScore();

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        score_text.setString("Score: " + std::to_string(scoreHandler->GetScore()));
        hi_score_text.setString("Hi-Score: " + std::to_string(scoreHandler->GetHiScore()));
        window.draw(score_text);
        window.draw(hi_score_text);

        cur_flashing_time += time;
        if (cur_flashing_time >= flashing_time * 2)
            cur_flashing_time = 0;

        switch (game_state) {
        case 1:
            for (int i = 0; i < welcome_sprites.size(); i++)
                window.draw(welcome_sprites[i]);

            window.draw(how_to_play_text);
            window.draw(points_text);
            press_enter_text.setString("Press Enter To Start");
            if (cur_flashing_time <= flashing_time)
                window.draw(press_enter_text);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
                game_state = 0;
            break;
        case 2:
            if (enemyController->GetSprites().size() > 0) {
                for (int i = 0; i < enemyController->GetSprites().size(); i++) {
                    window.draw(enemyController->GetSprites()[i]);
                }
            }

            window.draw(game_over_text);
            press_enter_text.setString("Press Enter To Restart");
            if (cur_flashing_time <= flashing_time)
                window.draw(press_enter_text);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                resetter->Reset(true);
                game_state = 0;
                cur_flashing_time = 0;
            }
            break;
        default:
            player->Update(time);
            enemyController->Update(time);
            bullet_pool->Update(time);

            fps_text.setString("FPS: " + std::to_string((int)(1 / time)));
            hp_text.setString("Hp: " + std::to_string(player->getHP()));
            
            if (player->getHP() <= 0) {
                game_state = 2;
                break;
            }
            window.draw(player->getSprite());

            if (enemyController->GetSprites().size() == 0) resetter->Reset();
            for (int i = 0; i < enemyController->GetSprites().size(); i++) {
                window.draw(enemyController->GetSprites()[i]);
            }

            for (int i = 0; i < bullet_pool->GetSprites().size(); i++) {
                window.draw(bullet_pool->GetSprites()[i]);
            }

            if (SHOW_FPS) window.draw(fps_text);
            window.draw(hp_text);

            break;
        }
        window.display();

        float fpsLock = 1 / FPS;
        sf::sleep(sf::seconds(fpsLock));
    }

    scoreHandler->SaveScore();
    //delete player;
    return 0;
}
