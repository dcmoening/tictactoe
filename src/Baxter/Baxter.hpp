#ifndef BAXTER_H
#define BAXTER_H

#include <stdlib.h>
#include <gtest/gtest.h>

#include "Tictactoe.hpp"

class Baxter
{
public:
    // use default ctor
    Baxter(T3& t3, const char player) :
        m_t3(t3),
        m_player(player),
        m_otherPlayer(player == t3.PLAYER_O ? t3.PLAYER_X : t3.PLAYER_O)
    {
    }

    void Move();

private:
    FRIEND_TEST(BaxterTest, CalculateRow);
    FRIEND_TEST(BaxterTest, CalculateCol);
    FRIEND_TEST(BaxterTest, CalculateDiag);
    FRIEND_TEST(BaxterTest, CalculatePaths);

    T3& m_t3;
    const char m_player;
    const char m_otherPlayer;
    static constexpr size_t diag1{0};
    static constexpr size_t diag2{1};

    // empty spots that are possibilities for next move
    int playableIndexOfRow{0};
    int playableIndexOfCol{0};
    int playableIndexOfDiag1{0};
    int playableIndexOfDiag2{0};


    struct LargestSet
    {
        size_t index{0};
        int value{0};
        size_t emptyRow{0};
        size_t emptyCol{0};
        bool valid{false};
    };

    void CalculatePaths(LargestSet& largestSet);
    void CalculateRow(LargestSet& largestSet, char player, char otherPlayer);
    void CalculateCol(LargestSet& largestSet, char player, char otherPlayer);
    void CalculateDiag(LargestSet& largestSet, char player, char otherPlayer);
};

#endif