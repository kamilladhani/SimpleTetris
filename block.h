#ifndef __BLOCK_H__
#define __BLOCK_H__

const int MAXCELLS = 4;

class Cell;
class Board;

class Block {
	char type;
	int level, dir, numcells;
	Board * b;
	Cell * cells[4];

	char generate(int level); //generates a block
	void setCells(); // Sets the pointer *b, (allows block to appear on board)
	bool canMove(std::string dir); //checks if a block can move
	
	//private rotate methods
	void rotateI(bool clockwise);
	void rotateJ(bool clockwise);
	void rotateL(bool clockwise);
	void rotateO(bool clockwise);
	void rotateS(bool clockwise);
	void rotateZ(bool clockwise);
	void rotateT(bool clockwise);
	public:
		Block(int level, Board * b, char type);
		~Block();
		int getLevel(); //gets the level that the block was introduced at
		int getNumCells(); //gets the number of cells still in the block
		void setNumCells(int num); //sets the new number of cells in the block
		Cell ** getCells(); //gets the array of cells in block
		bool setCellBlockPointer(); //returns false if player loses, else true
		char getType(); //gets the block type
		void drop(); //drops the block
		void down(bool clearcells, bool replacecells); //moves block down
		void left(bool clearcells, bool replacecells); //moves block left
                void right(bool clearcells, bool replacecells); //moves block right
		void rotatec();//rotates block clockwise
		void rotatecc(); //rotates block counterclockwise
		friend std::ostream &operator<<(std::ostream &out, const Block &b);
};
				
#endif
