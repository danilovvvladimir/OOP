#include <Windows.h>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

const char CH_SPACE = ' ';
const char CH_SPACE2 = '_';
const char CH_DOT = '.';
const char CH_WALL = '#';
const char CH_FILL_POINT = 'O';

const int MAX_SIZE = 100;
const int directionX[4] = { 1, -1, 0, 0 };
const int directionY[4] = { 0, 0, 1, -1 };

struct Point
{
	int x, y;
};
std::vector<Point> startPoints;
char field[MAX_SIZE][MAX_SIZE]{ 0 };

std::queue<Point> q;

void exploreNeighbours(Point p)
{
	for (int i = 0; i < 4; i++)
	{
		Point neighbourPoint = p;
		neighbourPoint.x += directionX[i];
		neighbourPoint.y += directionY[i];
		if (neighbourPoint.x < 0 || neighbourPoint.x > MAX_SIZE - 1)
			continue;
		if (neighbourPoint.y < 0 || neighbourPoint.y > MAX_SIZE - 1)
			continue;
		if (field[neighbourPoint.x][neighbourPoint.y] == CH_WALL)
			continue;
		if (field[neighbourPoint.x][neighbourPoint.y] == CH_FILL_POINT)
			continue;
		if (field[neighbourPoint.x][neighbourPoint.y] == CH_DOT)
			continue;

		field[neighbourPoint.x][neighbourPoint.y] = CH_DOT;
		q.push(neighbourPoint);
	}
}

void showField(std::ostream& output)
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			output << field[i][j];
		}
		output << std::endl;
	}
}
void validateField(std::ifstream& inputFile)
{
	bool markerEndLine = false;
	bool markerLoop = false;
	bool markerEndLineLoop = false;

	char ch;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{

			ch = CH_SPACE;
			if (markerEndLineLoop)
			{
				ch = CH_SPACE2;
				while (ch != '\n')
				{
					inputFile.get(ch);
					if (ch == CH_SPACE2)
					{
						ch = '\n';
					}
				}
				markerEndLine = false;
				markerEndLineLoop = false;
			}

			if (markerLoop)
			{
				if (j == MAX_SIZE - 1)
				{
					markerLoop = false;
				}
				field[i][j] = ch;
				continue;
			}
			else
			{
				inputFile.get(ch);
			}

			if (j == MAX_SIZE - 1)
			{
				markerEndLine = true;
			}

			if (ch == '\n')
			{
				if (!markerEndLine)
				{
					markerLoop = true;
					j--;
					continue;
				}
				else
				{
					j--;
					continue;
				}
			}
			else
			{
				if (markerEndLine)
				{
					markerEndLineLoop = true;
					field[i][j] = ch;
				}
				else
				{
					field[i][j] = ch;
				}
			}

			if (ch == CH_FILL_POINT)
			{
				startPoints.push_back(Point{ i, j });
			}
		}
	}
}

void fillField()
{
	if (startPoints.size() > 0)
	{
		for (int i = 0; i < static_cast<int>(startPoints.size()); i++)
		{
			q.push(startPoints[i]);

			if (!q.empty())
			{
				while (!q.empty())
				{
					Point tempP = q.front();
					q.pop();
					exploreNeighbours(tempP);
				}
			}
		}
	}
}

int HandleFill(std::string inputFilePath, std::string outputFilePath)
{
	std::ifstream inputFile;
	inputFile.open(inputFilePath);

	if (inputFile.is_open())
	{
		validateField(inputFile);
		fillField();
		std::ofstream outputFile;
		outputFile.open(outputFilePath);
		if (outputFile.is_open())
		{

			showField(outputFile);
		}
		else
		{
			std::cout << "OUTFILE not opened" << std::endl;
			return 1;
		}
	}
	else
	{
		std::cout << "INFILE not opened" << std::endl;
		return 1;
	}

	return 0;
}

int main(int argc, char* argv[])
{

	if (argc != 3)
	{
		std::cout << "Invalid arguments count\n"
				  << "Usage fill.exe <input file> <output file>\n";

		return 1;
	}

	int statusCode = HandleFill(argv[1], argv[2]);
	if (statusCode != 0)
	{
		return 1;
	}

	return 0;
}
