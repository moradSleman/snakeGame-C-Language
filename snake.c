/*morad sleeman id:205535982*/
/*basel hawary id:302373188*/
/*Date : 7/6/2016*/
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#define borderx 103
#define bordery 25
#define arrayculomn 50
#define arrayline 20
#define firstnumsteps 80

COORD coord = {0, 0};
int snakeplace[arrayline][arrayculomn];
int score=0;
int remainingsteps=firstnumsteps;
char direction;
int headline;
int headculomn;
int snakebodycount=1;
int badfoodline;
int badfoodculomn;

void randomgoodfood();
//the function search an index to put the good food in it and make sure that it's current value is 0 (nothing in it)

void randombadfood();
//the function search an index to put the bad food in it and make sure that it's current value is 0 (nothing in it)

void SetColor(int ForgC);

void gotoxy (int x, int y);

void printboarder();
//this function print boarder on the background and down print last score

void printremainingsteps();
//this function prints the remaining steps with all step

void printsnakearray();
/*this function print at the  appropriate place on the screen for every value at the snakeplacearray a white square for -1
that is the boarder of snake moving, and blue square for 1000 the is the head , and yellow square for -1000 that is the tail
, and white sqaure for numbers between 1 and less than 100 that is the body ,
a green square for -2 the is good food , and a red sqaure for -3 the is bad food*/

void printerror();
// this function search a place for ten chars and print try again

char printmainpage();
//this function prints the menu of the game (mainpage) and return the value of the input (enter)

void setbeginingarray();
//this functiom equal the first value of every index(snake with 3 square on the top) to print it another function

int checkinput();
//theis function chech an input if it legal and return 1 if succes and 0 if not legal

void swapsnakebody(int *headlineshift,int *headculomnshift);
/*this function gets int pointers of the index of the last headplace and swap it with the biggest snakebodycount
till reach the last of the body then the snakebodycount equal to 0 then change the headshift to a tail
and delete the tail(-1000) to (0)*/

void snakemove();
/*this function check what is the current direction and moves the snake to the appropiate place with the help of swapsnakebody function*/

void swapfoodtobody();
//this function adds one square to the body of the snake and add new good and bad food

int directionsteps();
/*this function check whitch is step is now and check if itis going to the body or bad food or the tail or there is no remainingsteps
then returns 0 , and returns 1 if success moving */

void randomgoodfood()
{
    int goodfoodline;
    int goodfoodculomn;
    goodfoodline=(rand()%10)*2;
    goodfoodculomn=(rand()%10)*5;
    if(snakeplace[goodfoodline][goodfoodculomn]!=0)
        return randomgoodfood();
    else
        {
            snakeplace[goodfoodline][goodfoodculomn]=-2;
            return;
        }

}

void randombadfood()
{
    badfoodline=(rand()%10)*2;
    badfoodculomn=(rand()%10)*5;
    if(snakeplace[badfoodline][badfoodculomn]!=0)
        return randombadfood();
    else
        {
            snakeplace[badfoodline][badfoodculomn]=-3;
            return;
        }

}
void SetColor(int ForgC)
{
     WORD wColor;
     //This handle is needed to get the current background attribute

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //csbi is used for wAttributes word

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //To mask out all but the background attribute, and to add the color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}


void gotoxy (int x, int y)
{
        coord.X = x; coord.Y = y; // X and Y coordinates
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void printboarder()
{
        int i,j;
    gotoxy(0,0);
    for(i=0;i<=borderx;i++)
        for(j=0;j<=bordery;j++)
         if(i==0 || i==borderx)
    {
        gotoxy(i,j);
        SetColor(15);
        printf("\xDB");
    }
    else
    {
        if(j>0 &&  j<bordery)
            continue;
        if(j==0 || j==bordery)
        {
            gotoxy(i,j);
            printf("\xDB");
        }
    }
    gotoxy(borderx/2-5,1);
    SetColor(30);
    printf("SNAKE GAME");
    SetColor(15);
    gotoxy(borderx-20,bordery-1);
    printf("Last score: %d",score);

}

void printremainingsteps()
{
    gotoxy(borderx-20,bordery-2);
    printf("remainingsteps :%d",remainingsteps);
    gotoxy (0,bordery+1);
}

void printsnakearray()
{
    int i,j;
    int x,y;
    for(i=0,y=3;i<arrayline;i++,y++)
     for(j=0,x=25;j<arrayculomn;j++,x++)
     {
         if(snakeplace[i][j]==-1)
         {
             gotoxy(x,y);
             printf("\xB2");
         }
         if(snakeplace[i][j]==1000)
         {
             gotoxy(x,y);
             SetColor(9);
             printf("\xFE");
             SetColor(15);
         }
         if (snakeplace[i][j]==-1000)
         {
             gotoxy(x,y);
             SetColor(14);
             printf("\xFE");
             SetColor(15);
         }
         if(snakeplace[i][j]>0 && snakeplace[i][j]<1000)
         {
             gotoxy(x,y);
             printf("\xFE");
         }
         if(snakeplace[i][j]==-2)
         {
             gotoxy(x,y);
             SetColor(10);
             printf("\xFE");
             SetColor(15);
         }
         if(snakeplace[i][j]==-3)
         {
             gotoxy(x,y);
             SetColor(12);
             printf("\xFE");
             SetColor(15);
         }
     }
     gotoxy(0,bordery+1);
}

void printerror()
{
    int i,j;
    int count=0;
    for(i=0;i<arrayline;i++)
    {

        for(j=0;j<arrayculomn;j++)
        {
            if(snakeplace[i][j]==0 && snakeplace[i][j+1]==0 && j+1<arrayculomn-1)
            count++;
            else
            if(snakeplace[i][j]==0 && count==9)
            count++;
            else
                count=0;
            if(count==10)
                break;
        }
        if(count==10)
        break;
     }
     gotoxy(25+j-9,3+i);
     SetColor(30);
     printf("try again!");
     SetColor(15);
     gotoxy(0,bordery);

}

char printmainpage()
{
    char input;
    printboarder();
    gotoxy(borderx/2-8,bordery/2-2);
    printf("click a to start");
    gotoxy(borderx/2-8,bordery/2-1);
    printf("click another key to exit");
    gotoxy(0,bordery+1);

      input=getch();
    return input;
}
void setbeginingarray()
{
    int i,j;
    for(i=0;i<arrayline;i++)
        for(j=0;j<arrayculomn;j++)
    {
        if(i==0 || i==arrayline-1)
            snakeplace[i][j]=-1;
        else
            if(j==0 || j==arrayculomn-1)
            snakeplace[i][j]=-1;
                else
                    snakeplace[i][j]=0;
    }
    headline=1;
    headculomn=3;
    snakeplace[headline][headculomn]=1000;
    snakeplace[1][2]=1;
    snakeplace[1][1]=-1000;
   randomgoodfood();
   randombadfood();
}


int checkinput()
{
     direction=getch();
     if(direction!='2' && direction!='4' && direction!='6' && direction!='8')
        return 0;
        return 1;
}



void swapsnakebody(int *headlineshift,int *headculomnshift)
{
    if(snakebodycount!=0)//if snakebody is around the head search where is the high value of snakebodycount and swap with the head
    {
        if(snakeplace[(*headlineshift)-1][*headculomnshift]==snakebodycount)
    {
        snakeplace[(*headlineshift)-1][*headculomnshift]=1000;
        snakeplace[*headlineshift][*headculomnshift]=snakebodycount;
        (*headlineshift)--;
        return;
    }
    if(snakeplace[*headlineshift][(*headculomnshift)-1]==snakebodycount)
    {
        snakeplace[*headlineshift][(*headculomnshift)-1]=1000;
        snakeplace[*headlineshift][*headculomnshift]=snakebodycount;
        (*headculomnshift)--;
        return ;
    }
    if(snakeplace[(*headlineshift)+1][*headculomnshift]==snakebodycount)
    {
        snakeplace[(*headlineshift)+1][*headculomnshift]=1000;
        snakeplace[*headlineshift][*headculomnshift]=snakebodycount;
        (*headlineshift)++;
        return;
    }
    if(snakeplace[*headlineshift][(*headculomnshift)+1]==snakebodycount)
    {
        snakeplace[*headlineshift][*headculomnshift+1]=1000;
        snakeplace[*headlineshift][*headculomnshift]=snakebodycount;
        (*headculomnshift)++;
        return;
    }
    //if the complete of snake body is in the other side then seearch where and swap
    if(snakeplace[*headlineshift][arrayculomn-2]==snakebodycount)
    {
        snakeplace[*headlineshift][*headculomnshift]=snakebodycount;
        snakeplace[*headlineshift][(*headculomnshift)+arrayculomn-3]=1000;
        *headculomnshift=(*headculomnshift)+arrayculomn-3;
        return ;
    }
    if(snakeplace[*headlineshift][1]==snakebodycount)
    {
        snakeplace[*headlineshift][*headculomnshift]=snakebodycount;
        snakeplace[*headlineshift][1]=1000;
        *headculomnshift=1;
        return ;
    }
    if(snakeplace[1][*headculomnshift]==snakebodycount)
    {
        snakeplace[*headlineshift][*headculomnshift]=snakebodycount;
        snakeplace[1][*headculomnshift]=1000;
        *headlineshift=1;
        return ;
    }
    if(snakeplace[*(headlineshift)+arrayline-3][*headculomnshift]==snakebodycount)
    {
        snakeplace[*headlineshift][*headculomnshift]=snakebodycount;
        snakeplace[(*headlineshift)+arrayline-3][*headculomnshift]=1000;
        *headlineshift=(*headlineshift)+arrayline-3;
        return ;
    }

    }
    else //if snakebodycount==0 search about the tail (-1000) and delete it and change the headshift to a tail (-1000)
    {
        if(snakeplace[(*headlineshift)-1][*headculomnshift]==-1000)
            snakeplace[(*headlineshift)-1][*headculomnshift]=0;
         if(snakeplace[*headlineshift][(*headculomnshift)-1]==-1000)
            snakeplace[*headlineshift][(*headculomnshift)-1]=0;
             if(snakeplace[(*headlineshift)+1][*headculomnshift]==-1000)
            snakeplace[(*headlineshift)+1][*headculomnshift]=0;
             if(snakeplace[*headlineshift][(*headculomnshift)+1]==-1000)
            snakeplace[*headlineshift][(*headculomnshift)+1]=0;


            if(snakeplace[*headlineshift][arrayculomn-2]==-1000)
                snakeplace[*headlineshift][arrayculomn-2]=0;
            if(snakeplace[*headlineshift][1]==-1000)
                snakeplace[*headlineshift][1]=0;
                if(snakeplace[arrayline-2][*headculomnshift]==-1000)
                snakeplace[arrayline-2][*headculomnshift]=0;
                if(snakeplace[1][*headculomnshift]==-1000)
                snakeplace[1][*headculomnshift]=0;
            snakeplace[*headlineshift][*headculomnshift]=-1000;
            return ;
    }

}


void snakemove()
{
   int downcount=0;
    int headlineshift=headline;
    int headculomnshift=headculomn;
  while (snakebodycount>=0)
  {
      swapsnakebody(&headlineshift,&headculomnshift);
      snakebodycount--;
      downcount++;
  }
  snakebodycount+=downcount;
 if(direction=='6' && (headculomn<arrayculomn-2))
  {
      headculomn++;
      snakeplace[headline][headculomn]=1000;
      return;
  }
  if(direction=='6' && headculomn==arrayculomn-2)
  {
      snakeplace[headline][1]=1000;
      headculomn=1;
      return;
  }
  if(direction=='2' && headline<arrayline-2)
  {
      headline++;
      snakeplace[headline][headculomn]=1000;
      return;

  }
  if(direction=='2' && headline==arrayline-2)
  {
      snakeplace[1][headculomn]=1000;
      headline=1;
      return ;
  }
  if(direction=='4' && headculomn-1!=0)
  {
      snakeplace[headline][headculomn-1]=1000;
      headculomn--;
      return ;
  }
  if(direction=='4' && headculomn-1==0)
  {
      snakeplace[headline][arrayculomn-2]=1000;
      headculomn=arrayculomn-2;
      return ;
  }
  if(direction=='8' && headline-1!=0)
  {
      snakeplace[headline-1][headculomn]=1000;
      headline--;
      return ;
  }
  if(direction=='8' && headline-1==0)
  {
      snakeplace[arrayline-2][headculomn]=1000;
      headline=arrayline-2;
  }
  return ;
}
void swapfoodtobody()//this function adds one square to the body of the snake
{
    snakebodycount++;
    if(direction=='6' && headculomn+1!=arrayculomn-1)
    {
        snakeplace[headline][headculomn]=snakebodycount;
        snakeplace[headline][headculomn+1]=1000;
        headculomn++;
        randomgoodfood();
        snakeplace[badfoodline][badfoodculomn]=0;
        randombadfood();
        return;
    }
    if(direction=='6' && headculomn+1==arrayculomn-1 )
    {
        snakeplace[headline][headculomn]=snakebodycount;
        snakeplace[headline][1]=1000;
        headculomn=1;
         randomgoodfood();
        snakeplace[badfoodline][badfoodculomn]=0;
        randombadfood();
        return ;
    }
    if(direction=='8' && headline-1!=0)
    {
        snakeplace[headline][headculomn]=snakebodycount;
        snakeplace[headline-1][headculomn]=1000;
        headline--;
         randomgoodfood();
        snakeplace[badfoodline][badfoodculomn]=0;
        randombadfood();
        return ;
    }
    if(direction=='8' && headline-1==0)
    {
        snakeplace[headline][headculomn]=snakebodycount;
        snakeplace[arrayline-2][headculomn]=1000;
        headline=arrayline-2;
         randomgoodfood();
        snakeplace[badfoodline][badfoodculomn]=0;
        randombadfood();
        return ;
    }
    if(direction=='4' && headculomn-1!=0)
    {
        snakeplace[headline][headculomn]=snakebodycount;
        snakeplace[headline][headculomn-1]=1000;
        headculomn--;
         randomgoodfood();
        snakeplace[badfoodline][badfoodculomn]=0;
        randombadfood();
        return ;
    }
     if(direction=='4' && headculomn-1==0)
    {
        snakeplace[headline][headculomn]=snakebodycount;
        snakeplace[headline][arrayculomn-2]=1000;
        headculomn=arrayculomn-2;
         randomgoodfood();
        snakeplace[badfoodline][badfoodculomn]=0;
        randombadfood();
        return ;
    }
     if(direction=='2' && headline+1!=arrayline-1)
    {
        snakeplace[headline][headculomn]=snakebodycount;
        snakeplace[headline+1][headculomn]=1000;
        headline++;
         randomgoodfood();
        snakeplace[badfoodline][badfoodculomn]=0;
        randombadfood();
        return ;

    }
     if(direction=='2' && headline+1==arrayline-1)
    {
        snakeplace[headline][headculomn]=snakebodycount;
        snakeplace[1][headculomn]=1000;
        headline=1;
         randomgoodfood();
        snakeplace[badfoodline][badfoodculomn]=0;
        randombadfood();
        return ;
    }
}


int directionsteps()
{
    if (direction=='6')
   {
        if(remainingsteps==0 || snakeplace[headline][headculomn+1]==-3 || snakeplace[headline][headculomn+1]>0 || snakeplace[headline][headculomn+1]==-1000)
       return 0;

       if(snakeplace[headline][headculomn+1]==-2 || snakeplace[headline][headculomn-arrayculomn+3]==-2)
        {
            swapfoodtobody();
            score+=5;
            remainingsteps=firstnumsteps;
            return 1;
        }

       if(snakeplace[headline][headculomn+1]==0 || snakeplace[headline][headculomn+1]==-1)
       {
           snakemove();
           remainingsteps--;
           return 1;
       }
   }
   if (direction=='4')
   {
       if(remainingsteps==0 || snakeplace[headline][headculomn-1]==-3 || snakeplace[headline][headculomn-1]>0 || snakeplace[headline][headculomn-1]==-1000)
       return 0;

       if(snakeplace[headline][headculomn-1]==-2 || snakeplace[headline][headculomn+arrayculomn-3]==-2)
        {
            swapfoodtobody();
            score+=5;
            remainingsteps=firstnumsteps;
            return 1;
        }

       if (snakeplace[headline][headculomn-1]==0 || snakeplace[headline][headculomn-1]==-1)
       {
           snakemove();
           remainingsteps--;
           return 1;
       }

   }
   if(direction=='8')
    {
  if(remainingsteps==0 || snakeplace[headline-1][headculomn]==-3 || snakeplace[headline-1][headculomn]>0 || snakeplace[headline-1][headculomn]==-1000)
       return 0;

      if(snakeplace[headline-1][headculomn]==-2 || snakeplace[headline+arrayline-3][headculomn]==-2)
        {
            swapfoodtobody();
            score+=5;
            remainingsteps=firstnumsteps;
            return 1;
        }

       if (snakeplace[headline-1][headculomn]==0 || snakeplace[headline-1][headculomn]==-1)
       {
           snakemove();
           remainingsteps--;
           return 1;
       }
}
if(direction =='2')
    {
    if(remainingsteps==0 || snakeplace[headline+1][headculomn]==-3 || snakeplace[headline+1][headculomn]>0 || snakeplace[headline+1][headculomn]==-1000)
       return 0;
       if(snakeplace[headline+1][headculomn]==-2 || snakeplace[headline-arrayline+3][headculomn]==-2)
        {
            swapfoodtobody();
            score+=5;
            remainingsteps=firstnumsteps;
            return 1;
        }
       if (snakeplace[headline+1][headculomn]==0 || snakeplace[headline+1][headculomn]==-1)
       {
           snakemove();
           remainingsteps--;
           return 1;
       }
}
return 0;
}


int main()
{
    srand(time(NULL));
    char ch;//to keep the value return from function printmainpage
    int gameinput;
    int successstepp;
    int numerrors=0;
    ch=printmainpage();
   if (ch=='a')
   {
       system("cls");
       printboarder();
       printremainingsteps();
       setbeginingarray();
       printsnakearray();
       do
       {
           gameinput=checkinput();
           if(gameinput==0 && numerrors==1)
           {
               system("cls");
               gotoxy(borderx/2-5,bordery/2);
               printf("!!error input!!");
               gotoxy(0,bordery-1);
               return 1;
           }
           if(gameinput==0 && numerrors<1)
            {
                system("cls");
                printboarder();
                printsnakearray();
                printremainingsteps();
                printerror();
                numerrors++;
                continue;
            }
            if(gameinput==1)
            {
                numerrors=0;
                successstepp=directionsteps();
                if(successstepp==1)
                {
                    system("cls");
                    printboarder();
                    printsnakearray();
                    printremainingsteps();

                }
                if(successstepp==0)
                {
                    system("cls");
                    gotoxy(borderx/2-5,bordery/2);
                    printf("GAME OVER!");
                    gotoxy(borderx/2-5,bordery/2+1);
                    printf("your score is: %d",score);
                    gotoxy(0,bordery-1);
                    system("pause");
                    system("cls");
                    remainingsteps=firstnumsteps;
                    ch=printmainpage();
                    if(ch=='a')
                     {
                         system("cls");
                         setbeginingarray();
                         score=0;
                         printboarder();
                         printsnakearray();
                         printremainingsteps();
                     continue;
                     }
                        else
                        return 1;
                }
            }
       }while(1);
   }
   else

    return 1;

   return 0;
}



