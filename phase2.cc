#include <array>
#include <cmath>
#include <iostream>

using std::vector;

float epsilon = .1;
int ro = 1024;
int col = 1024;
int iterations = 0;

using Grid = array<array<float, ro>, col>;

void read_variables()
	{
		//get epsilon
		std::cout << "Enter epsilon:";
		std::cin >> epsilon;
		//get rows
		std::cout << "Enter number of rows:";
		std::cin >> ro;
		//get columns
		std::cout << "Enter number of columns:";
		std::cin >> col;
		//get grid
		std::cout << "Grid:";
		std::cin >> ;
	}
void print_grid(Grid * grid)
{
	std::cout << "Total Iterations:" << iterations << std::endl;
   std::cout << "Epsilon:" << epsilon << std::endl;
	std::cout << "Number of rows:" << ro << std::endl;
	std::cout << "Number of columns:" << col << std::endl;	
	for (int row=0; row<i; ++row)
	{
		for (int column=0; column < j; ++column)
		{
			std::cout << (*grid)[row][column] << " ";
		}
		std::cout << std::endl;
	}
}

void initialize(Grid * grid) 
{
	for (int column = 0; column < j; ++column) 
	{
		(*grid)[0][column] = 0;
	}

	for (int row = 1; row < i-1; ++row) 
	{
		(*grid)[row][0] = 0;
		for (int column = 1; column < j-1; ++column) 
		{
			(*grid)[row][column] = 50;
		}
		(*grid)[row][j] = 0;
	}

	for (int column = 0; column < j; ++column) {
		(*grid)[i-1][0] = 0;
	}
}


bool is_stable(Grid * grid) {
	// Loop across all the interior points
	for (int row=1; row<i-1; ++row) { //I'm trying to look at the inside points
		for (int column = 1; column < j-1; ++column) 
		{
			// check to see if the point is stable
			// if it is stable, check the next point
			// if it is not stable, return false;
			if (epsilon < std::fabs((((*grid)[row+1][column]+(*grid)[row-1][column]+(*grid)[row][column+1]+(*grid)[row][column-1])/4)-(*grid)[row][column]))
				return false;
		}
	}

	return true;
}

Grid * calculate_next(Grid *current) 
{
	Grid * next = new Grid(*current);
	
	for (int row=1; row < i-1; ++row) 
	{ 
		for (int column = 1; column < j-1; ++column) 
		{
			(*next)[row][column] = (((*current)[row+1][column]+(*current)[row-1][column]+(*current)[row][column+1]+(*current)[row][column-1])/4);
		}
	}
	// reassign values of interior squares	

	return next;
}


int main() 
	{
	read_variables();
	Grid * grid = new Grid();

	// create, initialize, and print grid
	initialize(grid);
	//print_grid(grid); //print initial grid

	
	print_grid(grid);

	while (!is_stable(grid)) 
	{
		// calculate the new values of the grid
		Grid * newgrid = calculate_next(grid);
		delete grid;
		grid = newgrid;
		++iterations;
 //if (iterations ==179)
	//	{print(grid);}
		//std::cout << "Iteration:" << iterations << std::endl;
	}

	
	return 0;
}

