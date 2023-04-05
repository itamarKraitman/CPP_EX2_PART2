#pragma once 

#include <iostream>
#include <string>
#include <vector>
#include "card.hpp"

using namespace std;

namespace ariel{
    class Player {
        private:

        const string name;
        vector<Card> stack;
        int stackSize;
        int taken;
        bool isRegistred;
        double winRate;
        int wins;
        int cardsWon;
        double drawRate;
        int drawsHappened;

        public:

        Player(const string name); // constructor

        Player(const Player& player) noexcept; // copy constructor

        Player& operator=(const Player& other); // copy assignment operator

        Player(Player&& other) noexcept; // move constructor

        Player& operator=(Player&& other) noexcept; // move assignment operator

        ~Player();

        string getName() const;

        bool registred() const;

        int stacksize() const;

        int cardesTaken() const;

        Card putCard(); // puts the next card in player's deck

        void addCardsToPlayerTaken(int amountToAdd);

        void setStack(int numOfCardsToReduce); // number of cards

        void setStack(Card card); // add card to stack

        void pushToStack(const Card& card);

        vector<Card> getStack();

        double getWinRate() const;

        void setWinRate();

        double getDrawRate() const;

        void setDrawRate();

        int getNumberOfDraws() const;

        void setNumberOfDraws();

        int getWins() const;

        void setWins();
    };
}