#include <sstream>
#include "textdisplay.h"
#include "window.h"
#include "block.h"
#include "cell.h"
#include "board.h"
using namespace std;

const int CELLWIDTH = 50;
const int CELLHEIGHT = 33;

int Board::hiscore = 0;

void Board::init() {
        for (int i = 0; i < BOARDWIDTH; i++) {
                for (int j = 0; j < BOARDHEIGHT; j++) {
                        theBoard[i][j].setCoords(i, j);
                        if (w) {
                                theBoard[i][j].setGraphics(25+i*CELLWIDTH, 150+j*CELLHEIGHT, CELLWIDTH, CELLHEIGHT);
                        }
                }
        }
}

Board::Board(bool graphics) : next(NULL), w(NULL), level(0), score(0) {
	theBoard = new Cell* [BOARDWIDTH];
	for (int p=0; p<BOARDWIDTH; p++) {
                theBoard[p] = new Cell[BOARDHEIGHT];
	}
	td = new TextDisplay;
	if (graphics) {
		w = new Xwindow(700, 800);
		w->drawBigString(283, 50, "QUADRIS");
		w->fillRectangle(25, 150, 500, 594);
		stringstream hs, ls;
		hs << hiscore;
		string s = hs.str();
		w->drawString(25, 100, "HiScore: " + s);
		w->drawString(300, 100, "Score: 0");
		ls << level;
		s = ls.str();
		w->drawString(550, 100, "Level: " + s);
		w->drawString(575, 325, "Next");
	}
	init();
}

Board::~Board() {
	delete w;
	delete next;
        for (int i=0; i<BOARDWIDTH; i++) {
        	delete [] theBoard[i];
        }
	delete [] theBoard;
	delete td;
}

Cell** Board::getTheBoard() {
	return theBoard;
}

Block* Board::getNext() {
	return next;
}

TextDisplay * Board::getTD() {
	return td;
}

Xwindow * Board::getWindow() {
	return w;
}

void Board::setNext(Block* newnext) {
	this->next = newnext;
	if (w) {
		w->fillRectangle(550, 350, 120, 150, 0);
		char type = newnext->getType();
		if (type == 'I') {
			w->fillRectangle(550, 380, 120, 30, 2);
		} else if (type == 'J') {
			w->fillRectangle(580, 350, 30, 30, 3); 
			w->fillRectangle(580, 380, 90, 30, 3);
		} else if (type == 'L') {
                        w->fillRectangle(640, 350, 30, 30, 4);
                        w->fillRectangle(580, 380, 90, 30, 4);
                }  else if (type == 'O') {
                        w->fillRectangle(610, 350, 60, 30, 5);
                        w->fillRectangle(610, 380, 60, 30, 5);
                } else if (type == 'S') {
                        w->fillRectangle(580, 380, 60, 30, 6);
                        w->fillRectangle(610, 350, 60, 30, 6);
                } else if (type == 'Z') {
                        w->fillRectangle(580, 350, 60, 30, 7);
                        w->fillRectangle(610, 380, 60, 30, 7);
                } else if (type == 'T') {
                        w->fillRectangle(580, 350, 90, 30, 8);
                        w->fillRectangle(610, 380, 30, 30, 8);
                }
	}		
}

void Board::lineScoreUpdate(int lines) {
	if (lines!=0) {
		score += ((level + lines) * (level + lines));
		if (w) {
			w->fillRectangle(300, 60, 100, 40, 0);
                	stringstream ss;
                	ss << score;
                	string s = ss.str();
                	w->drawString(300, 100, "Score: " + s);
		}
	}
}

void Board::blockScoreUpdate(int blockLevel) {
	score += ((blockLevel+1)*(blockLevel+1));
	if (w) {
		w->fillRectangle(300, 60, 100, 40, 0);
        	stringstream ss;
        	ss << score;
        	string s = ss.str();
        	w->drawString(300, 100, "Score: " + s);
	}
}

int Board::getLevel() {
	return level;
}

void Board::setLevel(int level) {
	if (level>=0 && level<=3) {
		this->level=level;
		if (w) {
			w->fillRectangle(550, 60, 100, 40, 0);
			stringstream ls;
			ls << level;
			string s = ls.str();
			w->drawString(550, 100, "Level: " + s);
		}
	}
}


//main will pass each row through here to check if full.
bool Board::linefull(int row) { 
	for(int i=0; i<10; i++) {
		if (theBoard[i][row].getB() == NULL) {return false;}
	}
	return true;
}

// clears row and moves everything else down.
void Board::clearline(int row) {
	for(int i=0; i<BOARDWIDTH; i++) {
		if (theBoard[i][row].getB()->getNumCells() == 1) { 
			blockScoreUpdate(theBoard[i][row].getB()->getLevel());
			delete theBoard[i][row].getB();
		} else {
			for(int j=0; j<MAXCELLS; j++) {
				Cell** p = theBoard[i][row].getB()->getCells();
				if (p[j] == &theBoard[i][row]) {
					p[j] = NULL; 
					theBoard[i][row].getB()\
						->setNumCells(theBoard[i][row].getB()->getNumCells() - 1);
					theBoard[i][row].notifyTDisplay(*td);
				}
			}
		}
		theBoard[i][row].setB(NULL);
	}
	if (w) { w->fillRectangle(25, 150+row*CELLHEIGHT, 500, CELLHEIGHT); }
	for(int i=row-1; i>=3; i--) {
		for(int j=0; j<BOARDWIDTH; j++) {
			theBoard[j][i+1].setB(theBoard[j][i].getB());
			theBoard[j][i+1].notifyTDisplay(*td);
			if (w && (theBoard[j][i+1].getB() || theBoard[j][i+2].getB())) {
                                theBoard[j][i+1].notifyGDisplay(w);
                        }
		}
	}
}

void Board::setHiscore() {
	if (score > hiscore) { 
		hiscore=score;
		if (w) {
			w->fillRectangle(25, 60, 120, 40, 0);
                	stringstream hs;
                	hs << score;
                	string s = hs.str();
                	w->drawString(25, 100, "HiScore: " + s);
		 }
	}
}

ostream &operator<<(ostream &out, const Board &b) {
	ostringstream ss;
	ss << b.score;  //converts score to a string (for length)           
	string s = ss.str();
	char blank = ' ';
	out << "Level:       " << b.level << endl;
	out << "Score:   " << (string((5-s.length()),blank)) << b.score << endl;
	ss << b.hiscore;
	s = ss.str();
	out << "Hi Score: " << (string((5-s.length()),blank)) << b.hiscore << endl;
	out << "----------" << endl;
	out << *b.td;
	out << "----------" << endl;
	out << "Next:" << endl;
	out << *b.next << endl;
	return out;
}
	


 
