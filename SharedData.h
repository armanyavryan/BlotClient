#pragma once
#include <QString>

enum class PacketType{
    None =-1,
    NCommands = 0,
    NFloatingValues,
    NCards
};

namespace NCommands{
const QString CONNECTED           = "CONNECTED";
const QString DISCONNECTED        = "DISCONNECTED";
const QString CONNETION_FINISHED  = "CONNETION_FINISHED";
const QString LOADING_FINISHED    = "LOADING_FINISHED";
};

namespace NFloatingValues{
const QString CONNECTION_PROGRESS = "CONNECTION_PROGRESS";
const QString LOADING_PROGRESS = "LOADING_PROGRESS";

};


namespace NCards{
const QString DELIVER_8_CARDS = "DELIVER_8_CARDS";

};


enum class CardSuits{
    Clubs = 0,
    Spades,
    Hearts,
    Diamonds
};

enum class CardRanks{
    Two = 2,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace = 14,
};
