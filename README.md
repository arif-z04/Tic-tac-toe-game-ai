# Infinite Tic-Tac-Toe (C Project)

A command-line Tic-Tac-Toe game in C with a twist:  
**Each player can only have 3 marks on the board at a time.**  
When a player makes a 4th move, their oldest mark disappears!  
Play against a simple AI and keep score over multiple rounds.

---

## Features

- Classic 3x3 Tic-Tac-Toe board
- Each player (You: X, AI: O) can only have 3 marks at a time
- Oldest mark for a player disappears when making a 4th move
- Play against an AI opponent
- Score tracking across rounds
- Clear instructions and board display
- Cross-platform screen clearing (Windows/Linux)

---

## How to Build

### Requirements

- GCC or any C99-compatible compiler
- Windows or Linux

### Build (using MinGW or similar)

```sh
mingw32-make
```
Or manually:
```sh
gcc -Wall -Wextra -std=c99 -O3 main.c game.c ai.c -o tic_tac_toe
```

---

## How to Play

1. Run the executable:
    ```sh
    ./tic_tac_toe
    ```
2. Follow the on-screen instructions.
3. Enter your move as:  
   ```
   row col
   ```
   (e.g., `1 2` for row 1, column 2)
4. Press `Q` at any prompt to quit.

---

## File Structure

- `main.c` - Main game loop and user interaction
- `game.c` / `game.h` - Game logic, board management, move history
- `ai.c` / `ai.h` - Simple AI logic for computer moves
- `README.md` - This file

---

## Rules

- You are **X**, AI is **O**
- Only 3 marks per player on the board at any time
- Making a 4th move removes your oldest mark
- First to get 3 in a row wins the round
- Scores are tracked until you quit

---

## Example Board

```
 X |   | O 
---|---|---
   | X |   
---|---|---
 O |   | X 
```

---

## License

MIT License (see LICENSE if provided)

---

## Credits

- Developed by S.M.Arifuzzaman
- Inspired by classic Tic-Tac-Toe with an infinite twist!