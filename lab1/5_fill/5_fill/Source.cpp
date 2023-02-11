#include <iostream>
#include <queue>
#include <vector>
#include <Windows.h>
#include <fstream>

using namespace std;

const int MAX_SIZE = 5;
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
		if (ttPoint.x < 0 || ttPoint.x > MAX_SIZE - 1) continue;
		if (ttPoint.y < 0 || ttPoint.y > MAX_SIZE - 1) continue;
		if (field[ttPoint.x][ttPoint.y] == '#') continue;
		if (field[ttPoint.x][ttPoint.y] == 'O') continue;
		if (field[ttPoint.x][ttPoint.y] == '.') continue;

		field[ttPoint.x][ttPoint.y] = '.';
		q.push(ttPoint);
	}
}

void showField(std::ostream& output)
{
	system("cls");
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE; j++)
		{
			output << field[i][j];
		}
		output << endl;
	}
	Sleep(20);
}


int main()
{
	vector<Point> startPoints;
	ifstream inputFile;
	inputFile.open("in.txt");
	if (!inputFile.is_open())
	{
		cout << "FILE not opened" << endl;
		return 1;
	}

	char ch;


	bool isEnd = false;

	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int j = 0; j < MAX_SIZE+1; j++)
		{
			if (j == MAX_SIZE)
			{
				isEnd = !isEnd;
				continue;
			}
			if (isEnd)
			{
				field[i][j] = '_';
				continue;
			}
			
			ch = ' ';
			inputFile.get(ch);
			if (ch != '\n')
			{
				field[i][j] = ch;
			}
			else
			{
				isEnd = true;
				if (j == 0)
				{
					j--;
				}
			}

			if (ch == 'O')
			{
				startPoints.push_back(Point{ i,j });
			}

		}
	}

	//showField(cout);

	cout << endl << endl;


	if (startPoints.size() > 0)
	{
		for (int i = 0; i < static_cast<int>(startPoints.size()); i++)
		{
			q.push(startPoints[i]);

			if (!q.empty())
			{
				cout << "Q not empty" << endl;
				while (!q.empty())
				{
					Point tempP = q.front();
					q.pop();
					exploreNeighbours(tempP);
					showField(cout);
				}
			}
		}

	}
	inputFile.close();
	ofstream outputFile;
	outputFile.open("out.txt");
	showField(outputFile);

	outputFile.close();


	return 0;
}