#include "Resetter.h"

Resetter* Resetter::resetter = nullptr;

Resetter* Resetter::getResetter() {
    if (!resetter) {
        resetter = new Resetter();
    }

    return resetter;
}

Resetter::Resetter() { }

void Resetter::Reset(bool resetScore) {
    BulletPool::getPool()->Reset();
    EnemyController::getEnemyController()->Reset();
    Player::getPlayer()->Reset();
    if (resetScore) ScoreHandler::getScoreHandler()->Reset();
}
