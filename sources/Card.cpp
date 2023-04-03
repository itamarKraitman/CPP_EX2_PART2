
#include "card.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>

using namespace std;

// namespace ariel
// {
    Card::Card() {}

    Card::Card(int number, signs sign) // constructor
    {
        this->number = number;
        this->sign = sign;
    }

    Card::Card(const Card &card) noexcept
    {
        try
        {
            this->number = card.number;
            this->sign = card.sign;
        }
        catch (const logic_error &e)
        {
            cerr << e.what() << endl;
        }
    }

    Card &Card::operator=(const Card &other) { return *this; }

    Card &Card::operator=(Card &&other) noexcept { return *this; } // move assignment operator

    Card::Card(Card &&other) noexcept {}

    Card::~Card() {} // distructor

    int Card::getNumber() const
    {
        return this->number;
    }

    signs Card::getSign() const
    {
        return this->sign;
    }

    string Card::toString() const
    {
        string sgn;
        string num;
        switch (number)
        {
        case 1:
            num = "Ace";
            break;
        case 11:
            num = "Prince";
            break;
        case 12:
            num = "Queen";
            break;
        case 13:
            num = "King";
            break;
        default:
            num = to_string(number);
        }

        switch (sign)
        {
        case signs::Clubs:
            sgn = "Clubs";
            break;
        case signs::Diamonds:
            sgn = "Diamonds";
            break;
        case signs::Hearts:
            sgn = "Hearts";
            break;
        case signs::Spades:
            sgn = "Spades";
        }
        return num + " of " + sgn;
    }

// }
