#include <stdio.h>
#include "game.h"
#include "ai.h"

int main() {
    GameState game;
    init_game(&game);
    
    printf("Tic-Tac-Toe with Sliding Window AI\n");
    printf("You are X, AI is O\n");
    printf("Enter row and column (0-2) separated by space\n");
    
    while (1) {
        display_board(&game);
        
        if (game.current_player == 'X') {
            // Human's turn
            int row, col;
            printf("Your move (row col): ");
            scanf("%d %d", &row, &col);
            
            if (!make_move(&game, row, col)) {
                printf("Invalid move. Try again.\n");
                continue;
            }
        } else {
            // AI's turn
            printf("AI is thinking...\n");
            Move ai_move = find_best_move(&game);
            make_move(&game, ai_move.row, ai_move.col);
            printf("AI played at %d %d\n", ai_move.row, ai_move.col);
        }
        
        // Check if the board is full and slide if needed
        if (game.move_count >= MAX_MOVES) {
            slide_board(&game);
        }
        
        // Check for winner
        char winner = check_win(&game);
        if (winner != ' ') {
            display_board(&game);
            if (winner == 'X') {
                printf("Congratulations! You won!\n");
            } else {
                printf("AI won! Better luck next time.\n");
            }
            break;
        }
    }
    
    return 0;
}