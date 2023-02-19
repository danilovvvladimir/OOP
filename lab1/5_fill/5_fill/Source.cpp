#include <Windows.h>
#include <fstream>
#include <iostream>
#include <optional>
#include <queue>
#include <vector>

const char CH_SPACE = ' ';
const char CH_UNAVAILABLE = '_';
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

struct Args
{
	std::string inputFilePath;
	std::string outputFilePath;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid arguments count\n"
				  << "Usage fill.exe <input file> <output file>\n";

		return std::nullopt;
	}

	Args args;
	args.inputFilePath = argv[1];
	args.outputFilePath = argv[2];
	return args;
}

std::vector<Point> startPoints;
std::queue<Point> queue;
char field[MAX_SIZE][MAX_SIZE]{ 0 };

void ExploreNeighbours(Point p)
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
		queue.push(neighbourPoint);
	}
}

void PrintField(std::ostream& output)
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
int CheckChInField(char& ch, int i, int& j, bool& markerEndLine, bool& markerNotEndLoop, bool& markerEndLineLoop)
{
	if (ch == '\n')
	{
		if (!markerEndLine)
		{
			markerNotEndLoop = true;
		}
		j--;
		return 1;
	}
	else
	{
		if (markerEndLine)
		{
			markerEndLineLoop = true;
		}
		field[i][j] = ch;

		if (ch == CH_FILL_POINT)
		{
			startPoints.push_back(Point{ i, j });
		}
	}

	return 0;
}

void HandleEndLineLoop(char& ch, std::istream& inputFile, bool& markerEndLine, bool& markerEndLineLoop)
{
	ch = CH_UNAVAILABLE;
	while (ch != '\n')
	{
		inputFile.get(ch);
		if (ch == CH_UNAVAILABLE)
		{
			ch = '\n';
		}
	}
	markerEndLine = false;
	markerEndLineLoop = false;
}

void ValidateField(std::istream& inputFile)
{
	bool markerEndLine = false;
	bool markerNotEndLoop = false;
	bool markerEndLineLoop = false;

	char ch;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			ch = CH_SPACE;
			if (markerEndLineLoop)
			{
				HandleEndLineLoop(ch, inputFile, markerEndLine, markerEndLineLoop);
			}

			if (markerNotEndLoop)
			{
				if (j == MAX_SIZE - 1)
				{
					markerNotEndLoop = false;
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

			int statusCh = CheckChInField(ch, i, j, markerEndLine, markerNotEndLoop, markerEndLineLoop);
			if (statusCh == 1)
			{
				continue;
			}
		}
	}
}

void FillField()
{
	for (int i = 0; i < static_cast<int>(startPoints.size()); i++)
	{
		queue.push(startPoints[i]);

		while (!queue.empty())
		{
			Point queueBottomPoint = queue.front();
			queue.pop();
			ExploreNeighbours(queueBottomPoint);
		}
	}
}

int HandleFill(const std::string& inputFilePath, const std::string& outputFilePath)
{
	std::ifstream inputFile;
	inputFile.open(inputFilePath);

	if (!inputFile.is_open())
	{
		std::cout << "INFILE not opened" << std::endl;
		return 1;
	}
	ValidateField(inputFile);
	FillField();

	std::ofstream outputFile;
	outputFile.open(outputFilePath);
	if (!outputFile.is_open())
	{
		std::cout << "OUTFILE not opened" << std::endl;
		return 1;
	}

	PrintField(outputFile);

	return 0;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	int statusCode = HandleFill(argv[1], argv[2]);
	if (statusCode != 0)
	{
		return 1;
	}

	return 0;
}
