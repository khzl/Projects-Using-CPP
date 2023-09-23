#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
void Welcome();
void Instructions();
void Record();
void IncorrectChoice();
void LostGame();
void Win();
// Game initial settings 
bool Game = false;
const int Width = 50;
const int Height = 20;
// variable for snake position and fruit position and also score 
int HorizontalPositionSnake, VerticalPositionSnake, HorizontalPositionFruit, VerticalPositionFruit, Score;
// Snake body segments
int SnakeXCoordinates[100]; // Array to store x-coordinates of snake segments
int SnakeYCoordinates[100]; // Array to store y-coordinates of snake segments
int NumberOfSegments;       // Keeps track of the number of segments in the snake's body
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction direction;
// initial values when game start
void Init()
{
	Game = true;
	direction = STOP;
	HorizontalPositionSnake = Width / 2;
	VerticalPositionSnake = Height / 2;
	HorizontalPositionFruit = rand() % Width;
	VerticalPositionFruit = rand() % Height;
	Score = 0;
	SnakeXCoordinates[100];
	SnakeYCoordinates[100];
}
// creating a map container where snake and fruit appears 
void Map()
{
	system("cls");
	SetConsoleTextAttribute(hConsole, 180);
	for (int RowCounter = 0; RowCounter < Width + 2; RowCounter++)
		cout << "#";
		cout << endl;
		for (int RowCounter = 0; RowCounter < Height; RowCounter++)
		{
			for (int ColumnCounter = 0; ColumnCounter < Width; ColumnCounter++)
			{
				if (ColumnCounter == 0)
					cout << "#";
				if (RowCounter == VerticalPositionSnake && ColumnCounter == HorizontalPositionSnake)
					cout << "0";
				else if (RowCounter == VerticalPositionFruit && ColumnCounter == HorizontalPositionFruit)
					cout << "X";
				else
				{
					bool Print = false;
					for (int TailSegmentIndex = 0; TailSegmentIndex < NumberOfSegments; TailSegmentIndex++)
					{
						if (SnakeXCoordinates[TailSegmentIndex] == ColumnCounter && SnakeYCoordinates[TailSegmentIndex] == RowCounter)
						{
							cout << "o";
							Print = true;
						}
					}
					if (!Print)
						cout << " ";
				}
				if (ColumnCounter == Width - 1)
					cout << "#";
			}
			cout << endl;
		}
		for (int RowCounter = 0; RowCounter < Width + 2; RowCounter++)
			cout << "#";
		cout << endl;
		cout << "Score is " << Score << endl;
}
// managing input of keyboard to control snake 
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			direction = LEFT;
			break;
		case 'd':
			direction = RIGHT;
			break;
		case 'w':
			direction = UP;
			break;
		case 's':
			direction = DOWN;
			break;
		case 'x':
			Game = false;
			break;
		case 'r':
			direction = STOP;
			Welcome();
			break;
		default:
			break;
		}
	}
}
// logic how snake should grow in size and when game stops 
void Logic()
{
	int PreviousHorizontalPosition = SnakeXCoordinates[0];
	int PreviousVerticalPosition = SnakeYCoordinates[0];
	int PreviousHorizontalPosition2, PreviousVerticalPosition2;
	SnakeXCoordinates[0] = HorizontalPositionSnake;
	SnakeYCoordinates[0] = VerticalPositionSnake;
	for (int Counter = 1; Counter < NumberOfSegments; Counter++)
	{
		PreviousHorizontalPosition2 = SnakeXCoordinates[Counter];
		PreviousVerticalPosition2 = SnakeYCoordinates[Counter];
		SnakeXCoordinates[Counter] = PreviousHorizontalPosition;
		SnakeYCoordinates[Counter] = PreviousVerticalPosition;
		PreviousHorizontalPosition = PreviousHorizontalPosition2;
		PreviousVerticalPosition = PreviousVerticalPosition2;
	}
	switch (direction)
	{
	case UP:
		VerticalPositionSnake--;
		break;
	case DOWN:
		VerticalPositionSnake++;
		break;
	case LEFT:
		HorizontalPositionSnake--;
		break;
	case RIGHT:
		HorizontalPositionSnake++;
		break;
	default:
		break;
	}
	if (HorizontalPositionSnake >= Width)
		HorizontalPositionSnake = 0;
	else if (HorizontalPositionSnake < 0)
		HorizontalPositionSnake = Width - 1;
	if (VerticalPositionSnake >= Height)
		VerticalPositionSnake = 0;
	else if (VerticalPositionSnake < 0)
		VerticalPositionSnake = Height - 1;
	for (int Counter = 0; Counter < NumberOfSegments; Counter++)
	{
		if (SnakeXCoordinates[Counter] == HorizontalPositionSnake && SnakeYCoordinates[Counter] == VerticalPositionSnake)
		{
			LostGame();
		}
	}
	if (HorizontalPositionSnake == HorizontalPositionFruit && VerticalPositionSnake == VerticalPositionFruit)
	{
		Score += 1;
		NumberOfSegments++;
		HorizontalPositionFruit = rand() % Width;
		VerticalPositionFruit = rand() % Height;
	}
}
// condition when a player wins 
void Win()
{
	if (Score == 100)
	{
		system("cls");
		cout << endl << endl << endl << endl << endl;
		cout << "                                ";
		cout << "Congratulations you won the game " << endl;
		cout << endl;
		cout << "                                ";
		cout << "To go back please enter any key" << endl;
		char Back;
		cin >> Back;
		if (Back)
		{
			Welcome();
			Game = false;
		}
	}
}
// starting game 
void StartGame()
{
	Init();
	while (Game)
	{
		Map();
		Input();
		Logic();
		Win();
		Sleep(10);
	}
}
void Welcome()
{
	system("cls");
	cout << endl << endl << endl << endl << endl << endl << endl;
	cout << "                                              ";
	cout << "Welcome to the snake game!" << endl;
	cout << "                          " << "1. If you want to start game press 1" << endl;
	cout << "                          " << "2. To see instruction press 2" << endl;
	cout << "                          " << "3. To see record press 3" << endl;
	char Choice;
	cin >> Choice;
	switch (Choice)
	{
	case '1':
		system("cls");
		StartGame();
		break;
	case '2':
		Instructions();
		break;
	case '3':
		Record();
		break;
	default:
		IncorrectChoice();
		break;
	}
}
void Instructions()
{
	system("cls");
	cout << endl << endl << endl << endl << endl << endl << endl;
	cout << "                           ";
	cout << "Welcome to the snake game!" << endl;
	cout << endl;
	cout << "                           " << "here are Instructions" << endl;
	cout << "                           " << "1. If you reach current record you won the game" << endl;
	cout << endl;
	cout << "                           " << "2. when you grow up in size you cannot touch yourself, " << endl << "                                          " << "if you touch you will lose the game" << endl;
	cout << endl;
	cout << "                           " << "3. when you grow up in size you cannot touch yourself, " << endl << "                                          " << "if you move backwards when you body is backward" << endl << "                              " << "you automatically lose the game" << endl;
	cout << endl;
	char Back;
	cout << "                           " << "To go back press any key" << endl;
	cin >> Back;
	if (Back)
		Welcome();
}
void Record()
{
	system("cls");
	cout << endl << endl << endl << endl << endl << endl << endl;
	cout << "                             ";
	cout << "Welcome to the snake game!" << endl;
	cout << endl;
	cout << "                             " << "Current record is 100" << endl;
	cout << endl;
	cout << "                             " << "If you reach 100 you will win the game" << endl;
	char Back;
	cout << endl;
	cout << "                             " << "To go back press any key" << endl;
	cin >> Back;
	if (Back)
		Welcome();
}
void IncorrectChoice()
{
	cout << "Please try again next time" << endl;
	cout << endl;
	char Back;
	cout << "To go back press any key" << endl;
	cin >> Back;
	if (Back)
		Welcome();
}
void LostGame()
{
	Game = false;
	system("cls");
	cout << endl << endl << endl << endl << endl << endl << endl;
	cout << "                                  ";
	cout << "sorry you lost the game " << endl;
	cout << "                        " << "Your score was " << Score << endl;
	cout << "                        ";
	cout << "To go back press any button" << endl;
	char Back;
	cin >> Back;
	if (Back)
	{
		Game = false;
		Welcome();
	}
}
int main()
{
	SetConsoleTextAttribute(hConsole, 116);
	Welcome();
	return 0;
}
