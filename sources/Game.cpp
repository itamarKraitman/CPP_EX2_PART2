
#include <iostream>
#include <sstream>
#include "game.hpp"
#include "player.hpp"

using namespace std;

// namespace ariel
// {

Game::Game(Player &player1, Player &player2) : p1(player1), p2(player2)
{
    if (player1.registred() || player2.registred())
    {
        throw invalid_argument("Player can be registred only to one game!");
    }
    this->p1 = player1;
    this->p2 = player2;
    this->winner = "";
    generateDeckAndDeal();
}

Game::Game(const Game &game) noexcept : p1(game.p1), p2(game.p2) {}

Game &Game::operator=(const Game &other) { return *this; } // copy assignment operator

Game &Game::operator=(Game &&other) noexcept { return *this; } // move assignment operator

Game::Game(Game &&other) noexcept : p1(other.p1), p2(other.p2) {} // move constructor

Game::~Game() {}

void Game::generateDeckAndDeal() // generates regular deck, shuffle it, and deal to players
{

    size_t w = 0;
    // generate cards and push into the deck
    for (int i = 0; i < 13; i++)
    {
        for (signs j = Clubs; j <= Spades; j = signs(j + 1))
        {
            Card newCard(Card(i + 1, j));
            // cout << newCard.toString() << endl;
            deck.emplace_back(newCard);
            // cout << deck.back().getNumber() << " " << deck.back().getSign() << endl;
            w++;
        }
    }

    // cout << "\nprint" << endl;

    // for (Card card : deck)
    // {
    //     cout << card.getNumber() << " " << card.getSign() << endl;
    // }

    // cout << "\nshuffle" << endl;

    // shuffle the deck
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(deck.begin(), deck.end(), default_random_engine(seed));

    for (int i = 0; i < 26; i++)
    {
        Card card1 = deck.back();
        deck.pop_back();
        p1.pushToStack(card1);
        // cout << "Card dealt to player 1: " << card1.toString() << endl;

        Card card2 = deck.back();
        deck.pop_back();
        p2.pushToStack(card2);
        // cout << "Card dealt to player 2: " << card2.toString() << endl;
    }
}

static int turnCounter = 0;

void Game::playTurn()
{
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
    // cout << p1.getStack().size() << p2.getStack().size() << endl;
    this->lastTurnLog << "p1 plays " << p1Card.getNumber() << " of " << p1Card.getSign() << " p2 plays " << p2Card.getNumber() << " of " << p2Card.getSign();
    while (p1Card.getNumber() == p2Card.getNumber()) // war scenario, until there is no draw so no war
    {
        this->lastTurnLog << " draw.";
        p1.setNumberOfDraws();
        p2.setNumberOfDraws();
        p1.setDrawRate();
        p2.setDrawRate();
        // both put card down- need to check if not causing data leak
        p1.putCard();
        p2.putCard();
        // both put card up
        p1Card = p1.putCard();
        p2Card = p2.putCard();
        // cout << p1.getStack().size() << p2.getStack().size() << endl;
        // add playes to lastTurnLog
        this->lastTurnLog << "p1 plays " << p1Card.getNumber() << " of " << p1Card.getSign() << " p2 plays " << p2Card.getNumber() << " of " << p2Card.getSign();
        numberOfCardsThrewInTurn += 4;
    }
    // both stack-- if can, if player runs out of cards he looses- in putCard()
    // if p1 wins: add cards to taken, win rate++, update win rate
    if (p1Card.getNumber() > p2Card.getNumber())
    {
        p1.setWins();
        p1.setWinRate();
        p1.addCardsToPlayerTaken(numberOfCardsThrewInTurn);
        this->lastTurnLog << "p1 wins.\n";
    }
    else if (p2Card.getNumber() > p1Card.getNumber())
    {
        p2.setWins();
        p2.setWinRate();
        p2.addCardsToPlayerTaken(numberOfCardsThrewInTurn);
        this->lastTurnLog << "p2 wins.\n";
    }
    this->gameLog += lastTurnLog.str(); // add turn log to gameLog
    this->lastTurnLog << "";
}

void Game::printLastTurn()
{
    cout << this->lastTurnLog.str() << endl;
}

void Game::playAll()
{
    while (p1.getStack().size() > 0 && p2.getStack().size() > 0)
    {
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
// }