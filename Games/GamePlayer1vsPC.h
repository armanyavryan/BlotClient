#pragma once


#include "DeckOfCards.h"
#include <QObject>

class Client;

class GamePlayer1vsPC: public QObject
{
    Q_OBJECT
public:
    explicit GamePlayer1vsPC(QObject *parent = nullptr);
    void startGame(Client* client);

private:
    Client* m_client = nullptr;
    DeckOfCards m_deck;
};
