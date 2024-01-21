QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Card/Card.cpp \
    Client.cpp \
    DeckOfCards.cpp \
    Games/GamePlayer1vsPC.cpp \
    Games/GamePlayers4.cpp \
    MainWindow.cpp \
    TcpServer.cpp \
    main.cpp

HEADERS += \
    Card/Card.h \
    Client.h \
    DeckOfCards.h \
    Games/GamePlayer1vsPC.h \
    Games/GamePlayers4.h \
    MainWindow.h \
    SharedData.h \
    TcpServer.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
