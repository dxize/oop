#include <stdio.h>
#include <iostream>
#include <string>	
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <iomanip>

double MatrixToDeterminant(std::vector<std::vector<double>>& matrix)
{
	double det = 0;
	std::vector<double> rowFirst = matrix[0];
	std::vector<double> rowSecond = matrix[1];

	if (matrix.size() == 3)
	{
		std::vector<double> rowThird = matrix[2];

		det = rowFirst[0] * rowSecond[1] * rowThird[2] + rowFirst[1] * rowSecond[2] * rowThird[0] +
			rowFirst[2] * rowSecond[0] * rowThird[1] - rowFirst[2] * rowSecond[1] * rowThird[0] -
			rowFirst[0] * rowSecond[2] * rowThird[1] - rowFirst[1] * rowSecond[0] * rowThird[2];
	}
	else //matrix.size() == 2
	{
		det = rowFirst[0] * rowSecond[1] - rowFirst[1] * rowSecond[0];
	}

	return det;
}

void ToTransposeMatrix(std::vector<std::vector<double>>& matrix,
	std::vector<std::vector<double>>& transposeMatrix)
{
	for (int i = 0; i < 3; ++i)
	{
		std::vector<double> newRow;

		newRow.push_back(matrix[0][i]);
		newRow.push_back(matrix[1][i]);
		newRow.push_back(matrix[2][i]);
		transposeMatrix.push_back(newRow);
	}
}

void ToAdjugateMatrix(std::vector<std::vector<double>>& matrix, 
	std::vector<std::vector<double>>& adjugateMatrix)
{
	std::vector<std::vector<double>> transposeMatrix;

	ToTransposeMatrix(matrix, transposeMatrix);
	for (int i = 0; i < 3; ++i)
	{
		std::vector<double> row;

		for (int j = 0; j < 3; ++j)
		{
			std::vector<std::vector<double>> minor;

			for (int x = 0; x < 3; ++x) {
				if (x == i) continue; 
				std::vector<double> newRow;
				for (int y = 0; y < 3; ++y) {
					if (y == j) continue; 
					newRow.push_back(transposeMatrix[x][y]);
				}
				minor.push_back(newRow);
			}

			double det = MatrixToDeterminant(minor);	
			double elMatrix = std::pow(-1, i + j + 2) * det;

			row.push_back(elMatrix);
		}
		adjugateMatrix.push_back(row);
	}
}

int ToInverseMatrix(std::vector<std::vector<double>>& matrix, std::vector<std::vector<double>>& inverseMatrix)
{
	double determinant = 0;
	std::vector<std::vector<double>> adjugateMatrix;

	determinant = MatrixToDeterminant(matrix);

	if (determinant != 0)
	{
		ToAdjugateMatrix(matrix, adjugateMatrix);
		for (int i = 0; i < 3; ++i)
		{
			std::vector<double> row;

			for (int j = 0; j < 3; ++j)
			{
				double result = (1 / determinant) * adjugateMatrix[i][j];

				row.push_back(result);
			}

			inverseMatrix.push_back(row);
		}

	}
	else
	{
		std::cout << "Non-invertible";
		return 1;
	}

	return 0;
}

int InitData(std::istream& input, std::vector<std::vector<double>>& matrix) 
{
	std::string line;

	while (std::getline(input, line)) 
	{
		std::istringstream iss(line);
		std::vector<double> row;
		double num;

		while (iss >> num) 
		{
			row.push_back(num);
		}

		if (!iss.eof()) 
		{
			std::cout << "Invalid matrix" << std::endl;
			matrix.clear();
			return 1;
		}

		if (row.empty()) 
		{
			std::cout << "Invalid matrix" << std::endl;
			matrix.clear();
			return 1;
		}

		if (row.size() != 3 || matrix.size() > 3)
		{
			std::cout << "Invalid matrix format" << std::endl;
			matrix.clear();
			return 1;
		}

		matrix.push_back(row);
	}

	if (matrix.empty() || matrix.size() != 3)
	{
		std::cout << "Invalid matrix format";
		return 1;
	}

	return 0;
}

int OpenFileForStream(const std::string& inputFileName, std::vector<std::vector<double>>& matrix)
{
	std::ifstream inputFile(inputFileName);
	if (!inputFile)
	{
		std::cout << "ERROR: File can not open";
		return 1;
	}

	int status = 0;
	status = InitData(inputFile, matrix);
	if (status != 0)
	{
		return 1;
	}

	return 0;
}

std::string OperatingMode(char** argv, int argc)
{
	if (argc == 2 && std::string(argv[1]) == "-h")
	{
		std::cout << "1) For manual entry, enter only the name of the executable file into the command line\n"
			<< "2) If there is a file with a pre-prepared graph, then enter the name of"
			<< "the executable file in the console and, separated by a space, the name of the file with the input data\n\n"
			<< "!!!!The coefficients of the input matrix are arranged in three elements in each row (3*3)"
			<< "and are separated by a tab character!!!!\n";
		return "manual";
	}
	else if (argc == 1)
	{
		return "console";
	}
	else if (argc == 2)
	{
		return "file";
	}
	else
	{
		return "";
	}
}

void PrintMatrix(std::vector<std::vector<double>>& inverseMatrix)
{

	std::ios::fmtflags old_flags = std::cout.flags();
	std::streamsize old_precision = std::cout.precision();

	std::cout << std::fixed << std::setprecision(3);


	for (int i = 0; i < 3; ++i)
	{
		std::vector<double> row = inverseMatrix[i];

		for (int j = 0; j < 3; ++j)
		{
			std::cout << row[j] << "\t";
		}

		std::cout << "\n";
	}

	std::cout.flags(old_flags);
	std::cout.precision(old_precision);
}

int main(int argc, char* argv[])
{
	std::string mode = OperatingMode(argv, argc);
	std::vector<std::vector<double>> matrix;
	std::vector<std::vector<double>> inverseMatrix;
	bool status = 0;
	
	if (mode == "manual")
	{
		return 0;
	}
	else if (mode == "file")
	{
		std::string inputFileName = argv[1];

		status = OpenFileForStream(inputFileName, matrix);
	}
	else if (mode == "console")
	{
		status = InitData(std::cin, matrix);
	}
	else
	{
		std::cout << "ERROR!\nEnter -h for help or check if the parameters you entered are correct.\n";
		return 1;
	}

	if (status == 0)
	{
		status = ToInverseMatrix(matrix, inverseMatrix);
	}

	if (status == 0)
	{
		PrintMatrix(inverseMatrix);
	}
	else
	{
		return 1;
	}
	
	return 0;
} //ÊÎÍÑÒÀÍÒÛ ÄËß i < 3