#include <ctime>

#include "minesweeper.h"

int MineSweeper::rand_int(const int from, const int to)
{
	const std::uniform_int_distribution uid(from, to);
	return uid(random_device);
}

MineSweeper::MineSweeper(const int x, const int y, const int mines)
{
	x_ = x;
	y_ = y;
	mines_ = mines;
	init_mines_ = mines;
	
	random_device.seed(time(nullptr));	//time is seed for random device
	
	for (int i = 0; i < x; i++)
		game_field.emplace_back(y, 0);		

	play_field = game_field;

	//randomly placing mines
	for (auto n = init_mines_; n != 0;)
	{
		char& cell = game_field[rand_int(0, x - 1)][rand_int(0, y - 1)];
		if (cell == '*')
			continue;
		cell = '*';
	}

	//generate info about mines around each cell
	for (int i = 0; i < x; i++)
		for (int j = 0; j < y; j++)
			if (game_field[i][j] == '*')
			{
				for (int a = -1; a <= 1; a++)
					for (int b = -1; b <= 1; b++)
					{
						if ((a == 0 && b == 0) || (i + a == x_ || j + b == y_ || i + a == -1 || j + b == -1)) //check bounds and cell itself
							continue;
						if (game_field[i + a][j + b] == '*')
							continue;

						game_field[i + a][j + b] += 1;
					}
			}
}

char MineSweeper::getGameCell(const int x, const int y)
{
	if (x > x_ || y > y_ || x < 0 || y < 0)
		return '?';							//garbage input = garbage out
	return game_field[x][y];
}

void MineSweeper::setFlag(const int x, const int y)
{
	if (mines_ == 0 || game_lost || (x > x_ || y > y_ || x < 0 || y < 0))
		return;
	if (play_field[x][y] != 'O')
	{
		play_field[x][y] = 'F';
		mines_--;
	}
}

void MineSweeper::removeFlag(const int x, const int y)
{
	if (game_lost || (x > x_ || y > y_ || x < 0 || y < 0))
		return;
	if (play_field[x][y] == 'F')
	{
		play_field[x][y] = 0;
		mines_++;
	}
}

void MineSweeper::openCell(const int x, const int y)
{
	if (game_lost || (x > x_ || y > y_ || x < 0 || y < 0))
		return;

	if (play_field[x][y] != 'F' && play_field[x][y] != '=' && game_field[x][y] == '*')
	{
		game_lost = true;
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
open_neighbors(x, y);
	
}

bool MineSweeper::checkWon()
{
	if (x_ * y_ - init_mines_ == open_cells_)
		game_won = true;
	return game_won;
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

void MineSweeper::open_neighbors(int x, int y)
{
	const int cell = game_field[x][y];
	int flag_count = 0;
	for (int a = -1; a <= 1; a++)
		for (int b = -1; b <= 1; b++)
		{
			if ((a == 0 && b == 0) || (x + a == x_ || y + b == y_ || x + a == -1 || y + b == -1))
				continue;

			if (play_field[x + a][y + b] == 'F') flag_count++;
		}
	if (cell == flag_count)
	{
		for (int a = -1; a <= 1; a++)
			for (int b = -1; b <= 1; b++)
			{
				if ((a == 0 && b == 0) || (x + a == x_ || y + b == y_ || x + a == -1 || y + b == -1))
					continue;
				if (play_field[x + a][y + b] != 'O'&&play_field[x + a][y + b] != 'F')
					openCell(x + a, y + b);
			}
	}
}
