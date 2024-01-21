#include "MainWindow.h"
#include "Games/GamePlayer1vsPC.h"
#include "TcpServer.h"

#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    createMembers();
    initMembers();
    doLayout();
    makeConnections();
}

void MainWindow::createMembers()
{
    m_labelPort = new QLabel;
    m_labelServerStatus = new QLabel;
    m_btnConnect = new QPushButton("Connect");

    m_server = new TcpServer;
    m_game_1vsPC = new GamePlayer1vsPC();

}

void MainWindow::initMembers()
{
    m_labelPort->setText(QString::number(m_server->getPort()));
    m_labelServerStatus->setText("Server is Not Live.");
}

void MainWindow::doLayout()
{
    QWidget * cw = new QWidget;
    this->setCentralWidget(cw);

    QVBoxLayout *lay = new QVBoxLayout;
    cw->setLayout(lay);

    lay->addWidget(m_labelPort);
    lay->addWidget(m_labelServerStatus);
    lay->addWidget(m_btnConnect);
}

void MainWindow::makeConnections()
{

    connect(m_server, &TcpServer::clientConnected, this, [=](QHostAddress addr){

    });

    connect(m_server, &TcpServer::clientDisConnected, this, [=](QHostAddress addr){

    });

    connect(m_btnConnect, &QPushButton::clicked, this, [=](){
        m_isStarted = ! m_isStarted;
        if(m_isStarted){
            bool ok = m_server->start();
            if(!ok){
                m_btnConnect->setText("Connect");
                m_labelServerStatus->setText("Server Failed to Start.");
            }
            else{
                m_btnConnect->setText("Disconnect");
                m_labelServerStatus->setText("Server is Live.");
            }
        }
        else{
            m_server->stop();
            m_btnConnect->setText("Connect");
            m_labelServerStatus->setText("Server is Not Live.");
        }

    });
}
