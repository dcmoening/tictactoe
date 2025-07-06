#ifndef TICTACTOE_H
#define TICTACTOE_H

struct T3
{
    static const size_t SIZE = 4;
    const char EMPTY = '.';
    const char PLAYER_X = 'X';
    const char PLAYER_O = 'O';

    char board[SIZE][SIZE] = {0};
    int winsX = 0, winsO = 0;
    char currentPlayer = 0;
};


#endif