// GE523: Discrete Event Systems
// IE511: Integer Programming
// IE523: Financial Computing
//
// A Sudoku Solver in C++ written by Jianwei Su
//Hints by Prof. R.S. Sreenivas
// This is written in a "C" like syntax.  You can think about how to
// put this into an include file etc on your own.
//
// There is an ILP formulation for any 9 x 9 Sudoku Puzzle
// See the handout for the formulation -- there are 729 variables
// with a whole lot of constraints that is driven by the input
// (which is the incomplete board-layout).  You can write this
// (moderate-size) ILP automatically in C++, which is then solved
// using the API for Lpsolve.

//The links I used to solve this problem:
//http://lp-solve.2324885.n4.nabble.com/Successful-Sudoku-Solver-td8059.html
//http://lpsolve.sourceforge.net/5.5/


#define WIN32
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>

#include "lp_lib.h"

using namespace std;

// Global variables for the problem 9*9*9 = 729
// See my handout for further explanations
lprec* lp;
double solution[729];

// This sets the generic ILP for the Sudoku Puzzle
// It does not use any of the pre-determined board-positions,
// that part is done after the input file is read.
void set_sudoku_ilp()
{
	// setting the problem up: 9*9*9 = 729 variables
	lp = make_lp(0, 729);

	// This keeps the message reporting of lp_solve to a minimum
	set_verbose(lp, 3);

	{
		for (int i = 1; i <= 9; i++)
		{
			for (int j = 1; j <= 9; j++)
			{
				// constraint that says each (i,j) entry in the 9x9 table
				// should have one number in it
				// creating a row with 1's at the right spot (the first
				// entry has to be a zero; this is idiosynchratic of lpsolve)

				double row[730];
				
				//in that array, everything is filled as 0s
				for (int a = 0; a < 730;a++)
					row[a] = 0;

				//1 is being added to the each space ( i.e. each of 729)
				for (int k = 1; k <= 9; k++)
					row[(81 * (i - 1)) + (9 * (j - 1)) + k] = 1;

				//1 is added if a number is put ( from 1 to 9) and if constraints are satisfied
				// adding the constraint
				add_constraint(lp, row, EQ, 1);
			}
		}
	}
	// Using the above code as a guide, put the appropriate lines that
	// articulate the constraint that says each number must appear once
	// in each row in the 9x9 table; create a bunch of rows with 1's at
	// the right spot (the first entry has to be a zero; this is
	// idiosynchratic of lpsolve)
	//Row
	for (int i = 1; i <= 9; i++)
	{
		for (int k = 1; k <= 9; k++)
		{
			double row[730];
			for (int a = 0; a < 730; a++)
				row[a] = 0;

			for (int j = 1; j <= 9; j++)
				row[(81 * (i - 1)) + (9 * (j - 1)) + k] = 1;

			// adding the constraint
			add_constraint(lp, row, EQ, 1);
		}
	}

	// Using the above code as a guide, put the appropriate lines that
		// articulate the constraint that says each number must appear once
		// in each column in the 9x9 table; create a bunch of rows with 1's at
		// the right spot (the first entry has to be a zero; this is
		// idiosynchratic of lpsolve)
	//Column
	for (int j = 1; j <= 9; j++)
	{
		for (int k = 1; k <= 9; k++)
		{
			double row[730];
			for (int a = 0; a < 730; a++)
			{
				row[a] = 0;
			}

			for (int i = 1; i <= 9; i++)
			{
				row[(81 * (i - 1)) + (9 * (j - 1)) + k] = 1;
			}

			// adding the constraint
			add_constraint(lp, row, EQ, 1);
		}
	}

	// making sure each number occurs once within each block
	  // Using the above code as a guide, put the appropriate lines that
			// articulate theconstraint that says each number must appear once
			// in each 3 x 3 block; create a bunch of rows with 1's at the right
			// spot (the first entry has to be a zero; this is idiosynchratic of
			// lpsolve)
		// Block 1
	{
		for (int k = 1; k <= 9; k++)
		{
			double row[730];
			for (int a = 0; a < 730; a++)
				row[a] = 0;

			for (int i = 1; i <= 3; i++)
			{
				for (int j = 1; j <= 3; j++)
				{
					row[(81 * (i - 1)) + (9 * (j - 1)) + k] = 1;
				}
			}
			add_constraint(lp, row, EQ, 1);
		}
	}

	// Block 2
	{
		for (int k = 1; k <= 9; k++)
		{
			
			double row[730];
			for (int a = 0; a < 730; a++)
				row[a] = 0;

			for (int i = 1; i <= 3; i++)
			{
				for (int j = 4; j <= 6; j++)
				{
					row[(81 * (i - 1)) + (9 * (j - 1)) + k] = 1;
				}
			}
			add_constraint(lp, row, EQ, 1);
		}
	}

	// Block 3
	{
		for (int k = 1; k <= 9; k++)
		{
			
			double row[730];
			for (int a = 0; a < 730; a++)
				row[a] = 0;

			for (int i = 1; i <= 3; i++)
			{
				for (int j = 7; j <= 9; j++)
				{
					row[(81 * (i - 1)) + (9 * (j - 1)) + k] = 1;
				}
			}
			add_constraint(lp, row, EQ, 1);
		}
	}

	// Block 4
	{
		for (int k = 1; k <= 9; k++)
		{
			
			double row[730];
			for (int a = 0; a < 730; a++)
				row[a] = 0;

			for (int i = 4; i <= 6; i++)
			{
				for (int j = 1; j <= 3; j++)
				{
					row[(81 * (i - 1)) + (9 * (j - 1)) + k] = 1;
				}
			}
			add_constraint(lp, row, EQ, 1);

		}
	}

	// Block 5
	{
		for (int k = 1; k <= 9; k++)
		{
		
			double row[730];
			for (int a = 0; a < 730; a++)
				row[a] = 0;

			for (int i = 4; i <= 6; i++)
			{
				for (int j = 4; j <= 6; j++)
				{
					row[(81 * (i - 1)) + (9 * (j - 1)) + k] = 1;
				}
			}
			add_constraint(lp, row, EQ, 1);
		}
	}

	// Block 6
	{
		for (int k = 1; k <= 9; k++)
		{
			
			double row[730];
			for (int a = 0; a < 730; a++)
				row[a] = 0;

			for (int i = 4; i <= 6; i++)
			{
				for (int j = 7; j <= 9; j++)
				{
					row[(81 * (i - 1)) + (9 * (j - 1)) + k] = 1;
				}
			}
			add_constraint(lp, row, EQ, 1);
		}
	}

	// Block 7
	{
		for (int k = 1; k <= 9; k++)
		{
			double row[730];
			for (int a = 0; a < 730; a++)
				row[a] = 0;

			for (int i = 7; i <= 9; i++)
			{
				for (int j = 1; j <= 3; j++)
				{
					row[(81 * (i - 1)) + (9 * (j - 1)) + k] = 1;
				}
			}
			add_constraint(lp, row, EQ, 1);

		}
	}

	// Block 8
	{
		for (int k = 1; k <= 9; k++)
		{
			
			double row[730];
			for (int a = 0; a < 730; a++)
				row[a] = 0;

			for (int i = 7; i <= 9; i++)
			{
				for (int j = 4; j <= 6; j++)
				{
					row[(81 * (i - 1)) + (9 * (j - 1)) + k] = 1;
				}
			}
			add_constraint(lp, row, EQ, 1);
		}
	}

	// Block 9
	{
		for (int k = 1; k <= 9; k++)
		{
			
			double row[730];
			for (int a = 0; a < 730; a++)
				row[a] = 0;

			for (int i = 7; i <= 9; i++)
			{
				for (int j = 7; j <= 9; j++)
				{
					row[(81 * (i - 1)) + (9 * (j - 1)) + k] = 1;
				}
			}
			add_constraint(lp, row, EQ, 1);
		}
	}

	// upper-bound each variable by 1
	for (int i = 1; i <= 729; i++)
	{
		double row[730];
		for (int j = 0; j < 730; j++)
			row[j] = 0;
		row[i] = 1;
		add_constraint(lp, row, LE, 1);
	}

	// it does not matter what the objective function (why?)
	// I am minimizing the sum of all variables.
	{
		double row[730];
		for (int i = 1; i < 730; i++)
			row[i] = 1;
		row[0] = 0;

		set_obj_fn(lp, row);
	}

	// set the variables to be integers
	for (int i = 1; i <= 729; i++)
		set_int(lp, i, TRUE);
}

// This subroutine reads the incomplete board-information from the
// input file and sets the appropriate constraints before the ILP
// is solved.

void read_input_data(char* argv[])
{
	// reading the input filename from commandline
	ifstream input_filename(argv[1]);

	if (input_filename.is_open()) {

		cout << "Input File Name: " << argv[1] << endl;
		cout << endl << "Initial Board Position" << endl;
		for (int i = 1; i <= 9; i++)
		{
			for (int j = 1; j <= 9; j++)
			{
				int value_just_read;
				input_filename >> value_just_read;

				// check if we have a legitimate integer between 1 and 9
				if ((value_just_read >= 1) && (value_just_read <= 9))
				{
					// printing initial value of the puzzle with some formatting
					cout << value_just_read << " ";

					// add appropriate constraints that bind the value of the
					// appropriate variables based on the incomplete information
					// that was read from the input file

					cout << value_just_read << " ";
					double row[730];
					for (int a = 0; a < 730; a++)
						row[a] = 0;
					row[(81 * (i - 1)) + (9 * (j - 1)) + value_just_read] = 1;

					add_constraint(lp, row, EQ, 1);

				}
				else {
					// printing initial value of the puzzle with some formatting
					cout << "X ";
				}

			}
			cout << endl;
		}
	}
	else {
		cout << "Input file missing" << endl;
		exit(0);
	}
}

// The ILP formulation is solved using the API for Lpsolve
// Pay attention to how the solution is interpretted...

//Actually I didn't know how to solve this part perfectly. I asked my classmates to help me this part.

void solve_the_puzzle()
{
	int ret;
	// solve the lp
	ret = solve(lp);
	
	//To show how many solutions
	int solutions = 0;

	// Check if you had a solution 
	// (see online guide for the codes at http://lpsolve.sourceforge.net/5.0/ )
	while (ret == 0)
	{
		// Optimal assignment
		get_variables(lp, solution);
		//Set an empty array
		double row[730];
		for (int a = 0; a < 730; a++)
		{
			row[a] = 0;
		}
		//the number of solutions
		solutions++;
		// print the solution
		cout << endl << "Solution " << solutions << endl;
		{
			// Figure out a way to look at the 729-long 0/1 vector solution
			// to the ILP and print the appropriate integer value to be
			// inserted into each square of the solution to the Sudoku puzzle
			for (int i = 1; i <= 9; i++)
			{
				for (int j = 1; j <= 9; j++)
				{
					for (int k = 1; k <= 9; k++)
					{
						if (solution[(81 * (i - 1)) + (9 * (j - 1)) + k - 1] == 1)
						{
							cout << k << " ";
							row[(81 * (i - 1)) + (9 * (j - 1)) + k] = 1;
						}
					}
				}
				cout << endl;
			}
			
			//Use recursive method here.
			add_constraint(lp, row, LE, 80);
			ret = solve(lp);
		}
	}
	if (solutions == 0)
	{
		cout << "Check the input file... looks like there is no solution" << endl;
	}
	delete_lp(lp);;
}

int main(int argc, char* argv[])
{
	// formulate the non-input related part of the puzzle
	set_sudoku_ilp();

	// read the incomplete input information, and set appropriate constraints
	read_input_data(argv);

	// solve the puzzle and print the solution
	solve_the_puzzle();

	return(0);
}