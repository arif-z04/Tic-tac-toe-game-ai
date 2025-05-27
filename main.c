#include <stdio.h>
#include <windows.h>
#include <ctype.h>
#include "game.h"
#include "ai.h"

int main() {
    GameState game;
    init_game(&game);
    
    display_instructions();
    printf("Press any key to start...");
    getchar();
    
    while (1) {
        init_game(&game);
        display_board(&game);
        
        while (1) {
            if (game.current_player == 'X') {
                // Human's turn
                int row, col;
                printf("Your move (row col, Q to quit): ");
                
                char input[10];
                fgets(input, sizeof(input), stdin);
                
                if (toupper(input[0]) == 'Q') {
                    printf("Final Score - You: %d, AI: %d\n", game.human_score, game.ai_score);
                    return 0;
                }
                
                if (sscanf(input, "%d %d", &row, &col) != 2) {
                    printf("Invalid input. Please enter row and column (0-2).\n");
                    continue;
                }
                
                if (!make_move(&game, row, col)) {
                    printf("Invalid move. Try again.\n");
                    continue;
                }
            } else {
                // AI's turn
                printf("AI is thinking...\n");
                #ifdef _WIN32
                Sleep(1000);  // Pause for dramatic effect
                #else
                sleep(1);
                #endif
                
                Move ai_move = find_best_move(&game);

                if(!make_move(&game, ai_move.row, ai_move.col)){
                    printf("AI made invalid move! This shouldn't happen! \n");
                    continue;
                }
                
                printf("AI played at %d %d\n", ai_move.row, ai_move.col);
            }
            
            display_board(&game);
            
            // Check for winner
            char winner = check_win(&game);
            if (winner != ' ') {
                if (winner == 'X') {
                    printf("You won this round!\n");
                    game.human_score++;
                } else {
                    printf("AI won this round!\n");
                    game.ai_score++;
                }
                
                printf("Score - You: %d, AI: %d\n", game.human_score, game.ai_score);
                printf("Press Q to quit or any other key to continue...");
                
                char choice = getchar();
                getchar();  // Consume newline
                
                if (toupper(choice) == 'Q') {
                    printf("Final Score - You: %d, AI: %d\n", game.human_score, game.ai_score);
                    return 0;
                }
                break;
            }
        }
    }
    
    return 0;
}