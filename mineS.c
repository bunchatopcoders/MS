#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h> // bool

typedef struct
{
 bool flag;
 bool bomb;
 int nbombs ; //adjacent 
 bool save;	

} boards;






int main()
{

int row = 10 , col = 10 ;
int mines = 1+(row*col)/10;

// scan later
boards board[row][col];
int l,m;

//intialize=0
for (l= 0 ; l<row ; l++)
for (m = 0 ; m< col ; m++)
{
		board[l][m].flag =0;
		board[l][m].bomb =0;
		board[l][m].nbombs =0;
		board[l][m].save =0;
	
	
}

// function SEt mines position
int i ,x,y,u,v ;
srand(time(NULL));
puts("Enter first co-ordinates(x,y) : ");
scanf("%d%d",&x,&y); // cannot contain mines
// do while check 0<=x,y<n(row,col)
x--;
y--;


for (i = 0 ; i< mines ; i++)
{u = rand()%(row-1); //0- (row-1)
v = rand()%(col-1); // 0- (col-1)

if ((board[u][v].bomb) && (x==u && y==v) )
  i--;
 else
 board[u][v].bomb = 1;
}	



// function adjacent to mine

for (l = 0 ; l<row ; l++)
for (m = 0 ; m< col ; m++)
{
		if (!board[l][m].bomb){ // int cell 
			for(x=l-1; x<= l+1 ; x++)
				for( y = m-1 ; y<= m+1 ; y++)
					if (board[x][y].bomb)
						board[l][m].nbombs++;
						//printf("%d-",board[l][m].nbombs);
						}
		
}


 

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



return 0;
}




