#include <iostream>
//#include<time>
#include<chrono>
#include <cstdio>
#include "sudoku.h"

using namespace std;

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============\n\n";

  cout << "Calling load_board():\n";
  load_board("easy.dat", board);

  cout << '\n';
	cout << "Displaying Sudoku board with display_board():\n";
  display_board(board);
  cout << "Done!\n\n";

  cout << "=================== Question 1 ===================\n\n";

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  cout << "=================== Question 2 ===================\n\n";

  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);

  // write more tests

  cout << "=================== Question 3 ===================\n\n";

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board)) {
    cout << "Save board to 'easy-copy.dat' successful.\n";
  } else {
    cout << "Save board failed.\n";
  }
  cout << '\n';

  cout << "=================== Question 4 ===================\n\n";

  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  // write more tests

  cout << "=================== Question 5 ===================\n\n";

  // write more tests
  

  load_board("mystery1.dat", board);
  auto stop = chrono::high_resolution_clock::now();
  auto start = chrono::high_resolution_clock::now();
  if (solve_board(board)) {
	stop = chrono::high_resolution_clock::now();
    cout << "The 'myster1' board has a solution:\n";
    display_board(board);
	cout << "The time it took to get this solution was: " << chrono::duration_cast<chrono::microseconds>(stop-start).count() << " microseconds." << endl;
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';
	
  load_board("mystery2.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery2' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  auto stop2 = chrono::high_resolution_clock::now();
  auto start2 = chrono::high_resolution_clock::now();
  load_board("mystery3.dat", board);
  if (solve_board(board)) {
    stop2 = chrono::high_resolution_clock::now();
    cout << "The 'mystery3' board has a solution:\n";
    display_board(board);
	cout << "The time it took to get this solution was: " << chrono::duration_cast<chrono::microseconds>(stop2-start2).count() << " microseconds." << endl;
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';
  cout << "Mystery1 board was solved x" << chrono::duration_cast<chrono::microseconds>(stop-start).count() / chrono::duration_cast<chrono::microseconds>(stop2-start2).count() << " times slower than Mystery3 board." << endl;

  return 0; 
} 
