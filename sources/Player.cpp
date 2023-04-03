
#include <iostream>
#include <string>
#include <vector>
#include "player.hpp"

using namespace std;

// namespace ariel
// {

    Player::Player(const string name) : name(name)
    {
        this->stackSize = 0;
        // this->stack;
        this->taken = 0;
        this->isRegistred = false;
        this->winRate = 0;
        this->cardsWon = 0;
        this->drawRate = 0;
        this->drawsHappened = 0;
    }

    Player::Player(const Player &player) noexcept {}

    Player &Player::operator=(const Player &other) { return *this; } // copy assignment operator

    Player::Player(Player &&other) noexcept {} // move constructor

    Player &Player::operator=(Player &&other) noexcept { return *this; } // move assignment operator

    Player::~Player() 
    {
        // delete and free memory of all Cards in stack
        stack.clear(); 
        stack.shrink_to_fit();
    }

    string Player::getName() const
    {
         return this->name; 
    }

    bool Player::registred() const
    {
        return this->isRegistred;
    }

    int Player::stacksize() const
    { 
        return this->stackSize; 
    }

    int Player::cardesTaken() const
    { 
        return this->taken; 
    }

    Card Player::putCard()
    { // puts the next card from player's deck
        Card topCard;
        if (stackSize > 0)
        {
            stackSize--;
            topCard = this->stack.front();
            stack.erase(stack.begin()); // remove first element
        }
        else
        {
            cout << this->name << " is running out of cards";
        }
        return topCard;
    }

    void Player::addCardsToPlayerTaken(int amountToAdd) 
    {
        this->taken += amountToAdd;
    }

    void Player::setStack(int numOfCardsToReduce) 
    {
        this->stackSize += numOfCardsToReduce;
    }

    void Player::setStack(Card card) 
    { 
        this->stack.insert(stack.begin(), card);
    }

    void Player::pushToStack(const Card& card) {
        this->stack.push_back(card);
    }

    vector<Card> Player::getStack()
    {
        return this->stack;
    }

    double Player::getWinRate() const
    { 
        return this->winRate; 
    }

    void Player::setWinRate() 
    {
        this->winRate = this->wins / (this->wins + this->drawsHappened);
    }

    double Player::getDrawRate() const
    { 
        return this->drawRate; 
    }

    void Player::setDrawRate() 
    {
        this->drawRate = this->drawsHappened / (this->wins + this->drawsHappened);
    }

    int Player::getNumberOfDraws() const
    { 
        return this->drawsHappened; 
    }

    void Player::setNumberOfDraws() 
    {
        this->drawsHappened++;
    }

    int Player::getWins() const
    {
        return this->wins;
    }

    void Player::setWins()
    {
        this->wins++;
    }
// }
