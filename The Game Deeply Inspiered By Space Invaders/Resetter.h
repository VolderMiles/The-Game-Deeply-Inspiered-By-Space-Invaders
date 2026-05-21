#pragma once

#include "Player.h"
#include "EnemyController.h"
#include "ScoreHandler.h"
#include "BulletPool.h"

class Resetter {
private:
    static Resetter* resetter;

    Resetter();

public:
    Resetter(Resetter const&) = delete;
    void operator = (Resetter const&) = delete;
    
    static Resetter* getResetter();

    void Reset(bool resetScore = false);
};

