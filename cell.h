#ifndef _CELL_H_
#define _CELL_H_

class TextDisplay;
class Xwindow;
class Block;

class Cell {
  int r, c, x, y, width, height;
  Block* b;
  public:
  	Cell();
	int getRow(); //gets the row r
  	int getCol(); //gets the column c
	void setCoords(int c, int r); //sets coordinates c and r
	void setGraphics(int x, int y, int width, int height); //sets graphics fields
  	Block* getB(); //gets the block pointer (which block the cell is a part of)
  	void setB(Block *b); // sets the new block pointer
  	void notifyTDisplay(TextDisplay &td); // notifies the textdisplay
  	void notifyGDisplay(Xwindow *w); // notifies the graphics display
};

#endif 
