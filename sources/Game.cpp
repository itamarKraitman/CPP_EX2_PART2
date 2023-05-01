
#include "game.hpp"
#include "player.hpp"
#include <algorithm>
#include <iostream>
#include <random>
namespace ariel
{
    using namespace std;

    Game::Game(Player &player1, Player &player2) : player1(player1), player2(player2)
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
        // dealing 26 cards to each player- dealing i and i + 1 did not work. do not know why exactly- GPT
        for (unsigned long int i = 0; i < 26; i++)
        {
            player1.pushToStack(deck[i]);
            player2.pushToStack(deck[i + 26]);
        }
    }
    void Game::playTurn()
    {
        if (&player1 == &player2) // in my opinion, it should be in constructor, but for tests it's here
        {
            throw "Player can't player against himself";
        }

        if (player1.stacksize() == 0 || player2.stacksize() == 0)
        {
            throw "One player is run out of cards";
        }

        string turnLog = "";
        int cardsOnTable = 0; // how many cards on table, taken by the turn winner at the end of the turn

        if (this->player1.stacksize() > 0 && this->player2.stacksize() > 0) // play turn iff both players have at least one card
        {
            player1.setTurnsPlayed(); // increase number of turns by 1
            player2.setTurnsPlayed();
            Card player1Card = this->player1.putCard();
            Card player2Card = this->player2.putCard();
            cardsOnTable += 2;
            turnLog += this->player1.getName() + " card is: " + player1Card.toString() + ", " + this->player2.getName() + " card is: " + player2Card.toString() + ".";

            // war case- both players played cards with same number, lasts as long as both players plays cards with same number or running out of cards
            while (player1Card.getNumber() == player2Card.getNumber())
            {
                // increase Turns played by 1 to both players and draw rate as well
                player1.setDrawRate();
                player2.setDrawRate();
                turnLog += " Draw! ";
                try // if players run out of cards during turn, it throws exception
                {
                    // two faced-down cards -- throws exception if one player runs out of cards
                    this->player1.putCard();
                    this->player2.putCard();
                    // two daced-up cards
                    player1Card = this->player1.putCard();
                    player2Card = this->player2.putCard();
                    turnLog += this->player1.getName() + " card is: " + player1Card.toString() + ", " + this->player2.getName() + " card is: " + player2Card.toString() + ".";
                    cardsOnTable += 4;
                }
                catch (exception e) // both players run out of cards, game ends and each player take the cards he put on the table
                {
                    player1.setCardsTaken(cardsOnTable / 2);
                    player2.setCardsTaken(cardsOnTable / 2);
                    break;
                }
            }
            //  Ace strong against all execpt for 2
            if (player1Card.getNumber() == 1 && player2Card.getNumber() != 2)
            {
                turnLog += " " + player1.getName() + " wins.";
                player1.winTurn(cardsOnTable);
            }
            else if (player1Card.getNumber() != 2 && player2Card.getNumber() == 1)
            {
                turnLog += " " + player2.getName() + " wins.";
                player2.winTurn(cardsOnTable);
            }
            // two regular cases- one player has crad with higher number than the other
            else if (player1Card.getNumber() > player2Card.getNumber())
            {
                turnLog += " " + player1.getName() + " wins.";
                player1.winTurn(cardsOnTable);
            }
            else if (player2Card.getNumber() > player1Card.getNumber())
            {
                turnLog += " " + player1.getName() + " wins.";
                player1.winTurn(cardsOnTable);
            }
        }
        turnLog += "\n";
        this->gameLogs.push_back(turnLog);
    }

    void Game::printLastTurn() const
    {
        if (this->gameLogs.empty())
        {
            cout << "Game has not statrted yet" << endl;
        }
        else
        {
            cout << this->gameLogs.back();
        }
    }
    void Game::playAll()
    {
        while (this->player1.stacksize() > 0 && this->player2.stacksize() > 0) // can play iff both players have cards to play with
        {
            playTurn();
        }

        // find the winner- NOTE! case of a tie is default (look at the default constructor of Player)
        if (player1.cardesTaken() < player2.cardesTaken())
        {
            this->winner = player2;
        }
        else if (player2.cardesTaken() < player1.cardesTaken())
        {
            this->winner = player1;
        }
    }

    void Game::printWiner() const
    {
        if (this->gameLogs.empty())
        {
            cout << "Game has not statrted yet" << endl;
        }
        else
        {
            cout << "The winner is :" << this->winner.getName() << endl;
        }
    }

    void Game::printLog() const
    {
        if (this->gameLogs.empty())
        {
            cout << "Game has not statrted yet" << endl;
        }
        else
        {
            for (string turnLog : this->gameLogs)
            {
                cout << turnLog;
            }
        }
    }
    void Game::printStats() const
    {
        string player1Stats = this->player1.playerStats();
        string player2Stats = this->player2.playerStats();
        cout << player1Stats << "\n\n"
             << player2Stats << endl;
    }
};