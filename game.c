#include <stdio.h>
#include <stdlib.h>
#include "game.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    printf("\033[2J\033[H");
#endif
}

void init_game(GameState *game) {
    clear_screen();
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            game->board[i][j] = ' ';
        }
    }
    game->move_count = 0;
    game->current_player = 'X';  // Human starts first
    game->human_score = 0;
    game->ai_score = 0;
}

// instruction menu
void display_instructions() {
    printf("\n=== TIC-TAC-TOE INSTRUCTIONS ===\n");
    printf("1. You are X, AI is O\n");
    printf("2. Enter row and column (0-2) separated by space\n");
    printf("3. After 3 moves per player, oldest moves disappear\n");
    printf("4. First to get 3 in a row wins the round\n");
    printf("5. Game continues until you choose to quit\n");
    printf("6. Press 'Q' to quit the game at any time\n");

    printf("\nBoard coordinates:\n");
    printf("(0,0) | (0,1) | (0,2)\n");
    printf("------|-------|------\n");
    printf("(1,0) | (1,1) | (1,2)\n");
    printf("------|-------|------\n");
    printf("(2,0) | (2,1) | (2,2)\n");
    printf("\n");
}

void display_board(const GameState *game) {
    clear_screen();
    printf("\n=== INFINITE TIC-TAC-TOE ===\n");
    printf("Your Score: %d | AI Score: %d\n", game->human_score, game->ai_score);
    printf("\nCurrent Player: %c\n", game->current_player);
    
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

    // Count current player's marks on the board
    int player_moves = 0;
    for (int i = 0; i < game->move_count; i++) {
        if (game->moves[i].player == game->current_player) {
            player_moves++;
        }
    }

    // If player already has 3 marks, remove their oldest move
    if (player_moves == 3) {
        remove_oldest_move(game, game->current_player);
    }

    game->board[row][col] = game->current_player;

    // Record the move at the end
    game->moves[game->move_count].row = row;
    game->moves[game->move_count].col = col;
    game->moves[game->move_count].player = game->current_player;
    game->move_count++;

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

    // Check columns
    for (int j = 0; j < BOARD_SIZE; j++) {
        if (game->board[0][j] != ' ' && 
            game->board[0][j] == game->board[1][j] && 
            game->board[1][j] == game->board[2][j]) {
            return game->board[0][j];
        }
    }

    // Check diagonals
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

// void remove_oldest_move(GameState *game) {
//     if (game->move_count > MAX_HISTORY) {
//         int oldest_index = (game->move_count - MAX_HISTORY - 1) % MAX_HISTORY;
//         Move oldest = game->moves[oldest_index];
//         game->board[oldest.row][oldest.col] = ' ';
//     }
// }

void remove_oldest_move(GameState *game, char player) {
    int oldest_index = -1;
    // Find the oldest move for the given player
    for (int i = 0; i < game->move_count; i++) {
        if (game->moves[i].player == player) {
            oldest_index = i;
            break;
        }
    }
    if (oldest_index != -1) {
        Move oldest = game->moves[oldest_index];
        game->board[oldest.row][oldest.col] = ' ';
        // Shift moves left
        for (int i = oldest_index; i < game->move_count - 1; i++) {
            game->moves[i] = game->moves[i + 1];
        }
        game->move_count--;
    }
}
