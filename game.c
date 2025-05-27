#include <stdio.h>
#include <stdlib.h>
#include "game.h"

void init_game(GameState *game) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            game->board[i][j] = ' ';
        }
    }
    game->move_count = 0;
    game->current_player = 'X';  // Human starts first
}

void display_board(const GameState *game) {
    printf("\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf(" %c | %c | %c ", game->board[i][0], game->board[i][1], game->board[i][2]);
        if (i != BOARD_SIZE - 1) {
            printf("\n---|---|---\n");
        }
    }
    printf("\n");
}

int make_move(GameState *game, int row, int col) {
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || game->board[row][col] != ' ') {
        return 0;  // Invalid move
    }

    game->board[row][col] = game->current_player;
    
    // Record the move
    if (game->move_count < MAX_MOVES) {
        game->moves[game->move_count].row = row;
        game->moves[game->move_count].col = col;
        game->move_count++;
    }
    
    // Switch player
    game->current_player = (game->current_player == 'X') ? 'O' : 'X';
    return 1;
}

char check_win(const GameState *game) {
    // Check rows
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (game->board[i][0] != ' ' && 
            game->board[i][0] == game->board[i][1] && 
            game->board[i][1] == game->board[i][2]) {
            return game->board[i][0];
        }
    }
    // Checking columns
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (game->board[0][j] != ' ' && 
            game->board[0][j] == game->board[1][j] && 
            game->board[1][j] == game->board[2][j]) {
            return game->board[0][j];
        }
    }
    // checking Diagonals

    if (game->board[0][0] != ' ' && 
        game->board[0][0] == game->board[1][1] && 
        game->board[1][1] == game->board[2][2]) {
        return game->board[0][0];
    }
    
    if (game->board[0][2] != ' ' && 
        game->board[0][2] == game->board[1][1] && 
        game->board[1][1] == game->board[2][0]) {
        return game->board[0][2];
    }

    return ' ';  // No winner yet
}

void slide_board(GameState *game) {
    if (game->move_count >= MAX_MOVES) {
        // Remove the oldest move
        Move oldest = game->moves[0];
        game->board[oldest.row][oldest.col] = ' ';
        
        for (int i = 0; i < MAX_MOVES - 1; i++) {
            game->moves[i] = game->moves[i + 1];
        }
        game->move_count--;
    }
}