#ifndef SUDOKU_H
#define SUDOKU_H

typedef struct 
{
	// struktura opisuje poziciju (npr. 9x9 matrica)
	// struktura može imati dodatne èlanove da bi se olakšale neke provjere (npr. broj ispunjenih polja)
	char grid[9][9];			//9x9 matrica charova koji predstavlja sudoku
	int load;					//broj ispunjenih polja
} Position;

typedef struct 
{
	// struktura opisuje upisivanje jednog broja u sudoku
	int i,j;					//koordinate
	char input;					//broj koji se upisuje
} Move;

// kreira novi sudoku od zadanih brojeva
Position* fromGrid(char grid[9][9]);

// ispisuje sudoku poziciju
void printPosition(Position *p);

// ispunjava moves sa legalnim potezima u poziciji p
// vraæa broj leganih poteza
int legalMoves(Position *p, Move moves[1000]);

// upisuje potez m u poziciju p 
void makeMove(Position *p, Move m);

// poništava potez m u poziciji p 
void undoMove(Position *p, Move m);

// rekurzivna funkcija koja implementira DFS pretragu 
int solveSudoku(Position *p);

// sortiranje poteza (za dodatni dio zadatka)
void sortMoves(Move moves[1000], int n);

#endif