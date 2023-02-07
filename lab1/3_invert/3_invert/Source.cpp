#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 


// Функция нахождения определителя в 3*3 матрице
// Функция нахождения определителя в 2*2 матрице
// Функция нахождения союзной матрицы
// Функция нахождения транпонированной матрицы
// Главная функция нахождения обратной матрицы (союзная-транспонированная * 1/определитель 3*3)
// 
//
//
//

double findTripleMatrixDeterminant(double matrix[][3])
{
	double determinant = ((matrix[0][0] * matrix[1][1] * matrix[2][2]) + (matrix[0][2] * matrix[1][0] * matrix[2][1]) + (matrix[0][1] * matrix[1][2] * matrix[2][0]) -
		(matrix[0][2] * matrix[1][1] * matrix[2][0]) + (matrix[0][1] * matrix[1][0] * matrix[2][2]) + (matrix[0][0] * matrix[1][2] * matrix[2][1]));
	return determinant;
}


double findDoubleMatrixDeterminant(double matrix[][2])
{
	double determinant = ((matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0] ));
	return determinant;
}

void findAdjugateMatrix(double matrix[][3])
{
	//double ** AdjugateMatrix = new double* [3];
	double AdjugateMatrix[3][3];
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

			AdjugateMatrix[i][j] = findDoubleMatrixDeterminant(minorAdjugateMatrix);
			if (isMinus)
			{
				AdjugateMatrix[i][j] = -1 * AdjugateMatrix[i][j];
			}
			isMinus = !isMinus;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			std::cout << AdjugateMatrix[i][k] << "\t";
		}
		std::cout << std::endl;
	}
	//return AdjugateMatrix;
}

std::string transformDoubleToStringAndRound(double num)
{
	std::string result;
	std::string numStr = std::to_string(num);
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

int main()
{
	system("chcp 1251> nul");
	std::string fInPath = "in.txt";
	std::ifstream fIn;
	fIn.open(fInPath);

	double matrixIn[3][3];
	//string matrixFloatIn[3][3];

	if (fIn.is_open())
	{
		for (int i = 0; i < 3; i++)
		{
			for (int k = 0; k < 3; k++)
			{
				// Запись матрицы в двумерный массив.
				double tempNumber;
				fIn >> tempNumber;
				matrixIn[i][k] = tempNumber;
			}
		}
		double determinant = findTripleMatrixDeterminant(matrixIn);
		if (determinant == 0)
		{

			std::cout << "Детерминант матрицы равен нулю, обратной матрицы не существует." << std::endl;
		}
		else
		{
			std::cout << "Детерминант матрицы: " << determinant << std::endl << std::endl;

		}
		std::cout << std::endl;
		findAdjugateMatrix(matrixIn);
		std::cout << std::endl;
		std::cout << std::endl;
		//for (int i = 0; i < 3; i++)
		//{
		//	for (int k = 0; k < 3; k++)
		//	{
		//		double tempNumber;
		//		tempNumber = (1.0 / matrixIn[i][k]);
		//		tempNumber = round(1000 * tempNumber) / 1000.0;
		//		matrixFloatIn[i][k] = transformDoubleToStringAndRound(tempNumber);
		//		//matrixFloatIn[i][k] = 1.0 / matrixIn[i][k];
		//	}
		//}


	}
	else
	{
		std::cout << "Couldn't open the file" << std::endl;
	}

	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			std::cout << matrixIn[i][k] << "\t";
		}
		std::cout << std::endl;
	}
	return 0;
}