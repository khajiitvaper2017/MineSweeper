
#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <vector>
#include <random>
using namespace std;
class MineSweeper
{
public:
	MineSweeper(int,int,int);
	char field(int,int);
	int getX() const {return x_;}
	int getY() const {return y_;}
	int getMines() const {return mines_;}
	int getInitMines() const {return init_mines_;}
	int getOpenCells() const {return open_cells_;}
	bool getGameState() const { return !failed; }
	bool setFlag(int,int);
	bool removeFlag(int,int);
	bool openCell(int,int);
	bool checkWon();
	vector<vector<char>> play_field;
private:
	void open_neighbors(int,int);
	void open_mines();
	void open_null_neighbors(int,int);
	int rand_int(int,int);
	bool failed =false;
	bool won =false;
	int x_=9,
	y_=9,
	mines_=10,
	init_mines_=10,
	open_cells_=0;
	mt19937 random_device;
	vector<vector<char>> game_field;
};

#endif // MINESWEEPER_H
