#pragma once

#include "DeckOfCards.h"
#include <QObject>

class Client;

class GamePlayers4 : public QObject
{
    Q_OBJECT
public:
    explicit GamePlayers4(QObject *parent = nullptr);
    void startGame(Client* client1, Client* client2, Client* client3, Client* client4);

signals:

private:
    Client* m_client1 = nullptr;
    Client* m_client2 = nullptr;
    Client* m_client3 = nullptr;
    Client* m_client4 = nullptr;

    DeckOfCards m_deck;
};
