//SNAKE GAME//

#include <graphics.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

char player[50];
int length = 15;
int endcheck = 3;
int score = 0;

void gameOver(int);
void gameStart();
void gameStart1(int,int [],int [],int,int,int);
void menu();
void scoreRecord(int);
void scoreHistory();
void levelTwo(int);


int main(void)
{
	//levelTwo();
	system("cls");
	system("color A");
	printf("\n\t\t Enter name: ");
	gets(player);
	menu();
    return 0;
}

//CONSOLE//
void menu()
{
	int choice;
	int levelChoice;
	
	system("cls");
	system("color A");
		
	printf("\n\n\t\t\t\t Snake Game");
	printf("\n\t\t \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Welcome to the Main Menu %s \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2",player);
    printf("\n\n\n\t\t 1.Start Game.\n");
    printf("\t\t 2.Score record.\n");
    printf("\t\t 3.Play Again.\n");
    printf("\t\t 4.Level Selection.\n");
    printf("\t\t 5.Exit.");
    
    printf("\n\n\n\t\t Enter your choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
    case 1:
    	gameStart();
    	break;
    case 2:
    	scoreHistory();
		break;
    case 3:
        gameStart();
        break;
    case 4:
    	system("cls");
    	printf("\n\n\t\t \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 Level Selection \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2",player);
    	printf("\n\n\n\t\t 1.Level 1\n");
    	printf("\t\t 2.Level 2\n");
    	printf("\t\t 3.Main Menu");
    	printf("\n\n\n\t\t Enter your choice: ");
    	scanf("%d", &levelChoice);
    	switch(levelChoice)
    	{
    		case 1:
    			gameStart();
    			break;
    		case 2:
    			initwindow(1009,813);
    			score = 0;
    			levelTwo(score);
    			break;
    		case 3:
    			menu();
    			break;
    		default:
    			printf("Enter Valid Choice!");
		}
		break;
    case 5:
    	exit(0);
    default:
    	printf("Enter Valid Choice!");
    }
}

//ACTUAL GAME//
void gameStart()
{
    initwindow(1009,813);


    //TO GET MAXIMUM COORDINATES//
    int maxX = getmaxx();
    int maxY = getmaxy();    

    //TO GET MIDPOINT COORDINATES//
    int midX = maxX/2;
    int midY = maxY/2;

    //SNAKES COORDINATES//
    int x[500],y[500];

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
    	if(score >= 20)
    	{
    		gameStart1(constantDirection,x,y,xCoordinateOfFood,yCoordinateOfFood,score);	
		}
    	
        //BORDERS//
        setfillstyle(SOLID_FILL,GREEN);
        bar(0,0,maxX,10);
        bar(0,0,10,maxY);
        bar(0,maxY,maxX,maxY-10);
        bar(maxX,maxY,maxX-10,0); //Right bar

        //FOOD
        srand(time(NULL));

        if(x[0] == xCoordinateOfFood && y[0] == yCoordinateOfFood)
        {
            length += 1;
            score += 10;
            //Black food color
            setfillstyle(1,BLACK);
            bar(xCoordinateOfFood,yCoordinateOfFood,xCoordinateOfFood+10,yCoordinateOfFood+10); 
			//Food production 
            do
            {
                xCoordinateOfFood = 15 + rand() % 990;
                yCoordinateOfFood = 15 + rand() % 790;
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
		//Gameover condition
		if(x[0] >= 1000 || x[0] <= 0 || y[0] >= 800 || y[0] <= 0)
        {
            gameOver(score);
            break;
        }
		for(int i = 2; i < length; i++)
		{
			if(x[0] == x[i] && y[0] == y[i])
			{
				endcheck = i;
				break;
			}
		}
		if(x[0] == x[endcheck] && y[0] == y[endcheck])
		{
			gameOver(score);
			break;	
		}
    }
}

void gameStart1(int constantDirection, int x[0], int y[0], int xCoordinateOfFood, int yCoordinateOfFood,int score)
{
    //TO GET MAXIMUM COORDINATES//
    int maxX = getmaxx();
    int maxY = getmaxy();    

    //TO GET MIDPOINT COORDINATES//
    int midX = maxX/2;
    int midY = maxY/2;

    int direction;

    while(1)
    {
    	//Borders
    	setfillstyle(SOLID_FILL,GREEN);
    	bar(maxX-10,0,maxX,midY-50);
    		
    	//Gate
    	setfillstyle(SOLID_FILL,BLACK);
        bar(maxX-10,midY-50,maxX,midY+50);	

		//Borders
    	setfillstyle(SOLID_FILL,GREEN);
    	bar(maxX-10,midY+50,maxX,maxY);
    	
        setfillstyle(SOLID_FILL,GREEN);
        bar(0,0,maxX,10);
        bar(0,0,10,maxY);
        bar(0,maxY,maxX,maxY-10);
        //bar(maxX,maxY,maxX-10,0); //Right bar

        //FOOD
        srand(time(NULL));

        if(x[0] == xCoordinateOfFood && y[0] == yCoordinateOfFood)
        {
            length += 1;
            score += 10;
            //Black food color
            setfillstyle(1,BLACK);
            bar(xCoordinateOfFood,yCoordinateOfFood,xCoordinateOfFood+10,yCoordinateOfFood+10); 
			//Food production 
            do
            {
                xCoordinateOfFood = 15 + rand() % 990;
                yCoordinateOfFood = 15 + rand() % 790;
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
        
        //Enter the gate
        if(x[0] >= maxX-10 && x[0] <= maxX && y[0] >= midY-50 && y[0] <= midY+50)
        {
        	levelTwo(score);
		}
        
		//Gameover condition
		if(x[0] >= 1000 || x[0] <= 0 || y[0] >= 800 || y[0] <= 0)
        {
            gameOver(score);
            break;
        }
		for(int i = 2; i < length; i++)
		{
			if(x[0] == x[i] && y[0] == y[i])
			{
				endcheck = i;
				break;
			}
		}
		if(x[0] == x[endcheck] && y[0] == y[endcheck])
		{
			gameOver(score);
			break;	
		}
    }
}

void levelTwo(int score)
{
    //TO GET MAXIMUM COORDINATES//
    int maxX = getmaxx();
    int maxY = getmaxy();    

    //TO GET MIDPOINT COORDINATES//
    int midX = maxX/2;
    int midY = maxY/2;

    //SNAKES COORDINATES//
    int x[500],y[500];
    int length = 15;

    x[0] = midX;
    y[0] = midY;

    //MOVEMENT COORDINATES//
    int constantDirection = 1;

    int xCoordinateOfFood = midX - 100;
    int yCoordinateOfFood = midY - 100;

    int direction;

    while(1)
    {
        //BORDERS//
        setfillstyle(SOLID_FILL,GREEN);
        bar(0,0,maxX,10); 								//Top bar
        bar(0,0,10,maxY);
        bar(0,maxY,maxX,maxY-10);
        bar(maxX,maxY,maxX-10,0);
             
        //Obstacle
        setfillstyle(SOLID_FILL,GREEN);
        bar(50,50,maxX-50,60);   						//Top Obstacle
        bar(50,maxY-50,maxX-50,maxY-60);				//Bottom Obstacle
        
        bar(midX-200,midY-200,midX+200,midY-190);  		//Mid Top Obstacle
        bar(midX-200,midY+200,midX+200,midY+190);  		//Mid Bottom Obstacle
        
        //FOOD
        srand(time(NULL));

        if(x[0] == xCoordinateOfFood && y[0] == yCoordinateOfFood)
        {
            length += 1;
            score += 10;
            //Black food color
            setfillstyle(1,BLACK);
            bar(xCoordinateOfFood,yCoordinateOfFood,xCoordinateOfFood+10,yCoordinateOfFood+10); 
			//Food production 
            do
            {
                xCoordinateOfFood = 15 + rand() % 990;
                yCoordinateOfFood = 15 + rand() % 790;
                
                //Food to generate outside top obstacle
                if(xCoordinateOfFood >= 50 && xCoordinateOfFood <= maxX-50 || yCoordinateOfFood >= 50 && yCoordinateOfFood <= 60)   
				{
                	xCoordinateOfFood = 15 + rand() % 990;
               		yCoordinateOfFood = 15 + rand() % 790;
				}
				//Food to generate outside bottom obstacle
				else if(xCoordinateOfFood >= 50 && xCoordinateOfFood <= maxX-50 || yCoordinateOfFood >= maxY-50 && yCoordinateOfFood <= maxY-60)
				{
                	xCoordinateOfFood = 15 + rand() % 990;
                	yCoordinateOfFood = 15 + rand() % 790;
				}
				//Food to generate outside mid top obstacle
				else if(xCoordinateOfFood >= midX-200 && xCoordinateOfFood <= midX+200 || yCoordinateOfFood >= midY-200 && yCoordinateOfFood <= midY-190)
				{
                	xCoordinateOfFood = 15 + rand() % 990;
                	yCoordinateOfFood = 15 + rand() % 790;
				}
				//Food to generate outside mid bottom obstacle
				else if(xCoordinateOfFood >= midX-200 && xCoordinateOfFood <= midX+200 || yCoordinateOfFood >= midY+200 && yCoordinateOfFood <= midY+190)
				{
                	xCoordinateOfFood = 15 + rand() % 990;
                	yCoordinateOfFood = 15 + rand() % 790;
				}
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
		//Gameover condition
		if(x[0] >= 1000 || x[0] <= 0 || y[0] >= 800 || y[0] <= 0)
        {
            gameOver(score);
            break;
        }
        //Top Obstacle
        if(x[0] >= 50 && x[0] < maxX-50 && y[0] >= 50 && y[0] < 60)
        {
        	gameOver(score);
        	break;
		}
		//Bottom Obstacle
		if(x[0] >= 50 && x[0] < maxX-50 && y[0] >= maxY-60 && y[0] < maxY-50)
        {
        	gameOver(score);
        	break;
		}
		//Mid Top Obstacle
		if(x[0] >= midX-200 && x[0] < midX+200 && y[0] >= midY-200 && y[0] < midY-190)
        {
        	gameOver(score);
        	break;
		}
		//Mid Bottom Obstacle
		if(x[0] >= midX-200 && x[0] < midX+200 && y[0] >= midY+190 && y[0] < midY+200)
        {
        	gameOver(score);
        	break;
		}
		//Snake kills itself
		for(int i = 2; i < length; i++)
		{
			if(x[0] == x[i] && y[0] == y[i])
			{
				endcheck = i;
				break;
			}
		}
		if(x[0] == x[endcheck] && y[0] == y[endcheck])
		{
			gameOver(score);
			break;	
		}
    }
}

//Game-Over screen
void gameOver(int score)
{
	settextstyle(10,0,5);
    int maxX = getmaxx();
    int maxY = getmaxy();

    int midX = maxX/2;
    int midY = maxY/2;

    char printScore[200];

    delay(100);

    int width = 285; //textwidth((char*)"GAME OVER!!!");
    int height = 59; //textheight((char*)"GAME OVER!!!");
    int width1 = 348; //textwidth((char*)"YOUR SCORE IS: ");
    int height1 = 59; //textheight((char*)"YOUR SCORE IS: ");
    
    setcolor(CYAN);
    outtextxy(midX-width/2,midY-height/2,(char*)"GAME OVER!!!");

    setcolor(RED);
    outtextxy(midX-width/2,(midY-100)-height/2,(char*)"GAME OVER!!!");

    sprintf(printScore,"YOUR SCORE IS: %d",score);
    outtextxy(midX-width1/2,(midY+100)-height1/2,printScore);

    int width2 = textwidth((char*)"Press E to go to Main menu");
    int height2 = textheight((char*)"Press E to go to Main menu");

    setcolor(CYAN);
    outtextxy(midX-width2/2,(midY+200)-height2/2,(char*)"Press E to goto Main menu");
      
	delay(2000);
	
    //Menu//
    while(1)
    {
		if(GetAsyncKeyState(69))
		{
			closegraph();
			scoreRecord(score);
			menu();
			break;
		}
    }
    
}

//Record in File
void scoreRecord(int score)
{
	char newplayer[20];
	int j;
	FILE *info;
	info = fopen("record.txt","a+");
	for(j=0; player[j]!='\0'; j++)
	{ 
		//To convert the first letter to capital
		newplayer[0] = toupper(player[0]);
		if(player[j-1]==' ')
		{
			newplayer[j] = toupper(player[j]);
			newplayer[j-1] = player[j-1];
		}
		else {
			newplayer[j] = player[j];
		}	
	}
	newplayer[j]='\0';
	fprintf(info,"\t\t\tPlayer: %s\n",newplayer);
	fprintf(info,"\t\t\tScore: %d\n",score);
	for(int i=0;i<=50;i++)
	{
		fprintf(info,"%c",'__');
	}
	fprintf(info,"\n");
	fclose(info);
}

//To see record history
void scoreHistory()
{
	system("cls");
	printf("\n\t\t\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2 Score History \xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\n\n");
	FILE *getInfo;
	char character;
	char back;
	
	getInfo = fopen("record.txt", "r");
	if(getInfo == NULL)
    {
        // Unable to open file hence exit
        printf("Unable to open file.\n");
        exit(0);
    }
    
	do{
		character = fgetc(getInfo);
		putchar(character);
	}while(character != EOF);
	fclose(getInfo);
	printf("\n\n\t\t\t Press 'B' to go to main menu: ");
	scanf(" %c", &back);
	back = toupper(back);
	if(back == 'B')
	{
		menu();	
	}	
}


