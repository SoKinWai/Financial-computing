//This is my first assignment
//N-queens problem

#ifndef Queen
#define Queen
#include <iostream>
#include <cmath>
#include <stdbool.h>
#include<vector>
using namespace std;

class Board
{
private:
	// private data member: size of the chessboard
		int size;
	
	//This is a global variable to calculate how many solutions
	int number = 0;
	
	//Actually I am not good at using pointer, so after I googled that, I chose to use vector to vector to solve this problem
	//Here are the links I got form Google: https://www.geeksforgeeks.org/printing-solutions-n-queen-problem/
	//https://stackoverflow.com/questions/11289770/n-queens-in-c-using-vectors
	//https://www.youtube.com/watch?v=pAKZp_EucVg&feature=youtu.be
	
	//Construct an empty chessboard here
	//0 means there is no queen on the chessboard
	// private member function
		vector<vector<int>> Empty_board(int size)
		{
			vector<vector<int>> board(size, vector<int>(size, 0));
			cout << "The empty board is: " << endl;
			
			int a = 0, b = 0;
			
			for (a = 0; a < size; a++)
			{
				for (b = 0;b < size; b++)
				{
					cout << board[a][b] << ' ';
				}
				cout << endl;
			}

			return board;
		}
	
		// private member function:  returns 'false' if
		// the (row, col) position is not safe.
		// Construct  function: bool is_this_position_safe
		// "true" if the (row,col) position is safe.  If it is
		// unsafe (i.e. some other queen can threaten this position)
		// return "false"

		/* A utility function to check if a queen can
		be placed on board[row][col]. Note that this
		function is called when "col" queens are
		already placed in columns from 0 to col -1.
		So we need to check only left side for
		attacking queens */
		bool is_this_position_safe(vector<vector<int>> board, int row, int col, int size)
		{
			int a, b;

			/*Check this row of the left side*/
			for (a = 0; a<col; a++)
			{
				if (board[row][a] == 1)
				{
					return false;
				}
			}

			/* Check upper diagonal on left side */
			for (a = row, b = col; a >= 0 && b >= 0; a--, b--)
			{
				if (board[a][b] == 1)
					return false;
			}

			/* Check lower diagonal on left side */
			for (a = row, b = col; b >= 0 && a < size; a++, b--)
			{
				if (board[a][b] == 1)
					return false;
			}

			return true;

		}

		
		/* A utility function to print solution */
		// private member function: prints the board position
		void print_board(vector<vector<int>> board, int size)
		{
			number++;
			cout << "The board " << number << " is:" << endl;
			
			int a = 0, b = 0;

			for (a = 0; a < size; a++)
			{
				for (b = 0;b < size;b++)
				{
					cout << board[a][b];
				}

				cout << endl;
			}

			cout << endl;
		}

		
		// private member function: recursive backtracking
		/* A recursive utility function to solve N
		Queen problem */
		bool solve(vector<vector<int>> board, int col, int size)
		{
			/* base case: If all queens are placed
			then return true */
			if (col == size)
			{
				print_board(board, size);
				return true;
			}

			int a = 0;

			for (a = 0;a < size;a++)
			{

				if (is_this_position_safe(board, a, col, size))
				{
					board[a][col] = 1;
					
					//
					//
					bool Next_path=solve(board, col + 1, size);

					if (!Next_path)
					{
						board[a][col] = 0;
					}
				}

			}
			
			//It has to return false, because it still needs to test the rest of solutions
			return false; 
		}
			


public:
	// Solves the n-Queens problem by (recursive) backtracking
	void nQueens(int size)
	{
		//Let's construct an empty chessboard with size x size here
		//Use the Empty_board from above to initialize 
		vector<vector<int>> board= Empty_board(size);
		cout << endl << endl << "These are solutions: " << endl<< endl;

		//Use the recursive function from above to find how many ways to solve n queens problem
		//Insert the previous empty to the recursive function
		//Show what situations there are no ways to solve n queens problem.
		if (!solve(board,0,size) && number == 0)
		{
			cout << "There is no solution for " <<size<< " queens"<< endl << endl;
		}
		else
		{
			cout << size << " queens problem has " << number << " ways to solve." << endl;
		}
	}



};

#endif