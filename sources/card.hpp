
#pragma once 

#include <string>
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;



namespace ariel {

    enum signs {
        Clubs = 0,
        Diamonds = 1,
        Hearts = 2,
        Spades = 3
    };

    class Card
    {
        int number; // 1-13 (11=prince, 12=queen, 13=king)
        signs sign; // clubs (♣) (0), diamonds (♦) (1), hearts (♥) (2), and spades (♠) (3)

        
        public:

        Card();

        Card(int number, signs sign); // constructor

        Card(const Card& card) noexcept; // copy constructor

        Card& operator=(const Card& other); // copy assignment operator

        Card(Card&& other) noexcept; // move constructor

        Card& operator=(Card&& other) noexcept; // move assignment operator

        ~Card();

        int getNumber() const;

        signs getSign() const;

        string toString() const;

        string numberAndSignAsString() const;

    };
}