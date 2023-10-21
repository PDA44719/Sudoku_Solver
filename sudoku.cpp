#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

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

/* function that checks if all the board positions are occupied by 1-9 digits */
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
/* end of function is_complete */

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

bool check_block(const int row_offset, const int column_offset, const char digit, const char board[9][9]){
	for (int m=0; m<3; m++){
		for (int n=0; n<3; n++){
			if (board[m+row_offset][n+column_offset] == digit)
				return false;
		}
	}
	return true;
}

bool make_move(const char position[2], const char digit, char board[9][9]){
	int row_n, column_n, row_offset, column_offset;
	row_n = position[0] - 'A';
	column_n = position[1] - '1';

	// out out bounds
	if (row_n<0 || row_n>8 || column_n<0 || column_n>8){
		return false;
	}

	row_offset = calculate_block_offset(row_n);
	column_offset = calculate_block_offset(column_n);
	
	// Insert the digit if insertion is valid and return true, otherwise return false
	if (check_row_and_column(row_n, column_n, digit, board) && check_block(row_offset, column_offset, digit, board)){ 
		board[row_n][column_n] = digit;
		return true;
	}

	return false; // Inserting the digit at that position was invalid
}
