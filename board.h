#ifndef _BOARD_H_
#define _BOARD_H_
#include <iostream>
#include <sstream>
#include <string>

const int BOARDWIDTH = 10;
const int BOARDHEIGHT = 18;

class Cell;
class Block;
class TextDisplay;
class Xwindow;

class Board {
  Cell** theBoard;
  Block* next;
  int level;
  int score;
  TextDisplay *td;
  Xwindow *w;

  static int hiscore;

  public:
	Board(bool graphics);
	~Board();
	void init();
	Cell** getTheBoard(); //returns the 2D array of cells
	Block* getNext(); //returns the next block to be played
	TextDisplay * getTD();
	Xwindow * getWindow();
	void setNext(Block* newnext); //sets the next block
	void lineScoreUpdate(int lines); //updates the score when lines cleared
	void blockScoreUpdate(int blockLevel); //updates block score
	int getLevel(); // returns the current level
	void setLevel(int level); //sets the current level
	bool linefull(int row); //returns true if row full, else false
	void clearline(int row); // clears the row
	void setHiscore(); //sets the new high score
	friend std::ostream &operator<<(std::ostream &out, const Board &b);
};


#endif
