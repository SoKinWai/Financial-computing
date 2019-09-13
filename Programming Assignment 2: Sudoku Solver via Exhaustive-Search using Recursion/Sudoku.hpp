/*
*  sudoku.hpp
*  Sudoku
*  Created by Jianwei Su
*  This is my second homework
*/

//Here are the links I googled for this homework:
//https://stackoverflow.com/questions/843083/open-file-by-its-full-path-in-c
//https://www.sanfoundry.com/cpp-program-solve-sudoku-problem-backtracking/
//https://www.geeksforgeeks.org/sudoku-backtracking-7/
//https://www.youtube.com/watch?v=soZpO1kNC8Q
//http://www.cplusplus.com/reference/fstream/ifstream/
//https://mathbits.com/MathBits/CompSci/Files/End.htm
//https://stackoverflow.com/questions/26720064/how-can-i-transfer-a-text-file-to-array-2d-in-c
//https://stackoverflow.com/questions/1107705/systempause-why-is-it-wrong

#ifndef sudoku
#define sudoku

#include <vector>
#include <fstream>
#include<cmath>
#include<string>
#include<iostream>
using std::vector;
using namespace std;
class Sudoku
{
private:
	
	// Private
	int puzzle[9][9];
	
	//This is a global variable to calculate how many solutions
	int number = 0;
	
	/* Find row, col of an unassigned cell
  If there is none, return true
  For digits from 1 to 9
    a) If there is no conflict for digit at row, col
        assign digit to row, col and recursively try fill in rest of puzzle
    b) If recursion successful, return true
    c) Else, remove digit and try another
  If all digits have been tried and nothing worked, return false*/
	
  // Private member function that checks if the named row is valid
  // check validity of "row" 
  //1<=k<=9
	bool row_valid(int row, int k)
	{
		int a;

		for (a = 0;a < 9;a++)
		{
			if (puzzle[row][a] == k)
			{
				return false;
			}
		}

		return true;
	}

	// Private member function that checks if the named column is valid
	// check validity of "col" 
	bool col_valid(int col, int k)
	{
		int b;
		
		for (b = 0;b < 9;b++)
		{
			if (puzzle[b][col] == k)
			{
				return false;
			}
		}
	
		return true;
	}

	/*There are 9 blocks, so we have to find a way to make sure any small box will return to the beginning of the block.
	Then we can go over the whole block(9 small boxes) and check if there exists duplicate numbers. In order to do this, we use mod.
	For example row=2, col=5. 2-2 mod 3=0. 5-5 mod 3=3. (0, 3) is the beginning of this block, so we will use this way to make sure 
	it will go back to the beginning and check these 9 small boxes.*/
	
	// Private member function that checks if the named 3x3 block is valid
	// check 3 x 3 block validity 
	bool block_valid(int row, int col, int k)
	{
		//Let row and col go back to the beginning of the block.
		int a = row - (row % 3);

		int b = col - (col % 3);
		
		int c, d;

		//Then we can use for loop to check all 9 small boxes.
		for (c = a;c < (a + 3);c++)
		{
			for (d = b;d < (b + 3);d++)
			{
				if (puzzle[c][d]==k)
				{
					return false;
				}
			}
		}
		return true;
	}

public:
	// we are not doing any checks on the input puzzle -- that is,
	// we are assuming they are indeed valid

	// Public member function that reads the incomplete puzzle
	void read_puzzle(int argc, char * const argv[])
	{
		string input_file; //Use the samples from compass

		cout << "Please enter the entire location path for the input file: " << endl;

		//Notice that we have to enter the entire location path for the input file

		cin >> input_file;
	
		//ifstream function is to read those data from the sample file
		ifstream in_file(input_file);
	
		if (in_file.is_open())
		{
			//eof() means the end of the file
			while (!in_file.eof())
			{
				for (int a = 0;a < 9;a++)
				{
					for (int b = 0;b < 9;b++)
					{
						//Transfer a text file to array 2D 
						in_file >> puzzle[a][b];
					}
				}
			}
		}
		else
		{
			cout << "File is not existed. " << endl;
		}
	
	}

	// Public member function that prints the puzzle when called
	void print_puzzle()
	{
		if (number != 0)
		{
			cout << endl << "Solution " << number<<":";
		}

		cout << endl << "Board Position" << endl;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				// check if we have a legitimate integer between 1 and 9
				if ((puzzle[i][j] >= 1) && (puzzle[i][j] <= 9))
				{
					// printing initial value of the puzzle with some formatting
					cout << puzzle[i][j] << " ";
				}
				else {
					// printing initial value of the puzzle with some formatting
					cout << "X ";
				}
			}
			cout << endl;
		}
	}

	// Public member function that (recursively) implements the brute-force 
	// search for possible solutions to the incomplete Sudoku puzzle
	// this part of the code identifies the row and col number of the 
	// first incomplete (i.e. 0) entry in the puzzle.  If the puzzle has
	// no zeros, the variable row will be 9 => the puzzle is done, as 
	// each entry is row-, col- and block-valid...
	bool Solve(int row, int col)
	{
		//I use an integer a to demonstrate 2 situations, when a is 0, we can print puzzle and number of solution
		//when a is 1, we should use recursive to fill 0s and test them.
		int a = 0;

		int b;
		int c;
		for (b = 0;b < 9;b++)
		{
			for (c = 0;c<9;c++)
			{
				if (puzzle[b][c] == 0)
				{
					row = b;
					col = c;
					a = 1;
				}

			}

		}

		if (a == 1)
		{
			int d;
			
			// check if we have a legitimate integer between 1 and 9
			for (d = 1;d < 10;d++)
			{
				if ((row_valid(row, d) == true) && (col_valid(col, d) == true) && (block_valid(row, col, d) == true))
				{
					puzzle[row][col] = d;
					
					//Use recursive method here
					if (Solve(row, col))
					{
						return true;
					}
					else
					{
						puzzle[row][col] = 0;
					}
				}




			}
		}
		
		if (a == 0)
		{
			//Count how many solutuons
			number++;
			
			//Print the puzzle
			print_puzzle();
		
			
		}

		//It has to return false, because it still needs to test the rest of solutions
		return false;
	
	}
};
#endif