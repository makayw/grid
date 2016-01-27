#include <array>
#include <cmath>
#include <iostream>


// allows me to drop std:: before array
using std::array;


using Grid = array<array<float, 1024>, 1024>;

void print(Grid * grid)
{
	for (int row=0; row<1024; ++row)
	{
		for (int column=0; column < 1024; ++column)
		{
			std::cout << (*grid)[row][column] << " ";
		}
		std::cout << std::endl;
	}
}

void initialize(Grid * grid) 
{
	for (int column = 0; column < 1024; ++column) 
	{
		(*grid)[0][column] = 0;
	}

	for (int row = 1; row < 1023; ++row) 
	{
		(*grid)[row][0] = 0;
		for (int column = 1; column < 1023; ++column) 
		{
			(*grid)[row][column] = 50;
		}
		(*grid)[row][1023] = 0;
	}

	for (int column = 0; column < 1024; ++column) {
		(*grid)[1023][0] = 0;
	}
}


bool is_stable(Grid * grid) {
	float epsilon = .1;
	// Loop across all the interior points
	for (int row=1; row<1023; ++row) { //I'm trying to look at the inside points
		for (int column = 1; column < 1023; ++column) 
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
	
	for (int row=1; row < 1023; ++row) 
	{ 
		for (int column = 1; column < 1023; ++column) 
		{
			(*next)[row][column] = (((*current)[row+1][column]+(*current)[row-1][column]+(*current)[row][column+1]+(*current)[row][column-1])/4);
		}
	}
	// reassign values of interior squares	

	return next;
}


int main() 
	{

	Grid * grid = new Grid();

	// Create and initialize 2D grids
	initialize(grid);


	int iterations = 0;
	while (!is_stable(grid)) {
		// calculate the new values of the grid
		Grid * newgrid = calculate_next(grid);
		delete grid;
		grid = newgrid;
		++iterations;
 //if (iterations ==179)
	//	{print(grid);}
		//std::cout << "Iteration:" << iterations << std::endl;
	}


	// print out the number of iterations that took
	std::cout << "Iterations:" << iterations << std::endl;

	return 0;
}

