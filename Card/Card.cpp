#include "Card.h"

Card::Card(CardSuits suit, CardRanks rank)
    : m_suit{suit},
    m_rank{rank}
{

}

CardSuits Card::suit() const
{
    return m_suit;
}

CardRanks Card::rank() const
{
    return m_rank;
}
