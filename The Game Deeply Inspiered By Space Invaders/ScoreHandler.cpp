#include "ScoreHandler.h"

ScoreHandler* ScoreHandler::scoreHandler = nullptr;

ScoreHandler* ScoreHandler::getScoreHandler() {
    if (!scoreHandler) {
        scoreHandler = new ScoreHandler();
    }

    return scoreHandler;
}

ScoreHandler::ScoreHandler() { }

void ScoreHandler::Reset() { score = 0; }

void ScoreHandler::LoadScore() {
    std::ifstream file("High Score.txt");
    if (file.is_open()) {
        std::string a;
        file >> hi_score;
        file.close();
    }
}
void ScoreHandler::SaveScore() {
    std::ofstream file;
    file.open("High Score.txt", std::ofstream::out | std::ofstream::trunc);
    if (file.is_open()) {
        file << std::to_string(hi_score);
        file.close();
    }
}
int ScoreHandler::GetScore() { return score; }
int ScoreHandler::GetHiScore() { return hi_score; }
void ScoreHandler::IncraeseScore(int value) {
    score += value;
    if (score > hi_score)
        hi_score = score;
}