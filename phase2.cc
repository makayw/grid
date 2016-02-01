#include <array>
#include <cmath>
#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

float epsilon = 0;
uint32_t rownum = 0;
uint32_t colnum = 0;
uint32_t iterations = 0;

using Grid = vector<vector<float>>;

void read_variables(Grid *grid)
{

		//get iteration number
		std::cin.read(reinterpret_cast<char *>(&iterations), sizeof(uint32_t));
		//get epsilon
		std::cin.read(reinterpret_cast<char *>(&epsilon), sizeof(float));

		//get rows
		std::cin.read(reinterpret_cast<char *>(&rownum), sizeof(uint32_t));
		grid->resize(rownum);

		//get columns
		std::cin.read(reinterpret_cast<char *>(&colnum), sizeof(uint32_t));
		for (uint32_t row=0; row<rownum; ++row)
		{
			(*grid)[row].resize(colnum);
		}

		//get grid
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
	std::cout.write(reinterpret_cast<char const*>(&iterations), sizeof(uint32_t));;
   std::cout.write(reinterpret_cast<char const*>(&epsilon), sizeof(float));
	std::cout.write(reinterpret_cast<char const*>(&rownum), sizeof(uint32_t));
	std::cout.write(reinterpret_cast<char const*>(&colnum), sizeof(uint32_t));	
	for (uint32_t row=0; row<rownum; ++row)
	{
		for (uint32_t column=0; column < colnum; ++column)
		{
			std::cout.write(reinterpret_cast<char *>(&(*grid)[row][column]), sizeof(float));
		}
	}
}

void initialize(Grid * grid) 
{
	for (uint32_t column = 0; column < colnum; ++column) 
	{
		(*grid)[0][column] = 0;
	}

	for (uint32_t row = 1; row < rownum-1; ++row) 
	{
		(*grid)[row][0] = 0;
		for (uint32_t column = 1; column < colnum-1; ++column) 
		{
			(*grid)[row][column] = 50;
		}
		(*grid)[row][colnum] = 0;
	}

	for (uint32_t column = 0; column < colnum; ++column) {
		(*grid)[rownum-1][0] = 0;
	}
}


bool is_stable(Grid * grid) {
	// Loop across all the interior points
	for (uint32_t row=1; row<rownum-1; ++row) { //I'm trying to look at the inside points
		for (uint32_t column = 1; column < colnum-1; ++column) 
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
	
	for (uint32_t row=1; row < rownum-1; ++row) 
	{ 
		for (uint32_t column = 1; column < colnum-1; ++column) 
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
	//initialize(grid);
	//print_grid(grid); //print initial grid

	

	while (!is_stable(grid)) 
	{
		// calculate the new values of the grid
		Grid * newgrid = calculate_next(grid);
		delete grid;
		grid = newgrid;
		++iterations;
	}
	{iterations+1;}
	print_grid(grid);
	
	return 0;
}

