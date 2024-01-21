#include "GamePlayers4.h"

GamePlayers4::GamePlayers4(QObject *parent)
    : QObject{parent}
{

}


void GamePlayers4::startGame(Client *client1, Client *client2, Client *client3, Client *client4)
{
    m_client1 = client1;
    m_client2 = client2;
    m_client3 = client3;
    m_client4 = client4;

    Q_ASSERT(m_client1 != nullptr);
    Q_ASSERT(m_client2 != nullptr);
    Q_ASSERT(m_client3 != nullptr);
    Q_ASSERT(m_client4 != nullptr);

    auto cards = m_deck.deliver8by8();

}
