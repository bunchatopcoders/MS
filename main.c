#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<windows.h>

typedef struct boards
{
 int flag;
 int bomb;
 int nbombs; //adjacent
 int open;
} boards;

void printopened(boards ** board,int row,int col);
int opens(boards ** board ,int y,int x,int row,int col);
int gameplay(boards ** board,int row,int col);
void print(boards** board ,int row ,int col );



void printopened(boards ** board,int row,int col)
{
int l,m;
for (l= 0 ; l<col ; l++)
for (m = 0 ; m< row ; m++)
{

					if (board[l][m].open == 1)
                        printf("%d\t",board[l][m].nbombs);
					else if (board[l][m].flag == 1)
                        printf("F\t");
                    else if (board[l][m].flag == 2)
                        printf("?/t");
                    else printf("X/t");
}
 printf("\n");
}

int opens(boards ** board ,int y,int x,int row,int col)
{
    int l,m;
    if (board[y][x].bomb)
    {
    system("cls");
    puts("GAME OVER");
    print(board,row,col);
    return 1;
    }
    else {
    if ( board[y][x].nbombs==0)
    {
        board[y][x].open=1;
        for(l=y-1; l<= y+1 ; l++)
				for( m = x-1 ; m<= x+1 ; m++)
				 opens(board,l,m,row,col);
    }
    else board[y][x].open=1;
    return 0;
}
}


void print(boards** board ,int row ,int col )//case lose not complete
{
int l,m;
for (l= 0 ; l<row ; l++)

{for (m = 0 ; m< col ; m++)
{

					if (board[l][m].bomb == 1)
					printf("*\t");
					else
					printf("%d\t",board[l][m].nbombs);
}
 printf("\n");
}

}



int gameplay(boards ** board,int row,int col)
{

char c;
int gamemoves=0,x,y,loses=0;
while (!loses)
{
    puts("enter co-ordinates");
    scanf("%d%d",&x,&y);
    x--;
    y--;
    puts("either 0 for open 1 for flag 2 for question mark");
    c=getchar();
    gamemoves++;
    system("cls");
    switch (c)
    {
        case 0:
            if(board[y][x].flag!=0)
        puts("you can not open this cell");
            else{
        loses=opens(board,y,x,row,col);
        break;
}
        case 1:
        board[y][x].flag=1;
        break;
        case 2:
        board[y][x].flag=2;
        break;
    }



return gamemoves;
}

int main()
{

    int row ,col ;
 puts("enter number of columns");
 scanf("%d",&col);
 puts("enter number of row");
 scanf("%d",&row);
int mines = 1+(row*col)/10;
int i,gamemoves;
boards ** board;
board = (boards**) calloc(col,sizeof(boards**));
for(i=0; i< row; i++)
    board[i] = (boards*) calloc(row,sizeof(boards));
int x,y,u,v,z,w,l,m;
srand(time(NULL));
puts("Enter first co-ordinates(x,y) : ");
scanf("%d%d",&x,&y); // cannot contain mines
// do while check 0<=x,y<n(row,col)
x--;
y--;
w=x;
z=y;

for (i = 0 ; i< mines ; i++)
{v = rand()%(col-1); //0- (row-1)
u = rand()%(row-1); // 0- (col-1)

if ((board[v][u].bomb) && (y==u && x==v) )
  i--;
 else
 board[v][u].bomb = 1;
}

// function adjacent to mine
for (l = 0 ; l< col; l++)
  for (m = 0 ; m< row ; m++)
{
		if (board[l][m].bomb==0) // int cell
			for(x=l-1; x<= l+1 ; x++)
				for( y = m-1 ; y<= m+1 ; y++)
				     if (board[x][y].bomb)
						board[l][m].nbombs++;
}
open(board,z,w);
gamemoves=gameplay(board,row,col);
return 0;
}
