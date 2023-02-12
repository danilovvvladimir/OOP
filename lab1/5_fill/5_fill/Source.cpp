#include <Windows.h>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MAX_SIZE = 100;
const int directionX[4] = { 1, -1, 0, 0 };
const int directionY[4] = { 0, 0, 1, -1 };
char field[MAX_SIZE][MAX_SIZE]{ 0 };

struct Point
{
	int x, y;
};

queue<Point> q;
void exploreNeighbours(Point p)
{
	for (int i = 0; i < 4; i++)
	{
		Point ttPoint = p;
		ttPoint.x += directionX[i];
		ttPoint.y += directionY[i];
		if (ttPoint.x < 0 || ttPoint.x > MAX_SIZE - 1)
			continue;
		if (ttPoint.y < 0 || ttPoint.y > MAX_SIZE - 1)
			continue;
		if (field[ttPoint.x][ttPoint.y] == '#')
			continue;
		if (field[ttPoint.x][ttPoint.y] == 'O')
			continue;
		if (field[ttPoint.x][ttPoint.y] == '.')
			continue;

		field[ttPoint.x][ttPoint.y] = '.';
		q.push(ttPoint);
	}
}

void showField(std::ostream& output)
{
	//system("cls");
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			output << field[i][j];
		}
		output << endl;
	}
	//Sleep(20);
}

int main()
{
	// Игнорирование символов за MAX_SIZE, делается так: если на крайнем J не \n, то пока не будет встречен конец строки inputFile.get(ch);
	// Вынесение по функциям, validateFile, fill, showField на printField переименовать
	// Константы для символов
	// argc, argv
	vector<Point> startPoints;
	ifstream inputFile;
	inputFile.open("emp.txt");
	if (!inputFile.is_open())
	{
		cout << "FILE not opened" << endl;
		return 1;
	}

	bool isEnd = false;
	bool isN = false;
	bool isAddN = false;


	char ch;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			ch = ' ';
			if (!isN && !isAddN)
			{
				inputFile.get(ch);
			}
			if (isAddN)
			{
				ch = '\n';
				isAddN = false;
				isEnd = true;
			}
			if (j == MAX_SIZE - 1)
			{
				isEnd = true;
				if (isN)
				{
					isN = false;
					ch = ' ';
					isAddN = true;
				}
			}

			if (isN && !isEnd)
			{
				field[i][j] = ' ';
				continue;
			}
			if (ch != '\n')
			{
				if (!isN)
				{
					field[i][j] = ch;
				}
			}
			else
			{
				if (j == 0 && isEnd)
				{
					j--;
					isEnd = false;
				}
				else
				{

					isN = true;
					field[i][j] = ' ';
					if (j == MAX_SIZE - 1)
					{
						isN = false;
					}
				}
			}
			if (ch == 'O')
			{
				startPoints.push_back(Point{ i, j });
			}
		}
	}
	//showField(cout);
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
					//showField(cout);
				}
			}
		}
	}
	inputFile.close();
	ofstream outputFile;
	outputFile.open("out.txt");
	showField(outputFile);
	//showField(cout);

	outputFile.close();

	return 0;
}
