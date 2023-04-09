#include "card.hpp"
#include <string>

namespace ariel
{
    using namespace std;

    Card::Card(int number, Signs sign)
    {
        this->number = number;
        this->sign = sign;
    };

    string Card::toString()
    {
        string numberAsString;
        string signAsString;

        switch (this->number)
        {
        case 1:
            numberAsString = "Ace";
            break;
        case 11:
            numberAsString = "Prince";
            break;
        case 12:
            numberAsString = "Queen";
            break;
        case 13:
            numberAsString = "King";
            break;
        default:
            numberAsString = to_string(this->number);
            break;
        }

        switch (this->sign)
        {
        case Diamonds:
            signAsString = "Diamonds";
            break;
        case Spades:
            signAsString = "Spades";
            break;
        case Hearts:
            signAsString = "Hearts";
            break;
        default:
            signAsString = "Clubs";
            break;
        }

        return numberAsString + " of " + signAsString;
    };

    int Card::getNumber()
    {
        return this->number;
    }
};