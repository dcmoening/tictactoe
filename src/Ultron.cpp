#include <stdlib.h>
#include <time.h>

#include "Ultron.hpp"

void Ultron::Move()
{
    int priority = 0; // Default defensive

    if ((m_player == m_t3.PLAYER_X && m_t3.winsX < m_t3.winsO) ||
        (m_player == m_t3.PLAYER_O && m_t3.winsO < m_t3.winsX)) {
        priority = 1; // Play offensive if losing
    }

    char players[2] = { m_player, m_otherPlayer };

    // Look for immediate wins/block (4 in a row)
    for (int pIdx = 0; pIdx < 2; pIdx++) {
        char p = players[pIdx];
        for (int k = -2; k < 1; k++) {
            for (int i = 0; i < m_t3.SIZE; i++) {
                for (int j = 0; j < m_t3.SIZE; j++) {
                    // Vertical checks
                    if (j - k >= 0 && j - k + 3 < m_t3.SIZE) {
                        if (m_t3.board[i][j-k] == m_t3.EMPTY && m_t3.board[i][j-k+1] == p && m_t3.board[i][j-k+2] == p && m_t3.board[i][j-k+3] == p) { m_t3.board[i][j-k] = m_player; return; }
                        if (m_t3.board[i][j-k] == p && m_t3.board[i][j-k+1] == m_t3.EMPTY && m_t3.board[i][j-k+2] == p && m_t3.board[i][j-k+3] == p) { m_t3.board[i][j-k+1] = m_player; return; }
                        if (m_t3.board[i][j-k] == p && m_t3.board[i][j-k+1] == p && m_t3.board[i][j-k+2] == m_t3.EMPTY && m_t3.board[i][j-k+3] == p) { m_t3.board[i][j-k+2] = m_player; return; }
                        if (m_t3.board[i][j-k] == p && m_t3.board[i][j-k+1] == p && m_t3.board[i][j-k+2] == p && m_t3.board[i][j-k+3] == m_t3.EMPTY) { m_t3.board[i][j-k+3] = m_player; return; }
                    }
                    // Horizontal checks
                    if (i - k >= 0 && i - k + 3 < m_t3.SIZE) {
                        if (m_t3.board[i-k][j] == m_t3.EMPTY && m_t3.board[i-k+1][j] == p && m_t3.board[i-k+2][j] == p && m_t3.board[i-k+3][j] == p) { m_t3.board[i-k][j] = m_player; return; }
                        if (m_t3.board[i-k][j] == p && m_t3.board[i-k+1][j] == m_t3.EMPTY && m_t3.board[i-k+2][j] == p && m_t3.board[i-k+3][j] == p) { m_t3.board[i-k+1][j] = m_player; return; }
                        if (m_t3.board[i-k][j] == p && m_t3.board[i-k+1][j] == p && m_t3.board[i-k+2][j] == m_t3.EMPTY && m_t3.board[i-k+3][j] == p) { m_t3.board[i-k+2][j] = m_player; return; }
                        if (m_t3.board[i-k][j] == p && m_t3.board[i-k+1][j] == p && m_t3.board[i-k+2][j] == p && m_t3.board[i-k+3][j] == m_t3.EMPTY) { m_t3.board[i-k+3][j] = m_player; return; }
                    }
                }
            }
        }

        // Diagonal bottom-left to top-right
        if (m_t3.board[0][0] == m_t3.EMPTY && m_t3.board[1][1] == p && m_t3.board[2][2] == p && m_t3.board[3][3] == p) { m_t3.board[0][0] = m_player; return; }
        if (m_t3.board[0][0] == p && m_t3.board[1][1] == m_t3.EMPTY && m_t3.board[2][2] == p && m_t3.board[3][3] == p) { m_t3.board[1][1] = m_player; return; }
        if (m_t3.board[0][0] == p && m_t3.board[1][1] == p && m_t3.board[2][2] == m_t3.EMPTY && m_t3.board[3][3] == p) { m_t3.board[2][2] = m_player; return; }
        if (m_t3.board[0][0] == p && m_t3.board[1][1] == p && m_t3.board[2][2] == p && m_t3.board[3][3] == m_t3.EMPTY) { m_t3.board[3][3] = m_player; return; }

        // Diagonal bottom-right to top-left
        if (m_t3.board[3][0] == m_t3.EMPTY && m_t3.board[2][1] == p && m_t3.board[1][2] == p && m_t3.board[0][3] == p) { m_t3.board[3][0] = m_player; return; }
        if (m_t3.board[3][0] == p && m_t3.board[2][1] == m_t3.EMPTY && m_t3.board[1][2] == p && m_t3.board[0][3] == p) { m_t3.board[2][1] = m_player; return; }
        if (m_t3.board[3][0] == p && m_t3.board[2][1] == p && m_t3.board[1][2] == m_t3.EMPTY && m_t3.board[0][3] == p) { m_t3.board[1][2] = m_player; return; }
        if (m_t3.board[3][0] == p && m_t3.board[2][1] == p && m_t3.board[1][2] == p && m_t3.board[0][3] == m_t3.EMPTY) { m_t3.board[0][3] = m_player; return; }
    }

    // Defensive or offensive based on priority: switch player order
    if (priority == 0) {
        players[0] = m_otherPlayer;
        players[1] = m_player;
    } else {
        players[0] = m_player;
        players[1] = m_otherPlayer;
    }

    // Prioritized placement logic
    for (int pIdx = 0; pIdx < 2; pIdx++) {
        char p = players[pIdx];
        for (int k = -2; k < 1; k++) {
            for (int i = 0; i < m_t3.SIZE; i++) {
                for (int j = 0; j < m_t3.SIZE; j++) {
                    // Horizontal triples
                    if (j-k >= 0 && j-k+2 < m_t3.SIZE) {
                        if (m_t3.board[i][j-k] == m_t3.EMPTY && m_t3.board[i][j-k+1] == p && m_t3.board[i][j-k+2] == p) { m_t3.board[i][j-k] = m_player; return; }
                        if (m_t3.board[i][j-k] == p && m_t3.board[i][j-k+1] == m_t3.EMPTY && m_t3.board[i][j-k+2] == p) { m_t3.board[i][j-k+1] = m_player; return; }
                        if (m_t3.board[i][j-k] == p && m_t3.board[i][j-k+1] == p && m_t3.board[i][j-k+2] == m_t3.EMPTY) { m_t3.board[i][j-k+2] = m_player; return; }
                    }
                    // Vertical triples
                    if (i-k >= 0 && i-k+2 < m_t3.SIZE) {
                        if (m_t3.board[i-k][j] == m_t3.EMPTY && m_t3.board[i-k+1][j] == p && m_t3.board[i-k+2][j] == p) { m_t3.board[i-k][j] = m_player; return; }
                        if (m_t3.board[i-k][j] == p && m_t3.board[i-k+1][j] == m_t3.EMPTY && m_t3.board[i-k+2][j] == p) { m_t3.board[i-k+1][j] = m_player; return; }
                        if (m_t3.board[i-k][j] == p && m_t3.board[i-k+1][j] == p && m_t3.board[i-k+2][j] == m_t3.EMPTY) { m_t3.board[i-k+2][j] = m_player; return; }
                    }
                }
            }
        }
        // Diagonal triples bottom-right to top-left
        for (int i = 0; i+2 < m_t3.SIZE; i++) {
            for (int j = 0; j+2 < m_t3.SIZE; j++) {
                if (m_t3.board[i][j] == m_t3.EMPTY && m_t3.board[i+1][j+1] == p && m_t3.board[i+2][j+2] == p) { m_t3.board[i][j] = m_player; return; }
                if (m_t3.board[i][j] == p && m_t3.board[i+1][j+1] == m_t3.EMPTY && m_t3.board[i+2][j+2] == p) { m_t3.board[i+1][j+1] = m_player; return; }
                if (m_t3.board[i][j] == p && m_t3.board[i+1][j+1] == p && m_t3.board[i+2][j+2] == m_t3.EMPTY) { m_t3.board[i+2][j+2] = m_player; return; }
            }
        }
        // Diagonal triples top-left to bottom-right
        for (int i = 0; i+2 < m_t3.SIZE; i++) {
            for (int j = 2; j < m_t3.SIZE; j++) {
                if (m_t3.board[i][j] == m_t3.EMPTY && m_t3.board[i+1][j-1] == p && m_t3.board[i+2][j-2] == p) { m_t3.board[i][j] = m_player; return; }
                if (m_t3.board[i][j] == p && m_t3.board[i+1][j-1] == m_t3.EMPTY && m_t3.board[i+2][j-2] == p) { m_t3.board[i+1][j-1] = m_player; return; }
                if (m_t3.board[i][j] == p && m_t3.board[i+1][j-1] == p && m_t3.board[i+2][j-2] == m_t3.EMPTY) { m_t3.board[i+2][j-2] = m_player; return; }
            }
        }
    }

    // Attack center squares if empty
    for (int i = 1; i <= 2; i++) {
        for (int j = 1; j <= 2; j++) {
            if (m_t3.board[i][j] == m_t3.EMPTY) { m_t3.board[i][j] = m_player; return; }
        }
    }

    // Corners for defensive mode
    if (priority == 0) {
        int corners[4][2] = { {0,0}, {0,3}, {3,0}, {3,3} };
        for (int k = 0; k < 4; k++) {
            int i = corners[k][0], j = corners[k][1];
            if (m_t3.board[i][j] == m_t3.EMPTY) { m_t3.board[i][j] = m_player; return; }
        }
    }

    // If no strategic move: random placement
    srand(time(NULL));
    while (1) {
        int randRow = rand() % m_t3.SIZE;
        int randCol = rand() % m_t3.SIZE;
        if (m_t3.board[randCol][randRow] == m_t3.EMPTY) {
            m_t3.board[randCol][randRow] = m_player;
            return;
        }
    }
}