#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <string>

const int TASK_PRECISION = 3;

struct Args
{
	std::string matrixFileName;
};
double** CreateDynamicMatrix(int n)
{
	double** dynamicMatrix = new double*[n];
	for (int i = 0; i < n; i++)
	{
		dynamicMatrix[i] = new double[n];
	}
	return dynamicMatrix;
}

void CleanDynamicMatrix(double** matrix, int n)
{
	for (int i = 0; i < n; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

double FindTripleMatrixDeterminant(double** matrix)
{
	double determinant = (((matrix[0][0] * matrix[1][1] * matrix[2][2]) + (matrix[0][2] * matrix[1][0] * matrix[2][1]) + (matrix[0][1] * matrix[1][2] * matrix[2][0])) - ((matrix[0][2] * matrix[1][1] * matrix[2][0]) + (matrix[0][1] * matrix[1][0] * matrix[2][2]) + (matrix[0][0] * matrix[1][2] * matrix[2][1])));
	return determinant;
}

double FindDoubleMatrixDeterminant(double** matrix)
{
	double determinant = ((matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]));
	return determinant;
}

void fillDoubleMinor(int i, int j, double** minor, double** matrix)
{
	if (i == 0 && j == 0)
	{
		minor[0][0] = matrix[1][1];
		minor[0][1] = matrix[1][2];
		minor[1][0] = matrix[2][1];
		minor[1][1] = matrix[2][2];
	}
	if (i == 0 && j == 1)
	{
		minor[0][0] = matrix[1][0];
		minor[0][1] = matrix[1][2];
		minor[1][0] = matrix[2][0];
		minor[1][1] = matrix[2][2];
	}
	if (i == 0 && j == 2)
	{
		minor[0][0] = matrix[1][0];
		minor[0][1] = matrix[1][1];
		minor[1][0] = matrix[2][0];
		minor[1][1] = matrix[2][1];
	}
	//
	if (i == 1 && j == 0)
	{
		minor[0][0] = matrix[0][1];
		minor[0][1] = matrix[0][2];
		minor[1][0] = matrix[2][1];
		minor[1][1] = matrix[2][2];
	}
	if (i == 1 && j == 1)
	{
		minor[0][0] = matrix[0][0];
		minor[0][1] = matrix[0][2];
		minor[1][0] = matrix[2][0];
		minor[1][1] = matrix[2][2];
	}
	if (i == 1 && j == 2)
	{
		minor[0][0] = matrix[0][0];
		minor[0][1] = matrix[0][1];
		minor[1][0] = matrix[2][0];
		minor[1][1] = matrix[2][1];
	}
	//
	if (i == 2 && j == 0)
	{
		minor[0][0] = matrix[0][1];
		minor[0][1] = matrix[0][2];
		minor[1][0] = matrix[1][1];
		minor[1][1] = matrix[1][2];
	}
	if (i == 2 && j == 1)
	{
		minor[0][0] = matrix[0][0];
		minor[0][1] = matrix[0][2];
		minor[1][0] = matrix[1][0];
		minor[1][1] = matrix[1][2];
	}
	if (i == 2 && j == 2)
	{
		minor[0][0] = matrix[0][0];
		minor[0][1] = matrix[0][1];
		minor[1][0] = matrix[1][0];
		minor[1][1] = matrix[1][1];
	}
}

double** FindTripleAdjugateMatrix(double** matrix)
{
	double** adjugateMatrix = CreateDynamicMatrix(3);
	double** minorAdjugateMatrix = CreateDynamicMatrix(2);

	bool isMinus = false;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			fillDoubleMinor(i, j, minorAdjugateMatrix, matrix);
			adjugateMatrix[i][j] = FindDoubleMatrixDeterminant(minorAdjugateMatrix);
			if (isMinus && (adjugateMatrix[i][j] != 0))
			{
				adjugateMatrix[i][j] = -1 * adjugateMatrix[i][j];
			}
			isMinus = !isMinus;
		}
	}
	CleanDynamicMatrix(minorAdjugateMatrix, 2);
	return adjugateMatrix;
}

double** TransposeMatrix(double** matrix)
{
	double** transposedMatrix = new double*[3];
	for (int i = 0; i < 3; i++)
	{
		transposedMatrix[i] = new double[3];
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			transposedMatrix[i][j] = matrix[j][i];
		}
	}

	return transposedMatrix;
}

double** InvertMatrix(double** transposedAdjMatrix, double determinant)
{
	double** invertedMatrix = new double*[3];

	for (int i = 0; i < 3; i++)
	{
		invertedMatrix[i] = new double[3];
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			invertedMatrix[i][j] = transposedAdjMatrix[i][j] / determinant;
		}
	}

	return invertedMatrix;
}

void PrintMatrix(std::ostream& output, double** matrix)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			output << std::fixed << std::setprecision(TASK_PRECISION);
			output << matrix[i][j] << "\t\t";
		}
		output << std::endl;
	}
}

void ReadInputToMatrix(std::istream& input, double** matrix)
{
	double num;
	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			input >> num;
			matrix[i][k] = num;
		}
	}
}

int Invert(std::string inputFilePath, std::ostream& output)
{
	std::ifstream fIn;
	fIn.open(inputFilePath);

	if (!fIn.is_open())
	{
		std::cout << "Couldn't open the file" << std::endl;
		return 1;
	}

	double** startMatrix = CreateDynamicMatrix(3);
	ReadInputToMatrix(fIn, startMatrix);

	double determinant = FindTripleMatrixDeterminant(startMatrix);

	if (determinant == 0)
	{
		std::cout << "Inverted matrix for this matrix doesn't exist." << std::endl;
		return 1;
	}

	double** adjMatrix = CreateDynamicMatrix(3);
	adjMatrix = FindTripleAdjugateMatrix(startMatrix);

	double** transposedMatrix = CreateDynamicMatrix(3);
	transposedMatrix = TransposeMatrix(adjMatrix);

	double** invertedMatrix = CreateDynamicMatrix(3);
	invertedMatrix = InvertMatrix(transposedMatrix, determinant);

	PrintMatrix(output, invertedMatrix);

	CleanDynamicMatrix(startMatrix, 3);
	CleanDynamicMatrix(adjMatrix, 3);
	CleanDynamicMatrix(transposedMatrix, 3);
	CleanDynamicMatrix(invertedMatrix, 3);

	return 0;
}

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count" << std::endl;
		std::cout << "Usage: Invert.exe <matrix file name>" << std::endl;
		return std::nullopt;
	}

	Args args;
	args.matrixFileName = argv[1];
	return args;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	int statusCode = Invert(args->matrixFileName, std::cout);
	if (statusCode != 0)
	{
		return 1;
	}

	return 0;
}
