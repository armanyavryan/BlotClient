#include "GamePlayer1vsPC.h"

#include "Client.h"

GamePlayer1vsPC::GamePlayer1vsPC(QObject *parent)
    :QObject{parent}
{

}

void GamePlayer1vsPC::startGame(Client *client)
{
    m_client = client;

    Q_ASSERT(m_client != nullptr);
    auto cards = m_deck.deliver8by8();

    std::vector<Card> palyer1Cards;
    std::vector<Card> palyer2Cards;
    std::vector<Card> palyer3Cards;
    std::vector<Card> palyer4Cards;
    for (int i = 0; i < 8; ++i) {
        palyer1Cards.push_back(cards[i]);
        palyer2Cards.push_back(cards[8 +  i]);
        palyer3Cards.push_back(cards[16 + i]);
        palyer4Cards.push_back(cards[24 + i]);
    }

    m_client->deliverCards(palyer1Cards);
}
