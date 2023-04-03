#include "graphics.h"
#include <climits>
#include <unistd.h>
#include <queue>
#include <iostream>

using namespace std;
const int EMPTY = 0;
const int BODY  = 1;
const int APPLE = 2;
const int WALL  = 3;
int fires = 3;
int fires_2=3;

enum dir {up,down,Left,Right};
dir snakedir = down;
dir snakedir_2 = down;
bool IsGameOver = false;

struct location
{
    int r;
    int c;
};
bool IsFireStarted;
bool IsFireStarted_2;

location fireLocation;
dir fireDiraction;
queue<location> snakebody;
queue<location> snakebody_2;

int board[35][35]=
{
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3},
    {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
}
;





void arrow_1(int color)
{
    setcolor(color);
    int points[8]= {170,190,220-10,210,170,230,170,190};
    drawpoly(4,points);
    setfillstyle(SOLID_FILL,color);
    fillpoly(4,points);

}
void arrow_2(int color)
{
    setcolor(color);
    int points[8]= {170,240,220-10,260,170,280,170,240};
    drawpoly(4,points);
    setfillstyle(SOLID_FILL,color);
    fillpoly(4,points);

}
void arrow_3(int color)
{
    setcolor(color);
    int points[8]= {170,290,220-10,310,170,330,170,290};
    drawpoly(4,points);
    setfillstyle(SOLID_FILL,color);
    fillpoly(4,points);

}
void arrow_4(int color)
{
    setcolor(color);
    int points[8]= {170,340,220-10,360,170,380,170,340};
    drawpoly(4,points);
    setfillstyle(SOLID_FILL,color);
    fillpoly(4,points);

}

// menu bar
void menu(int box_color,int text_color)
{

    setcolor(box_color);
    setcolor(text_color);
    settextstyle(EUROPEAN_FONT,HORIZ_DIR,4);
    outtextxy(240,200,"START");
    outtextxy(240,250,"HELP");
    outtextxy(240,300,"ABOUT");
    outtextxy(240,350,"EXIT");
}




void score()
{
    setcolor(YELLOW);
    settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
    outtextxy(0,640,"Player 1");
    char arr[50];
    setcolor(WHITE);
    sprintf(arr, "Fires: %i", fires);
    outtextxy(0, 660, arr);

}
void score_2()
{
    setcolor(RED);
    settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
    outtextxy(350,640,"Player 2");
    char arr[50];
    setcolor(WHITE);
    sprintf(arr, "Fires: %i", fires_2);
    outtextxy(350, 660, arr);

}
void eraseSnakeBody_2(int r,int c)
{
    int x= c*18;
    int y =r*18;
    setfillstyle(SOLID_FILL,BLACK);
    bar(x,y,x+18,y+18);
}
void eraseSnakeBody(int r,int c)
{
    int x= c*18;
    int y =r*18;
    setfillstyle(SOLID_FILL,BLACK);
    bar(x,y,x+18,y+18);
}
void EraseFire(int r,int c)
{
    int x= c*18;
    int y =r*18;
    setfillstyle(SOLID_FILL,BLACK);
    bar(x,y,x+18,y+18);
    board[r][c]=0; //delete wall from array
}
void drawFire(int r,int c)
{
    int x= c*18;
    int y =r*18;
    readimagefile("fire.ico",x+1,y+1,x+17,y+17);
}
void drawSnakeBody(int r,int c)
{
    int x= c*18;
    int y =r*18;
    setfillstyle(SOLID_FILL,YELLOW);
    bar(x+1,y+1,x+17,y+17);
}

void drawSnakeBody_2(int r,int c)
{
    int x= c*18;
    int y =r*18;
    setfillstyle(SOLID_FILL,RED);
    bar(x+1,y+1,x+17,y+17);
}
void drawall(int r,int c)
{
    int x= c*18;
    int y =r*18;
    setfillstyle(SOLID_FILL,LIGHTRED);
    bar(x,y,x+18,y+18);
    setcolor(BLACK);
    setlinestyle(SOLID_LINE,1,NORM_WIDTH);
    line(x,y,x+18,y);
    line(x,y+9,x+18,y+9);
    line(x,y+18,x+18,y+18);
    line(x+12,y,x+12,y+9);
    line(x+6,y+9,x+6,y+18);



}
void drawApple(int r,int c)
{
    int x= c*18;
    int y =r*18;
    readimagefile("apple.ico",x+1,y+1,x+17,y+17);

}

void drawBoard()
{


    for (int r=0; r<35; r++)
        for(int c=0; c<35; c++)
            switch (board[r][c])
            {
            case EMPTY:
                break;
//    case BODY:
//    drawSnakeBody_2(r,c);
//    drawSnakeBody(r,c);
                break;
            case APPLE:
                drawApple(r,c);
                break;
            case WALL:
                drawall(r,c);
                break;
            }

}
void initsnake_2()
{
    location loc;
    loc.r =20 ;
    loc.c = 20;
    for(int i=0; i<=4; i++) //second snake
    {
        snakebody_2.push(loc);
        board[loc.r][loc.c]=1;
        loc.r+=1;
    }
}
void initsnake()
{
    location loc;
    loc.r =2 ;
    loc.c = 10;
    for(int i=0; i<=4; i++) //first snake
    {
        snakebody.push(loc);
        board[loc.r][loc.c]=1;
        loc.r+=1;
    }
}
void Won_p1()
{
    string sound ="gameover.wav";
    PlaySound(sound.c_str(),NULL,SND_ASYNC); //sync sound play then code execute
    IsGameOver=true;
    setcolor(YELLOW);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(TRIPLEX_FONT,HORIZ_DIR,4);
    outtextxy(getmaxx()/2,getmaxx()/2,"Yellow Won!");
}
void Won_p2()
{
    string sound ="gameover.wav";
    PlaySound(sound.c_str(),NULL,SND_ASYNC); //sync sound play then code execute
    IsGameOver=true;
    setcolor(RED);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(TRIPLEX_FONT,HORIZ_DIR,4);
    outtextxy(getmaxx()/2,getmaxx()/2,"Red Won!");
}
location getNextFire()
{
    location nextFireloc = fireLocation;

    switch(fireDiraction)       //change value according to dir
    {
    case up:
        nextFireloc.r -=1;
        break;
    case down:
        nextFireloc.r +=1;
        break;
    case Left:
        nextFireloc.c -=1;
        break;
    case Right:
        nextFireloc.c +=1;
        break;
    }
    return nextFireloc;
}

location getNexthead()
{


    location head = snakebody.back();
    switch(snakedir)       //change value according to dir
    {
    case up:
        head.r -=1;
        break;
    case down:
        head.r +=1;
        break;
    case Left:
        head.c -=1;
        break;
    case Right:
        head.c +=1;
        break;
    }
    return head;
}
location getNexthead_2()
{
    location head = snakebody_2.back();
    switch(snakedir_2)       //change value according to dir
    {
    case up:
        head.r -=1;
        break;
    case down:
        head.r +=1;
        break;
    case Left:
        head.c -=1;
        break;
    case Right:
        head.c +=1;
        break;
    }
    return head;
}
//normal move
void MoveSnakeToNextLocation( location nextHead)
{

    snakebody.push(nextHead);                //add in queue
    drawSnakeBody(nextHead.r,nextHead.c);    //draw in yellow
    board[nextHead.r][nextHead.c] = 1;       //change value in 2d array

    location tail=snakebody.front(); //get tail
    snakebody.pop();                 //delete tail from queue
    eraseSnakeBody(tail.r,tail.c);   //draw tail with black
    board[tail.r][tail.c] =0;        //change value in 2d array
}
void MoveSnakeToNextLocation_2( location nextHead)
{

    snakebody_2.push(nextHead);                //add in queue
    drawSnakeBody_2(nextHead.r,nextHead.c);    //draw in yellow
    board[nextHead.r][nextHead.c] = 1;       //change value in 2d array

    location tail=snakebody_2.front(); //get tail
    snakebody_2.pop();                 //delete tail from queue
    eraseSnakeBody_2(tail.r,tail.c);   //draw tail with black
    board[tail.r][tail.c] =0;        //change value in 2d array
}
//when eat apple
void MoveAndGrowSnakeToNextLocation( location nextHead)
{
    snakebody.push(nextHead);                //just draw without erase tail
    drawSnakeBody(nextHead.r,nextHead.c);
    board[nextHead.r][nextHead.c] = 1;

}
void MoveAndGrowSnakeToNextLocation_2( location nextHead)
{
    snakebody_2.push(nextHead);                //just draw without erase tail
    drawSnakeBody_2(nextHead.r,nextHead.c);
    board[nextHead.r][nextHead.c] = 1;

}
void generateApple()
{
    int r,c;
    do
    {
        r=rand()%18;
        c=rand()%18;
    }
    while(board[r][c] != EMPTY);
    board[r][c]=APPLE;
    drawApple(r,c);
}
void generateApple_2()
{
    int r,c;
    do
    {
        r=( 18 + ( rand() % ( 33 - 18 + 1 ) ));
        c=( 18 + ( rand() % ( 33 - 18 + 1 ) ));
    }
    while(board[r][c] != EMPTY);
    board[r][c]=APPLE;
    drawApple(r,c);
}
void gameOver()
{
    string sound ="gameover.wav";
    PlaySound(sound.c_str(),NULL,SND_ASYNC); //sync sound play then code execute
    IsGameOver=true;
    setcolor(WHITE);
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    settextstyle(TRIPLEX_FONT,HORIZ_DIR,4);
    outtextxy(getmaxx()/2,getmaxx()/2,"GAME OVER");
}
//decision according to the next thing
void movesnake()
{
    location nextHead = getNexthead();
    string sound ="eat.wav";
    if(board[nextHead.r][nextHead.c]==1)
        Won_p2();

    switch (board[nextHead.r][nextHead.c])
    {
    case EMPTY:
        MoveSnakeToNextLocation(nextHead);
        break;
    case APPLE:
        fires++;          //increase fire when eat apple
        score();
        PlaySound(sound.c_str(),NULL,SND_ASYNC); //async sound while other code execute normally
        MoveAndGrowSnakeToNextLocation(nextHead);
        generateApple();
        break;
    case WALL:
    case BODY:
        Won_p2();
        break;
    }

}
void movesnake_2()
{
    location nextHead = getNexthead_2();
    string sound ="eat.wav";
    if(board[nextHead.r][nextHead.c]==1)
        Won_p1();
    if(nextHead.r>=35 || nextHead.c>=35)
        Won_p1();
    switch (board[nextHead.r][nextHead.c])
    {
    case EMPTY:
        MoveSnakeToNextLocation_2(nextHead);
        break;
    case APPLE:
        fires_2++;          //increase fire when eat apple
        score_2();
        PlaySound(sound.c_str(),NULL,SND_ASYNC); //async sound while other code execute normally
        MoveAndGrowSnakeToNextLocation_2(nextHead);
        generateApple_2();
        break;
    case WALL:
        Won_p1();
    case BODY:
        break;
    }

}
void ChangeDir(char ch)
{
    switch(ch)       //change dir according to input ch
    {
    case KEY_UP     :
        if(snakedir == down) break ;
        snakedir =up;
        break;
    case KEY_DOWN   :
        if(snakedir == up  ) break ;
        snakedir =down;
        break; //not dye when press inverse key
    case KEY_LEFT   :
        if(snakedir == Right) break ;
        snakedir =Left;
        break;
    case KEY_RIGHT  :
        if(snakedir == Left) break;
        snakedir =Right;
        break;

    }
}
void startFire()
{
    IsFireStarted=true;
    fireLocation =getNexthead();
    fireDiraction=snakedir;
    drawFire(fireLocation.r,fireLocation.c);
    string sound ="fire.wav";
    PlaySound(sound.c_str(),NULL,SND_ASYNC); //sync sound play then code execute
}
void startFire_2()
{
    IsFireStarted_2=true;
    fireLocation =getNexthead_2();
    fireDiraction=snakedir_2;
    drawFire(fireLocation.r,fireLocation.c);
    string sound ="fire.wav";
    PlaySound(sound.c_str(),NULL,SND_ASYNC); //sync sound play then code execute
}
void ChangeDir_2(char ch)
{
    switch(ch)       //change dir according to input ch
    {
    case 'w'     :
        if(snakedir_2 == down) break ;
        snakedir_2 =up;
        break;
    case 's'   :
        if(snakedir_2 == up  ) break ;
        snakedir_2 =down;
        break; //not dye when press inverse key
    case 'a'   :
        if(snakedir_2 == Right) break ;
        snakedir_2 =Left;
        break;
    case 'd'  :
        if(snakedir_2 == Left) break;
        snakedir_2 =Right;
        break;
    case 32   :
        if(!(IsFireStarted || fires_2<=0))  //player 2 fire
        {
            startFire_2();
            fires_2--;
            score_2();
            break;

        }
    }
}

void stopFire()
{
    IsFireStarted=false;
    IsFireStarted_2=false;
    EraseFire(fireLocation.r,fireLocation.c);
}

void moveFire()
{
    if(IsFireStarted)
    {
        location nextFireloc =getNextFire();

        if(board[fireLocation.r][fireLocation.c]==1)
            Won_p1();
        if(nextFireloc.r >= 34 ||nextFireloc.r <= 0 ||
                nextFireloc.c >= 34 ||nextFireloc.c <= 0 ||
                (board[fireLocation.r][fireLocation.c]==3))  //to make wall get damage one by one
        {
            stopFire();
            return;
        }


        drawFire(nextFireloc.r,nextFireloc.c);
        EraseFire(fireLocation.r,fireLocation.c);
        fireLocation=nextFireloc;
    }
}
void moveFire_2()
{
    if(IsFireStarted_2)
    {
        location nextFireloc =getNextFire();

        if(board[fireLocation.r][fireLocation.c]==1)
            Won_p2();
        if(nextFireloc.r >= 34 ||nextFireloc.r <= 0 ||
                nextFireloc.c >= 34 ||nextFireloc.c <= 0 ||
                (board[fireLocation.r][fireLocation.c]==3))  //to make wall get damage one by one
        {
            stopFire();
            return;
        }


        drawFire(nextFireloc.r,nextFireloc.c);
        EraseFire(fireLocation.r,fireLocation.c);
        fireLocation=nextFireloc;
    }
}
void CheckKay()  //check if key is arrow
{
    char ch;
    if(kbhit())
    {
        ch = getch();
        if(ch == 0)
        {
            ch = getch();
            ChangeDir(ch);
        }
        else if (ch =='+')
        {
            if(!(IsFireStarted || fires<=0))  //not fire (more than one at same time or fires ended)
            {
                startFire();
                fires--;
                score();
            }
        }
        ChangeDir_2(ch);
    }
}

int main()
{

    initwindow(630,680);
    readimagefile("cover.jpg",0,0,630,630);
    sleep(3);
    cleardevice();


    int arrow_color=14;
    int box_color=11;
    int text_color=14;

    int menu_item=0;
    bool running = true ;
    char key;
    string sound ="start.wav";
    PlaySound(sound.c_str(),NULL,SND_ASYNC); //sync sound play then code execute
    while(running)
    {
        switch(menu_item)
        {
        case 0:
            cleardevice();
            arrow_1(arrow_color);
            menu(box_color,text_color);
            break;
        case 1:
            cleardevice();
            arrow_2(arrow_color);
            menu(box_color,text_color);
            break;
        case 2:
            cleardevice();
            arrow_3(arrow_color);
            menu(box_color,text_color);
            break;
        case 3:
            cleardevice();
            arrow_4(arrow_color);
            menu(box_color,text_color);
            break;
        }
        key=getch();
        if(key == KEY_DOWN && menu_item!=3 ) //down button pressed
        {
            string sound ="beep.wav";
            PlaySound(sound.c_str(),NULL,SND_ASYNC); //sync sound play then code execute
            menu_item++;
            continue;

        }

        if(key== KEY_UP && menu_item!=0 ) //up button pressed
        {
            string sound ="beep.wav";
            PlaySound(sound.c_str(),NULL,SND_ASYNC); //sync sound play then code execute
            menu_item--;
            continue;
        }
        if(key == 13)
        {
            string sound ="select.wav";
            PlaySound(sound.c_str(),NULL,SND_ASYNC); //sync sound play then code execute
            switch(menu_item)
            {
            case 0:
                running=false;  //play game
                cleardevice();
                break;
            case 1:
                cleardevice();
                setcolor(WHITE);
                settextstyle(EUROPEAN_FONT,HORIZ_DIR,2);
                outtextxy(20,70,"TWO SNAKES COMPETE UNTIL ONE DIE!");
                setcolor(YELLOW);
                settextstyle(EUROPEAN_FONT,HORIZ_DIR,2);
                outtextxy(20,150,"PLAYER 1:");
                setcolor(WHITE);
                settextstyle(EUROPEAN_FONT,HORIZ_DIR,1);
                outtextxy(60,190,"UP        -->     UP    ARROW");
                outtextxy(60,220,"DOWN      -->     DOWN  ARROW");
                outtextxy(60,250,"LEFT      -->     LEFT  ARROW");
                outtextxy(60,280,"RIGHT     -->     RIGHT ARROW");
                outtextxy(60,310,"FIRE      -->     PLUS");

                setcolor(RED);
                settextstyle(EUROPEAN_FONT,HORIZ_DIR,2);
                outtextxy(20,350,"PLAYER 2:");
                setcolor(WHITE);
                settextstyle(EUROPEAN_FONT,HORIZ_DIR,1);
                outtextxy(60,390,"UP      -->     W");
                outtextxy(60,420,"DOWN    -->     S");
                outtextxy(60,450,"LEFT      -->     A");
                outtextxy(60,480,"RIGHT     -->     D");
                outtextxy(60,510,"FIRE      -->     SPACE");
                setcolor(YELLOW);
                settextstyle(EUROPEAN_FONT,HORIZ_DIR,4);
                outtextxy(20,590,"BACK");
                key=getch();
                if(key==13)
                {
                    string sound ="select.wav";
                    PlaySound(sound.c_str(),NULL,SND_ASYNC); //sync sound play then code execute
                    cleardevice();
                    running=true;
                }
                break;
            case 2:
                cleardevice();
                settextstyle(EUROPEAN_FONT,HORIZ_DIR,4);
                outtextxy(170,50,"CREDITS");
                setcolor(WHITE);
                settextstyle(EUROPEAN_FONT,HORIZ_DIR,2);
                outtextxy(100,200,"FCI_ZU");
                outtextxy(100,250,"PROGRAMMER: MOHIE ELDEN");
                outtextxy(100,300,"COVER: MOAAZ KHALID");
                setcolor(YELLOW);
                settextstyle(EUROPEAN_FONT,HORIZ_DIR,4);
                outtextxy(20,380,"BACK");
                key=getch();
                if(key==13)
                {
                    string sound ="select.wav";
                    PlaySound(sound.c_str(),NULL,SND_ASYNC); //sync sound play then code execute
                    cleardevice();
                    running=true;
                }
                break;
            case 3:
                cleardevice();
                settextstyle(EUROPEAN_FONT,HORIZ_DIR,4);
                outtextxy(50,200,"THANKS FOR PLAYING!");
                sleep(3);
                return 0;
            }
        }
    }
    string sound2 ="start_game.wav";
    PlaySound(sound2.c_str(),NULL,SND_ASYNC); //sync sound play then code execute
    cleardevice();
    cleardevice();
    score();
    score_2();
    setfillstyle(SOLID_FILL,GREEN);
    bar(640,0,670,670);
    initsnake();
    initsnake_2();
    drawBoard();
    int gametimer = 0;
    while(!IsGameOver)
    {
        if(gametimer == INT_MAX)
            gametimer=0;
        if(gametimer% 300000==0)
        {
            moveFire();
            moveFire_2();
        }
        if(gametimer %9000000==0)
        {
            movesnake();
            movesnake_2();
        }

        gametimer++;
        CheckKay();
    }

    while( !kbhit() );



    return 0;
}


//to make wall get damage one by one
//increase fire when eat apple
//delete wall from array so snake not dye when walk through it
//2 snakes between them third WALL
//each side has unique apples generated
//snake die when 1-touch another snake
//2- touch another snake fire
//3- touch wall
//when snake die the other one
