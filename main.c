#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <ctime>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77


using namespace std;

int breakLoop = 0;
int conditionChecker=0;
int input = RIGHT;
int temp = RIGHT;
int snakeOneInitialLength = 3, snakeOneScore = 0, snakeOneBitten = 0, snakeOneCoordinates=0;
int snakeTwoInitialLength = 3, snakeTwoScore = 0, snakeTwoBitten = 0, snakeTwoCoordinates=0;
int user_selection=0;
char snakeOne_segment='*';
char snakeTwo_segment='#';
int secondPlayer=0;

struct snakeXY {
	int x;
	int y;
} food;

const int maximum_snake_length = 50;
struct snakeXY first_snake[maximum_snake_length];
struct snakeXY second_snake[maximum_snake_length];

void gotoxy(int x, int y)
{
HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); 
COORD cursorCoord;
cursorCoord.X = x;
cursorCoord.Y = y;
SetConsoleCursorPosition(consoleHandle, cursorCoord);
}

void clearScreen()
{
system("cls");
}

void sleep(unsigned int mseconds)
{
      clock_t goal = mseconds + clock();
      while (goal > clock());
}

void playgorund_border() {
	gotoxy(90,1);
	for(int i=0; i<26; i++) {
		printf("@");
		printf("\n");
		for(int j=0; j<90; j++) {
			printf(" ");
		}
	}
	gotoxy(1, 26);
	for(int i=0; i<90; i++) {
		printf("@");
	}
}

void clear_line(int x, int y) {
	gotoxy(x,y);
	for(int i=0; i<60; i++) {
		printf(" ");
	}
}

void welcome_screen() {
	gotoxy(30, 8);
	printf("Snake v2.0\n");
	gotoxy(20, 11);
	printf("1. New Game");
	gotoxy(20, 12);
	printf("2. Load Game");
	gotoxy(20, 13);
	printf("Proceed by enterig your desired option's number: \n");
	scanf("%d", &user_selection);
	//printf("%d", user_selection);
	clear_line(30,8);
	clear_line(20,11);
	clear_line(20,12);
	clear_line(20, 13);
	clear_line(0, 14);
}

void proceed_menu() {
	switch(user_selection) {
		case 1:
		gotoxy(20, 11);
		printf("1. Singleplayer");
		gotoxy(20, 12);
		printf("2. Multiplayer");
		gotoxy(20, 13);
		printf("Proceed by enterig your desired option's number: \n");
		scanf("%d", &user_selection);
		break;
		case 2:
		gotoxy(20, 11);
		printf("Enter Your Username: \n");
		getch();
		FILE *loadFile;
				saveFile=fopen("save.dat", "r+");
				if(saveFile=='\0') {
					printf("File Not Accessible!");
				}
				for(int i=0; i<snakeOneInitialLength; i++) {
					fscanf(saveFile, "%d%d", snakeOne[i].x, snakeOne[i].y);
				}
				fclose(saveFile);
		break;
	}
	clear_line(20, 11);
	clear_line(20, 12);
	clear_line(20, 13);
	clear_line(0, 14);
}

void snake_initializer(struct snakeXY snakeOne[maximum_snake_length], char segmentOne) {
		
	gotoxy(15,10);
	snakeOne[0].x=3;
	snakeOne[0].y=5;
	snakeOne[1].x=2;
	snakeOne[1].y=5;
	snakeOne[2].x=1;
	snakeOne[2].y=5;
	gotoxy(1,5);
	printf("%c", segmentOne);
	gotoxy(2,5);
	printf("%c", segmentOne);
	gotoxy(3,5);
	printf("%c", segmentOne);

}

int snake_movement(struct snakeXY snakeOne[maximum_snake_length], char segmentOne, const int left, const int right, const int up, const int down){
	
	while(1){
		if(kbhit()){
			temp=getch();
			if(temp=='p') {
				//gotoxy(21,28);
				FILE *saveFile;
				saveFile=fopen("save.dat", "w+");
				if(saveFile=='\0') {
					printf("File Not Accessible!");
				}
				for(int i=0; i<snakeOneInitialLength; i++) {
					fprintf(saveFile, "%d%d", snakeOne[i].x, snakeOne[i].y);
				}
				fclose(saveFile);
				printf("wtf");
			}
			if(temp!=left && temp!=down && temp!=right && temp!=up) {
				continue;
			}
			if(input==right){
				if(temp==left) {
					continue;
				}
			}
			if(input==left){
				if(temp==right) {
					continue;
				}
			}
			if(input==up){
				if(temp==down) {
					continue;
				}
			}
			if(input==down){
				if(temp==up) {
					continue;
				}
			}
			input = temp;
		}
			gotoxy(snakeOne[snakeOneInitialLength-1].x,snakeOne[snakeOneInitialLength-1].y);
			printf(" ");
			for(int j=snakeOneInitialLength-2;j>=0;j--){
				snakeOne[j+1].x=snakeOne[j].x;
				snakeOne[j+1].y=snakeOne[j].y;
			}
			//switch case to analyse user's entered key
			if(input==up) {
				snakeOne[0].y-=1;
			}
			else if(input==down) {
				snakeOne[0].y+=1;
			}
			else if(input==left) {
				snakeOne[0].x-=1;
			}
			else if(input==right) {
				snakeOne[0].x+=1;
			}
			gotoxy(snakeOne[0].x,snakeOne[0].y);
			printf("%c", segmentOne);
			Sleep(90);
			//conditional statement to increase the snakeOneScore and initial length of the snake
			if(snakeOne[0].x==food.x && snakeOne[0].y==food.y){
				snakeOneInitialLength++;
				snakeOneScore+=10;
				break;
			}
			for(int i=1;i<snakeOneInitialLength && snakeOneBitten==0;i++){
				if(snakeOne[0].x==snakeOne[i].x && snakeOne[0].y==snakeOne[i].y)  {
					snakeOneBitten=1;
				}
			}
			//in case the snake bites itself
			if(snakeOneBitten==1) {
				conditionChecker=-1;
				break; 
			}
			if(snakeOne[0].x<1 || snakeOne[0].x>89 || snakeOne[0].y<1 || snakeOne[0].y>25) {
				snakeOneCoordinates=1;
			}
			//in case the snake moves out of the defined boundries
			if(snakeOneCoordinates==1) {
				conditionChecker=-2;
				break;
			}
	}
	return conditionChecker;
}

void interactions(struct snakeXY snakeOne[maximum_snake_length], char segmentOne, const int left, const int right, const int up, const int down) {
	gotoxy(20, 28);
	printf("Press p to save your progress");
	while(1){
		food.x=(rand())%90;
		food.y=(rand())%26;
		gotoxy(food.x,food.y);
		printf("+");
		//loop for the movement of the snake
		breakLoop = snake_movement(snakeOne, segmentOne, left, right, up, down);
		if(breakLoop==-1) {
			break;
		}
		else if(breakLoop==-2) {
			break;
		}
		gotoxy(100, 10);
		printf("Score: %d", snakeOneScore);
	}
}

void multiplayer_initializer(struct snakeXY snakeOne[maximum_snake_length], struct snakeXY snakeTwo[maximum_snake_length], char segmentOne, char segmentTwo) {
		
	gotoxy(15,10);
	snakeOne[0].x=3;
	snakeOne[0].y=5;
	snakeOne[1].x=2;
	snakeOne[1].y=5;
	snakeOne[2].x=1;
	snakeOne[2].y=5;
	gotoxy(1,5);
	printf("%c", segmentOne);
	gotoxy(2,5);
	printf("%c", segmentOne);
	gotoxy(3,5);
	printf("%c", segmentOne);
	
	gotoxy(20,20);
	snakeOne[0].x=20;
	snakeOne[0].y=20;
	snakeOne[1].x=19;
	snakeOne[1].y=20;
	snakeOne[2].x=18;
	snakeOne[2].y=20;
	gotoxy(18,20);
	printf("%c", segmentOne);
	gotoxy(19,20);
	printf("%c", segmentOne);
	gotoxy(20,20);
	printf("%c", segmentOne);

}

int multiplayer_movement(struct snakeXY snakeOne[maximum_snake_length], struct snakeXY snakeTwo[maximum_snake_length], char segmentOne, char segmentTwo){
	int left, right, up, down;
	while(1){
		while(1){
		if(kbhit()){
			temp=getch();
			if(temp=='a'||temp=='s'||temp=='d'||temp=='w') {
				secondPlayer=1;
				//input='d';
				left='a'; right='d'; up='w'; down='s';
			} else {
				left=LEFT; right=RIGHT; up=UP; down=DOWN;
			}
			if(temp!=left && temp!=down && temp!=right && temp!=up) {
				continue;
			}
			if(input==right){
				if(temp==left) {
					continue;
				}
			}
			if(input==left){
				if(temp==right) {
					continue;
				}
			}
			if(input==up){
				if(temp==down) {
					continue;
				}
			}
			if(input==down){
				if(temp==up) {
					continue;
				}
			}
			input = temp;
		}
			if(secondPlayer==1) {
				gotoxy(snakeTwo[snakeTwoInitialLength-1].x,snakeTwo[snakeTwoInitialLength-1].y);
				printf(" ");
				for(int j=snakeTwoInitialLength-2;j>=0;j--){
				snakeTwo[j+1].x=snakeTwo[j].x;
				snakeTwo[j+1].y=snakeTwo[j].y;
			}
			}
			gotoxy(snakeOne[snakeOneInitialLength-1].x,snakeOne[snakeOneInitialLength-1].y);
			printf(" ");
			for(int j=snakeOneInitialLength-2;j>=0;j--){
				snakeOne[j+1].x=snakeOne[j].x;
				snakeOne[j+1].y=snakeOne[j].y;
			}
			//switch case to analyse user's entered key
			if(input==up) {
				if(secondPlayer==1) {
					snakeTwo[0].y-=1;
				} else {
					snakeOne[0].y-=1;
				}
			}
			else if(input==down) {
				if(secondPlayer==1) {
					snakeTwo[0].y+=1;
				} else {
					snakeOne[0].y+=1;
					
				}
			}
			else if(input==left) { 
				if(secondPlayer==1) {
					snakeTwo[0].x-=1;
				} else {
					snakeOne[0].x-=1;
				}
			}
			else if(input==right) {
				if(secondPlayer==1) {
					snakeTwo[0].x+=1;
				} else {
					snakeOne[0].x+=1;
				}
			}
			
			if(secondPlayer==1) {
				gotoxy(snakeTwo[0].x,snakeTwo[0].y);
				printf("%c", segmentTwo);
			}
			gotoxy(snakeOne[0].x,snakeOne[0].y);
			printf("%c", segmentOne);
			Sleep(90);
			//conditional statement to increase the snakeOneScore and initial length of the snake
			if(secondPlayer==1) {
				if(snakeTwo[0].x==food.x && snakeTwo[0].y==food.y){
				snakeTwoInitialLength++;
				snakeTwoScore+=10;
				break;
				}
			}
			if(snakeOne[0].x==food.x && snakeOne[0].y==food.y){
				snakeOneInitialLength++;
				snakeOneScore+=10;
				break;
			}
			if(secondPlayer==1) {
				for(int i=1;i<snakeTwoInitialLength && snakeTwoInitialLength==0;i++){
					if(snakeTwo[0].x==snakeTwo[i].x && snakeTwo[0].y==snakeTwo[i].y)  {
						snakeTwoBitten=1;
					}
				}
			}
			for(int i=1;i<snakeOneInitialLength && snakeOneBitten==0;i++){
				if(snakeOne[0].x==snakeOne[i].x && snakeOne[0].y==snakeOne[i].y)  {
					snakeOneBitten=1;
				}
			}
			//in case the snake bites itself
			if(secondPlayer==1) {
				if(snakeTwoBitten==1) {
					conditionChecker=-1;
					break; 
				}
			}
			if(snakeOneBitten==1) {
				conditionChecker=-1;
				break; 
			}
			if(secondPlayer==1) {
				if(snakeTwo[0].x<1 || snakeTwo[0].x>89 || snakeTwo[0].y<1 || snakeTwo[0].y>25) {
				snakeTwoCoordinates=1;
			}
			}
			if(snakeOne[0].x<1 || snakeOne[0].x>89 || snakeOne[0].y<1 || snakeOne[0].y>25) {
				snakeOneCoordinates=1;
			}
			//in case the snake moves out of the defined boundries
			if(secondPlayer==1) {
				if(snakeTwoScore==1) {
				conditionChecker=-2;
				break;
				}
			}
			if(snakeOneCoordinates==1) {
				conditionChecker=-2;
				break;
			}
		}
		return conditionChecker;
	}
}

void multiplayer_interactions(struct snakeXY snakeOne[maximum_snake_length], struct snakeXY snakeTwo[maximum_snake_length], char segmentOne, char segmentTwo) {
	gotoxy(20, 28);
	printf("Press p to save your progress");
	while(1){
		food.x=(rand())%90;
		food.y=(rand())%26;
		gotoxy(food.x,food.y);
		printf("+");
		//loop for the movement of the snake
		breakLoop = multiplayer_movement(snakeOne, snakeTwo, segmentOne, segmentTwo);
		if(breakLoop==-1) {
			break;
		}
		else if(breakLoop==-2) {
			break;
		}
		gotoxy(100, 10);
		printf("Player 1 Score: %d", snakeOneScore);
		gotoxy(100, 11);
		printf("Player 2 Score: %d", snakeTwoScore);
	}
}

int main() {
	playgorund_border();
	welcome_screen();
	proceed_menu();
	if(user_selection==1) {
	snake_initializer(first_snake, snakeOne_segment);
	interactions(first_snake, snakeOne_segment, LEFT, RIGHT, UP, DOWN);
	}
	if(user_selection==2) {
		//temp='d';
		//input='d';
		multiplayer_initializer(first_snake, second_snake, snakeOne_segment, snakeTwo_segment);
		multiplayer_interactions(first_snake, second_snake, snakeOne_segment, snakeTwo_segment);
	}
	//snake_initializer();
	//interactions();
	clearScreen();
	gotoxy(0,0);
	printf("Game Over!\nThanks for playing.\nYou may exit the gamy by pressing any key\n\n");
	getch();
	return 0;
}
