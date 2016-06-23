#include "textdisplay.h"
#include "window.h"
#include "cell.h"
#include "board.h"
#include "block.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {	
	string commands[] = {"left","right","down","clockwise","counterclockwise",
			     "drop","levelup","leveldown","restart"}; //Note: order matters!
	bool graphics = true; 
	bool movedDown = false;
	string file = "sequence.txt";
	int startlevel = 0;
	for (int i=1; i<argc; i++) {
		string arg = argv[i];
		if (arg=="-text") {graphics=false;}
		if (arg=="-seed") { int seed = atoi(argv[i+1]); srand(seed); }
		if (arg=="-scriptfile") {file = argv[i+1];}
		if (arg=="-startlevel") {startlevel = atoi(argv[i+1]);} 
	}	
	Board *b = new Board(graphics);
	b->setLevel(startlevel);
	string s;
	char firstblock = 0;
	char secondblock = 0;
	ifstream f(file.c_str());
	if (b->getLevel() == 0) {
                        f>>firstblock; 
        		f>>secondblock;
	}
	Block* curr = new Block(b->getLevel(), b, firstblock); //if level not 0, will be changed in block.cc
	curr->setCellBlockPointer(); //puts the block in play
	Block* next = new Block(b->getLevel(), b, secondblock); // same as above
	b->setNext(next);
	cout << *b;
	int mult = 1; 
	while (cin>>s) {
	    string m = s.substr(0,1); //gets first letter of string
	    istringstream ss(m);
	    if (!(ss >> mult)) { mult = 1; } //if no mult, mult = 1
	    else { s = s.substr(1); } //if mult, take it off of the command name
	    for (int i=0; i<9; i++) {
            	if (commands[i].substr(0,s.length()) == s) { //checks for incomplete commands
		    s = commands[i];
		}
	    }
	    if (s == commands[0] && mult > 1 && b->getWindow()) {
		curr->left(true, false);
		mult--;
	    } else if (s == commands[1] && mult > 1 && b->getWindow()) {
		curr->right(true, false);
		mult--;
	    } else if (s == commands[2] && mult > 1 && b->getWindow()) {
		curr->down(true, false);
		mult--;
	    }
	    for (int i=0; i<mult; i++) {
		if (s=="alias") { // (alias old new) changes a command name
			cin >> s;
			string changed;
			cin >> changed;
			for (int i=0; i<9; i++) {
				if (commands[i]==s) commands[i]=changed;
			}
		}
		if (s==commands[0]) { // left
			if (mult == 1 && b->getWindow()) curr->left(true, true);
			else curr->left(false, false);
		}
		else if (s==commands[1]) { // right
			if (mult == 1 && b->getWindow()) curr->right(true, true);
			else curr->right(false, false);
		}
		else if (s==commands[2]) { // down
			if (mult == 1 && b->getWindow()) curr->down(true, true);
                        else curr->down(false, false);
			movedDown = true;
		}
		else if (s==commands[3]) { //rotate clockwise
			if (movedDown) { cout << "Cannot rotate!" << endl; }
			else { curr->rotatec(); }
		}
		else if (s==commands[4]) { //rotate counterclockwise
                        if (movedDown) { cout << "Cannot rotate!" << endl; }
			else { curr->rotatecc(); }
		}
		else if (s==commands[5]) { //drop
			curr->drop();
			curr = next;
			movedDown = false;
			int numl=0; // Number of lines cleared
			for (int i=0; i<BOARDHEIGHT; i++) {
				if (b->linefull(i)) {b->clearline(i); numl++;}
			}
			b->lineScoreUpdate(numl);
			b->setHiscore();
			if (!curr->setCellBlockPointer()) { //if new block doesnt fit at the top
				delete b; 
				cout << "YOU LOST!" << endl; // Lose
				  
				return 0;}
			if (b->getLevel() == 0) {
				f >> firstblock;
				if (f.eof()) {
					f.close();
					f.open(file.c_str());
					f >> firstblock;
				}
			}
			next = new Block(b->getLevel(), b, firstblock);
			b->setNext(next);
		}
		else if (s==commands[6]) { // levelup
			b->setLevel(b->getLevel()+1);
		}
		else if (s==commands[7]) { // leveldown
                        b->setLevel(b->getLevel()-1);
                }
		else if (s==commands[8]) { // restart
			b->setHiscore();
			delete curr;
			delete b;
			b = new Board(graphics);
			b->setLevel(startlevel);
			firstblock = 0;
			secondblock = 0;
			if (b->getLevel() == 0) {
				f.close();
				f.open(file.c_str());
				f>>firstblock;
				f>>secondblock;
			}
			curr = new Block(b->getLevel(), b, firstblock);
			curr->setCellBlockPointer(); // puts first block in play
			movedDown = false;
        		next = new Block(b->getLevel(), b, secondblock);
        		b->setNext(next);
			continue;
		}
	    }
	    if ((s == commands[0] || s == commands[1] || s == commands[2]) && mult > 1 && b->getWindow()) {
	    	Cell ** cells = curr->getCells();
		Xwindow * w = b->getWindow();
		for (int i = 0; i < MAXCELLS; i++) {
			cells[i]->notifyGDisplay(w); //notifies graphics display of changes
		}
	    }
	    cout << *b; // prints board
	}
	delete b;
}	


