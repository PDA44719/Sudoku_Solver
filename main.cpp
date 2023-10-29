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
  cout << "a valid move.\n";

  // Should be invalid insertion because the position is out of bounds
  cout << "Putting '5' into C0 is ";
  if (!make_move("C0", '5', board)) {
    cout << "NOT ";
  }
  cout << "a valid move.\n";

  // Should be invalid because the digit is already present in the block
  cout << "Putting '9' into F5 is ";
  if (!make_move("F5", '9', board)) {
    cout << "NOT ";
  }
  cout << "a valid move.\n";

  // Should be invalid because the digit is already present in the column
  cout << "Putting '8' into G3 is ";
  if (!make_move("G3", '8', board)) {
    cout << "NOT ";
  }
  cout << "a valid move.\n";

  // Should be invalid because there is a digit already present at that position 
  cout << "Putting '7' into E8 is ";
  if (!make_move("E8", '7', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n";
  display_board(board);

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
  save_board("medium-solution.dat", board);

  // write more tests
  load_board("mystery1.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery1' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';
  save_board("mystery1-solution.dat", board);

  load_board("mystery2.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery2' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
    // Display board to make sure it is the same is the original
    display_board(board); 
  }
  cout << '\n';
  save_board("mystery2-solution.dat", board);

  load_board("mystery3.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery3' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';
  save_board("mystery3-solution.dat", board);

  cout << "=================== Question 5 ===================\n\n";

  /*
  In this section, the time it took to solve 'mystery1' and 'mystery3' will be
  computed. Furthermore, as the solve_board function has been programmed to calculate
  the number of recursive calls, this information will also be displayed (it can also
  be seen in the Question 4 section)
  */
  
  load_board("mystery1.dat", board);
  auto start = chrono::high_resolution_clock::now();
  solve_board(board);
	auto stop = chrono::high_resolution_clock::now();
  auto time_difference = chrono::duration_cast<chrono::milliseconds>(stop-start).count();  
  cout << "The 'mystery1' solution was found in " << time_difference << " ms." << endl;
	
  load_board("mystery3.dat", board);
  start = chrono::high_resolution_clock::now();
  solve_board(board); 
  stop = chrono::high_resolution_clock::now();
  time_difference = chrono::duration_cast<chrono::milliseconds>(stop-start).count(); 
  cout << "The 'mystery3' solution was found in " << time_difference << " ms." << endl;

  return 0; 
} 
