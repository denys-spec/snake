#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
using namespace std;

int board[17][17];
int apples = 0;
int snake_body_i[100];
int snake_body_j[100];
int applei, applej;

void ShowBoard();
void EatApple();

int k;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

int main()
{
	cout << "press [enter] to play snake\n";

	char input;

	input = _getch();

	if (input == '\r') {

		int i, j, game, snakei, snakej, taili, tailj;
		game = 1;

		snakei = 8;
		snakej = 4;

		char lastinput;

		Sleep(500);

		ShowBoard();
		input = _getch();

		srand(time(NULL));

		applei = rand() % 15 + 1;
		applej = rand() % 15 + 1;

		board[applei][applej] = 3;

		k = 0;

		snake_body_i[k] = snakei;
		snake_body_j[k] = snakej;
		//k++;

		input = _getch();

		while (game)
		{
			if (_kbhit()) {
				lastinput = input;
				input = _getch();
				if (input == 'w' && lastinput == 's')
					input = 's';
				if (input == 'a' && lastinput == 'd')
					input = 'd';
				if (input == 's' && lastinput == 'w')
					input = 'w';
				if (input == 'd' && lastinput == 'a')
					input = 'a';
			}

			for (i = k; i > 0; i--)
			{
				snake_body_i[i] = snake_body_i[i - 1];
				snake_body_j[i] = snake_body_j[i - 1];
			}

			if (input == 'w')
			{
				snake_body_i[0]--;
			}

			if (input == 's')
			{
				snake_body_i[0]++;
			}

			if (input == 'a')
			{
				snake_body_j[0]--;
			}

			if (input == 'd')
			{
				snake_body_j[0]++;
			}

			if (board[snake_body_i[0]][snake_body_j[0]] == 2 || board[snake_body_i[0]][snake_body_j[0]] == 1) {
				SetConsoleTextAttribute(console, 64);
				cout << " You lose!";
				SetConsoleTextAttribute(console, 7);
				return 0;
			}

			if (snake_body_i[0] == applei && snake_body_j[0] == applej)
			{
				EatApple();
				k++;
			}

			system("CLS");

			ShowBoard();
			cout << k << ' ';
			for (i = 0; i < k; i++)
			{
				cout << "=";
			}
			cout << "o~";

			Sleep(100);
		}
	}
}

void EatApple() 
{
	do {
		applei = rand() % 10 + 1;
		applej = rand() % 10 + 1;
	} while (board[applei][applej] == 2);

	board[applei][applej] = 3;
}

void ShowBoard()
{
	int i, j;
	for (i = 0; i <= 16; i++)
	{
		board[i][0] = 1;
		board[i][16] = 1;
		board[0][i] = 1;
		board[16][i] = 1;
	}
	for (i = 1; i < 16; i++)
	{
		for (j = 1; j < 16; j++)
		{
			if (board[i][j] % 2 == 0)
				board[i][j] = 0;
		}
	}
	board[snake_body_i[0]][snake_body_j[0]] = 4;
	for (i = 1; i <= k; i++)
	{
		board[snake_body_i[i]][snake_body_j[i]] = 2;
	}
	for (i = 0; i <= 16; i++)
	{
		for (j = 0; j <= 16; j++)
		{
			char o;

			SetConsoleTextAttribute(console, 7);
			o = ' ';
			if (board[i][j] == 1) {
				SetConsoleTextAttribute(console, 14);
				o = '=';
			}
			if (board[i][j] == 2) {
				SetConsoleTextAttribute(console, 10);
				o = '_';
			}
			if (board[i][j] == 3) {
				SetConsoleTextAttribute(console, 12);
				o = '@';
			}
			if (board[i][j] == 4) {
				SetConsoleTextAttribute(console, 10);
				o = 'o';
			}
			cout << o << ' ';
		}
		cout << '\n';
	}
}