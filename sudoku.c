#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>

Position* fromGrid(char grid[9][9]) 
{
	int i,j;														//za setanje po matrici
	Position *mySudoku = (Position*)malloc(sizeof(Position));		//alociraj mem oblika strukture Position (predstavlja sudoku)
	mySudoku->load=0;

	for (i=0;i<9;i++)
	{
		for (j=0;j<9;j++)
		{
			mySudoku->grid[i][j] = grid[i][j];						//prekopiraj broj na poziciju
			if (grid[i][j] > 0 && grid[i][j] < 10)					//ako je u dozvoljenom intervalu
				(mySudoku->load)++;									//povecaj broj upisanih brojeva
			else if (grid[i][j] > 9 || grid[i][j]<0)				//ako neko pobogu neispravno zada grid
			{
				printf("Error: Number at position [%d][%d] out of interval (0-9)",i,j);
				return NULL;
			}
		}
	}
	return mySudoku;
}

void printPosition(Position *p) 
{
	int i,j;
	printf("-----------------\n");				//uljepsavanja
	for (i=0;i<9;i++)
	{											//
		for (j=0;j<9;j++)						//setaj po poljima
		{
			printf("%d", p->grid[i][j]);		
			if (j==2 || j==5 ||j==8)			//uljepsavanje
				printf(" | ");
			if (j==8)							//novi red kad si dosa do kraja reda
				printf("\n");
		}
		if (i==2 || i==5 || i==8)				//uljepsavanje
			printf("-----------------\n");
	}
}

int legalMoves(Position *p, Move moves[1000]) 
{
	int a,b;										//ova dva su koordinate za setanje po sudokuu
	int m,n;										//jedan je za provjeravat broj, drugi je za provjeravat redak i stupac
	int k=0;										//ovog vracam, broji poteze
	int flag = 1;									//sluzi za provjerit jeli potez legalan
	for (a=0;a<9;a++)
	{
		for (b=0;b<9;b++)							//
		{											//
			if (p->grid[a][b]==0)					// setanje po sudoku
			{
				for (m=1;m<10;m++)					//broj za usporedjivanje
				{
					for (n=0;n<9;n++)				//za redak i stupac trenutne pozicije
					{
						if (p->grid[a][n]==m)		//uvik isti redak, minja se stupac
						{
							flag=0;
							break;
						}
						if (p->grid[n][b]==m)		//uvik isti stupac, minja se redak
						{
							flag=0;
							break;
						}
					}
					if (!flag)
					{
						flag = 1;
						continue;
					}

					if ((p->grid[((a/3)*3)+((a+1)%3)][((b/3)*3)+((b+1)%3)] == m) || (p->grid[((a/3)*3)+((a+1)%3)][((b/3)*3)+((b+2)%3)] == m)
					|| (p->grid[((a/3)*3)+((a+2)%3)][((b/3)*3)+((b+1)%3)] == m) || (p->grid[((a/3)*3)+((a+2)%3)][((b/3)*3)+((b+2)%3)] == m))
					flag=0;					//ovo je sve jedan ogromni praseci if, uglavnom, pokriva pozicije koje nisu provjerene
											//sa ova gornja dva if-a
					if (flag && n==9)		//mislin da mi ovi flag ode mozda niti ne triba, mogu stavit continue u gornji if
					{
						moves[k].i=a;		//koordinata x je a
						moves[k].j=b;		//koordinata y je b
						moves[k].input=m;	//broj koji moze na tu poziciju je onaj koji je prosa sve zadane provjere
						//printf("%d. (%d,%d) -> %d\n",k,moves[k].i,moves[k].j,m);
						k++;				//inkrementiraj broj koji ces vratit
					}
				flag=1;
				}
			}
		}
	}
	return k;
}

void makeMove(Position *p, Move m) 
{
	p->grid[m.i][m.j]=m.input;
	(p->load)++;
}

void undoMove(Position *p, Move m)
{
	p->grid[m.i][m.j]=0;
	(p->load)--;
}

int ncnt = 0;

int solveSudoku(Position *p) 
{
	int i,k;
	Move moves[1000];
	k = legalMoves(p,moves);

	ncnt++;
	if(ncnt % 10000 == 0)						//ovo broji rekurzivne pozive
	{
	  printf("%d rekurzivnih poziva\n",ncnt);
	  printf("%d ispunjeno\n",p->load);
	}

	if (p->load==81)							//ako je load 81 znaci da je sudoku ispunjen
	{
		printf("81 ispunjeno\n SUCCESS !!\n");
		return 1;
	}

	for (i=0;i<k;i++)
	{
		makeMove(p,moves[i]);					//napravi potez
		if (solveSudoku(p))						//rukurzivni poziv
		{
			return 1;
		}
		undoMove(p,moves[i]);					//kad ovaj gornji poziv ne dodje do kraja, ponisti taj potez koji si napravija
	}
	return 0;
}

/*void sortMoves(Move moves[1000], int n) 
{

}*/