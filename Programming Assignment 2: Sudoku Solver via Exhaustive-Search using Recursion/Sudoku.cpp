// Soduku Solver using Brute-Force Search implemted using 
// recursion.
// Written for IE523: Financial Computation by Prof. Sreenivas
// and GE523: Discrete Event Systems
//
#include <iostream>
#include "sudoku.hpp"

int main(int argc, char * const argv[])
{
	Sudoku x;
	x.read_puzzle(argc, argv);
	x.print_puzzle();
	x.Solve(0, 0);
	//x.alternate_Solve(0, 0);
	//x.print_puzzle();
	
	//Without system("pause"), the command window will close after I enter the file's path.
	system("pause");
	return 0;
}