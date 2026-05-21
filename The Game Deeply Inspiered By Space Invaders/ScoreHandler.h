#pragma once
#include <iostream>
#include <string>
#include <fstream>

class ScoreHandler {
private:
    int score = 0, hi_score = 0;

    static ScoreHandler* scoreHandler;

    ScoreHandler();

public:
    ScoreHandler(ScoreHandler const&) = delete;
    void operator = (ScoreHandler const&) = delete;
    
    static ScoreHandler* getScoreHandler();

    void Reset();

    void SaveScore();
    void LoadScore();
    int GetScore();
    int GetHiScore();
    void IncraeseScore(int value);
};
