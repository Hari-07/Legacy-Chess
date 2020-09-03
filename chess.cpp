#include<iostream.h>
#include<fstream.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>


int movable[8][8]={0};

int board[8][8]={-2,-1,0,0,0,0,1,2,      //1 for Pawn
		 -3,-1,0,0,0,0,1,3,      //2 for Rook
		 -4,-1,0,0,0,0,1,4,     //3 for Knight
		 -6,-1,0,0,0,0,1,6,     //4 for Bishop
		 -5,-1,0,0,0,0,1,5,     //5 for Queen
		 -4,-1,0,0,0,0,1,4,     //6 for King
		 -3,-1,0,0,0,0,1,3,
		 -2,-1,0,0,0,0,1,2};


int w=50;
int hos=230;//Horizontal Offset
int vos=30;//Vertical Offset
int midx=getmaxx()/2;
int midy=getmaxy()/2;
int bow;
int check=0;
int crun=0;

//Starting the game
void boardinit();
void boarddraw();

void chess2();//2 Player
void chess1();//1 Player
void checkenq(int);
void clear();
void computer();
void LegalMoves(int a,int b);
void returnblack(int &a,int &b);
int emptycheck(int,int);//Checks if a box is empty
int givex(int);//Converts box coordinate to Graphical Coordinate
int givey(int);
int move(int a,int b,int x,int y);
int possibleinit(int,int);



void main()
{
  int e=1;
  int ch=-1;
  char a;

  int gdriver = DETECT, gmode;
  initgraph(&gdriver, &gmode, "C:/TURBOC3/BGI");

  setfillstyle(3,15);
  bar3d(0,0,getmaxx(),getmaxy(),0,1);
  setfillstyle(1,0);
  bar3d(20,20,getmaxx()-20,getmaxy()-20,0,1);


  int midx=getmaxx()/2-250;
  int midy=getmaxy()/2+70;

  setcolor(10);
  settextstyle(1,0,9);
  outtextxy(midx-28,midy-250,"CHESS 2K17");

  settextstyle(7,0,1);
  setcolor(15);
  outtextxy(midx,midy-15,"1 PLAYER");
  outtextxy(midx,midy,"2 PLAYER");
  outtextxy(midx,midy+15,"EXIT");

  settextstyle(3,0,1);
  setcolor(4);
  outtextxy(midx+280,midy-15,"DESIGNED AND DEVELOPED BY:");
  setcolor(12);
  outtextxy(midx+280,midy,"Harinandan R Nair");

  setcolor(15);
    while(e)
    {
	outtextxy(midx-13,midy+(15*ch),">");
	a=getch();
	setfillstyle(1,0);
	bar(midx-13,midy+(15*ch),midx,midy+(15*ch)+20);
	if(a==72 && ch!=-1)ch--;
	else if(a==80 && ch!=1)ch++;
	else if(a=='a')
	{
	    clear();
	    if(ch==-1)chess1();
	    else if(ch==0)chess2();
	    else e=0;
	}
    }
}

class drawPieces
{
  public:
    void drawPawn(int x,int y,int a)
    {
	int border=0,fill=15;
	if(a<0)
	{
	    border=15;
	    fill=0;
	}
	x=givex(x);
	y=givey(y)+w/2-6;

	setcolor(border);
	line(x-16,y,x+16,y);
	arc(x,y,111,180,16);
	arc(x,y,0,68,16);
	arc(x,y-20,120,220,8);
	arc(x,y-20,-30,60,8);
	arc(x,y-30,-30,230,5);
	setfillstyle(1,fill);
	floodfill(x,y-1,border);
    }

    void drawRook(int x,int y,int a)
    {
	int border=0,fill=15;
	if(a<0)
	{
	    border=15;
	    fill=0;
	}
	x=givex(x);
	y=givey(y)+w/2-7;

	setcolor(border);
	rectangle(x-14,y-3,x+14,y+3);
	rectangle(x-11,y-9,x+11,y-3);
	rectangle(x-8,y-30,x+8,y-9);
	rectangle(x-11,y-36,x+11,y-30);
	rectangle(x-11,y-39,x-6,y-36);
	rectangle(x-3,y-39,x+3,y-36);
	rectangle(x+6,y-39,x+11,y-36);
	setfillstyle(1,fill);
	floodfill(x,y,border);
	floodfill(x,y-4,border);
	floodfill(x,y-10,border);
	floodfill(x,y-31,border);
	floodfill(x,y-37,border);
	floodfill(x-7,y-37,border);
	floodfill(x+7,y-37,border);
    }

    void drawKnight(int x,int y,int a)
    {
	int border=0,fill=15;
	if(a<0)
	{
	    border=15;
	    fill=0;
	}
	x=givex(x);
	y=givey(y)+w/2-3;

	setcolor(border);
	line(x-15,y,x+15,y);
	arc(x,y,110,180,15);
	arc(x-50,y,0,45,65);
	line(x-5,y-46,x-5,y-38);
	arc(x-12,y+2,70,110,17);
	line(x-18,y-14,x-21,y-22);
	arc(x+30,y+18,122,140,65);
	setfillstyle(1,fill);
	floodfill(x,y-1,border);
    }

    void drawBishop(int x,int y,int a)
    {
	int border=0,fill=15;
	if(a<0)
	{
	    border=15;
	    fill=0;
	}
	x=givex(x);
	y=givey(y)+w/2;

	setcolor(border);
	rectangle(x-12,y-7,x+12,y-3);
	rectangle(x-9,y-11,x+9,y-7);
	rectangle(x-6,y-30,x+6,y-11);
	arc(x+15,y-36,160,195,20);
	arc(x-15,y-36,-15,18,20);
	line(x-5,y-41,x,y-47);
	line(x+5,y-41,x,y-47);
	setfillstyle(1,fill);
	floodfill(x,y-4,border);
	floodfill(x,y-8,border);
	floodfill(x,y-12,border);
	floodfill(x,y-31,border);
    }

    void drawKing(int x,int y,int a)
    {
	int border=0,fill=15;
	if(a<0)
	{
	    border=15;
	    fill=0;
	}
	x=givex(x);
	y=givey(y)+w/2-4;

	setcolor(border);
	rectangle(x-15,y-6,x+15,y);
	rectangle(x-12,y-12,x+12,y-6);
	line(x-12,y-12,x-15,y-26);
	line(x+12,y-12,x+15,y-26);
	arc(x-9,y-26,0,180,6);
	arc(x+9,y-26,0,180,6);
	line(x-3,y-26,x-1,y-21);
	line(x+3,y-26,x+1,y-21);
	rectangle(x-5,y-37,x+5,y-33);
	line(x-2,y-40,x-2,y-26);
	line(x-2,y-40,x+2,y-40);
	line(x+2,y-40,x+2,y-26);

	setfillstyle(1,fill);
	floodfill(x,y-1,border);
	floodfill(x,y-7,border);
	floodfill(x,y-13,border);
	floodfill(x,y-34,border);
	floodfill(x+3,y-34,border);
	floodfill(x-3,y-34,border);
	floodfill(x,y-38,border);
    }

    void drawQueen(int x,int y,int a)
    {
	int border=0,fill=15;
	if(a<0)
	{
	    border=15;
	    fill=0;
	}
	x=givex(x);
	y=givey(y)+w/2-4;

	setcolor(border);

	rectangle(x-15,y-6,x+15,y);
	rectangle(x-15,y-12,x+15,y-6);
	line(x-15,y-12,x-20,y-35);
	line(x-9,y-12,x-20,y-35);
	line(x-9,y-12,x-10,y-35);
	line(x-3,y-12,x-10,y-35);
	line(x-3,y-12,x,y-35);
	line(x+3,y-12,x,y-35);
	line(x+3,y-12,x+10,y-35);
	line(x+9,y-12,x+10,y-35);
	line(x+9,y-12,x+20,y-35);
	line(x+15,y-12,x+20,y-35);
	circle(x-20,y-35,2);
	circle(x-10,y-35,2);
	circle(x,y-35,2);
	circle(x+10,y-35,2);
	circle(x+20,y-35,2);

	setfillstyle(1, fill);
	floodfill(x,y-1,border);
	floodfill(x,y-7,border);
	floodfill(x+4,y-13,border);
	floodfill(x+10,y-13,border);
	floodfill(x,y-13,border);
	floodfill(x-4,y-13,border);
	floodfill(x-10,y-13,border);
	floodfill(x-20,y-36,border);
	floodfill(x-10,y-36,border);
	floodfill(x,y-36,border);
	floodfill(x+10,y-36,border);
	floodfill(x+20,y-36,border);

    }
}Draw;

void chess2()
{
  bow=1;

  int gdriver = DETECT, gmode;
  initgraph(&gdriver, &gmode, "C:/TURBOC3/BGI");

    while(1)
    {
	clear();
	checkenq(bow);
	boarddraw();

	if(bow==1)
	{

	    int a,b;//Current Position
	    int x,y;//Future Position


	    cout<<"LEGAL MOVES WILL BE HIGHLIGHTED - ENTER 100 TO EXIT"<<endl;
	    cout<<"CURRENT MOVE IS FOR WHITE"<<endl<<endl;

	    if(check==1 || check==-1)cout<<"CHECK"<<endl<<endl;

	    cout<<"Enter Location of\nPiece to move:(x,y)\n";

	    cin>>a;
	    if(a==100)break;

	    cin>>b;
	    if(b==100)break;

	    if(emptycheck(a,b))
	    {
		cout<<"Invalid Move"<<endl<<endl<<"Try Again";
		getch();
		continue;
	    }
	    else if(board[a-1][b-1]<0)
	    {
		cout<<"Player is White";
		getch();
		continue;
	    }
	    setfillstyle(1,5);
	    movable[a-1][b-1]=1;
	    floodfill(givex(a-1),givey(b-1)+w/2-1,15);
	    LegalMoves(a,b);


	    cout<<"\n\nEnter Location to\nmove to:(x,y)\n";

	    cin>>x;
	    if(x==100)break;

	    cin>>y;
	    if(y==100)break;

	    if(move(a,b,x,y)==0)bow*=-1;
	}
	else
	{

	    int a,b;//Current Position
	    int x,y;//Future Position


	    cout<<"LEGAL MOVES WILL BE HIGHLIGHTED - ENTER 100 T0 EXIT"<<endl;
	    cout<<"CURRENT MOVE IS FOR BLACK"<<endl<<endl;

	    if(check==1 ||check==-1)cout<<"CHECK"<<endl<<endl;

	    cout<<"Enter Location of\nPiece to move:(x,y)\n";

	    cin>>a;
	    if(a==100)break;

	    cin>>b;
	    if(b==100)break;

	    if(emptycheck(a,b))
	    {
		cout<<"Invalid Move"<<endl<<endl<<"Try Again";
		getch();
		continue;
	    }
	    else if(board[a-1][b-1]>0)
	    {
		cout<<"Player is Black";
		getch();
		continue;
	    }
	    movable[a-1][b-1]=1;
	    setfillstyle(1,5);
	    floodfill(givex(a-1),givey(b-1)+w/2-1,15);
	    LegalMoves(a,b);


	    cout<<"\n\nEnter Location to\nmove to:(x,y)\n";

	    cin>>x;
	    if(x==100)break;

	    cin>>y;
	    if(y==100)break;

	    if(move(a,b,x,y)==0)bow*=-1;
	}
	bow*=-1;
    }
    closegraph();
}
void chess1()
{
  bow=1;

    while(1)
    {
	clear();
	checkenq(bow);
	boarddraw();

	if(bow==1)
	{
	    int a,b;//Current Position
	    int x,y;//Future Position


	    cout<<"LEGAL MOVES WILL BE HIGHLIGHTED - ENTER 100 TO EXIT"<<endl;
	    cout<<"PLAYER IS WHITE"<<endl<<endl;

	    if(check==1 ||check==-1)cout<<"CHECK"<<endl<<endl;

	    cout<<"Enter Location of\nPiece to move:(x,y)\n";

	    cin>>a;
	    if(a==100)break;

	    cin>>b;
	    if(b==100)break;

	    if(emptycheck(a,b))
	    {
		cout<<"Invalid Move"<<endl<<endl<<"Try Again";
		getch();
		continue;
	    }
	    else if(board[a-1][b-1]<0)
	    {
		cout<<"Player is White";
		getch();
		continue;
	    }
	    movable[a-1][b-1]=1;
	    setfillstyle(1,5);
	    floodfill(givex(a-1),givey(b-1)+w/2-1,15);
	    LegalMoves(a,b);

	    cout<<"\n\nEnter Location to\nmove to:(x,y)\n";

	    cin>>x;
	    if(x==100)break;

	    cin>>y;
	    if(y==100)break;

	    if(move(a,b,x,y)==0)bow*=-1;
	}
	else computer();
	bow*=-1;
    }
    closegraph();
}

void boarddraw()
{
    clear();
    setcolor(15);

    //Horizontal Lines
    for(int i=0;i<9;i++)
	line(0+hos,(i*w)+vos,(8*w)+hos,(i*w)+vos);

    //Vertical Lines
    for(i=0;i<9;i++)
	line((i*w)+hos,0+vos,(i*w)+hos,(8*w)+vos);



    //Colouring the Boxes
    int c=1;
    int color;
    for(i=0;i<8;i++)
    {
	for(int j=0;j<8;j++)
	{
	    if(c==1)color=7;
	    else color=8;

	    c*=-1;
	    setfillstyle(1,color);
	    floodfill(givex(i),givey(j),15);
	}
	c*=-1;
    }

    setfillstyle(1,15);
    for(i=0;i<8;i++)
    {
	for(int j=0;j<8;j++)
	{
	    if(board[i][j]==1 || board[i][j]==-1)
		Draw.drawPawn(i,j,board[i][j]);
	    else if(board[i][j]==2 || board[i][j]==-2)
		Draw.drawRook(i,j,board[i][j]);
	    else if(board[i][j]==3 || board[i][j]==-3)
		Draw.drawKnight(i,j,board[i][j]);
	    else if(board[i][j]==4 || board[i][j]==-4)
		Draw.drawBishop(i,j,board[i][j]);
	    else if(board[i][j]==5 || board[i][j]==-5)
		Draw.drawQueen(i,j,board[i][j]);
	    else if(board[i][j]==6 || board[i][j]==-6)
		Draw.drawKing(i,j,board[i][j]);
	}
    }
}

int emptycheck(int x,int y)
{
    if(board[x-1][y-1]==0)
	return 1;
    else
	return 0;
}

int givex(int a)
{
    return hos+(w/2)+(a*w);
}

int givey(int a)
{
    return vos+(w/2)+(a*w);
}

void LegalMoves(int a,int b)
{

   a--;
   b--;

   setfillstyle(1,13);
   int k;

   if(board[a][b]==1||board[a][b]==-1) //Moves of Pawn
   {
	if(b==3.5+(2.5*board[a][b]))
	{
	    k=possibleinit(a,b-board[a][b]);
	    if(k==0)return;

	    k=possibleinit(a,b-(2*board[a][b]));
	    if(k==0)return;
	}
	else
	{
	    k=possibleinit(a,b-board[a][b]);
	    if(k==0)return;
	}

   }

   if(board[a][b]==2||board[a][b]==-2) //Moves of Rook
   {
	int i=a,j=b;

	i++;
	while(i<8)
	{
	    k=possibleinit(i,b);
	    if(k==0)break;
	    i++;
	}

	i=a;
	i--;
	while(i>=0)
	{
	    k=possibleinit(i,b);
	    if(k==0)break;
	    i--;
	}
	i=a;
	j++;
	while(j<8)
	{
	    k=possibleinit(a,j);
	    if(k==0)break;
	    j++;
	}
	j=b;
	j--;
	while(j>=0)
	{
	    k=possibleinit(a,j);
	    if(k==0)break;
	    j--;
	}
   }

   if(board[a][b]==3||board[a][b]==-3) //Moves of Knight
   {
	possibleinit(a+2,b+1);
	possibleinit(a+2,b-1);
	possibleinit(a-2,b+1);
	possibleinit(a-2,b-1);
	possibleinit(a+1,b+2);
	possibleinit(a+1,b-2);
	possibleinit(a-1,b+2);
	possibleinit(a-1,b-2);
   }
   if(board[a][b]==4||board[a][b]==-4) //Moves of Bishop
   {
	int i=a,j=b;

	i++,j++;
	while(i<8 && j<8)
	{
	    k=possibleinit(i,j);
	    if(k==0)break;
	    i++;
	    j++;
	}

	i=a;
	j=b;
	i++,j--;
	while(i<8 && j>=0)
	{
	    k=possibleinit(i,j);
	    if(k==0)break;
	    i++;
	    j--;
	}

	i=a;
	j=b;
	i--,j++;
	while(i>=0 && j<8)
	{
	    k=possibleinit(i,j);
	    if(k==0)break;
	    i--;
	    j++;
	}

	i=a;
	j=b;
	i--,j--;
	while(i>=0 && j>=0)
	{
	    k=possibleinit(i,j);
	    if(k==0)break;
	    i--;
	    j--;
	}
   }

   if(board[a][b]==5||board[a][b]==-5) //Moves of Queen
   {
	int i=a,j=b;

	i++,j++;
	while(i<8 && j<8)
	{
	    k=possibleinit(i,j);
	    if(k==0)break;
	    i++;
	    j++;
	}

	i=a;
	j=b;
	i++,j--;
	while(i<8 && j>=0)
	{
	    k=possibleinit(i,j);
	    if(k==0)break;
	    i++;
	    j--;
	}

	i=a;
	j=b;
	i--,j++;
	while(i>=0 && j<8)
	{
	    k=possibleinit(i,j);
	    if(k==0)break;
	    i--;
	    j++;
	}

	i=a;
	j=b;
	i--,j--;
	while(i>=0 && j>=0)
	{
	    k=possibleinit(i,j);
	    if(k==0)break;
	    i--;
	    j--;
	}

	i=a;
	i++;
	while(i<8)
	{
	    k=possibleinit(i,b);
	    if(k==0)break;
	    i++;
	}

	i=a;
	i--;
	while(i>=0)
	{
	    k=possibleinit(i,b);
	    if(k==0)break;
	    i--;
	}
	i=a;

	j=b;
	j++;
	while(j<8)
	{
	    k=possibleinit(a,j);
	    if(k==0)break;
	    j++;
	}
	j=b;
	j--;
	while(j>=0)
	{
	    k=possibleinit(a,j);
	    if(k==0)break;
	    j--;
	}
   }
   if(board[a][b]==6||board[a][b]==-6) //Moves of King
   {
	possibleinit(a+1,b);
	possibleinit(a-1,b);
	possibleinit(a,b+1);
	possibleinit(a,b-1);
   }
}

int move(int a,int b,int x,int y)
{
	int temp;

	if(bow==1)
	{
	    temp=board[x-1][y-1];
	    board[x-1][y-1]=board[a-1][b-1];
	    board[a-1][b-1]=temp;

	    checkenq(1);

	    temp=board[x-1][y-1];
	    board[x-1][y-1]=board[a-1][b-1];
	    board[a-1][b-1]=temp;

	    if(check==1)
	    {
		cout<<endl<<endl<<"Illegal Move";
		return 0;
	    }
	}

	if(bow==-1)
	{
	    temp=board[x-1][y-1];
	    board[x-1][y-1]=board[a-1][b-1];
	    board[a-1][b-1]=temp;

	    checkenq(-1);

	    temp=board[x-1][y-1];
	    board[x-1][y-1]=board[a-1][b-1];
	    board[a-1][b-1]=temp;

	    if(check==-1)
	    {
		cout<<endl<<endl<<"Illegal Move";
		return 0;
	    }
	}

	if(movable[x-1][y-1]==2)
	{
		board[x-1][y-1]=board[a-1][b-1];
		board[a-1][b-1]=0;
		return 1;
	}
	else
	{
	    cout<<"Invalid Move"<<endl<<endl<<"Try Again";
	    getch();
	    return 0;
	}
}

class moves
{
  public:
    int a,b;//Current
    int x,y;//Future
};

void computer()
{
    randomize();
    int a,b;
    returnblack(a,b);
    a++;
    b++;
    fstream fio("CHESS.DAT",ios::binary|ios::in|ios::out|ios::trunc);
    moves m;
    int k=0;

    movable[a-1][b-1]=1;
    LegalMoves(a,b);
    m.a=a;
    m.b=b;
    for(int i=0;i<8;i++)
	for(int j=0;j<8;j++)
	    if(movable[i][j]==2)
	    {
		m.x=i+1;
		m.y=j+1;
		fio.write((char*)&m,sizeof(m));
		k++;
	    }
    fio.seekp(0,ios::beg);
    fio.read((char*)&m,sizeof(m));
    if(move(m.a,m.b,m.x,m.y)==0)bow*=-1;
}

void returnblack(int &a,int &b)
{
    a=random(8);
    b=random(8);

    if(board[a][b]<0)
	return;

    else
	returnblack(a,b);
}

void clear()
{
    setfillstyle(1,0);
    bar(0,0,getmaxx(),getmaxy());
    gotoxy(1,1);

    for(int i=0;i<8;i++)
    for(int j=0;j<8;j++)
    movable[i][j]=0;
}

int possibleinit(int a,int b)
{
    int p=2;
    if(crun==1)p=3;
    setfillstyle(1,13);

    if(a<0 || b<0 || a>7 || b>7)
	return 0;

    if(emptycheck(a+1,b+1))
    {
	movable[a][b]=p;
	if(p==2)floodfill(givex(a),givey(b)+w/2-1,15);
	return 1;
    }
    else
    {
	if(bow==1 && board[a][b]>0)
	    return 0;
	else if(bow== -1 && board[a][b]<0)
	    return 0;
	else
	{
	    movable[a][b]=p;
	    if(p==2)floodfill(givex(a),givey(b)+w/2-1,15);
	    return 0;
	}
    }
}

void checkenq(int a)
{
    crun=1;
    if(a==1)
    {
	for(int i=0;i<8;i++)
	for(int j=0;j<8;j++)
	    if(board[i][j]<0)
		LegalMoves(i+1,j+1);

	for(int p=0;p<8;p++)
	for(int q=0;q<8;q++)
	    if(board[p][q]==6 && movable[p][q]==3)
	    {
		check=1;
		crun=0;
		return;
	    }
	crun=0;
	check=0;
    }

    else if(a==-1)
    {
	for(int i=0;i<8;i++)
	for(int j=0;j<8;j++)
	if(board[i][j]>0)
	    LegalMoves(i+1,j+1);

	for(i=0;i<8;i++)
	for(j=0;j<8;j++)
	if(board[i][j]==-6 && movable[i][j]==3)
	{
	    crun=0;
	    check=-1;
	    return;
	}

	crun=0;
	check=0;
    }
}
