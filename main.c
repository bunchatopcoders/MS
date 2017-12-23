#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

typedef struct boards
{
 int flag;
 int bomb;
 int nbombs; //adjacent
 int open;
} boards;

void gameplay(int elapsed ,int moves ,int row,int col,int mines,boards board [col][row]);
void printopened(int row,int col,boards board [col][row]);
int opens(int y,int x,int row,int col,boards board [col][row]);
void print(int row ,int col ,boards board [col][row]);//case lose not complete

void openleft(int y, int x,int row,int col,boards board[col][row]);
void openright(int y, int x,int row,int col,boards board[col][row]);
void opentop(int y, int x,int row,int col,boards board[col][row]);
void openbottom(int y, int x,int row,int col,boards board[col][row]);
/* HAD this worked wou;d have been much better
    if ( board[y][x].nbombs==0)

    {

        board[y][x].open=1;

        for(l=y-1; l<= y+1 ; l++)

				for( m = x-1 ; m<= x+1 ; m++)

				 opens(board,l,m,row,col);

    }

    else board[y][x].open=1;
*/


void openleft(int y, int x,int row,int col,boards board[col][row])
{

    if(x>=0&&y>=0&&x<row&&y<col){
    board[y+1][x-1].open=1;
    board[y][x-1].open=1;
    board[y-1][x-1].open=1;
    }
    if(x>0)
        if(board[y][x-1].nbombs==0)
            openleft(y,x-1,col,row,board);

}

void openright(int y, int x,int row,int col,boards board[col][row])
{
if(x>=0&&y>=0&&x<row&&y<col){
    board[y+1][x+1].open=1;
    board[y][x+1].open=1;
    board[y-1][x+1].open=1;}

    if(x<row-1)
        if(board[y][x+1].nbombs==0)
            openright(y,x+1,col,row,board);

}


void opentop(int y, int x,int row,int col,boards board[col][row])
{
if(x>=0&&y>=0&&x<row&&y<col){
    board[y+1][x-1].open=1;
    board[y+1][x].open=1;
    board[y+1][x+1].open=1;
}
    if(y>0)
        if(board[y+1][x].nbombs==0)
            opentop(y+1,x,col,row,board);

}



void openbottom(int y, int x,int row,int col,boards board[col][row])
{
if(x>=0&&y>=0&&x<row&&y<col){
    board[y-1][x-1].open=1;
    board[y-1][x].open=1;
    board[y-1][x+1].open=1;
}
    if(y<col-1)
        if(board[y-1][x].nbombs==0)
            openbottom(y-1,x,col,row,board);

}

void printopened(int row,int col,boards board [col][row])
{
int l,m;
for (l= 0 ; l<col ; l++)
    {
for (m = 0 ; m< row ; m++)
{


					if (board[l][m].open == 1)
                        printf("%d\t",board[l][m].nbombs);
					if (board[l][m].flag == 1)
                        printf("F\t");
                    if (board[l][m].flag == 2)
                        printf("?\t");
                    if (board[l][m].flag == 0 && board[l][m].open == 0)
                        printf("X\t");
}
 printf("\n");
}
}

int opens(int y,int x,int row,int col,boards board [col][row])
{
    if (board[y][x].bomb==1)
    {
    board[y][x].open=1;
    system("cls");
    puts("GAME OVER");
    Sleep(500);
    print(row,col,board);
    return 1;
    }


   else
    {
   if ( board[y][x].nbombs==0)
    {

      board[y][x].open=1;
openleft(y,x,row,col,board);
openright(y,x,row,col,board);
opentop(y,x,row,col,board);
openbottom(y,x,row,col,board);


    }
    else board[y][x].open=1;
    return 0;
    }
}


void print(int row ,int col ,boards board [col][row])//case lose not complete
{
int l,m;
for (l= 0 ; l<col ; l++)
{
for (m = 0 ; m< row ; m++)
{

					if (board[l][m].bomb == 1)
                    {
                    if(board[l][m].open==0)
					printf("*\t");
					else if (board[l][m].open==1)
					printf("M\t");
					}
					else if(board[l][m].flag == 1)
					{
                    if(board[l][m].bomb==0)
                    printf("_\t");
                    }
                    else
					printf("%d\t",board[l][m].nbombs);
}
 printf("\n");
}

}



void gameplay(int e, int mo,int row,int col,int mines,boards board [col][row])
{
puts("u da man");
char c;
int x,y,n=0,loses=0,moves=mo,score;
char fname[16];
time_t start, end;
    long elapsed;
    time(&start);  /* start the timer */
while (loses==0)
{
    system("cls");
    printopened(row,col,board);
    puts("enter co-ordinates");
    scanf("%d%d",&x,&y);
    fflush(stdin);
    x--;
    y--;
    puts("either O for open, F for flag, Q for question mark,S to save current game");
    c=getchar();
    moves++;
    switch (c)
    {
        case 'o':
            if(board[y][x].flag!=0){
        puts("you can not open this cell");
        Sleep(1000);}
            else{
        loses=opens(y,x,row,col,board);
        break;
}
        case 'f':
        if(board[y][x].flag==0)
            board[y][x].flag=1;
        else board[y][x].flag=0;

        break;
        case 'q':
        if (board[y][x].flag==0)board[y][x].flag=2;
        else board[y][x].flag=0;
        break;
        case's':
            system("cls");
            time(&end);
            elapsed= difftime(end, start)+e;
            puts("enter name of file you want it to be saved in");
            scanf("%s",fname);
            FILE*f;
            f=fopen(fname,"w");
            fprintf(f,"%d,%d,%d,%d\n",elapsed,moves,row,col);
            for(y=0;y<col;y++)
                for(x=0;x<row;x++)
            fprintf(f,"%d,%d,%d,%d,%d,%d\n",x,y,board[y][x].open,board[y][x].nbombs,board[y][x].bomb,board[y][x].flag);
            fclose(f);
            break;

    }

    for(y=0;y<col;y++)
        for(x=0;x<row;x++)
        if(board[y][x].open!=0)
        n++;

    if((row-1)*(col-1)<=(mines+n))
    {
        loses=1;
        puts("VENI VIDI VICI");
        Sleep(1000);
        time(&end);
        elapsed= e+difftime(end, start);
        print(row,col,board);
        puts("Enter your Name");
        scanf("%s",fname);
        score=(row*row*row*row*col*col*col*col)/(elapsed*moves);
        FILE*f;
        f=fopen("scores.txt","a");
        fprintf(f,"\n %s\t%d",fname,score);
        fclose(f);
        system("cls");
        main();
    }
    }

}


int main()
{
    int row ,col,c,t,moves=0,mines,elapsed=0,i,m,l,x,y,u,v,z,w;
    char fname[16];
    char ch;
    FILE*f;
    puts("to play a new game press 1 to continue an old one press 2 to see the winners and their scores press 3");
    scanf("%d",&c);
    if (c==1)
    {


 puts("enter number of columns");
 scanf("%d",&col);
 puts("enter number of row");
 scanf("%d",&row);
mines = 1+(row*col)/10;
boards board[col][row];
for (l= 0 ; l<col ; l++)
for (m = 0 ; m< row ; m++)
{
		board[l][m].flag =0;
		board[l][m].bomb =0;
		board[l][m].nbombs =0;
		board[l][m].open =0;
}
srand(time(NULL));
puts("Enter first co-ordinates(x,y) : ");
scanf("%d%d",&x,&y); // cannot contain mines
// do while check 0<=x,y<n(row,col)
x--;
y--;
w=x;
z=y;

for (i = 0 ; i< mines ; i++)
{v = rand()%(col); //0- (row-1)
u = rand()%(row); // 0- (col-1)

if ((board[v][u].bomb) || (u==x && v==y) )
  i--;
 else
 board[v][u].bomb = 1;
}

// function adjacent to mine
for (l = 0 ; l< col; l++)
  for (m = 0 ; m< row ; m++)
{
		 // int cell
			for(x=l-1; x<= l+1 ; x++)
				for( y = m-1 ; y<= m+1 ; y++)
                    if(x>=0 &&y >=0&&x<col&&y<row)
				     if (board[x][y].bomb)
						board[l][m].nbombs++;
}

opens(z,w,row,col,board);
gameplay(elapsed,moves,row,col,mines,board);
}
else if(c==2)
{

puts("enter the name of file the game is saved in");
scanf("%s",fname);
fopen(fname,"r");

fscanf(f,"%d,%d,%d,%d\n",&elapsed,&moves,&row,&col);
boards board[col][row];
while(!feof(f))
fscanf(f,"%d,%d,%d,%d,%d,%d\n",&x,&y,&board[y][x].open,&board[y][x].nbombs,&board[y][x].bomb,&board[y][x].flag);

fclose(f);
gameplay(elapsed,moves,row,col,mines,board);
}
else if(c==3)
{
f=fopen("scores.txt","r");
while((ch=getc(f))!=EOF)
    printf("%c",ch);
fclose(f);
printf("\n");
main();
}

return 0;
}




