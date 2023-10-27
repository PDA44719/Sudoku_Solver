#ifndef SUDOKU_H
#define SUDOKU_H

void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);

/**
 * @brief Check if all the board cells are occupied by 1-9 digits
 * 
 * @param board: an array containing the 9x9 sudoku board
 * @return true if all cells contain digits
 * @return false if there are some empty cells
 */
bool is_complete(const char board[9][9]);

/**
 * @brief Attempt to insert a digit at a specific position in the board
 * 
 * @param position: a char array indicating the position in the board.
 * @param digit: the char containing the digit ('1' to '9')
 * @param board: an array containing the 9x9 sudoku board
 * @return true and insert the digit if the insertion is valid
 * @return false if the attempted move is invalid
 */
bool make_move(const char position[2], const char digit, char board[9][9]);

/**
 * @brief Store the sudoku board in a .dat file
 * 
 * @param filename: the name of the file where the board will be stored
 * @param board: an array containing the 9x9 sudoku board
 * @return true if the board was properly saved in the file
 * @return false if an error occurred during the saving process
 */
bool save_board(char* filename, const char board[9][9]);

/**
 * @brief Find a valid board solution, if possible
 * 
 * @param board: an array containing the 9x9 sudoku board
 * @return true if a solution was reached
 * @return false if a board solution could not be found
 */
bool solve_board(char board[9][9]);

#endif
