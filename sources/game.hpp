#pragma once
#include "player.hpp"
#include "card.hpp"

namespace ariel
{
    using namespace std;

    class Game
    {
    private:
        Player &p1;
        Player &p2;
        Player winner;
        int amountOfDraws;
        int amountOfRounds;
        vector<string> logs;
        string get_round_log();

    public:
        Game(Player &p1, Player &p2);
        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
    };
};
