#ifndef GAME_H
#define GAME_H

#define BOARD_SIZE 3
#define MAX_MOVES 9

typedef struct {
    int row;
    int col;
} Move;

typedef struct {
    char board[BOARD_SIZE][BOARD_SIZE];
    Move moves[MAX_MOVES];
    int move_count;
    char current_player;
} GameState;

void init_game(GameState *game);
void display_board(const GameState *game);
int make_move(GameState *game, int row, int col);
char check_win(const GameState *game);
void slide_board(GameState *game);

#endif