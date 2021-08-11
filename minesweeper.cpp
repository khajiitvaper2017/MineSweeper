#include <ctime>

#include "minesweeper.h"

int MineSweeper::rand_int(const int from, const int to)
{
	const uniform_int_distribution<int> uid(from, to);
	return uid(random_device);
}

MineSweeper::MineSweeper(const int x, const int y, const int mines)
{
	x_ = x;
	y_ = y;
	mines_ = mines;
	init_mines_ = mines;
	random_device.seed(time(nullptr));
	for (int i = 0; i < x; i++)
		game_field.emplace_back(y, 0);

	play_field = game_field;
	auto mines_push = mines;
	while (mines_push != 0)
	{
		char& cell = game_field[rand_int(0, x - 1)][rand_int(0, y - 1)];
		if (cell == '*')
			continue;
		cell = '*';
		mines_push--;
	}

	for (int i = 0; i < x; i++)
		shuffle(game_field[i].begin(), game_field[i].end(), random_device);


	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			if (game_field[i][j] == '*')
			{
				for (int a = -1; a <= 1; a++)
					for (int b = -1; b <= 1; b++)
					{
						if ((a == 0 && b == 0) || ((i + a) == x_ || (j + b) == y_ || (i + a) == -1 || (j + b) == -1))
							continue;
						if (game_field[i + a][j + b] == '*')
							continue;

						game_field[i + a][j + b] += 1;
					}
			}
		}
	}
}

char MineSweeper::field(int x, int y)
{
	if (x > x_ || y > y_ || x < 0 || y < 0)
		return '?';
	return game_field[x][y];
}

bool MineSweeper::setFlag(int x, int y)
{
	if (failed)return failed;
	if (x > x_ || y > y_ || x < 0 || y < 0) return failed;
	if (mines_ == 0)return failed;
	if (play_field[x][y] != 'O')
	{
		play_field[x][y] = 'F';
		mines_--;
	}
	return failed;
}

bool MineSweeper::removeFlag(int x, int y)
{
	if (failed)return failed;
	if (x > x_ || y > y_ || x < 0 || y < 0) return failed;
	if (play_field[x][y] == 'F')
	{
		play_field[x][y] = 0;
		mines_++;
	}
	return failed;
}

bool MineSweeper::openCell(int x, int y)
{
	if (failed)return failed;
	if (x > x_ || y > y_ || x < 0 || y < 0)
		return failed;

	if ((play_field[x][y] != 'F' && play_field[x][y] != '=') && game_field[x][y] == '*')
	{
		failed = true;
		open_mines();
	}
	else if (play_field[x][y] == 'O')
		open_neighbors(x, y);
	else
	{
		play_field[x][y] = 'O';
		open_cells_++;
	}
	if (game_field[x][y] == 0)
		open_null_neighbors(x, y);

	return failed;
}

bool MineSweeper::checkWon()
{
	if (x_ * y_ - init_mines_ == open_cells_)
		won = true;
	return won;
}

void MineSweeper::open_mines()
{
	for (int i = 0; i < x_; i++)
	{
		for (int j = 0; j < y_; j++)
		{
			if (game_field[i][j] == '*' && play_field[i][j] == 'F')
				play_field[i][j] = '=';
			else if (game_field[i][j] == '*')
				play_field[i][j] = '*';
		}
	}
}

void MineSweeper::open_null_neighbors(int x, int y)
{
	for (int a = -1; a <= 1; a++)
		for (int b = -1; b <= 1; b++)
		{
			if ((a == 0 && b == 0) || ((x + a) == x_ || (y + b) == y_ || (x + a) == -1 || (y + b) == -1))
				continue;
			if (play_field[x + a][y + b] == 'O')
				continue;
			if (play_field[x + a][y + b] == 'F')
			{
				play_field[x + a][y + b] = 0;
				mines_++;
			}
			openCell(x + a, y + b);
		}
}

void MineSweeper::open_neighbors(int x, int y)
{
	const int cell = game_field[x][y];
	int flag_count = 0;
	for (int a = -1; a <= 1; a++)
		for (int b = -1; b <= 1; b++)
		{
			if ((a == 0 && b == 0) || ((x + a) == x_ || (y + b) == y_ || (x + a) == -1 || (y + b) == -1))
				continue;

			if (play_field[x + a][y + b] == 'F') flag_count++;
		}
	if (cell == flag_count && cell != 0)
	{
		for (int a = -1; a <= 1; a++)
			for (int b = -1; b <= 1; b++)
			{
				if ((a == 0 && b == 0) || ((x + a) == x_ || (y + b) == y_ || (x + a) == -1 || (y + b) == -1))
					continue;
				if (play_field[x + a][y + b] != 'O' && play_field[x + a][y + b] != 'F')
					openCell(x + a, y + b);
			}
	}
}
