#include <fstream>
#include <iostream>
#include <optional>
#include <string>

struct Args
{
	std::string matrixFileName;
};

double FindTripleMatrixDeterminant(double** matrix)
{
	double determinant = (((matrix[0][0] * matrix[1][1] * matrix[2][2]) + (matrix[0][2] * matrix[1][0] * matrix[2][1]) + (matrix[0][1] * matrix[1][2] * matrix[2][0])) - ((matrix[0][2] * matrix[1][1] * matrix[2][0]) + (matrix[0][1] * matrix[1][0] * matrix[2][2]) + (matrix[0][0] * matrix[1][2] * matrix[2][1])));
	return determinant;
}

double FindDoubleMatrixDeterminant(double matrix[][2])
{
	double determinant = ((matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]));
	return determinant;
}

double** FindTripleAdjugateMatrix(double** matrix)
{
	double** adjugateMatrix = new double*[3];
	for (int i = 0; i < 3; i++)
	{
		adjugateMatrix[i] = new double[3];
	}
	double minorAdjugateMatrix[2][2];

	bool isMinus = false;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == 0 && j == 0)
			{
				minorAdjugateMatrix[0][0] = matrix[1][1];
				minorAdjugateMatrix[0][1] = matrix[1][2];
				minorAdjugateMatrix[1][0] = matrix[2][1];
				minorAdjugateMatrix[1][1] = matrix[2][2];
			}
			if (i == 0 && j == 1)
			{
				minorAdjugateMatrix[0][0] = matrix[1][0];
				minorAdjugateMatrix[0][1] = matrix[1][2];
				minorAdjugateMatrix[1][0] = matrix[2][0];
				minorAdjugateMatrix[1][1] = matrix[2][2];
			}
			if (i == 0 && j == 2)
			{
				minorAdjugateMatrix[0][0] = matrix[1][0];
				minorAdjugateMatrix[0][1] = matrix[1][1];
				minorAdjugateMatrix[1][0] = matrix[2][0];
				minorAdjugateMatrix[1][1] = matrix[2][1];
			}
			//
			if (i == 1 && j == 0)
			{
				minorAdjugateMatrix[0][0] = matrix[0][1];
				minorAdjugateMatrix[0][1] = matrix[0][2];
				minorAdjugateMatrix[1][0] = matrix[2][1];
				minorAdjugateMatrix[1][1] = matrix[2][2];
			}
			if (i == 1 && j == 1)
			{
				minorAdjugateMatrix[0][0] = matrix[0][0];
				minorAdjugateMatrix[0][1] = matrix[0][2];
				minorAdjugateMatrix[1][0] = matrix[2][0];
				minorAdjugateMatrix[1][1] = matrix[2][2];
			}
			if (i == 1 && j == 2)
			{
				minorAdjugateMatrix[0][0] = matrix[0][0];
				minorAdjugateMatrix[0][1] = matrix[0][1];
				minorAdjugateMatrix[1][0] = matrix[2][0];
				minorAdjugateMatrix[1][1] = matrix[2][1];
			}
			//
			if (i == 2 && j == 0)
			{
				minorAdjugateMatrix[0][0] = matrix[0][1];
				minorAdjugateMatrix[0][1] = matrix[0][2];
				minorAdjugateMatrix[1][0] = matrix[1][1];
				minorAdjugateMatrix[1][1] = matrix[1][2];
			}
			if (i == 2 && j == 1)
			{
				minorAdjugateMatrix[0][0] = matrix[0][0];
				minorAdjugateMatrix[0][1] = matrix[0][2];
				minorAdjugateMatrix[1][0] = matrix[1][0];
				minorAdjugateMatrix[1][1] = matrix[1][2];
			}
			if (i == 2 && j == 2)
			{
				minorAdjugateMatrix[0][0] = matrix[0][0];
				minorAdjugateMatrix[0][1] = matrix[0][1];
				minorAdjugateMatrix[1][0] = matrix[1][0];
				minorAdjugateMatrix[1][1] = matrix[1][1];
			}

			adjugateMatrix[i][j] = FindDoubleMatrixDeterminant(minorAdjugateMatrix);
			if (isMinus && (adjugateMatrix[i][j] != 0))
			{
				adjugateMatrix[i][j] = -1 * adjugateMatrix[i][j];
			}
			isMinus = !isMinus;
		}
	}
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

std::string TransformDoubleToCorrectString(double num)
{
	double number = round(1000 * num) / 1000.0;
	std::string result;
	std::string numStr = std::to_string(number);
	int length = numStr.size();
	int counter = 0;
	for (int i = 0; i < length; i++)
	{
		if (counter == 4)
		{
			break;
		}
		if (numStr[i] == '.' || counter > 0)
		{
			counter++;
		}
		result += numStr[i];
	}
	return result;
}

void PrintMatrix(std::ostream& output, double** matrix)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			output << TransformDoubleToCorrectString(matrix[i][j]) << "\t\t";
		}
		output << std::endl;
	}
}

void CleanDinamicMatrix(double** matrix)
{
	for (int i = 0; i < 3; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

double** createTripleMatrix()
{
	double** TripleMatrix = new double*[3];
	for (int i = 0; i < 3; i++)
	{
		TripleMatrix[i] = new double[3];
	}

	return TripleMatrix;
}

int Invert(std::string inputFilePath, std::ostream& output)
{
	std::ifstream fIn;
	fIn.open(inputFilePath);

	double** startMatrix = new double*[3];
	for (int i = 0; i < 3; i++)
	{
		startMatrix[i] = new double[3];
	}

	if (!fIn.is_open())
	{
		std::cout << "Couldn't open the file" << std::endl;
		return 1;
	}

	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			double num;
			fIn >> num;
			startMatrix[i][k] = num;
		}
	}

	double determinant = FindTripleMatrixDeterminant(startMatrix);

	if (determinant == 0)
	{
		std::cout << "Inverted matrix for this matrix doesn't exist." << std::endl;
		return 1;
	}

	double** adjMatrix = createTripleMatrix();
	adjMatrix = FindTripleAdjugateMatrix(startMatrix);

	double** transposedMatrix = createTripleMatrix();
	transposedMatrix = TransposeMatrix(adjMatrix);

	double** invertedMatrix = createTripleMatrix();
	invertedMatrix = InvertMatrix(transposedMatrix, determinant);

	PrintMatrix(output, invertedMatrix);

	CleanDinamicMatrix(startMatrix);
	CleanDinamicMatrix(adjMatrix);
	CleanDinamicMatrix(transposedMatrix);
	CleanDinamicMatrix(invertedMatrix);

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
