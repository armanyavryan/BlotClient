#include "DeckOfCards.h"
#include <algorithm>
#include <random>

DeckOfCards::DeckOfCards(QObject *parent)
    : QObject{parent}
{
    init();
}


std::vector<Card> DeckOfCards::deliver1by1()
{
    Q_ASSERT(m_size == m_deck.size() && m_size == 32);

    shuffle();
    std::vector<Card> orderedCards;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 8; ++j) {
            orderedCards.push_back(m_deck[i + 4 * j]);
        }
    }
    return orderedCards;
}

std::vector<Card> DeckOfCards::deliver8by8()
{
    Q_ASSERT(m_size == m_deck.size() && m_size == 32);

    shuffle();
    std::vector<Card> orderedCards;

    for (int i = 0; i < m_deck.size(); ++i) {
        orderedCards.push_back(m_deck[i]);
    }
    return orderedCards;
}

void DeckOfCards::init()
{
    for (int i = 0; i < m_size / 4; ++i) {
        CardRanks rank = CardRanks((int)CardRanks::Ace - i);
        for (int j = 0; j < 4; ++j) {
            Card card(CardSuits(j), rank);
            m_deck.push_back(card);
        }
    }
    Q_ASSERT(m_deck.size() == m_size);
}

void DeckOfCards::shuffle()
{
    //    auto rd = std::random_device {};
    //    auto rng = std::default_random_engine { rd() };

    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(m_deck), std::end(m_deck), rng);
}
