#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#define MINE_START_HEIGHT (1)
#define MINE_START_WIDTH (1)
#define MINE_END_HEIGHT (20)
#define MINE_END_WIDTH (20)
#define MINE_TABLE_HEIGHT (MINE_END_HEIGHT+2)
#define MINE_TABLE_WIDTH (MINE_END_WIDTH+2)
#define MINE_BOMB (-1)

using namespace std;

int mine[MINE_TABLE_HEIGHT][MINE_TABLE_WIDTH];
bool visibleMine[MINE_TABLE_HEIGHT][MINE_TABLE_WIDTH];

class Point
{
public :
	int X;
	int Y;

public :

	Point::Point(int x, int y) :
	   X(x), Y(y)
	{
	}

	void Point::operator =(Point pt)
	{
		this->X = pt.X;
		this->Y = pt.Y;
	}

	bool Point::operator ==(Point pt)
	{
		return (this->X == pt.X && this->Y == pt.Y);
	}

};

void initMine()
{
	for (int i = 0; i < MINE_TABLE_HEIGHT; i++)
	{
		for (int j = 0; j < MINE_TABLE_WIDTH; j++)
		{
			mine[i][j] = 0;
			visibleMine[i][j] = false;
		}
	}
}

void setMine(int mineNum)
{
	if (mineNum > MINE_END_HEIGHT * MINE_END_WIDTH) return;
	vector<Point> bombVector;
	srand((unsigned) time(NULL));

	for (int i = MINE_START_HEIGHT; i <= MINE_END_HEIGHT; i++)
	{
		for (int j = MINE_START_WIDTH; j <= MINE_END_WIDTH; j++)
		{
			Point tmpPoint(i, j);
			bombVector.push_back(tmpPoint);
		}
	}

	for (int i = 0; i < mineNum; i++)
	{
		int tmpRandom = rand() % bombVector.size();
		vector<Point>::iterator it = bombVector.begin();
		it += tmpRandom;
		Point tmpPoint = bombVector.at(tmpRandom);
		mine[tmpPoint.X][tmpPoint.Y] = MINE_BOMB;
		for (int j = -1; j <= 1; j++)
		{
			for (int k = -1; k <= 1; k++)
			{
				if ((j != 0 || k != 0) && mine[tmpPoint.X + j][tmpPoint.Y + k] != MINE_BOMB)
					mine[tmpPoint.X + j][tmpPoint.Y + k]++;
			}
		}
		bombVector.erase(it);
	}
}

void showMine()
{
	printf(" 0   ");
	for (int i = MINE_START_WIDTH; i <= MINE_END_WIDTH; i++)
		printf("%2d ", i);
	printf("\n\n");
	for (int i = MINE_START_HEIGHT; i <= MINE_END_HEIGHT; i++)
	{
		printf("%2d   ", i);
		for (int j = MINE_START_WIDTH; j <= MINE_END_WIDTH; j++)
		{
			if (visibleMine[i][j]) {
				if (mine[i][j] != 0)
					printf("%2d ", mine[i][j]);
				else
					printf("   ");
			} else
				printf(" * ");
		}
		printf("\n");
	}
}

void openArroundZero(int x, int y) {
	if (x < MINE_START_WIDTH || x > MINE_END_WIDTH || y < MINE_START_HEIGHT || y > MINE_END_HEIGHT)
		return;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if ((j != 0 || i != 0) && mine[y+j][x+i] == 0 && visibleMine[y+j][x+i] == false) {
				openArroundZero(x+i, y+j);
			}
			visibleMine[y+j][x+i] = true;
		}
	}
}

bool openMine()
{
	int x = 0, y = 0;
	scanf("%d %d", &x, &y);
	if (x < MINE_START_WIDTH || x > MINE_END_WIDTH || y < MINE_START_HEIGHT || y > MINE_END_HEIGHT)
		return false;
	visibleMine[y][x] = true;

	if (mine[y][x] == 0) {
		openArroundZero(x, y);
	}

	if (mine[y][x] == MINE_BOMB)
		return false;
	return true;
}

void clearConsole()
{
	system("cls");
}

void endMine()
{
	clearConsole();
	showMine();
	printf("Game over.\n");
}

int main(void)
{
	initMine();
	setMine(40);

	do
	{
		clearConsole();
		showMine();
	} while (openMine());

	endMine();

	return 0;
}
