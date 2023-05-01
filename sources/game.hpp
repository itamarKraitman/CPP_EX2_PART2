#pragma once
#include "player.hpp"
#include "card.hpp"

namespace ariel
{
    using namespace std;

    class Game
    {
    private:
        Player &player1;
        Player &player2;
        Player winner;
        int amountOfDraws;
        int amountOfRounds;
        vector<string> gameLogs;

    public:
        Game(Player &player1, Player &player2);
        void playTurn();
        void printLastTurn() const;
        void playAll();
        void printWiner() const;
        void printLog() const;
        void printStats() const;
    };
};
