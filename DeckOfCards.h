#pragma once

#include "Card/Card.h"
#include <QObject>

class DeckOfCards : public QObject
{
    Q_OBJECT
public:
    explicit DeckOfCards(QObject *parent = nullptr);

    std::vector<Card> deliver1by1();
    std::vector<Card> deliver8by8();
signals:

private:
    void init();
    void shuffle();
private:
    const int m_size = 32;
    std::vector<Card> m_deck;
};
