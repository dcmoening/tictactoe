#ifndef ULTRON_H
#define ULTRON_H

#include "Tictactoe.hpp"

class Ultron
{
public:
    Ultron(T3& t3, const char player) :
        m_t3(t3),
        m_player(player) ,
        m_otherPlayer(player == t3.PLAYER_O ? t3.PLAYER_X : t3.PLAYER_O)
    {
    }

    void Move();

private:
    T3& m_t3;
    const char m_player;
    const char m_otherPlayer;
};

#endif