
#include <iostream>
#include <sstream>
#include "game.hpp"
#include "player.hpp"

using namespace std;

namespace ariel
{

    Game::Game(Player &player1, Player &player2) : p1(player1), p2(player2)
    {
        if (player1.registred() || player2.registred())
        {
            throw invalid_argument("Player can be registred only to one game!");
        }
        this->p1 = player1;
        this->p2 = player2;
        this->winner = "";
        // generate cards and push into the deck
        vector<Card> deck(52);
        for (int i = 0; i < 13; i++)
        {
            for (signs j = Clubs; j <= Spades; j = signs(j + 1))
            {
                Card newCard(i + 1, j);
                deck.push_back(newCard);
            }
        }

        // shuffle the deck
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(deck.begin(), deck.end(), default_random_engine());

        for (int i = 0; i < 26; i++)
        {
            Card card1 = deck.back();
            deck.pop_back();
            p1.pushToStack(card1);

            Card card2 = deck.back();
            deck.pop_back();
            p2.pushToStack(card2);
        }
    }

    Game::Game(const Game &game) noexcept : p1(game.p1), p2(game.p2) {}

    Game &Game::operator=(const Game &other) { return *this; } // copy assignment operator

    Game &Game::operator=(Game &&other) noexcept { return *this; } // move assignment operator

    Game::Game(Game &&other) noexcept : p1(other.p1), p2(other.p2) {} // move constructor

    Game::~Game() {}

    static int turnCounter = 0;

    void Game::playTurn()
    {
        // cout << "turn: p1 stack: " << p1.getStack().size() << " p2 stack: " << p2.getStack().size() << endl;
        if (&p1 == &p2)
        {
            throw runtime_error("The game has only one player");
        }
        if (turnCounter == 26)
        {
            throw runtime_error("Game is over, can't play turns anymore");
        }
        int numberOfCardsThrewInTurn = 2; // in each turn at least 2 cards are thrown

        // both players throw cards
        Card p1Card = p1.putCard();
        Card p2Card = p2.putCard();
        cout << "P1 card is: " << p1Card.toString() << ", P2 card is: " << p2Card.toString();
        cout.flush();

        this->lastTurnLog << "p1 plays " << p1Card.getNumber() << " of " << p1Card.getSign() << " p2 plays " << p2Card.getNumber() << " of " << p2Card.getSign();
        while (p1Card.getNumber() == p2Card.getNumber()) // war scenario, until there is no draw so no war
        {
            cout << "Draw!" <<endl;
            cout.flush();

            this->lastTurnLog << " draw.";
            p1.setNumberOfDraws();
            p2.setNumberOfDraws();
            p1.setDrawRate();
            p2.setDrawRate();
            // both put card down- need to check if not causing data leak
            p1.putCard();
            p2.putCard();
            // putCard(p1);
            // putCard(p2);
            // both put card up
            p1Card = p1.putCard();
            p2Card = p2.putCard();
            cout << "P1 card is: " << p1Card.toString() << ", P2 card is: " << p2Card.toString();
            cout.flush();

            // add playes to lastTurnLog
            this->lastTurnLog << "p1 plays " << p1Card.getNumber() << " of " << p1Card.getSign() << " p2 plays " << p2Card.getNumber() << " of " << p2Card.getSign();
            numberOfCardsThrewInTurn += 4;
        }
        // both stack-- if can, if player runs out of cards he looses- in putCard()
        // if p1 wins: add cards to taken, win rate++, update win rate
        if (p1Card.getNumber() > p2Card.getNumber())
        {
            if (p2Card.getNumber() == 1 && p1Card.getNumber() == 2) // Ace wins 2
            {
                cout << "p2 wins"<< endl;;
                cout.flush();

                p2.setWins();
                p2.setWinRate();
                p2.addCardsToPlayerTaken(numberOfCardsThrewInTurn);
                this->lastTurnLog << "p2 wins.\n";
            }
            else
            {
                cout << "p1 wins" <<endl;
                cout.flush();

                p1.setWins();
                p1.setWinRate();
                p1.addCardsToPlayerTaken(numberOfCardsThrewInTurn);
                this->lastTurnLog << "p1 wins.\n";
            }
        }
        else if (p2Card.getNumber() > p1Card.getNumber())
        {
            if (p1Card.getNumber() == 1 && p2Card.getNumber() == 2) // Ace wins 2
            {
                cout << "p1 wins" << endl;
                cout.flush();

                p1.setWins();
                p1.setWinRate();
                p1.addCardsToPlayerTaken(numberOfCardsThrewInTurn);
                this->lastTurnLog << "p1 wins.\n";
            }
            else
            {
                cout << "p2 wins" << endl;
                cout.flush();
                p2.setWins();
                p2.setWinRate();
                p2.addCardsToPlayerTaken(numberOfCardsThrewInTurn);
                this->lastTurnLog << "p2 wins.\n";
            }
        }
        this->gameLog += lastTurnLog.str(); // add turn log to gameLog
        this->lastTurnLog << "";
    }

    // Card Game::putCard(Player& player)
    // { // puts the next card from player's deck
    //     if (player.getStack().size() > 0)
    //     {
    //         Card topCard = player.getStack().front();
    //         player.getStack().erase(player.getStack().begin()); // remove first element
    //         return topCard;
    //     }
    //     else
    //     {
    //         string s = "Game ends " + player.getName() + " is running out of cards, stack: " + to_string(player.getStack().size());
    //         throw runtime_error(s);
    //     }
    // }

    void Game::printLastTurn()
    {
        cout << this->lastTurnLog.str() << endl;
    }

    void Game::playAll()
    {
        // cout << "p1 stack: " << p1.getStack().size() << " p2 stack: " << p2.getStack().size() << endl;
        while (p1.getStack().size() > 0 && p2.getStack().size() > 0 && turnCounter < 26)
        {
            cout << turnCounter << endl;
            playTurn();
            turnCounter++;
        }
        turnCounter = 0; // after the game is ended, modify to 0 so the next game could be played
    }

    void Game::printWiner()
    {
        cout << this->winner;
    }

    void Game::printLog()
    {
        cout << this->gameLog << endl;
    }

    void Game::printStats() {} // TODO when tests come

    Player Game::getWinner()
    {
        return this->winner;
    }

}