
#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <vector>
#include <random>

class MineSweeper
{
public:
	MineSweeper(int x,int y,int mines);
	
	[[nodiscard]] char getGameCell(int x,int y);									//access game_field
	[[nodiscard]] int getX() const {return x_;}
	[[nodiscard]] int getY() const {return y_;}
	[[nodiscard]] int getMines() const {return mines_;}
	[[nodiscard]] int getInitMines() const {return init_mines_;}
	[[nodiscard]] int getOpenCells() const {return open_cells_;}
	[[nodiscard]] bool getGameState() const { return !game_lost; }
	
	void setFlag(int x, int y);
	void removeFlag(int x, int y);
	
	void openCell(int x, int y);
	
	bool checkWon();
	
	std::vector<std::vector<char>> play_field;							//field used by player '*'- Mine 'F'- Flag '='- Mine + Flag 'O'- Opened Cell
private:
	
	void open_neighbors(int,int);								//opens neighbours of cell if it's value equal to flag's count
	void open_null_neighbors(int,int);							//opens neighbours of cell if it's value is 0
	//TODO: functions could be united
	
	void open_mines();											//opens mines if game lost
	
	int rand_int(int from,int to);								//generate random int in [from:to]
	std::mt19937 random_device;										//random device for generating game field
	
	bool game_lost =false;											
	bool game_won =false;
	//TODO: implement better game state system
	
	int x_=9,y_=9,
		mines_=10,init_mines_=10,								//mines_ is count of remaining mines, init_mines_ doesn't change from the game started
		open_cells_ = 0;
	
	std::vector<std::vector<char>> game_field;							//2D array that contains field with mines and info about mines count
};

#endif // MINESWEEPER_H
