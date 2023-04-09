#include "player.hpp"
#include "card.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

namespace ariel
{
    using namespace std;

    Player::Player()
    {
        this->name = "It's a tie! no one won";
        this->stack.clear();
        this->cardstaken = 0;
        this->rounds = 0;
        this->wins = 0;
        this->draws = 0;
        this->winRate = 0;
        this->drawsRate = 0;
    }

    Player::Player(string name)
    {
        this->name = name;
        this->stack.clear();
        this->cardstaken = 0;
        this->rounds = 0;
        this->wins = 0;
        this->draws = 0;
        this->winRate = 0;
        this->drawsRate = 0;
    }

    int Player::stacksize()
    {
        return this->stack.size();
    }
    int Player::cardesTaken()
    {
        return this->cardstaken;
    }
    void Player::pushToStack(Card card)
    {
        this->stack.push_back(card);
    }
    Card Player::putCard()
    {
        if (this->stack.size() > 0)
        {
            Card card = this->stack.back();
            this->stack.pop_back();
            return card;
        }
        else
        {
            throw runtime_error("Player runs out of cards, cant play turn");
        }
    }

    string Player::turnLog(Card card)
    {
        return this->name + " played " + card.toString();
    }
    string Player::getName()
    {
        return this->name;
    }

    void Player::setRoundsPlayed()
    {
        this->rounds++;
    }

    void Player::setCardsTaken(int amountOfCards)
    {
        this->cardstaken += amountOfCards;
    }

    void Player::winTurn(int amountOfCards)
    {
        this->cardstaken += amountOfCards;
        this->wins++;
        this->winRate = (float)this->wins / this->rounds;
    }

    void Player::setDrawRate()
    {
        this->draws++;
        this->drawsRate = (float)this->draws / this->rounds;
    }

    string Player::playerStats()
    {
        string stats = "\n";
        stats += this->name + " report:";
        stats += "\nCards won: " + to_string(this->cardstaken);
        stats += "\nWins number: " + to_string(this->wins);
        stats += "\nDraws number: " + to_string(this->draws);

        ostringstream stream; // round to 2 decimal places (ChatGPT)
        stream << fixed << setprecision(2) << this->winRate;
        stats += "\nWin rate: " + stream.str();

        stream.str("");
        stream << fixed << setprecision(2) << this->drawsRate;
        stats += "\nDraws rate: " + stream.str();

        return stats;
    }
}