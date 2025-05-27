#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include "ai.h"

// Weighted evaluation function
int evaluate(const GameState *game) {
    char winner = check_win(game);
    
    if (winner == 'O') return 1000;    // AI wins
    if (winner == 'X') return -1000;   // Human wins
    
    int score = 0;
    
    // Evaluate all rows, columns and diagonals
    for (int i = 0; i < BOARD_SIZE; i++) {
        // Rows
        int x_count = 0, o_count = 0;
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (game->board[i][j] == 'X') x_count++;
            if (game->board[i][j] == 'O') o_count++;
        }
        score += evaluate_line(x_count, o_count);
        
        // Columns
        x_count = 0, o_count = 0;
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (game->board[j][i] == 'X') x_count++;
            if (game->board[j][i] == 'O') o_count++;
        }
        score += evaluate_line(x_count, o_count);
    }
    
    // Diagonals
    int x_count = 0, o_count = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (game->board[i][i] == 'X') x_count++;
        if (game->board[i][i] == 'O') o_count++;
    }
    score += evaluate_line(x_count, o_count);
    
    x_count = 0, o_count = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (game->board[i][BOARD_SIZE-1-i] == 'X') x_count++;
        if (game->board[i][BOARD_SIZE-1-i] == 'O') o_count++;
    }
    score += evaluate_line(x_count, o_count);
    
    return score;
}

int evaluate_line(int x_count, int o_count) {
    if (x_count == 3) return -100;
    if (o_count == 3) return 100;
    if (x_count == 2 && o_count == 0) return -10;
    if (o_count == 2 && x_count == 0) return 10;
    if (x_count == 1 && o_count == 0) return -1;
    if (o_count == 1 && x_count == 0) return 1;
    return 0;
}

int minimax(GameState *game, int depth, int is_maximizing, int alpha, int beta) {
    int score = evaluate(game);
    
    // Terminal nodes
    if (abs(score) >= 100) return score;
    if (depth >= 5) return score;  // Depth limit for performance
    
    if (is_maximizing) {
        int best = INT_MIN;
        
        // Move ordering - center first
        int move_order[BOARD_SIZE][BOARD_SIZE] = {
            {1, 0, 1},
            {0, 2, 0},
            {1, 0, 1}
        };
        
        for (int priority = 2; priority >= 0; priority--) {
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (move_order[i][j] == priority && game->board[i][j] == ' ') {
                        game->board[i][j] = 'O';
                        game->move_count++;
                        
                        int val = minimax(game, depth + 1, 0, alpha, beta);
                        
                        game->board[i][j] = ' ';
                        game->move_count--;
                        
                        best = (val > best) ? val : best;
                        alpha = (alpha > best) ? alpha : best;
                        if (beta <= alpha) return best;
                    }
                }
            }
        }
        return best;
    } else {
        int best = INT_MAX;
        
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (game->board[i][j] == ' ') {
                    game->board[i][j] = 'X';
                    game->move_count++;
                    
                    int val = minimax(game, depth + 1, 1, alpha, beta);
                    
                    game->board[i][j] = ' ';
                    game->move_count--;
                    
                    best = (val < best) ? val : best;
                    beta = (beta < best) ? beta : best;
                    if (beta <= alpha) return best;
                }
            }
        }
        return best;
    }
}

Move find_best_move(GameState *game) {
    int best_val = INT_MIN;
    Move best_move = {-1, -1, ' '};
    int alpha = INT_MIN;
    int beta = INT_MAX;
    
    // Check for immediate win
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (game->board[i][j] == ' ') {
                game->board[i][j] = 'O';
                if (check_win(game) == 'O') {
                    game->board[i][j] = ' ';
                    return (Move){i, j, ' '};
                }
                game->board[i][j] = ' ';
            }
        }
    }
    
    // Check for immediate block
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (game->board[i][j] == ' ') {
                game->board[i][j] = 'X';
                if (check_win(game) == 'X') {
                    game->board[i][j] = ' ';
                    return (Move){i, j, ' '};
                }
                game->board[i][j] = ' ';
            }
        }
    }
    
    // If center is available, take it
    if (game->board[1][1] == ' ') {
        return (Move){1, 1, ' '};
    }
    
    // Use minimax for other moves
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (game->board[i][j] == ' ') {
                game->board[i][j] = 'O';
                game->move_count++;
                
                int move_val = minimax(game, 0, 0, alpha, beta);
                
                game->board[i][j] = ' ';
                game->move_count--;
                
                if (move_val > best_val) {
                    best_move.row = i;
                    best_move.col = j;
                    best_val = move_val;
                }
            }
        }
    }
    
    return best_move;
}