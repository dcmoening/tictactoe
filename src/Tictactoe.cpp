#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <memory.h>

#include "Tictactoe.hpp"
#include "Baxter.hpp"
#include "Ultron.hpp"

struct T3 t3;

// Baxter is player "O"
Baxter baxter(t3, t3.PLAYER_O);
Ultron ultron(t3, t3.PLAYER_X);

void initializeBoard() {
    for (int i = 0; i < t3.SIZE; i++)
        for (int j = 0; j < t3.SIZE; j++)
            t3.board[i][j] = t3.EMPTY;
}

void printBoard() {
    for (int i = 0; i < t3.SIZE; i++) {
        for (int j = 0; j < t3.SIZE; j++) {
            printf("%c ", t3.board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int checkLine(char player, char a, char b, char c, char d) {
    return a == player && b == player && c == player && d == player;
}

int checkWin(char player) {
    // rows and columns
    for (int i = 0; i < t3.SIZE; i++) {
        if (checkLine(player, t3.board[i][0], t3.board[i][1], t3.board[i][2], t3.board[i][3])) return 1;
        if (checkLine(player, t3.board[0][i], t3.board[1][i], t3.board[2][i], t3.board[3][i])) return 1;
    }
    // diagonals
    if (checkLine(player, t3.board[0][0], t3.board[1][1], t3.board[2][2], t3.board[3][3])) return 1;
    if (checkLine(player, t3.board[0][3], t3.board[1][2], t3.board[2][1], t3.board[3][0])) return 1;
    return 0;
}

int isBoardFull() {
    for (int i = 0; i < t3.SIZE; i++)
        for (int j = 0; j < t3.SIZE; j++)
            if (t3.board[i][j] == t3.EMPTY) return 0;
    return 1;
}

void cpuMoveO() {
    // int row, col;
    // do {
    //     row = rand() % t3.SIZE;
    //     col = rand() % t3.SIZE;
    // } while (t3.board[row][col] != t3.EMPTY);
    // t3.board[row][col] = t3.PLAYER_O;
    baxter.Move();
}

void cpuMoveX() {
    // int row, col;
    // do {
    //     row = rand() % t3.SIZE;
    //     col = rand() % t3.SIZE;
    // } while (t3.board[row][col] != t3.EMPTY);
    // t3.board[row][col] = t3.PLAYER_X;
    ultron.Move();
}

int main() {
    srand(time(NULL));

    for (int game = 0; game < 1000; game++) {
        initializeBoard();
        int xTurn = game % 2 == 0;

        while (1) {
            if (xTurn) {
                //printf("Enemy's Turn\n");
                cpuMoveX();
            } else {
                //printf("my Turn\n");
                cpuMoveO();
            }

            //printBoard();

            t3.currentPlayer = xTurn ? t3.PLAYER_X : t3.PLAYER_O;
            if (checkWin(t3.currentPlayer)) {
                if (t3.currentPlayer == t3.PLAYER_X) t3.winsX++;
                else t3.winsO++;
                printf("%c wins!\n", t3.currentPlayer);
                break;
            }

            if (isBoardFull()) {
                printf("It's a draw!\n");
                break;
            }
            xTurn = !xTurn;
        }
        //printBoard();
    }

    // Final score calculation
    int scoreX = 0, scoreO = 0;
    if (t3.winsX > t3.winsO) scoreX = 3;
    else if (t3.winsO > t3.winsX) scoreO = 3;
    else scoreX = scoreO = 1;

    printf("Final Wins: X = %d, O = %d\n", t3.winsX, t3.winsO);
    printf("Final Score: X = %d, O = %d\n", scoreX, scoreO);

    return 0;
}
