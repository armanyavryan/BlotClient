#include "TcpServer.h"

#include "Client.h"
#include "Games/GamePlayer1vsPC.h"
#include "SharedData.h"

#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

#include <chrono>
#include <thread>

TcpServer::TcpServer(QObject *parent)
    : QObject(parent)
{
    createMembers();
    makeConnections();
}

TcpServer::~TcpServer()
{
    stop();
}

bool TcpServer::start()
{
    bool ok = m_server->listen(QHostAddress::Any, m_port);
    if(ok){
        qDebug() << __FUNCTION__ << "Sever is listneing...";
    }
    else{
        qDebug() << __FUNCTION__ << "Sever FAILED!!";
    }
    return ok;
}

void TcpServer::stop()
{
    if(!m_clients.isEmpty()){
        for (int i = 0; i < m_clients.size(); ++i) {
            m_clients[i]->sendCommand(NCommands::DISCONNECTED);
        }
    }
    m_server->close();
}

bool TcpServer::isListening() const
{
    return m_server->isListening();
}

quint16 TcpServer::getPort() const
{
    return m_port;
}

void TcpServer::onNewConnection()
{
    auto socket = m_server->nextPendingConnection();
    auto client = new Client(socket, this);
    m_clients.push_back(client);
    client->sendCommand(NCommands::CONNECTED);
    emit clientConnected(client->GetHostAddress());


    qDebug() << __FUNCTION__ << __LINE__;
    for (int i = 0; i < 100; ++i) {
        qDebug() << __FUNCTION__ << __LINE__<< i;

        client->sendFloatingValue(NFloatingValues::CONNECTION_PROGRESS, float(i) / 100.0f);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    connect(client, &Client::disConnected, this, [=](){
        auto c = dynamic_cast<Client*>(sender());
        emit clientDisConnected(c->GetHostAddress());
        for (int i = 0; i < m_clients.size(); ++i) {
            if(m_clients[i]->GetHostAddress() == c->GetHostAddress()){
                m_clients[i]->deleteLater();
                m_clients.removeAt(i);
                break;
            }
        }
    });

    startGame();
}

void TcpServer::createMembers()
{
    m_server = new QTcpServer(this);
}

void TcpServer::makeConnections()
{
    connect(m_server, &QTcpServer::newConnection, this, &TcpServer::onNewConnection);

    connect(m_server, &QTcpServer::acceptError, this, [=](QAbstractSocket::SocketError error){
        qDebug() << __FUNCTION__ << error;
    });
}

void TcpServer::startGame()
{
    m_game_1vsPC = new GamePlayer1vsPC();
    m_game_1vsPC->startGame(m_clients[0]);

}
