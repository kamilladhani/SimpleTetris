#include <iostream>
#include "textdisplay.h"
using namespace std;

const int BW = 10;
const int BH = 18;

TextDisplay::TextDisplay() {
	theDisplay = new char* [BH];
        for (int i = 0; i < BH; i++) {
                theDisplay[i] = new char[BW];
        }
	for (int r = 0; r < BH; r++) {
                for (int c = 0; c < BW; c++) {
			theDisplay[r][c] = ' ';
		}
	}
}

TextDisplay::~TextDisplay() {
	for (int i = 0; i < BH; i++) {
                delete [] theDisplay[i];
        }
        delete [] theDisplay;
}

void TextDisplay::notify(int r, int c, char ch) {
	theDisplay[r][c] = ch;
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
	for (int r = 0; r < BH; r++) {
                for (int c = 0; c < BW; c++) {
                        out << td.theDisplay[r][c];
                }
		out << endl;
        }
	return out;
}
