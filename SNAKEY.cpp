#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>

// to make using std easier
using namespace std;

// only global variable - bad practice i guess
bool gameOver;

// map dimensions
const int width = 20;
const int height = 20;

// head position variables
int x, y, fruitX, fruitY, score;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

// tail positioning
int tailX[100], tailY[100];
int numOfTail;

// setup function
void setup()
{
	gameOver = false;
	dir = STOP;

	// initial position of snake
	x = width / 2;
	y = height / 2;

	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

// drawing function
void draw()
{
	int i;
	int j;
	int k;

	// clears the screen
	system("cls");

	// top wall
	for (i = 0; i < width; i++)
		cout << "@";
	cout << endl;

	// side walls
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
			{
				cout << "@";
			}

			// snake spawn position
			if (i == y && j == x)
				cout << "O";

			// fruit spawn position
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else
			{
				// tail logic
				bool print = false;
				for (k = 0; k < numOfTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}
		}
		// this produces an empty line
		cout << endl;
	}


	// bottom wall
	for (i = 0; i < height; i++)
	{
		cout << "#";
	}
	cout << endl;

	// print out the score on the screen
	cout << "\n" << "Score: " << score;
}

void input()
{
	// boolean - returns 1 if key is pressed, 0 otherwise
	// just a case statement to determine the direction
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'w':
			dir = UP;
			break;
		case 'd':
			dir = RIGHT;
			break;

		case 'x':
			gameOver = true;
			break;
		}
	}
}

void logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;

	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < numOfTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case LEFT:
		x --;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	// die when you hit the wall
	//if (x > width || x < 0 || y > height || y < 0)
	//	gameOver = 1;
	
	// this allows our snake to go through the walls rather than dying
	if (x >= width)
		x = 0;
	if (x < 0)
		x = width - 1;
	if (y >= height)
		y = 0;
	if (y < 0)
		y = height - 1;

	for (int i = 0; i < numOfTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
			gameOver = 1;
	}

	if (x == fruitX && y == fruitY)
	{
		score += 25;
		// re-randomize fruit position
		fruitX = rand() % width;
		fruitY = rand() % height;

		// if fruit eaten then tail num increases
		numOfTail++;
	}
}

int main()
{
	// when main starts, it will call set up
	// as long as game is on, it calls those functions below
	setup();
	while (!gameOver)
	{
		draw();
		input();
		logic();
		this_thread::sleep_for(chrono::milliseconds(50));
	}

	return 0;
}