#pragma once

#include <QMainWindow>

class TcpServer;

class GamePlayer1vsPC;

class QLabel;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

private:
    void createMembers();
    void initMembers();
    void doLayout();
    void makeConnections();

private:
    QLabel *m_labelPort;
    QLabel *m_labelServerStatus;
    QPushButton *m_btnConnect;

    TcpServer *m_server = nullptr;
    bool m_isStarted = false;

    GamePlayer1vsPC *m_game_1vsPC;

};
