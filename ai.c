#include <limits.h>
#include "ai.h"

int evaluate(const GameState *game) {
    char winner = check_win(game);
    
    if (winner == 'O') return 10;    // AI wins
    if (winner == 'X') return -10;   // Human wins
    return 0;  // Draw
}

int minimax(GameState *game, int depth, int is_maximizing, int alpha, int beta) {
    int score = evaluate(game);
    
    // If game is over
    if (score == 10 || score == -10) return score;
    
    // If no moves left
    if (game->move_count == MAX_MOVES) return 0;
    
    if (is_maximizing) {
        int best = INT_MIN;
        
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (game->board[i][j] == ' ') {
                    // Make the move
                    game->board[i][j] = 'O';
                    game->move_count++;
                    
                    // Call minimax recursively
                    int val = minimax(game, depth + 1, 0, alpha, beta);
                    
                    // Undo the move
                    game->board[i][j] = ' ';
                    game->move_count--;
                    
                    best = (val > best) ? val : best;
                    alpha = (alpha > best) ? alpha : best;
                    if (beta <= alpha) break;
                }
            }
        }
        return best;
    } else {
        int best = INT_MAX;
        
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (game->board[i][j] == ' ') {
                    // Make the move
                    game->board[i][j] = 'X';
                    game->move_count++;
                    
                    // Call minimax recursively
                    int val = minimax(game, depth + 1, 1, alpha, beta);
                    
                    // Undo the move
                    game->board[i][j] = ' ';
                    game->move_count--;
                    
                    best = (val < best) ? val : best;
                    beta = (beta < best) ? beta : best;
                    if (beta <= alpha) break;
                }
            }
        }
        return best;
    }
}

Move find_best_move(GameState *game) {
    int best_val = INT_MIN;
    Move best_move = {-1, -1};
    
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (game->board[i][j] == ' ') {
                // Make the move
                game->board[i][j] = 'O';
                game->move_count++;
                
                // Compute evaluation function for this move
                int move_val = minimax(game, 0, 0, INT_MIN, INT_MAX);
                
                // Undo the move
                game->board[i][j] = ' ';
                game->move_count--;
                
                // If the value of the current move is better than best, update best
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