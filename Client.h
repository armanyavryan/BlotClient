#pragma once

#include "Card/Card.h"
#include <QObject>
#include <QHostAddress>

class QTcpSocket;

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QTcpSocket* socket, QObject *parent = nullptr);

    QString GetIPv4Address() const;
    QHostAddress GetHostAddress() const;

    void sendCommand(QString command);
    void sendFloatingValue(const QString& cmd, float val);
    void deliverCards(std::vector<Card> cards);

signals:
    void connected();
    void disConnected();


private slots:
    void onConnected();
    void onDisConnected();

private:
    void initIpv4Address();

    void makeConnections();

private:

    QHostAddress    m_address;
    QTcpSocket      *m_socket = nullptr;
    QString         m_ipv4Address;
};
