#pragma warning(disable : 4996)
#include <iostream>
#include <windows.h>
#include <conio.h>
#include<time.h>
using namespace std;

bool GameOver;
const int width = 20, height = 20;

int x, y; //координати змії
int xFruit, yFruit;
int score;

int xTail[150];
int yTail[150];
int nTail;

enum Run 
{ 
	STOP = 0,
	RIGHT,
	lEFT,
	UP,
	DOWN
};

Run run;

void SetUp();
void Draw();
void Input();
void Prog();


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int Start;

	cout << "\t\t\t\t\tГра \"ЗМІЙКА\"!";
	cout << "\n\nУправління в грі:\n\t\"W\" - рух вгору;\n\t\"S\" - рух вниз;\n\t\"A\" - рух вліво;\n\t\"D\" - рух вправо;\n\t\"Q\" - зупинити гру." << endl;
	cout << "Для управління в грі використовуйте лише латинські літери!";
	cout << "\n\nДля того, щоб розпочати гру натисніть будь-яку клавішу: "; cin >> Start;

	SetUp();
	while (!GameOver) //поки гру не завершено
	{
		Draw();
		Input();
		Prog();
	}

	cout << "\nГру завершено! К-сть набраних очок: " << score;
	cout << "\n\n";
	system("pause");		
}

void SetUp()
{
	srand(time(0));
	GameOver = false;
	run = STOP;
	x = width / 2 - 1; 
	y = height / 2 - 1;
	xFruit = rand() % 19;
	yFruit = rand() % 19;
	score = 0; 
}
		
void Draw()
{
	system("cls");

	for (int i = 0; i <= width+2; i++) 
	{
		cout << "I";
	}
	cout << endl;

	for (int i = 0; i <= height+2; i++)
	{
		for (int j = 0; j <= width+2; j++)
		{
			if (j == 0 || j == width+1)
			{
				cout << "I";
			}

			if (i == y && j == x)
			{
				cout << "@";
			}
			
			if (i == yFruit && j == xFruit)
			{
				cout << "t";
			}
			
			else
			{
				bool print = false;
				for (int h = 0; h < nTail; h++)
				{
					if (xTail[h] == j && yTail[h] == i)
					{
						print = true;
						cout << "O";
					}

				}

				if (!print)
				{
					cout << " ";
				}
			
			}
			
		}

		cout << endl;
	}

	for (int i = 0; i <= width+2; i++) 
	{
		cout << "I";
	}
	cout << endl;

	cout << "\n\tОчки: " << score << endl;
}

void Input()
{
	if (kbhit()) //якщо кнопка натиснута 
	{

		switch (getch())
		{
		case 'd':
			run = RIGHT;
			break;

		case 'D':
			run = RIGHT;
			break;

		case 'a':
			run = lEFT;
			break;

		case 'A':
			run = lEFT;
			break;

		case 'w':
			run = UP;
			break;

		case 'W':
			run = UP;
			break;

		case 's':
			run = DOWN;
			break;

		case 'S':
			run = DOWN;
			break;

		case 'q': //завершення гри
			GameOver = true;
			break;

		case 'Q': //завершення гри
			GameOver = true;
		}
	}
}

void Prog()
{
	int xFirst = xTail[0];
	int yFirst = yTail[0];

	xTail[0] = x;
	yTail[0] = y;
	int xNext, yNext;
	for (int i = 1; i < nTail; i++) //рух хвоста
	{
		xNext = xTail[i];
		yNext = yTail[i];
		xTail[i] = xFirst;
		yTail[i] = yFirst;
		xFirst = xNext;
		yFirst = yNext;
	}

	switch (run)
	{
	case RIGHT:
		x++;
		break;
	case LEFT:
		x--;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}

	if (y >= height || y < 0 || x < 0 || x >= width)
	{
		GameOver = true;
	}

	for (int i = 0; i < nTail; i++)
	{
		if (xTail[i] == x && yTail[i] == y)
		{
			GameOver = true;
		}
	}

	if (x == xFruit && y == yFruit)
	{
		score = score + 25;
		xFruit = rand() % 20;
		yFruit = rand() % 20;
		nTail++;
	}
}

