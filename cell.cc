#include <iostream>
#include "cell.h"
#include "textdisplay.h"
#include "window.h"
#include "block.h"
using namespace std;

Cell::Cell() :
	c(0), r(0), x(0), y(0), width(0), height(0), b(NULL) {}

void Cell::setCoords(int c, int r) {
	this->r = r;
	this->c = c;
}

void Cell::setGraphics(int x, int y, int width, int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

int Cell::getRow() {
	return r;
}

int Cell::getCol() {
        return c;
}

Block* Cell::getB() {
	return b;
}

void Cell::setB(Block *b) {
	this->b = b;
}

void Cell::notifyTDisplay(TextDisplay &td) {
	if (!b) {
		td.notify(r, c, ' '); //if no block pointer, no block uses this cell
	} else {
		td.notify(r, c, b->getType()); //gets the type of block at this cell
	}
}


//Sets the correct colour for the cell.
void Cell::notifyGDisplay(Xwindow *w) { 
	int colour;
	if (!b) { colour = 1; }
	else {
		char type = b->getType();
		if (type == 'I') {
			colour = 2;
		} else if (type == 'J') {
			colour = 3;
		} else if (type == 'L') {
                	colour = 4;
        	} else if (type == 'O') {
                	colour = 5;
        	} else if (type == 'S') {
                	colour = 6;
        	} else if (type == 'Z') {
                	colour = 7;
        	} else if (type == 'T') {
                	colour = 8;
        	}
	}
	w->fillRectangle(x,y,width,height,colour);
}

