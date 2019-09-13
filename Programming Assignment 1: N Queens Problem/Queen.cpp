// N Queens Problem via (Backtracking, which is implemented by) Recursion 
// Written by Jianwei Su for IE523: Financial Computing

#include <iostream>
#include "Queen.hpp"
using namespace std;

int main()
{
	Board X;

	//Chessboard's size
	int board_size;
	
	cout << "Please enter an integer for chessboard's size: " << endl;

	//Ask User to enter an integer for chessboard's size
	cin >> board_size;

	X.nQueens(board_size);

	return 0;
	
}