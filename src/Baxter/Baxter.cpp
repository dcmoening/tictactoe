#include <stdio.h>

#include "Baxter.hpp"

void Baxter::Move()
{
    LargestSet largestSet;
    CalculatePaths(largestSet);

    // Place player piece in the row and col provided by the calculation
    m_t3.board[largestSet.emptyRow][largestSet.emptyCol] = m_player;
}

// For the selected player, find the most number of
void Baxter::CalculateRow(LargestSet& largestSet, char player, char otherPlayer)
{
    int rowWeights = 0;
    size_t emptyRow = 0;
    size_t emptyCol = 0;

    for (size_t row = 0; row < m_t3.SIZE; ++row)
    {
        rowWeights = 0;
        for(size_t col = 0; col < m_t3.SIZE; ++col)
        {
            char piece = m_t3.board[row][col];

            if (piece == otherPlayer)
            {
                // Not a winning path.
                rowWeights = -1;
            }
            else if ((piece == player) && (rowWeights != -1))
            {
                // Possibly a winning path
                rowWeights++;
            }
            else if ((piece != player) && (piece != otherPlayer))
            {
                // just found an empty spot..
                emptyCol = col;
                emptyRow = row;
            }
        }

        if (rowWeights > largestSet.value)
        {
            largestSet.value = rowWeights;
            largestSet.emptyRow = emptyRow;
            largestSet.emptyCol = emptyCol;
        }
    }

    // provide an empty spot to play in case there is not a winning path.
    if (largestSet.value == 0)
    {
        largestSet.emptyRow = emptyRow;
        largestSet.emptyCol = emptyCol;
        largestSet.valid = true;
    }
}

void Baxter::CalculateCol(LargestSet& largestSet, char player, char otherPlayer)
{
    int colWeights = 0;
    size_t emptyRow = 0;
    size_t emptyCol = 0;

    for (size_t col = 0; col < m_t3.SIZE; ++col)
    {
        colWeights = 0;
        for(size_t row = 0; row < m_t3.SIZE; ++row)
        {
            char piece = m_t3.board[row][col];

            if (piece == otherPlayer)
            {
                // Not a winning path.
                colWeights = -1;
            }
            else if ((piece == player) && (colWeights != -1))
            {
                // Possibly a winning path
                colWeights++;
            }
            else if ((piece != player) && (piece != otherPlayer))
            {
                // just found an empty spot..
                emptyCol = col;
                emptyRow = row;
            }
        }

        if ((colWeights > largestSet.value))
        {
            largestSet.value = colWeights;
            largestSet.emptyRow = emptyRow;
            largestSet.emptyCol = col;
            largestSet.valid = true;
        }
    }

    // provide an empty spot to play in case there is not a winning path.
    if (largestSet.value == 0)
    {
        largestSet.emptyRow = emptyRow;
        largestSet.emptyCol = emptyCol;
        largestSet.valid = true;
    }
}

void Baxter::CalculateDiag(LargestSet& largestSet, char player, char otherPlayer)
{
    // Calculate Diag 1
    int diagWeight = 0;
    size_t emptyRow = 0;
    size_t emptyCol = 0;
    char piece = 0;

    for (size_t rowCol = 0; rowCol < m_t3.SIZE; ++rowCol)
    {
        piece = m_t3.board[rowCol][rowCol];

        if (piece == otherPlayer)
        {
            // Not a winning path.
            diagWeight = -1;
        }
        else if ((piece == player) && (diagWeight != -1))
        {
            // Possibly a winning path
            diagWeight++;
        }
        else if ((piece != player) && (piece != otherPlayer))
        {
            // just found an empty spot..
            emptyCol = rowCol;
            emptyRow = rowCol;
        }
    }

    if (diagWeight > largestSet.value)
    {
        largestSet.value = diagWeight;
        largestSet.emptyRow = emptyRow;
        largestSet.emptyCol = emptyCol;
        largestSet.valid = true;
    }

    // provide an empty spot to play in case there is not a winning path.
    if (largestSet.value == 0)
    {
        largestSet.emptyRow = emptyRow;
        largestSet.emptyCol = emptyCol;
        largestSet.valid = true;
    }

    // Calculate Diag 2
    diagWeight = 0;
    size_t diag2Col = 3;
    for (size_t diag2Row = 0; diag2Row < m_t3.SIZE; ++diag2Row)
    {
        piece = m_t3.board[diag2Row][diag2Col];

        if (piece == otherPlayer)
        {
            // Not a winning path.
            diagWeight = -1;
        }
        else if ((piece == player) && (diagWeight != -1))
        {
            // Possibly a winning path
            diagWeight++;
        }
        else if ((piece != player) && (piece != otherPlayer))
        {
            // just found an empty spot..
            emptyCol = diag2Col;
            emptyRow = diag2Row;
        }
        --diag2Col;
    }

    if (diagWeight > largestSet.value)
    {
        largestSet.value = diagWeight;
        largestSet.emptyRow = emptyRow;
        largestSet.emptyCol = emptyCol;
        largestSet.valid = true;
    }

    // provide an empty spot to play in case there is not a winning path.
    if (largestSet.value == 0)
    {
        largestSet.emptyRow = emptyRow;
        largestSet.emptyCol = emptyCol;
        largestSet.valid = true;
    }
}

void Baxter::CalculatePaths(LargestSet& largestSet)
{
    LargestSet myLargestSet;
    LargestSet enemyLargestSet;

    // Calculate my highest weight
    CalculateRow(myLargestSet, m_player, m_otherPlayer);
    //printf("LargestSet Row: value: %i, row: %zu, col: %zu\n", myLargestSet.value, myLargestSet.emptyRow, myLargestSet.emptyCol);
    CalculateCol(myLargestSet, m_player, m_otherPlayer);
    //printf("LargestSet Col: value: %i, row: %zu, col: %zu\n", myLargestSet.value, myLargestSet.emptyRow, myLargestSet.emptyCol);
    CalculateDiag(myLargestSet, m_player, m_otherPlayer);
    //printf("LargestSet Diag: value: %i, row: %zu, col: %zu\n", myLargestSet.value, myLargestSet.emptyRow, myLargestSet.emptyCol);

    // Calculate opponents highest weight
    CalculateRow(enemyLargestSet, m_otherPlayer, m_player);
    //printf("LargestSet E Row: value: %i, row: %zu, col: %zu\n", enemyLargestSet.value, enemyLargestSet.emptyRow, enemyLargestSet.emptyCol);
    CalculateCol(enemyLargestSet, m_otherPlayer, m_player);
    //printf("LargestSet E Col: value: %i, row: %zu, col: %zu\n", enemyLargestSet.value, enemyLargestSet.emptyRow, enemyLargestSet.emptyCol);
    CalculateDiag(enemyLargestSet, m_otherPlayer, m_player);
    //printf("LargestSet E Diag: value: %i, row: %zu, col: %zu\n", enemyLargestSet.value, enemyLargestSet.emptyRow, enemyLargestSet.emptyCol);

    // Place a piece with the largest set.
    if ((myLargestSet.value == 0) && (enemyLargestSet.value == 0))
    {
        // Doesn't look like there's a winning spot, play in a valid spot.
        largestSet = myLargestSet.valid ? myLargestSet : enemyLargestSet;
    }
    else
    {
        largestSet = myLargestSet.value > enemyLargestSet.value ? myLargestSet : enemyLargestSet;
    }
    //printf("LargestSet: value: %i, row: %zu, col: %zu\n", largestSet.value, largestSet.emptyRow, largestSet.emptyCol);
}