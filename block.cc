#include <iostream>
#include <cstdlib>
#include "board.h"
#include "cell.h"
#include "block.h"
using namespace std;

char Block::generate(int level) {
	char type;
	int rnum, random;
	if (level == 1) {
		random = rand() % 12;
		if (random > 9) {
			rnum = 6;
		} else if (random > 8) {
			rnum = 5;
		} else if (random > 7) {
			rnum = 4;
		} else if (random > 5) {
			rnum = 3;
		} else if (random > 3) {
			rnum = 2;
		} else if (random > 1) {
			rnum = 1;
		} else if (random >= 0) {
			rnum = 0;
		}
	} else if (level == 2) {
		rnum = rand() % 7;
	} else if (level == 3) {
		random = rand() % 9;
                if (random > 7) {
                        rnum = 6;
                } else if (random > 5) {
                        rnum = 5;
                } else if (random > 3) {
                        rnum = 4;
                } else if (random > 2) {
                        rnum = 3;
                } else if (random > 1) {
                        rnum = 2;
                } else if (random > 0) {
                        rnum = 1;
                } else if (random == 0) {
                        rnum = 0;
                }
	}
	if (rnum == 0) {
		type = 'I';
	} else if (rnum == 1) {
		type = 'J';
	} else if (rnum == 2) {
		type = 'L';
	} else if (rnum == 3) {
		type = 'O';
	} else if (rnum == 4) {
		type = 'S';
	} else if (rnum == 5) {
                type = 'Z';
	} else if (rnum == 6) {
                type = 'T';
	}
	return type;	
}
		
void Block::setCells() {
	Cell ** board = b->getTheBoard();
	if (type == 'I') {
		cells[0] = &board[0][3];
		cells[1] = &board[1][3];
		cells[2] = &board[2][3];
                cells[3] = &board[3][3];
	} else if (type == 'J') {
                cells[0] = &board[0][3];
                cells[1] = &board[0][2];
                cells[2] = &board[1][3];
                cells[3] = &board[2][3];
        } else if (type == 'L') {
                cells[0] = &board[0][3];
                cells[1] = &board[1][3];
                cells[2] = &board[2][3];
                cells[3] = &board[2][2];
        } else if (type == 'O') {
                cells[0] = &board[0][3];
                cells[1] = &board[1][3];
                cells[2] = &board[0][2];
                cells[3] = &board[1][2];
        } else if (type == 'S') {
                cells[0] = &board[0][3];
                cells[1] = &board[1][3];
                cells[2] = &board[1][2];
                cells[3] = &board[2][2];
        } else if (type == 'Z') {
                cells[0] = &board[0][2];
                cells[1] = &board[1][3];
                cells[2] = &board[1][2];
                cells[3] = &board[2][3];
        } else if (type == 'T') {
		cells[0] = &board[0][2];
                cells[1] = &board[1][3];
                cells[2] = &board[1][2];
                cells[3] = &board[2][2];
	}
}

Block::Block(int level, Board * b, char type) : level(level), dir(0), numcells(4), b(b) {
	bool islost;
	if (level == 0) {
		this->type = type;
	} else {
		this->type = generate(level);
	}
	setCells();
}

Block::~Block() {}

int Block::getLevel() {
	return level;
}

int Block::getNumCells() {
	return numcells;
}

void Block::setNumCells(int num) {
	this->numcells = num;
}

Cell ** Block::getCells() {
	return cells;
}

char Block::getType() {
	return type;
}

bool Block::setCellBlockPointer() {
	Cell ** board = b->getTheBoard();
	TextDisplay * t = b->getTD();
	Xwindow * w = b->getWindow();
	if (type == 'I' && (board[0][3].getB() != NULL || board[1][3].getB() != NULL || board[2][3].getB() != NULL || board[3][3].getB() != NULL)) { return false; }
	else if (type == 'J' && (board[0][3].getB() != NULL || board[0][2].getB() != NULL || board[1][3].getB() != NULL || board[2][3].getB() != NULL)) { return false; }
	else if (type == 'L' && (board[0][3].getB() != NULL || board[1][3].getB() != NULL || board[2][3].getB() != NULL || board[2][2].getB() != NULL)) { return false; }
	else if (type == 'O' && (board[0][3].getB() != NULL || board[1][3].getB() != NULL || board[0][2].getB() != NULL || board[1][2].getB() != NULL)) { return false; }
	else if (type == 'S' && (board[0][3].getB() != NULL || board[1][3].getB() != NULL || board[1][2].getB() != NULL || board[2][2].getB() != NULL)) { return false; }
	else if (type == 'Z' && (board[0][2].getB() != NULL || board[1][2].getB() != NULL || board[1][3].getB() != NULL || board[2][3].getB() != NULL)) { return false; }
	else if (type == 'T' && (board[0][2].getB() != NULL || board[1][2].getB() != NULL || board[2][2].getB() != NULL || board[1][3].getB() != NULL)) { return false; }	
	for (int i = 0; i < MAXCELLS; i++) {
		cells[i]->setB(this); //sets cell to point at this block
		cells[i]->notifyTDisplay(*t); //notifies textdisplay of change
		if (w) cells[i]->notifyGDisplay(w); //if graphics on, notify graphicsdisplay
	}
	return true;
}
	
void Block::rotateI(bool clockwise) {
	Cell ** board = b->getTheBoard();
	if (clockwise) {
		if (dir == 0 || dir == 2) {
                	cells[1] = &board[cells[1]->getCol()-1][cells[1]->getRow()-1];
                	cells[2] = &board[cells[2]->getCol()-2][cells[2]->getRow()-2];
                	cells[3] = &board[cells[3]->getCol()-3][cells[3]->getRow()-3];
			dir++;			
		} else if (dir == 1 || dir == 3) {
			cells[1] = &board[cells[1]->getCol()+1][cells[1]->getRow()+1];
                        cells[2] = &board[cells[2]->getCol()+2][cells[2]->getRow()+2];
                        cells[3] = &board[cells[3]->getCol()+3][cells[3]->getRow()+3];
			if (dir == 3) { dir = 0; }
			else { dir++; }
		}
	} else {
		if (dir == 0 || dir == 2) {
                        cells[1] = &board[cells[1]->getCol()-1][cells[1]->getRow()-1];
                        cells[2] = &board[cells[2]->getCol()-2][cells[2]->getRow()-2];
                        cells[3] = &board[cells[3]->getCol()-3][cells[3]->getRow()-3];
                        if (dir == 0) { dir = 3; }
			else { dir--; }
                } else if (dir == 1 || dir == 3) {
                        cells[1] = &board[cells[1]->getCol()+1][cells[1]->getRow()+1];
                        cells[2] = &board[cells[2]->getCol()+2][cells[2]->getRow()+2];
                        cells[3] = &board[cells[3]->getCol()+3][cells[3]->getRow()+3];
                        dir--;
		}
	}
}

void Block::rotateJ(bool clockwise) {
	Cell ** board = b->getTheBoard();
        if (clockwise) {
                if (dir == 0) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()];
                        cells[1] = &board[cells[1]->getCol()][cells[1]->getRow()];
                        cells[2] = &board[cells[2]->getCol()-1][cells[2]->getRow()-2];
                        cells[3] = &board[cells[3]->getCol()-1][cells[3]->getRow()-2];
                        dir++;
                } else if (dir == 1) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()-1];
                        cells[1] = &board[cells[1]->getCol()+1][cells[1]->getRow()];
                        cells[2] = &board[cells[2]->getCol()+2][cells[2]->getRow()+2];
                        cells[3] = &board[cells[3]->getCol()+1][cells[3]->getRow()+1];
                        dir++;
                } else if (dir == 2) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()+1];
                        cells[1] = &board[cells[1]->getCol()][cells[1]->getRow()+1];
                        cells[2] = &board[cells[2]->getCol()-1][cells[2]->getRow()-1];
                        cells[3] = &board[cells[3]->getCol()-1][cells[3]->getRow()-1];
                        dir++;
                } else if (dir == 3) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()];
                        cells[1] = &board[cells[1]->getCol()-1][cells[1]->getRow()-1];
                        cells[2] = &board[cells[2]->getCol()][cells[2]->getRow()+1];
                        cells[3] = &board[cells[3]->getCol()+1][cells[3]->getRow()+2];
                        dir = 0;
                }
        } else {
                if (dir == 0) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()];
                        cells[1] = &board[cells[1]->getCol()+1][cells[1]->getRow()+1];
                        cells[2] = &board[cells[2]->getCol()][cells[2]->getRow()-1];
                        cells[3] = &board[cells[3]->getCol()-1][cells[3]->getRow()-2];
                        dir = 3;
                } else if (dir == 1) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()];
                        cells[1] = &board[cells[1]->getCol()][cells[1]->getRow()];
                        cells[2] = &board[cells[2]->getCol()+1][cells[2]->getRow()+2];
                        cells[3] = &board[cells[3]->getCol()+1][cells[3]->getRow()+2];
                        dir--;
                } else if (dir == 2) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()+1];
                        cells[1] = &board[cells[1]->getCol()-1][cells[1]->getRow()];
                        cells[2] = &board[cells[2]->getCol()-2][cells[2]->getRow()-2];
                        cells[3] = &board[cells[3]->getCol()-1][cells[3]->getRow()-1];
                        dir--;
                } else if (dir == 3) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()-1];
                        cells[1] = &board[cells[1]->getCol()][cells[1]->getRow()-1];
                        cells[2] = &board[cells[2]->getCol()+1][cells[2]->getRow()+1];
                        cells[3] = &board[cells[3]->getCol()+1][cells[3]->getRow()+1];
                        dir--;
                }
        }
}

void Block::rotateL(bool clockwise) {
	Cell ** board = b->getTheBoard();
        if (clockwise) {
                if (dir == 0) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()];
                        cells[1] = &board[cells[1]->getCol()-1][cells[1]->getRow()-1];
                        cells[2] = &board[cells[2]->getCol()-2][cells[2]->getRow()-2];
                        cells[3] = &board[cells[3]->getCol()-1][cells[3]->getRow()+1];
                        dir++;
                } else if (dir == 1) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()];
                        cells[1] = &board[cells[1]->getCol()][cells[1]->getRow()];
                        cells[2] = &board[cells[2]->getCol()+1][cells[2]->getRow()+1];
                        cells[3] = &board[cells[3]->getCol()+1][cells[3]->getRow()-1];
                        dir++;
                } else if (dir == 2) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()-2];
                        cells[1] = &board[cells[1]->getCol()+1][cells[1]->getRow()+1];
                        cells[2] = &board[cells[2]->getCol()][cells[2]->getRow()];
                        cells[3] = &board[cells[3]->getCol()-1][cells[3]->getRow()-1];
                        dir++;
                } else if (dir == 3) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()+2];
                        cells[1] = &board[cells[1]->getCol()][cells[1]->getRow()];
                        cells[2] = &board[cells[2]->getCol()+1][cells[2]->getRow()+1];
                        cells[3] = &board[cells[3]->getCol()+1][cells[3]->getRow()+1];
                        dir = 0;
                }
        } else {
                if (dir == 0) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()-2];
                        cells[1] = &board[cells[1]->getCol()][cells[1]->getRow()];
                        cells[2] = &board[cells[2]->getCol()-1][cells[2]->getRow()-1];
                        cells[3] = &board[cells[3]->getCol()-1][cells[3]->getRow()-1];
                        dir = 3;
                } else if (dir == 1) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()];
                        cells[1] = &board[cells[1]->getCol()+1][cells[1]->getRow()+1];
                        cells[2] = &board[cells[2]->getCol()+2][cells[2]->getRow()+2];
                        cells[3] = &board[cells[3]->getCol()+1][cells[3]->getRow()-1];
                        dir--;
                } else if (dir == 2) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()];
                        cells[1] = &board[cells[1]->getCol()][cells[1]->getRow()];
                        cells[2] = &board[cells[2]->getCol()-1][cells[2]->getRow()-1];
                        cells[3] = &board[cells[3]->getCol()-1][cells[3]->getRow()+1];
                        dir--;
                } else if (dir == 3) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()+2];
                        cells[1] = &board[cells[1]->getCol()-1][cells[1]->getRow()-1];
                        cells[2] = &board[cells[2]->getCol()][cells[2]->getRow()];
                        cells[3] = &board[cells[3]->getCol()+1][cells[3]->getRow()+1];
                        dir--;
                }
        }
}

void Block::rotateS(bool clockwise) {
	Cell ** board = b->getTheBoard();
        if (clockwise) {
                if (dir == 0 || dir == 2) {
			cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()-1];
                        cells[1] = &board[cells[1]->getCol()-1][cells[1]->getRow()-2];
                        cells[2] = &board[cells[2]->getCol()][cells[2]->getRow()+1];
                        cells[3] = &board[cells[3]->getCol()-1][cells[3]->getRow()];
                        dir++;
                } else if (dir == 1 || dir == 3) {
			cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()+1];
                        cells[1] = &board[cells[1]->getCol()+1][cells[1]->getRow()+2];
                        cells[2] = &board[cells[2]->getCol()][cells[2]->getRow()-1];
                        cells[3] = &board[cells[3]->getCol()+1][cells[3]->getRow()];
                        if (dir == 3) { dir = 0; }
                        else { dir++; }
                }
        } else {
                if (dir == 0 || dir == 2) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()-1];
                        cells[1] = &board[cells[1]->getCol()-1][cells[1]->getRow()-2];
                        cells[2] = &board[cells[2]->getCol()][cells[2]->getRow()+1];
                        cells[3] = &board[cells[3]->getCol()-1][cells[3]->getRow()];
			if (dir == 0) { dir = 3; }
                        else { dir--; }
                } else if (dir == 1 || dir == 3) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()+1];
                        cells[1] = &board[cells[1]->getCol()+1][cells[1]->getRow()+2];
                        cells[2] = &board[cells[2]->getCol()][cells[2]->getRow()-1];
                        cells[3] = &board[cells[3]->getCol()+1][cells[3]->getRow()];
			dir--;
                }
        }
}

void Block::rotateZ(bool clockwise) {
        Cell ** board = b->getTheBoard();
        if (clockwise) {
                if (dir == 0 || dir == 2) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()+1];
                        cells[1] = &board[cells[1]->getCol()-1][cells[1]->getRow()-1];
                        cells[2] = &board[cells[2]->getCol()][cells[2]->getRow()];
                        cells[3] = &board[cells[3]->getCol()-1][cells[3]->getRow()-2];
                        dir++;
                } else if (dir == 1 || dir == 3) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()-1];
                        cells[1] = &board[cells[1]->getCol()+1][cells[1]->getRow()+1];
                        cells[2] = &board[cells[2]->getCol()][cells[2]->getRow()];
                        cells[3] = &board[cells[3]->getCol()+1][cells[3]->getRow()+2];
                        if (dir == 3) { dir = 0; }
                        else { dir++; }
                }
        } else {
                if (dir == 0 || dir == 2) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()+1];
                        cells[1] = &board[cells[1]->getCol()-1][cells[1]->getRow()-1];
                        cells[2] = &board[cells[2]->getCol()][cells[2]->getRow()];
                        cells[3] = &board[cells[3]->getCol()-1][cells[3]->getRow()-2];
			if (dir == 0) { dir = 3; }
                        else { dir--; }
                } else if (dir == 1 || dir == 3) {
			cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()-1];
                        cells[1] = &board[cells[1]->getCol()+1][cells[1]->getRow()+1];
                        cells[2] = &board[cells[2]->getCol()][cells[2]->getRow()];
                        cells[3] = &board[cells[3]->getCol()+1][cells[3]->getRow()+2];
			dir--;
                }
        }
}

void Block::rotateO(bool clockwise) {
	if (clockwise) {
		if (dir == 3) { dir = 0; }
		else { dir++; }
	} else {
		if (dir == 0) { dir = 3; }
                else { dir--; }
	}
}

void Block::rotateT(bool clockwise) {
	Cell ** board = b->getTheBoard();
        if (clockwise) {
                if (dir == 0) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()];
                        cells[1] = &board[cells[1]->getCol()][cells[1]->getRow()];
                        cells[2] = &board[cells[2]->getCol()][cells[2]->getRow()];
                        cells[3] = &board[cells[3]->getCol()-1][cells[3]->getRow()-1];
			dir++;
                } else if (dir == 1) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()+1];
                        cells[1] = &board[cells[1]->getCol()][cells[1]->getRow()];
                        cells[2] = &board[cells[2]->getCol()][cells[2]->getRow()];
                        cells[3] = &board[cells[3]->getCol()+1][cells[3]->getRow()+2];
			dir++;
                } else if (dir == 2) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()];
                        cells[1] = &board[cells[1]->getCol()-1][cells[1]->getRow()-1];
                        cells[2] = &board[cells[2]->getCol()-1][cells[2]->getRow()-1];
                        cells[3] = &board[cells[3]->getCol()-1][cells[3]->getRow()-1];
			dir++;
                } else if (dir == 3) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()-1];
                        cells[1] = &board[cells[1]->getCol()+1][cells[1]->getRow()+1];
                        cells[2] = &board[cells[2]->getCol()+1][cells[2]->getRow()+1];
                        cells[3] = &board[cells[3]->getCol()+1][cells[3]->getRow()];
			dir = 0;
                }
	} else {
                if (dir == 0) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()+1];
                        cells[1] = &board[cells[1]->getCol()-1][cells[1]->getRow()-1];
                        cells[2] = &board[cells[2]->getCol()-1][cells[2]->getRow()-1];
                        cells[3] = &board[cells[3]->getCol()-1][cells[3]->getRow()];
                        dir = 3;
                } else if (dir == 1) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()];
                        cells[1] = &board[cells[1]->getCol()][cells[1]->getRow()];
                        cells[2] = &board[cells[2]->getCol()][cells[2]->getRow()];
                        cells[3] = &board[cells[3]->getCol()+1][cells[3]->getRow()+1];
                        dir--;
                } else if (dir == 2) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()-1];
                        cells[1] = &board[cells[1]->getCol()][cells[1]->getRow()];
                        cells[2] = &board[cells[2]->getCol()][cells[2]->getRow()];
                        cells[3] = &board[cells[3]->getCol()-1][cells[3]->getRow()-2];
                        dir--;
                } else if (dir == 3) {
                        cells[0] = &board[cells[0]->getCol()][cells[0]->getRow()];
                        cells[1] = &board[cells[1]->getCol()+1][cells[1]->getRow()+1];
                        cells[2] = &board[cells[2]->getCol()+1][cells[2]->getRow()+1];
                        cells[3] = &board[cells[3]->getCol()+1][cells[3]->getRow()+1];
                        dir--;
                }
	}
}

void Block::rotatec() {
	int c, r;
	TextDisplay * t = b->getTD();
	Xwindow * w = b->getWindow();
	for (int i = 0; i < MAXCELLS; i++) {
                c = cells[i]->getCol();
                r = cells[i]->getRow();
                cells[i]->setB(NULL);
                cells[i]->notifyTDisplay(*t);
		if (w) cells[i]->notifyGDisplay(w);
	}
	if (type == 'I') {
		if ((dir == 1 || dir == 3) && cells[3]->getCol() > 6) {
			cout << "Cannot rotate!" << endl;
		} else { rotateI(true); }
	} else if (type == 'J') {
		if ((dir == 1 || dir == 3) && cells[3]->getCol() > 8) {
                        cout << "Cannot rotate!" << endl;
                } else { rotateJ(true); }
	} else if (type == 'L') {
        	if ((dir == 1 || dir == 3) && cells[3]->getCol() > 8) {
                        cout << "Cannot rotate!" << endl;
                } else { rotateL(true); }
	} else if (type == 'O') {
                rotateO(true);
        } else if (type == 'S') {
                if ((dir == 1 || dir == 3) && cells[3]->getCol() > 8) {
                        cout << "Cannot rotate!" << endl;
                } else { rotateS(true); }
        } else if (type == 'Z') {
                if ((dir == 1 || dir == 3) && cells[3]->getCol() > 8) {
                        cout << "Cannot rotate!" << endl;
                } else { rotateZ(true); }
        } else if (type == 'T') {
                if ((dir == 1 || dir == 3) && cells[3]->getCol() > 8) {
                        cout << "Cannot rotate!" << endl;
                } else { rotateT(true); }
        }
	for (int j = 0; j < MAXCELLS; j++) {
                cells[j]->setB(this);
                cells[j]->notifyTDisplay(*t);
       		if (w) cells[j]->notifyGDisplay(w); 
	}	
}

void Block::rotatecc() {
	int c, r;
        TextDisplay * t = b->getTD();
	Xwindow * w = b->getWindow();
	for (int i = 0; i < MAXCELLS; i++) {
                c = cells[i]->getCol();
                r = cells[i]->getRow();
                cells[i]->setB(NULL);
                cells[i]->notifyTDisplay(*t);
		if (w) cells[i]->notifyGDisplay(w);
	}
	if (type == 'I') {
                if ((dir == 1 || dir == 3) && cells[3]->getCol() > 6) {
                        cout << "Cannot rotate!" << endl;
		} else { rotateI(false); }
        } else if (type == 'J') {
        	if ((dir == 1 || dir == 3) && cells[3]->getCol() > 8) {
                        cout << "Cannot rotate!" << endl;
                } else { rotateJ(false); }
	} else if (type == 'L') {
                if ((dir == 1 || dir == 3) && cells[3]->getCol() > 8) {
                        cout << "Cannot rotate!" << endl;
                } else { rotateL(false); }
        } else if (type == 'O') {
                rotateO(false);
        } else if (type == 'S') {
                if ((dir == 1 || dir == 3) && cells[3]->getCol() > 8) {
                        cout << "Cannot rotate!" << endl;
                } else { rotateS(false); }
        } else if (type == 'Z') {
                if ((dir == 1 || dir == 3) && cells[3]->getCol() > 8) {
                        cout << "Cannot rotate!" << endl;
                } else { rotateZ(false); }
        } else if (type == 'T') {
                if ((dir == 1 || dir == 3) && cells[3]->getCol() > 8) {
                        cout << "Cannot rotate!" << endl;
                } else { rotateT(false); }
        }
	for (int j = 0; j < MAXCELLS; j++) {
		cells[j]->setB(this);
                cells[j]->notifyTDisplay(*t);
		if (w) cells[j]->notifyGDisplay(w);
	}		
}


bool Block::canMove(string dir) {
	Cell ** board = b->getTheBoard();
	int c, r;
	bool move = true;
	if (dir == "left") {
		for (int i = 0; i < MAXCELLS; i++) {
			c = cells[i]->getCol();
			r = cells[i]->getRow();
			if (c == 0 || (board[c-1][r].getB() != NULL && board[c-1][r].getB() != board[c][r].getB())) {
				move = false;
			}
		}
	} else if (dir == "right") {
		for (int i = 0; i < MAXCELLS; i++) {
                        c = cells[i]->getCol();
                        r = cells[i]->getRow();
                        if (c == 9 || ((board[c+1][r].getB() != NULL) && (board[c+1][r].getB() != board[c][r].getB()))) {
                                move = false;  
                        }
                }
	} else if (dir == "down") {
		for (int i = 0; i < MAXCELLS; i++) {
                        c = cells[i]->getCol();
                        r = cells[i]->getRow();
                        if (r == 17 || (board[c][r+1].getB() != NULL && board[c][r+1].getB() != board[c][r].getB())) {
                                move = false;
                        }
                }
	}
	return move;
}

void Block::left(bool clearcells, bool replacecells) {
	Cell ** board = b->getTheBoard();
	TextDisplay * t = b->getTD();
	Xwindow * w = b->getWindow();
	if (canMove("left")) {
		int c, r;
		for (int i = 0; i < MAXCELLS; i++) {
			c = cells[i]->getCol();		
			r = cells[i]->getRow();
			cells[i]->setB(NULL);
			cells[i]->notifyTDisplay(*t);
			if (clearcells) cells[i]->notifyGDisplay(w);
			cells[i] = &board[c-1][r];
			cells[i]->setB(this);
			cells[i]->notifyTDisplay(*t);
			if (replacecells) cells[i]->notifyGDisplay(w);
		}
	} else {
		cout << "Cannot move left!" << endl;
	}
}

void Block::right(bool clearcells, bool replacecells) {
	Cell ** board = b->getTheBoard();
	TextDisplay * t = b->getTD();
	Xwindow * w = b->getWindow();
	if (canMove("right")) {
                int c, r;
                for (int i = MAXCELLS-1; i>=0; i--) { //REVERSED ORDER OF CHECKING TO ENSURE CORRECT NOTIFICATION
                        c = cells[i]->getCol();
                        r = cells[i]->getRow();
			cells[i]->setB(NULL);
			cells[i]->notifyTDisplay(*t); 
                        if (clearcells) cells[i]->notifyGDisplay(w);
			cells[i] = &board[c+1][r];
                        cells[i]->setB(this);
			cells[i]->notifyTDisplay(*t);
			if (replacecells) cells[i]->notifyGDisplay(w);
                }
        } else {
                cout << "Cannot move right!" << endl;
        }
}

void Block::down(bool clearcells, bool replacecells) {
	Cell ** board = b->getTheBoard();
	TextDisplay * t = b->getTD();
	Xwindow * w = b->getWindow();
	if (canMove("down")) {
                int c, r;
                for (int i = 0; i < MAXCELLS; i++) {
                        c = cells[i]->getCol();
                        r = cells[i]->getRow();
                        cells[i]->setB(NULL);
			cells[i]->notifyTDisplay(*t);
			if (clearcells) cells[i]->notifyGDisplay(w);
                        cells[i] = &board[c][r+1];
                        cells[i]->setB(this);
			cells[i]->notifyTDisplay(*t);
			if (replacecells) cells[i]->notifyGDisplay(w);
                }
        } else {
                cout << "Cannot move down!" << endl;
        }
}

void Block::drop() {
	Xwindow * w = b->getWindow();
	if (canMove("down") && w) { down(true, false); } 
	while (canMove("down")) {
		down(false, false);
	}
	if (w) {
		for (int i = 0; i < MAXCELLS; i++) {
			cells[i]->notifyGDisplay(w);
		}
	}
}

std::ostream &operator<<(std::ostream &out, const Block &b) {
	if (b.type == 'I') {
		out << "IIII" << endl << endl;
	} else if (b.type == 'J') {
		out << "J" << endl << "JJJ" << endl;
	} else if (b.type == 'L') {
		out << "  L" << endl << "LLL" << endl;
	} else if (b.type == 'O') {
		out << "OO" << endl << "OO" << endl;
	} else if (b.type == 'S') {
		out << " SS" << endl << "SS" << endl;
	} else if (b.type == 'Z') {
		out << "ZZ" << endl << " ZZ" << endl;
	} else if (b.type == 'T') {
		out << "TTT" << endl << " T" << endl;
	}
} 
