#include <gtest/gtest.h>

#include "Tictactoe.hpp"
#include "Baxter.hpp"

class BaxterTest : public testing::Test
{
public:
    BaxterTest()
    {
        InitializeEmpty();
    }

    T3 m_t3;

    void InitializeEmpty()
    {
        for (size_t row=0; row<m_t3.SIZE; ++row)
        {
            for (size_t col=0; col<m_t3.SIZE; ++col)
            {
                m_t3.board[row][col] = m_t3.EMPTY;
            }
        }
    }

    void InitializeX()
    {
        for (size_t row=0; row<m_t3.SIZE; ++row)
        {
            for (size_t col=0; col<m_t3.SIZE; ++col)
            {
                m_t3.board[row][col] = m_t3.PLAYER_X;
            }
        }
    }

    void InitializeO()
    {
        for (size_t row=0; row<m_t3.SIZE; ++row)
        {
            for (size_t col=0; col<m_t3.SIZE; ++col)
            {
                m_t3.board[row][col] = m_t3.PLAYER_O;
            }
        }
    }
};

// Demonstrate some basic assertions.
TEST_F(BaxterTest, CalculateRow)
{
    Baxter::LargestSet largestSet;
    InitializeO();
    Baxter baxter(m_t3, m_t3.PLAYER_X);

    for (size_t col = 0; col < m_t3.SIZE; ++col)
    {
        // Set to empty
        m_t3.board[0][col] = m_t3.EMPTY;

        // calculate
        baxter.CalculateRow(largestSet, m_t3.PLAYER_X, m_t3.PLAYER_O);

        // check none of the O's have been modified
        for (size_t colCheck = 0; colCheck < m_t3.SIZE; ++colCheck)
        {
            if (col != colCheck)
            {
                EXPECT_EQ(m_t3.board[0][colCheck], m_t3.PLAYER_O);
                EXPECT_EQ(m_t3.board[largestSet.emptyRow][largestSet.emptyCol], m_t3.EMPTY);
            }
        }
        // restore to 'O'
        m_t3.board[0][col] = m_t3.PLAYER_O;
    }
}

TEST_F(BaxterTest, CalculateCol)
{
    Baxter::LargestSet largestSet;
    InitializeO();
    Baxter baxter(m_t3, m_t3.PLAYER_X);

    for (size_t row = 0; row < m_t3.SIZE; ++row)
    {
        // Set to empty
        m_t3.board[row][0] = m_t3.EMPTY;

        // calculate
        baxter.CalculateCol(largestSet, m_t3.PLAYER_X, m_t3.PLAYER_O);
        EXPECT_EQ(m_t3.board[largestSet.emptyRow][largestSet.emptyCol], m_t3.EMPTY);

        // check none of the O's have been modified
        for (size_t rowCheck = 0; rowCheck < m_t3.SIZE; ++rowCheck)
        {
            if (row != rowCheck)
            {
                EXPECT_EQ(m_t3.board[rowCheck][0], m_t3.PLAYER_O);
            }
        }
        // restore to 'O'
        m_t3.board[row][0] = m_t3.PLAYER_O;
    }
}

TEST_F(BaxterTest, CalculateDiag)
{
    Baxter::LargestSet largestSet;
    InitializeO();
    Baxter baxter(m_t3, m_t3.PLAYER_X);

    for (size_t rowCol = 0; rowCol < m_t3.SIZE; ++rowCol)
    {
        // Set to empty
        m_t3.board[rowCol][rowCol] = m_t3.EMPTY;

        // calculate
        baxter.CalculateDiag(largestSet, m_t3.PLAYER_X, m_t3.PLAYER_O);
        EXPECT_EQ(m_t3.board[largestSet.emptyRow][largestSet.emptyCol], m_t3.EMPTY);

        // check none of the O's have been modified
        for (size_t rowColCheck = 0; rowColCheck < m_t3.SIZE; ++rowColCheck)
        {
            if (rowCol != rowColCheck)
            {
                EXPECT_EQ(m_t3.board[rowColCheck][rowColCheck], m_t3.PLAYER_O);
            }
        }
        // restore to 'O'
        m_t3.board[rowCol][rowCol] = m_t3.PLAYER_O;
    }


    InitializeO();

    size_t diag2Col = 3;
    for (size_t diag2Row = 0; diag2Row < m_t3.SIZE; ++diag2Row)
    {
        // Set to empty
        m_t3.board[diag2Row][diag2Col] = m_t3.EMPTY;

        // calculate
        baxter.CalculateDiag(largestSet, m_t3.PLAYER_X, m_t3.PLAYER_O);

        EXPECT_EQ(m_t3.board[largestSet.emptyRow][largestSet.emptyCol], m_t3.EMPTY);

        // check none of the O's have been modified
        size_t diag2ColCheck = 3;
        for (size_t diag2RowCheck = 0; diag2RowCheck < m_t3.SIZE; ++diag2RowCheck)
        {
            // Not checking diag2ColCheck since there will be only one col value per a row value
            // For example: {{0,3}, {1,2}, {2,1}, {3,0}}
            if (diag2Row != diag2RowCheck)
            {
                EXPECT_EQ(m_t3.board[diag2RowCheck][diag2ColCheck], m_t3.PLAYER_O);
            }
            --diag2ColCheck;
        }
        // restore to 'O'
        m_t3.board[diag2Row][diag2Col] = m_t3.PLAYER_O;

        --diag2Col;
    }
}

// TEST_F(BaxterTest, CalculatePaths)
// {

// }

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}