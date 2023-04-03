
#pragma once 

#include "player.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

// namespace ariel {
    class Game {
        vector<Card> deck;
        Player& p1;
        Player& p2;
        string winner;
        string gameLog;
        stringstream lastTurnLog;
    
        public:

        Game(Player& player1, Player& player2);// constructor

        Game(const Game& game) noexcept; // copy constructor

        Game& operator=(const Game& other); // copy assignment operator

        Game(Game&& other) noexcept; // move constructor

        Game& operator=(Game&& other) noexcept; // move assignment operator

        ~Game();

        void generateDeckAndDeal();

        void playTurn();

        void printLastTurn();

        void playAll();

        void printWiner();

        void printLog();

        void printStats();

        Player getWinner();
    };
// }
