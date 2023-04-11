#pragma once
#include <string>
#include <vector>
#include "card.hpp"

namespace ariel
{
    using namespace std;

    class Player
    {
    private:
        vector<Card> stack;
        string name;
        int turns;
        int cardstaken;
        int wins;
        double winRate;
        int draws;
        double drawsRate;

    public:
        Player();
        Player(string name);
        string getName() const;
        int stacksize() const;
        int cardesTaken() const;
        void pushToStack(const Card& card);
        Card putCard();
        string turnLog(const Card& card) const;
        string playerStats(); // not const because modifiying winRate and drawRate
        void setTurnsPlayed();
        void setCardsTaken(int amountOfCards);
        void winTurn(int amountOfCards);
        void setDrawRate();
    };
};
