#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>


inline void Bin(std::vector<short>& b, int numberDec);

class linear_subspace
{
private:

	std::vector<std::vector<short>> subspace;

	int rows, columns;

public:

	linear_subspace() : rows{ 0 }, columns{ 0 }, subspace{ 0 } {}

	linear_subspace(std::ifstream& in) : linear_subspace() { read(in); }

	void read(std::ifstream&);													//reads from file and writes data to class field

	int getRows() const { return rows; }

	int getColumns() const { return columns; }

	void spec_weight(std::fstream&);

};


void linear_subspace::read(std::ifstream& in)
{

	int k = 0;

	while (!in.is_open())																		//file open check
	{
		std::cout << "\nfile open error. Please check the path to the file and re-enter it: ";
		std::string path;
		getline(std::cin, path);
		in.open("path");
	}


	std::string buffer, vectors;

	while (std::getline(in, buffer) && buffer.size() > 1)    //read from file to string variable
	{

		for (size_t i = 0; i < buffer.size(); i++)
			if (buffer[i] == ' ')
			{
				buffer.erase(i, 1);
				--i;
			}



		vectors += buffer + '\n';

		++rows;

	}

	columns = (vectors.size() - 1) / rows;


	in.clear();


	subspace.resize(rows);

	for (size_t i = 0; i < rows; i++)         //type conversion
	{
		subspace[i].resize(columns, 0);

		for (size_t j = 0; j < columns; j++)
		{
			subspace[i][j] = (short)vectors[k] - 48;
			++k;
		}
		++k;

	}
	k = 0;

}


void linear_subspace::spec_weight(std::fstream& out)
{
	uint64_t linear_combinations = pow(2, rows);     int weight_lenght = columns + 1;

	std::vector<std::vector<unsigned int>> weight(weight_lenght);

	for (size_t i = 0; i < weight_lenght; i++)
	{
		weight[i].resize(2);
		weight[i][0] = i;
	}


	std::vector<short> b(rows, 0);
	std::vector<short> buffer(columns, 0);
	int count = 0;

	for (uint64_t k = 0; k < linear_combinations; k++)
	{
		Bin(b, k);
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < columns; j++)
			{
				buffer[j] += b[i] * subspace[i][j];
				buffer[j] %= 2;
			}
		}

		for (size_t i = 0; i < columns; i++)
		{
			count += buffer[i];
		}

		weight[count][1]++;
		count = 0;

		for (size_t i = 0; i < columns; i++)
		{
			buffer[i] = 0;
		}
	}



	for (size_t i = 0; i < weight_lenght; i++)
	{
		out << weight[i][0] << '\t' << weight[i][1] << '\n';
	}

	out.clear();

}



inline void Bin(std::vector<short>& b, int numberDec)
{
	int rows = b.size(), i = 0;
	std::vector<short> bcopy(rows, 0);

	while (numberDec != 0)
	{
		bcopy[i] = numberDec % 2;
		numberDec /= 2;
		i++;
	}

	for (size_t i = 0; i < rows; i++)
	{
		b[i] = bcopy[rows - 1 - i];
	}
}
