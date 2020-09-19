#include "menu.h"

int screen[10] = {2,2,2,2,2,2,2,2,2,2};
int turn = 1,flag = 0;
int user,check;
COORD coord= {0,0}; // this is global variable
//center of axis is set to the top left cornor of the screen


void menu()
{
    int dec;
    printf("\n--------MENU--------");
    printf("\n1 : Play with a");
    printf("\n2 : Play with q");
    printf("\n3 : Exit");
    printf("\nEnter your - choice:>");
    scanf("%d",&dec);
    turn = 1;
    switch (dec)
    {
    case 1:
        user = 1;
        check = 0;
        user_test();
        break;
    case 2:
        user = 0;
        check = 1;
        start_game();
        break;
    case 3:
        exit(1);
    default:
        menu();
    }
}

void start_game()
{
// p==1 then X   p==0  then  O
    if(posswin(check))
    {
        go(posswin(check));
        flag = 1;
    }
    else if(posswin(user))
        go(posswin(user));
    else if(make2())
        go(make2());
    else
        go(make4());
    draw_board();

    if(flag)
    {
        gotoxy(30,20);
        //textcolor(128+RED);
        printf("Computer win");
        getch();
    }
    else
        user_test();
}

void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

int make2()
{
    if(screen[5] == 2)
        return 5;
    if(screen[2] == 2)
        return 2;
    if(screen[4] == 2)
        return 4;
    if(screen[6] == 2)
        return 6;
    if(screen[8] == 2)
        return 8;
    return 0;
}

int make4()
{
    if(screen[1] == 2)
        return 1;
    if(screen[3] == 2)
        return 3;
    if(screen[7] == 2)
        return 7;
    if(screen[9] == 2)
        return 9;
    return 0;
}

int posswin(int p)
{
// p==1 then X   p==0  then  O
    int i;
    int check_val,pos;

    if(p == 1)
        check_val = 18;
    else
        check_val = 50;

    i = 1;
    while(i<=9)//row check
    {
        if(screen[i] * screen[i+1] * screen[i+2] == check_val)
        {
            if(screen[i] == 2)
                return i;
            if(screen[i+1] == 2)
                return i+1;
            if(screen[i+2] == 2)
                return i+2;
        }
        i+=3;
    }

    i = 1;
    while(i<=3)//column check
    {
        if(screen[i] * screen[i+3] * screen[i+6] == check_val)
        {
            if(screen[i] == 2)
                return i;
            if(screen[i+3] == 2)
                return i+3;
            if(screen[i+6] == 2)
                return i+6;
        }
        i++;
    }

    if(screen[1] * screen[5] * screen[9] == check_val)
    {
        if(screen[1] == 2)
            return 1;
        if(screen[5] == 2)
            return 5;
        if(screen[9] == 2)
            return 9;
    }

    if(screen[3] * screen[5] * screen[7] == check_val)
    {
        if(screen[3] == 2)
            return 3;
        if(screen[5] == 2)
            return 5;
        if(screen[7] == 2)
            return 7;
    }
    return 0;
}

void go(int n)
{
    if(turn % 2)
        screen[n] = 3;
    else
        screen[n] = 5;
    turn++;
}

void user_test()
{
    int pos;

    check_draw();
    draw_board();
    gotoxy(30,18);
    printf("Your Turn :> ");
    scanf("%d",&pos);

    if(screen[pos] != 2)
        user_test();

    if(pos == posswin(user))
    {
        go(pos);
        draw_board();
        gotoxy(30,20);
        //textcolor(128+RED);
        printf("user Win");
        getch();
        exit(0);
    }

    go(pos);
    draw_board();
    start_game();
}



void check_draw()
{
    if(turn > 9)
    {
        gotoxy(30,20);
        //textcolor(128+RED);
        printf("Game Draw");
        getch();
        exit(0);
    }
}

void draw_board()
{
    int j;

    for(j=9; j<17; j++)
    {
        gotoxy(35,j);
        printf("|       |");
    }
    gotoxy(28,11);
    printf("-----------------------");
    gotoxy(28,14);
    printf("-----------------------");

    for(j=1; j<10; j++)
    {
        if(screen[j] == 3)
            put_X_O('X',j);
        else if(screen[j] == 5)
            put_X_O('O',j);
    }
}

void put_X_O(char ch,int pos)
{
    int m;
    int x = 31, y = 10;

    m = pos;

    if(m > 3)
    {
        while(m > 3)
        {
            y += 3;
            m -= 3;
        }
    }
    if(pos % 3 == 0)
        x += 16;
    else
    {
        pos %= 3;
        pos--;
        while(pos)
        {
            x+=8;
            pos--;
        }
    }
    gotoxy(x,y);
    printf("%c",ch);
}
