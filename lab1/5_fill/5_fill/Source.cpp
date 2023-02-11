#include <iostream>
#include <queue>
#include <vector>
#include <fstream>

using namespace std;

int directionX[4] = { 1, -1, 0, 0 };
int directionY[4] = { 0, 0, 1, -1 };
char field[10][10]{ 0 };

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
		if (ttPoint.x < 0 || ttPoint.x > 9) continue;
		if (ttPoint.y < 0 || ttPoint.y > 9) continue;
		if (field[ttPoint.x][ttPoint.y] == '#') continue;
		if (field[ttPoint.x][ttPoint.y] == 'O') continue;
		if (field[ttPoint.x][ttPoint.y] == '.') continue;
		
		field[ttPoint.x][ttPoint.y] = '.';
		q.push(ttPoint);
	}
}

void showField()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << field[i][j];
		}
		cout << endl;
	}
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
	
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			inputFile.get(ch);
			if (ch != '\n')
			{
				field[i][j] = ch;
			}
			else
			{
				j--;
			}

			if (ch == 'O')
			{
				startPoints.push_back(Point{ i,j });
			}

		}
	}

	showField();

	cout << endl << endl;

	cout << startPoints.size() << endl;

	if (startPoints.size() > 0)
	{
		q.push(startPoints[0]);

		if (q.empty())
		{
			cout << "Q is empty" << endl;
		}
		else
		{
			cout << "Q not empty" << endl;
			while (!q.empty())
			{
				// достаю Point, чекаю соседей
				Point tempP = q.front();
				q.pop();
				exploreNeighbours(tempP);
			}

		}

	}
	inputFile.close();

	showField();
	

	/*queue<Point> q;
	q.push(Point{ 1, 1 });
	q.push(Point{ 2, 2 });
	q.push(Point{ 3, 3 });

	while (!q.empty())
	{
		cout << q.front().x << endl;
		q.pop();
	}
	cout << "Queue is empty" << endl;
*/


	return 0;
}