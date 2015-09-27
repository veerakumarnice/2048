#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define LEN 4
#define QUIT -1
#define GOAL 2048
enum key{UP=1,LEFT,RIGHT,DOWN};
int keypress(void);
int array[LEN][LEN]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
int n[5]={2,2,2,2,4};
void display(int [LEN][LEN],int,int);
void moveup(void);
void moveleft(void);
void moveright(void);
void movedown(void);
void swap(int,int,int);
void input(void);
int com_max(int,int);
int maxdigit,end;
main()
{
    int key;
    randomize();
    input();
    display(array,LEN,LEN);
    while(1)
    {
        key=keypress();
        switch(key)
        {
        case QUIT:
            printf("\nGame Over: user Quitted");
            return 1;
        case UP:
            moveup();
            break;
        case LEFT:
            moveleft();
            break;
        case RIGHT:
            moveright();
            break;
        case DOWN:
            movedown();
            break;
       }
       input();
       display(array,LEN,LEN);

    }
}
void display(int arr[][LEN],int row,int col)
{
    int i,j,temp;
    clrscr();
    for(i=0;i<row;i++)
        for(j=0;j<col;j++)
        {
             printf("%s",j==0?"\n-----------------\n|":"\0");
             temp=*(*(arr+i)+j);
             if(temp)
                printf("%2d |",temp);
             else
                printf("   |");
        }
    printf("\n-----------------");
    printf("\n\nPress UP, LEFT , RIGHT or DOWN to slide and q to quit :");
}

int keypress(void)
{
    char press;
    top:
    if(!(press=getch()))
    {
        switch(getch())
        {
        case 72:
            return UP;
        case 75:
            return LEFT;
        case 77:
            return RIGHT;
        case 80:
            return DOWN;
        default:
            return keypress();
        }
    }
    else if(press=='q')
        return QUIT;
    else
        goto top;
}

void moveup(void)
{
    int i,j,firstzero=-1,movable;
    int iszero,ismov;
    for(j=0;j<4;j++,firstzero=-1)
    {
        int mrg=-1;
        top:
        while(array[++firstzero][j]&&firstzero<5)
            ;
        if(firstzero<4)
            iszero=1;
        else
            goto merge;
        movable=firstzero;
        while((!array[++movable][j])&&movable<5)
            ;
        if(movable<4)
            ismov=1;
        else
            goto merge;
        if(iszero&&ismov)
        {
            array[firstzero][j]=array[movable][j];
            array[movable][j]=0;
            goto top;
        }
        merge:

            while(++mrg<4)
            {
                if(array[mrg][j]==array[mrg+1][j])
                    array[mrg][j]*=2,array[mrg+1][j]=0,end=com_max(mrg,j),swap(mrg+1,j,UP);
            }
    }
}

void moveleft(void)
{
    int i,j,firstzero=-1,movable;
    int iszero,ismov;
    for(i=0;i<LEN;i++,firstzero=-1)
    {
        int mrg=-1;
        top:
        while(array[i][++firstzero]&&firstzero<(LEN+1))
            ;
        if(firstzero<LEN)
            iszero=1;
        else
            goto merge;
        movable=firstzero;
        while((!array[i][++movable])&&movable<(LEN+1))
            ;
        if(movable<LEN)
            ismov=1;
        else
            goto merge;
        if(iszero&&ismov)
        {
            array[i][firstzero]=array[i][movable];
            array[i][movable]=0;
            goto top;
        }
        merge:
            while(++mrg<LEN)
            {
                if(array[i][mrg]==array[i][mrg+1])
                    array[i][mrg]*=2,array[i][mrg+1]=0,end=com_max(i,mrg),swap(i,mrg+1,LEFT);
            }
    }
}

void moveright(void)
{
    int i,j,firstzero=LEN,movable;
    int iszero,ismov;
    for(i=LEN-1;i>-1;i--,firstzero=LEN)
    {
        int mrg=LEN;
        top:
        while(array[i][--firstzero]&&firstzero>-1)
            ;
        if(firstzero>0)
            iszero=1;
        else
            goto merge;
        movable=firstzero;
        while((!array[i][--movable])&&movable>-1)
            ;
        if(movable>-1)
            ismov=1;
        else
            goto merge;
        if(iszero&&ismov)
        {
            array[i][firstzero]=array[i][movable];
            array[i][movable]=0;
            goto top;
        }
        merge:
            while(--mrg>0)
            {
                if(array[i][mrg]==array[i][mrg-1])
                    array[i][mrg]*=2,array[i][mrg-1]=0,end=com_max(i,mrg),swap(i,mrg-1,RIGHT);
            }
    }
}

void movedown(void)
{
    int i,j,firstzero=LEN,movable;
    int iszero,ismov;
    for(j=LEN-1;j>-1;j--,firstzero=LEN)
    {
        int mrg=LEN;
        top:
        while(array[--firstzero][j]&&firstzero>-1)
            ;
        if(firstzero>0)
            iszero=1;
        else
            goto merge;
        movable=firstzero;
        while((!array[--movable][j])&&movable>-1)
            ;
        if(movable>-1)
            ismov=1;
        else
            goto merge;
        if(iszero&&ismov)
        {
            array[firstzero][j]=array[movable][j];
            array[movable][j]=0;
            goto top;
        }
        merge:
            while(--mrg>0)
            {
                if(array[mrg][j]==array[mrg-1][j])
                    array[mrg][j]*=2,array[mrg-1][j]=0,end=com_max(mrg,j),swap(mrg-1,j,DOWN);
            }
    }
}

void swap(int r,int c,int dir)
{
    switch(dir)
    {
    case UP:
        {
           while((++r)<LEN)
               array[r-1][c]=array[r][c];
           array[r-1][c]=0;
        }
        break;
    case LEFT:
        {
           while((++c)<LEN)
               array[r][c-1]=array[r][c];
           array[r][c-1]=0;
        }
        break;
    case RIGHT:
        {
           while((--c)>-1)
               array[r][c+1]=array[r][c];
           array[r][c+1]=0;
        }
        break;
    case DOWN:
        {
            while((--r)>-1)
               array[r+1][c]=array[r][c];
            array[r+1][c]=0;
        }
        break;
    }
}

int com_max(int p1,int p2)
{
    if(array[p1][p2]>maxdigit)
    {
        maxdigit=array[p1][p2];
        if(maxdigit==GOAL)
        {
             char choice;
             printf("\n\nGoal achieved:\n");
             printf("\nDo you want to Contiune 'y' or 'n': ");
             scanf(" %c",&choice);
             if(choice=='y')
                    return 1;
             else
                exit(0);
        }
    }
    return 0;
}

void input(void)
{
    int num,i,j,count;
    num=rand()%(LEN*LEN);
    while(1)
    {
    for(i=0;i<LEN;i++)
    {
        for(j=0;j<LEN;j++)
        {
            array[i][j]?0:++count;
            if(count==num)
            {
                 array[i][j]=n[num%5];
                 return;
            }

        }
    }
    }

}

