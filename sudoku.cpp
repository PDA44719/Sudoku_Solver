#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

// new comment
/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!\n";
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3)) {
    cout << "  +===========+===========+===========+\n";
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+\n";
  }
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|\n";
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) {
    cout << (char) ('1'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */

bool is_complete(const char board[9][9]){
	char ch;
	for (int row=0; row<9; row++){
		for (int column=0; column<9; column++){
			ch = board[row][column];
			if (ch < '1' || ch > '9'){
				return false;
			}
		}
	}
	return true;	
}

/**
 * @brief Check if a digit is already present inside a specific row or column
 * 
 * @param row_n: the index of the row to be checked  
 * @param column_n: the index of the column to be checked
 * @param digit: the char containing the digit ('1' to '9')
 * @param board: an array containing the 9x9 sudoku board 
 * @return true if the digit was not present inside the row or the column 
 * @return false if the digit was present inside either the row or the column 
 */
bool check_row_and_column(const int row_n, const int column_n, const char digit, const char board[9][9]){
	// Check all the row elements
	for (int i=0; i<9; i++){
		if (board[row_n][i] == digit){
			return false;
		}
	}
	// Check all the column elements
	for (int j=0; j<9; j++){
		if (board[j][column_n] == digit){
			return false;
		}
	}
	return true;
}

/**
 * @brief Calculate the vertical or horizontal offset of the block containing a specific
 * digit. E.g., an element on row 4 would be part of a block whose vertical offset is +3.
 * Hence, rows 0+3 to 2+3 (3-5) would be checked to determine if a move is legal
 * 
 * @param position: the index of the row or column position of a digit to be inserted
 * @return int, the block offset 
 */
int calculate_block_offset(int position){
	int offset;
	if (position<3)
		offset = 0;

	if (position>=3 && position<6)
		offset = 3;

	if (position>=6)
		offset = 6;

	return offset;
}

/**
 * @brief Check if a digit is present inside a specific 3x3 block
 * 
 * @param vertical_offset: the vertical offset of the block (example in previous function)
 * @param horizontal_offset: the horizontal offset of the block 
 * @param digit: the char containing the digit ('1' to '9')
 * @param board: an array containing the 9x9 sudoku board 
 * @return true if the digit was not present inside the block 
 * @return false if the digit was present, and hence the insertion is invalid
 */
bool check_block(const int vertical_offset, const int horizontal_offset, const char digit, const char board[9][9]){
	for (int row=0; row<3; row++){
		for (int col=0; col<3; col++){
			if (board[row+vertical_offset][col+horizontal_offset] == digit)
				return false;
		}
	}
	return true;
}

/**
 * @brief Check if a digit is already present at a specific board position. The format
 * of positions is position[0] = 'A'-'I' (row) & position[1] = '1'-'9' (column)
 * 
 * @param position: a char array indicating the position in the board 
 * @param board: an array containing the 9x9 sudoku board
 * @return true if a digit is already present at that position 
 * @return false if there is a dot (i.e., no digit) present at that position 
 */
bool number_already_present(const char position[2], const char board[9][9]){
	int row_n = position[0] - 'A';
	int column_n = position[1] - '1';

	if (board[row_n][column_n] != '.') // The cell already has a number inside
		return true;
	return false;
}

bool make_move(const char position[2], const char digit, char board[9][9]){
	int row_n, column_n, vertical_offset, horizontal_offset;
	row_n = position[0] - 'A';
	column_n = position[1] - '1';

	// If position out of bounds or number already present in the cell
	if (row_n<0 || row_n>8 || column_n<0 || column_n>8 
		|| number_already_present(position, board))
		return false;

	vertical_offset = calculate_block_offset(row_n);
	horizontal_offset = calculate_block_offset(column_n);
	
	// Place the digit if insertion is valid 
	if (check_row_and_column(row_n, column_n, digit, board)
		&& check_block(vertical_offset, horizontal_offset, digit, board)){ 
		
		board[row_n][column_n] = digit;
		return true;
	}

	return false; // Invalid insertion of the digit at that position
}

bool save_board(const char* filename, const char board[9][9]){
	ofstream os(filename);

	// Return false if file could not be opened
	if (!os){
		cout << "Failed" << endl;
		return false;
	}
	char board_row[9];
	for (int row_n=0; row_n<9; row_n++){
		strncpy(board_row, board[row_n], 9); // Copy the 9 row elements 
		os << board_row << endl;
	}
	return true;
}

/**
 * @brief Given the previous position that the find_next_digit function was checking,
 * determine the current position that the recursive function must check. The format of
 * positions is position[0] = 'A'-'I' (row) & position[1] = '1'-'9' (column)
 * 
 * @param previous_position: The position that the previous recursive call was checking 
 * @param current_position: The position that the current recursive call must check 
 * @param board: an array containing the 9x9 sudoku board 
 */
void get_current_position(char previous_position[2], char current_position[2], const char board[9][9]){
	strcpy(current_position, previous_position);
	bool empty_position_found = false;
	while (!empty_position_found){
		// Go to the next column if the end of the row has not been reached
		if (current_position[1]<'9') {
			current_position[1] += 1;
		}
		// Go to the next row after the final column has been reached
		else if (current_position[1]=='9'){
			current_position[0] += 1;
			current_position[1] = '1';
		}

		// If empty position found, exit loop
		if (!number_already_present(current_position, board))
			empty_position_found = true;
	}
}

/**
 * @brief Recursive function that will find a valid digit for a specific position and move
 * on to the next empty position, and keep repeating the process. When a valid digit is not
 * found, it goes to the previous position and tries new digits. If a valid solution cannot 
 * be found, false is the final return value of the recursive process 
 * 
 * @param previous_position: The position that the previous recursive call was checking 
 * @param board: an array containing the 9x9 sudoku board  
 * @return true if valid digits found for all empty board positions (i.e., solution found)
 * @return false if a valid digit was not found at a specific position 
 */
bool find_next_digit(char previous_position[2], char board[9][9]){
	// Keep track of the number of times the function is called when solving a board
	static int num_of_recursive_calls = 0;
	num_of_recursive_calls += 1;

	bool valid_move, solution_found;
	char current_position[] = ".."; 
	get_current_position(previous_position, current_position, board);
	int row_n = current_position[0] - 'A';
	int column_n = current_position[1] - '1';

	for (char digit='1'; digit<='9'; digit++){
		valid_move = make_move(current_position, digit, board); // Try to insert digit
		if (valid_move){
			if (is_complete(board)){ // The last move solved the board 
				cout << "Number of recursive calls: " << num_of_recursive_calls << endl;
				num_of_recursive_calls = 0; // Reset to 0 when solution found
				return true; 
			}
			else {
				// With the newly iserted digit, try to find a board solution
				solution_found = find_next_digit(current_position, board);	
				if (solution_found)
					return true; // The inserted digit led to a solution
				else {
					// Set the cell back to a dot and continue searching
					board[row_n][column_n] = '.'; 
				}
			}
		}
		
	}

	// Reset recursive calls to 0 if the board has no solution
	if (strcmp(previous_position, "A0") == 0)
		num_of_recursive_calls = 0; 
	return false; // No valid digit was found for the position
}

bool solve_board(char board[9][9]){
	char initial_position[] = "A0"; // Indicate board solving process has not started
	return find_next_digit(initial_position, board);
}
