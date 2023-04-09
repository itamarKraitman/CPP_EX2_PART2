
#include "game.hpp"
#include "player.hpp"
#include <algorithm>
#include <iostream>
#include <random>
namespace ariel
{
    using namespace std;

    Game::Game(Player &player1, Player &player2) : p1(player1), p2(player2)
    {
        this->winner = Player();
        // generating deck of 52 cards
        vector<Card> deck;
        for (int i = 1; i <= 13; i++) // generate deck (ChatGPT)
        {
            for (int j = Clubs; j <= Spades; j++)
            {
                deck.push_back(Card(i, static_cast<Signs>(j)));
            }
        }
        // shuffleing the deck (ChatGPT)
        random_device rd;
        mt19937 g(rd());
        shuffle(deck.begin(), deck.end(), g);
        // dealing 26 cards to each player
        for (unsigned long int i = 0; i < 26; i++)
        {
            p1.pushToStack(deck[i]);
            p2.pushToStack(deck[i + 26]);
        }
    }
    void Game::playTurn()
    {
        if (&p1 == &p2) // in my opinion, it should be in constructor, but for tests it's here
        {
            throw "Player can't player against himself";
        }

        if (p1.stacksize() == 0 || p2.stacksize() == 0)
        {
            throw "One player is run out of cards";
        }

        string turnLog = "";
        int cardsOnTable = 0; // how many cards on table, taken by the turn winner at the end of the turn

        if (this->p1.stacksize() > 0 && this->p2.stacksize() > 0) // play turn iff both players have at least one card
        {
            Card p1Card = this->p1.putCard();
            Card p2Card = this->p2.putCard();
            cardsOnTable += 2;
            turnLog += this->p1.getName() + " card is: " + p1Card.toString() + ", " + this->p2.getName() + " card is: " + p2Card.toString() + ".";

            // war case- both players played cards with same number, lasts as long as both players plays cards with same number or running out of cards
            while (p1Card.getNumber() == p2Card.getNumber())
            {
                p1.setRoundsPlayed();
                p2.setRoundsPlayed();
                p1.setDrawRate();
                p2.setDrawRate();
                turnLog += " Draw! ";
                try // if players run out of cards during turn, it throws exception
                {
                    // two faced-down cards -- throws exception if one player runs out of cards
                    this->p1.putCard();
                    this->p2.putCard();
                    // two daced-up cards
                    p1Card = this->p1.putCard();
                    p2Card = this->p2.putCard();
                    turnLog += this->p1.getName() + " card is: " + p1Card.toString() + ", " + this->p2.getName() + " card is: " + p2Card.toString() + ".";
                    cardsOnTable += 4;
                }
                catch (exception e) // both players run out of cards, game ends
                {
                    p1.setCardsTaken(cardsOnTable / 2);
                    p2.setCardsTaken(cardsOnTable / 2);
                    break;
                }
            }
            //  Ace strong against all execpt for 2
            if (p1Card.getNumber() == 1 && p2Card.getNumber() != 2)
            {
                turnLog += " " + this->p1.getName() + " wins.";
                p1.setRoundsPlayed();
                p1.winTurn(cardsOnTable);
                p2.setRoundsPlayed();
            }
            else if (p1Card.getNumber() != 2 && p2Card.getNumber() == 1)
            {
                turnLog += " " + this->p2.getName() + " wins.";
                p2.setRoundsPlayed();
                p2.winTurn(cardsOnTable);
                p1.setRoundsPlayed();
            }
            // two regular cases- one player has crad with higher number than the other
            else if (p1Card.getNumber() > p2Card.getNumber())
            {
                turnLog += " " + this->p1.getName() + " wins.";
                p1.setRoundsPlayed();
                p1.winTurn(cardsOnTable);
                p2.setRoundsPlayed();
            }
            else if (p2Card.getNumber() > p1Card.getNumber())
            {
                turnLog += " " + this->p2.getName() + " wins.";
                p2.setRoundsPlayed();
                p2.winTurn(cardsOnTable);
                p1.setRoundsPlayed();
            }
        }
        turnLog += "\n";
        this->gameLogs.push_back(turnLog);
    };

    void Game::printLastTurn()
    {
        cout << this->gameLogs.back();
    };
    void Game::playAll()
    {
        while (this->p1.stacksize() > 0 && this->p2.stacksize() > 0)
        {
            playTurn();
        }

        // find the winner- NOTE! case of a tie is default (look at the default constructor of Player)
        if (p1.cardesTaken() < p2.cardesTaken())
        {
            this->winner = p2;
        }
        else if (p2.cardesTaken() < p1.cardesTaken())
        {
            this->winner = p1;
        }
    };

    void Game::printWiner()
    {
        cout << "The winner is :" << this->winner.getName()<< endl;;
    };

    void Game::printLog()
    {
        for (string turnLog : this->gameLogs)
        {
            cout << turnLog;
        }
    };
    void Game::printStats()
    {
        string p1Stats = this->p1.playerStats();
        string p2Stats = this->p2.playerStats();
        cout << p1Stats << "\n\n"
             << p2Stats << endl;
    };
};