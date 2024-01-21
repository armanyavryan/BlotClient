#pragma once

#include "SharedData.h"

class Card
{
public:
    Card(CardSuits suit, CardRanks rank);
    CardSuits suit() const;
    CardRanks rank() const;

private:

    CardSuits m_suit;
    CardRanks m_rank;
};
