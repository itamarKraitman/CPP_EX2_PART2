#pragma once
#include <string>

namespace ariel
{
    using namespace std;

    enum Signs
    {
        Clubs,
        Hearts,
        Diamonds,
        Spades
    };

    class Card
    {
    private:
        int number;
        Signs sign;

    public:
        Card(int number, Signs sign);
        string toString() const;
        int getNumber() const;
    };
};
