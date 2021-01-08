//SNAKE GAME//

#include <graphics.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>


void gameOver(int);
void gameStart();
void menu();
void scoreRecord(int);

int main()
{
	menu();
    return 0;
}

//CONSOLE//
void menu()
{
	int choice;
	
	system("cls");
	system("color A");
	
	char player[50];
	
	printf("\n\n\t\t\t\t Snake Game");
	printf("\n\t\t \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Welcome to the Main Menu \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf("\n\t\t Enter name: ");
	gets(player);
    printf("\n\n\n\t\t 1.Start Game.\n");
    printf("\t\t 2.Highscore record.\n");
    printf("\t\t 3.Play Again.\n");
    printf("\t\t 4.Exit.");
    
    printf("\n\n\n\t\t Enter your choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
    case 1:
    	gameStart();
    	break;
    case 2:
		break;
    case 3:
        gameStart();
        break;
    case 4:
    	exit(0);
    }
}

//ACTUAL GAME//
void gameStart()
{
    int endcheck;

    initwindow(1009,813,(char*)"Snake");


    //TO GET MAXIMUM COORDINATES//
    int maxX = getmaxx();
    int maxY = getmaxy();
    
    //printf("%d %d", maxX, maxY);

    //TO GET MIDPOINT COORDINATES//
    int midX = maxX/2;
    int midY = maxY/2;
    
    //printf("%d %d", midX, midY);

    //SNAKES COORDINATES//
    int x[500],y[500];
    int length = 10;

    x[0] = midX;
    y[0] = midY;

    //MOVEMENT COORDINATES//
    int constantDirection = 2;

    int xCoordinateOfFood = midX - 100;
    int yCoordinateOfFood = midY - 100;

    int direction;

    //SCORE//
    int score = 0;
    int check;


    while(1)
    {
        //BORDERS//
        setfillstyle(SOLID_FILL,GREEN);
        bar(0,0,maxX,10);
        bar(0,0,10,maxY);
        bar(0,maxY,maxX,maxY-10);
        bar(maxX,maxY,maxX-10,0);

        //FOOD
        srand(time(NULL));

        if(x[0] == xCoordinateOfFood && y[0] == yCoordinateOfFood)
        {
            length += 1;
            score += 10;
            setfillstyle(1,BLACK);
            bar(xCoordinateOfFood,yCoordinateOfFood,xCoordinateOfFood+10,yCoordinateOfFood+10);
            do
            {
                xCoordinateOfFood = 1 + rand() % 1000;
                yCoordinateOfFood = 1 + rand() % 800;
            }while(getpixel(xCoordinateOfFood,yCoordinateOfFood) !=0 && xCoordinateOfFood > 10 && yCoordinateOfFood > 10);

            xCoordinateOfFood = xCoordinateOfFood/10;
            xCoordinateOfFood = xCoordinateOfFood*10;
            yCoordinateOfFood = yCoordinateOfFood/10;
            yCoordinateOfFood = yCoordinateOfFood*10;
        }
        setfillstyle(1,CYAN);
        bar(xCoordinateOfFood,yCoordinateOfFood,xCoordinateOfFood+10,yCoordinateOfFood+10);
        setfillstyle(1,GREEN);


        //MOVEMENT//
        if(GetAsyncKeyState(VK_RIGHT))
        {
            direction = 1;
        }else if(GetAsyncKeyState(VK_LEFT))
        {
            direction = 2;
        }else if(GetAsyncKeyState(VK_UP))
        {
            direction = 3;
        }else if(GetAsyncKeyState(VK_DOWN))
        {
            direction = 4;
        }else
        {
            direction = 0;
        }

        switch(direction)
        {
        case 0 :
            if(constantDirection == 1)
            {
                x[0] += 10;
            }else if(constantDirection == 2)
            {
                x[0] -= 10;
            }else if(constantDirection == 3)
            {
                y[0] -= 10;
            }else if(constantDirection == 4)
            {
                y[0] += 10;
            }else
            {
                direction = 0;
            }
            break;
        case 1 :
            x[0] += 10;
            constantDirection = 1;
            break;
        case 2 :
            x[0] -=10;
            constantDirection = 2;
            break;
        case 3 :
            y[0] -= 10;
            constantDirection = 3;
            break;
        case 4 :
            y[0] += 10;
            constantDirection = 4;
            break;
        }

        //SNAKE//
        for(int i = 0; i < length; i++)
        {
            bar(x[i],y[i],x[i]+10,y[i]+10);
        }

        for(int i = 499; i > 0; i--)
        {
            x[i] = x[i-1];
            y[i] = y[i-1];
        }

        delay(100);
        cleardevice();
        //printf("%d   %d   %d   %d  %d  \n",x[0],y[0],xCoordinateOfFood,yCoordinateOfFood,length);

        if(x[0] >= 1000 || x[0] <= 0 || y[0] >= 800 || y[0] <= 0)
        {
            gameOver(score);
            break;
        }

    }
}

//Game-Over screen
void gameOver(int score)
{
    int maxX = getmaxx();
    int maxY = getmaxy();

    int midX = maxX/2;
    int midY = maxY/2;

    char printScore[200];

    delay(100);
    cleardevice();

    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,5);
    int width = 276; //textwidth((char*)"GAME OVER!!!");
    int height = 46; //textheight((char*)"GAME OVER!!!");
    int width1 = 339; //textwidth((char*)"YOUR SCORE IS: ");
    int height1 = 46; //textheight((char*)"YOUR SCORE IS: ");
    
    printf("%d %d %d %d %d %d", width, height, width1, height1, midX, midY);

    setcolor(CYAN);
    outtextxy(midX-width/2,midY-height/2,(char*)"GAME OVER!!!");
    //delay(100);

    setcolor(RED);
    outtextxy(midX-width/2,(midY-100)-height/2,(char*)"GAME OVER!!!");

    sprintf(printScore,"YOUR SCORE IS: %d",score);
    outtextxy(midX-width1/2,(midY+100)-height1/2,printScore);

    int width2 = textwidth((char*)"Press P to PLAY AGAIN!!!");
    int height2 = textheight((char*)"Press P to PLAY AGAIN!!!");

    setcolor(CYAN);
    outtextxy(35+midX-width2/2,10+(midY+200)-height2/2,(char*)"Press P to PLAY AGAIN!!!");
     
    printf("%d %d %d %d", width, height, width1, height1); 
	delay(1000);
	
    //PLAY AGAIN//
    while(1)
    {
		if(GetAsyncKeyState(80))
		{
			closegraph();
			gameStart();
			break;
		}
		else if(GetAsyncKeyState(69))
		{
			closegraph();
			scoreRecord(score);	
		}
    }
    
}

void scoreRecord(int s)
{
	char player[20],newplayer[20],c;
	int j;
	FILE *info;
	info=fopen("record.txt","a+");
	getch();
	system("cls");
	printf("Enter your name\n");
	scanf("%s",player);
	for(j=0;player[j]!='\0';j++)
	{ 
	//to convert the first letter to capital
	newplayer[0] = toupper(player[0]);
	if(player[j-1]==' ')
	{
	newplayer[j] = toupper(player[j]);   //for higher score to be upper so touppercase
	newplayer[j-1]=player[j-1];}
	
	else newplayer[j]=player[j];
	
	}
	newplayer[j]='\0';
	fprintf(info,"\t\t\t\tList\n");
	fprintf(info,"Player Name %s\n",newplayer); 
	fprintf(info,"Score:%d\n",s);
	for(int i=0;i<=50;i++)
	{
		fprintf(info,"%c",'__');
	}
	fprintf(info,"\n");
	fclose(info);
	printf("Do you want to see past score records press 'y'\n");
	char ch = getch();
	system("cls");
	if(ch=='y' or ch=='Y'){
	info=fopen("record.txt","r");//to read the file
	do{
	putchar(c=getc(info));
	}while(c!=EOF);}//prints till the end of file
	fclose(info);
}

