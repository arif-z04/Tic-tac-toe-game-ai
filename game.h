#ifndef GAME_H
#define GAME_H

#define BOARD_SIZE 3
#define MAX_MOVES 6  // Keep track of last 6 moves (3 per player)

typedef struct {
    int row;
    int col;
    char player;
} Move;

typedef struct {
    char board[BOARD_SIZE][BOARD_SIZE];
    Move moves[MAX_MOVES];
    int move_count;
    char current_player;
    int human_score;
    int ai_score;
} GameState;

void init_game(GameState *game);
void display_board(const GameState *game);
int make_move(GameState *game, int row, int col);
char check_win(const GameState *game);
void remove_oldest_move(GameState *game, char player);
void display_instructions();
void clear_screen();

#endif