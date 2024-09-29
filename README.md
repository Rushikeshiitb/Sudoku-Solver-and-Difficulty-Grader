# Sudoku Solver and Difficulty Grader

## 1. Overview

This project implements a Sudoku solver using the Backtracking algorithm, designed to efficiently solve standard Sudoku puzzles. Additionally, it outputs a difficulty score based on various strategies applied and the number of empty cells.

## 2. Technologies Used
- **C++**
- **MS Excel** (For Data handling)

## 3. Approach and Features
**a**. **Input and Board Representation**
Input Mechanism: The project uses a 9x9 grid to represent the Sudoku board. The function take_input ensures valid input (numbers between 1 and 9 or -1 for empty cells) and initializes the board.
**b**. **Sudoku Solving Algorithm**
Backtracking Algorithm: This algorithm recursively tries placing numbers in empty cells while ensuring the current guess doesn’t violate Sudoku’s rules. It uses the safe_to_place function to verify if a number can be placed safely in a given row, column, and 3x3 sub-grid.
**c**. **Difficulty Analysis Features**
The project incorporates various Sudoku solving techniques to analyze and evaluate the puzzle's difficulty:

- **Naked Singles**: Counts the number of cells that have only one possible number based on existing constraints. Implemented in the naked_singles function.
- **Naked Doubles**: Identifies pairs of cells in a row, column, or grid that can only contain two numbers. Implemented in the naked_doubles function.
- **Naked Triples**: Similar to Naked Doubles but for triples of cells. Implemented in the naked_triples function.
- **Hidden Singles**: Identifies numbers that can only be placed in one cell of a row, column, or grid. Implemented in the hidden_singles function.
- **Hidden Doubles**: Identifies pairs of numbers that can only be placed in two specific cells of a row, column, or grid. Implemented in the hidden_doubles function.
## 4. Difficulty Rating
The difficulty rating is determined based on the number of Naked Singles, Naked Doubles, Naked Triples, Hidden Singles, and Hidden Doubles in the puzzle.
The more advanced techniques (like Naked and Hidden Doubles/Triples) required to solve the puzzle indicate a higher level of difficulty.
## 5. Conclusion
This project not only provides a solution to any given Sudoku puzzle but also offers a unique feature of difficulty rating, making it useful for users who want to understand the complexity of the puzzle. By implementing techniques commonly used in advanced Sudoku solving strategies, this project enhances the conventional backtracking solver.


