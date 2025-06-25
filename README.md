# C++ Console-Based Sudoku Game

A command-line Sudoku game written in C++. Generate, solve, and play Sudoku puzzles directly in your terminal.

## Features

* **Puzzle Generation**: Creates new Sudoku puzzles with a specified number of empty cells.
* **Automatic Solver**: Uses backtracking to solve any valid Sudoku puzzle.
* **Interactive Play**: Fill in numbers step-by-step, with conflict checking and completion feedback.
* **Grid Display**: Visual representation of the 9×9 Sudoku grid with clear subgrid separators.

## After Launch


Upon launch, you will see a menu:

1. **Generate new Sudoku puzzle**: Creates a fresh puzzle with 45 holes by default.
2. **Show solution**: Displays the full solution of the generated puzzle.
3. **Solve the puzzle**: Enter numbers interactively and check your work.
4. **Exit**: Quit the program.

Follow on-screen prompts to play.

## Gameplay

* **Filling cells**: Enter row (1–9), column (1–9), and the number (1–9) to insert into an empty cell.
* **Conflict detection**: The game prevents invalid moves that violate Sudoku rules.
* **Check solution**: Press `0` for row input to verify completeness and correctness.


