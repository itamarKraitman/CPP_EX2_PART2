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
        string getName();
        int stacksize();
        int cardesTaken();
        void pushToStack(Card card);
        Card putCard();
        string turnLog(Card card);
        string playerStats();
        void setTurnsPlayed();
        void setCardsTaken(int amountOfCards);
        void winTurn(int amountOfCards);
        void setDrawRate();
    };
};
