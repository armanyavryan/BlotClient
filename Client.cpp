#include "Client.h"

#include "SharedData.h"
#include <QTcpSocket>
#include <QDataStream>

Client::Client(QTcpSocket* socket, QObject *parent)
    : QObject{parent},
    m_socket{socket}
{
    initIpv4Address();
    makeConnections();
}


void Client::onConnected()
{
    emit connected();

}

void Client::onDisConnected()
{
    emit disConnected();
}


void Client::makeConnections(){
    connect(m_socket, &QTcpSocket::connected, this, &Client::onConnected);
    connect(m_socket, &QTcpSocket::disconnected, this, &Client::onDisConnected);
}


QString Client::GetIPv4Address() const
{
    return m_ipv4Address;
}

QHostAddress Client::GetHostAddress() const
{
    return m_socket->peerAddress();
}

void Client::sendCommand(QString cmd)
{
    quint8 type = (quint8)PacketType::NCommands;
    QByteArray arr;
    arr.push_back(type);
    arr.push_back(cmd.toLatin1());
    arr.push_back("\n");
    m_socket->write(arr);
    m_socket->flush();
    m_socket->waitForBytesWritten(100);
    qDebug() << __FUNCTION__ << __LINE__ << arr;
}

void Client::sendFloatingValue(const QString &cmd, float val)
{
    quint8 type = (quint8)PacketType::NFloatingValues;
    QByteArray arr;
    arr.push_back(type);
//    arr.push_back(":");
    arr.push_back(cmd.toLatin1());
//    arr.push_back(":");

    QByteArray valueByteArray;
    valueByteArray.append(reinterpret_cast<const char*>(&val), sizeof(float));

    float f2 = *reinterpret_cast<const float*>(valueByteArray.data());
    qDebug() << __FUNCTION__ << __LINE__ << f2;
    qDebug() << __FUNCTION__ << __LINE__ << "value data" << valueByteArray.toHex(' ').toStdString().c_str() ;


    arr.push_back(valueByteArray);
    arr.push_back("\n");

    m_socket->write(arr);
    m_socket->flush();
    qDebug() << __FUNCTION__ << __LINE__ << arr.toHex(' ').toStdString().c_str() << arr.size();

}

void Client::deliverCards(std::vector<Card> cards)
{
    Q_ASSERT(cards.size() == 8);

    quint8 type = (quint8)PacketType::NCards;
    QByteArray arr;
    arr.push_back(type);
    arr.push_back(NCards::DELIVER_8_CARDS.toLatin1());
    arr.push_back(QString(":").toLatin1());

    for (int i = 0; i < 8; ++i) {
        quint8 suit = (quint8)cards[i].suit();
        quint8 rank = (quint8)cards[i].rank();
        arr.push_back(suit);
        arr.push_back(rank);

    }

    m_socket->write(arr);
    m_socket->flush();
}

void Client::initIpv4Address()
{
    bool ok;
    auto ipv4address = m_socket->peerAddress().toIPv4Address(&ok);
    QString str_ip;
    if(ok){
        for (int i = 0; i < 4; ++i) {
            auto le = ipv4address & 0x11111111;
            if(i !=0){
                str_ip.prepend(".");
            }
            str_ip.prepend(QString::number(le));
            ipv4address  = ipv4address >> 4;
        }
        qDebug() << __FUNCTION__ << ipv4address;
    }
    m_ipv4Address = str_ip;
}
