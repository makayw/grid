#include <array>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

float epsilon = .1;
uint32_t rownum = 1024;
uint32_t colnum = 1024;
uint32_t iterations = 0;

using Grid = vector<vector<float>>;

void read_variables(Grid *grid)
	{

		//get epsilon
		std::cout << "Enter epsilon:";
		std::cin >> epsilon;

		//get rows
		std::cout << "Enter number of rows:";
		std::cin >> rownum;
		grid->resize(rownum);

		//get columns
		std::cout << "Enter number of columns:";
		std::cin.read >> colnum;
		for (uint32_t row=0; row<rownum; ++row)
		{
			(*grid)[row].resize(colnum);
		}

		//get grid
		std::cout << "Grid:";
		//Grid* grid;
		for (uint32_t row=0; row<rownum; ++row)
		{
		for (uint32_t column=0; column < colnum; ++column)
		{
		std::cin.read(reinterpret_cast<char *>(&(*grid)[row][column]), sizeof(float));
		}
		}
		}

void print_grid(Grid * grid)
{
	std::cout << "Total Iterations:" << iterations << std::endl;
   std::cout << "Epsilon:" << epsilon << std::endl;
	std::cout << "Number of rows:" << rownum << std::endl;
	std::cout << "Number of columns:" << colnum << std::endl;	
	for (uint32_t row=0; row<rownum; ++row)
	{
		for (uint32_t column=0; column < colnum; ++column)
		{
			std::cout << (*grid)[row][column] << " ";
		}
		std::cout << std::endl;
	}
}

void initialize(Grid * grid) 
{
	for (int column = 0; column < colnum; ++column) 
	{
		(*grid)[0][column] = 0;
	}

	for (int row = 1; row < rownum-1; ++row) 
	{
		(*grid)[row][0] = 0;
		for (int column = 1; column < colnum-1; ++column) 
		{
			(*grid)[row][column] = 50;
		}
		(*grid)[row][colnum] = 0;
	}

	for (int column = 0; column < colnum; ++column) {
		(*grid)[rownum-1][0] = 0;
	}
}


1bool is_stable(Grid * grid) {
	// Loop across all the interior points
	for (int row=1; row<rownum-1; ++row) { //I'm trying to look at the inside points
		for (int column = 1; column < colnum-1; ++column) 
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

Grid *fill_grid()
{
	vector (column, 0);
	
	

}
	

Grid * calculate_next(Grid *current) 
{
	Grid * next = new Grid(*current);
	
	for (int row=1; row < rownum-1; ++row) 
	{ 
		for (int column = 1; column < colnum-1; ++column) 
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
	read_variables(grid);

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

