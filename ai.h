#ifndef AI_H
#define AI_H

#include "game.h"

int evaluate(const GameState *game);
int evaluate_line(int x_count, int o_count);

int minimax(GameState *game, int depth, int is_maximizing, int alpha, int beta);
Move find_best_move(GameState *game);

#endif