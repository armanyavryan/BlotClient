#pragma once


#include <QObject>

#include <QHostAddress>

class GamePlayer1vsPC;

class QTcpServer;
class QTcpSocket;

class Client;

class TcpServer : public QObject
{
    Q_OBJECT
public:
    TcpServer(QObject *parent = nullptr);
    ~TcpServer();
    bool start();
    void stop();
    bool isListening() const;
    quint16 getPort() const;

signals:
    void clientConnected(QHostAddress addr);
    void clientDisConnected(QHostAddress addr);

private slots:
    void onNewConnection();

private:
    void createMembers();
    void makeConnections();

    void startGame();

private:
    QTcpServer          *m_server = nullptr;
    QList<Client*>      m_clients;
    quint16             m_port = 8888;


    GamePlayer1vsPC *m_game_1vsPC;
};
