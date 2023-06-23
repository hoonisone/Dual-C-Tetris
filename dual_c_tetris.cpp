#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define USER1_X 30
#define USER1_Y 11
#define USER1_O_COLOR 12
#define USER1_I_COLOR 4*16
#define USER1_B_COLOR 0
#define USER1_T_COLOR 12

#define USER2_X 120
#define USER2_Y 11
#define USER2_O_COLOR 9
#define USER2_I_COLOR 1*16
#define USER2_B_COLOR 0
#define USER2_T_COLOR 9
/////////////////////////////////////////////////
#define SPEED_A 100

///////////////////////////////////////key코드 정의 
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32
#define W 119
#define A 97
#define S 115
#define D 100
#define TAB 9
//////////////////////////////////텍스트 색깔 지 
#define BLACK 0
#define BLUE 1
#define GREEN 2 
#define CYAN 3 
#define RED 4
#define MAGENTA 5 
#define BROWN 6
#define LIGHTGRAY 7 
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13 
#define YELLOW 14
#define WHITE 15

#define GARO 10
#define SERO 17

#define false 0
#define true 1

//enum {false, true};

char Game1;
char Game2;

int Block1[GARO][SERO][2],		Block2[GARO][SERO][2];   // 색, 모양
int CurBlock1[4][4],  	CurBlock2[4][4];
int NextBlock1[4][4], 	NextBlock2[4][4];

int Score1,		Score2;
int Goal1,		Goal2;
int Level1,		Level2;
int Speed1,		Speed2;

int CurColor1,	CurColor2;
int CurTurn1,	CurTurn2;
int CurSort1,	CurSort2;
int CurShape1,  CurShape2;
int CurX1,   	CurX2;
int CurY1,   	CurY2;

int NextColor1, NextColor2;
int NextTurn1,  NextTurn2;
int NextSort1,  NextSort2;
int NextShape1, NextShape2;

int NewBlockOn1,NewBlockOn2;

int Rank1, 		Rank2;

clock_t LevelUpEvent1,LevelUpEvent2;

int Rank[11];

//////////////////////////

void CursorView(char show);
void gotoxy(int x, int y);
void Color(int color_number);
void F(int user, char mode, int num);
void DrawMab(int user);
void DrawInformation(int user);
void DrawBlock(int user, char mode);
void SetBlock(int X, int Y, int color, int shape);
void check_key(void);
void BlockSeting(int arr[][4], int Sort, int Color, int Turn);
void SetNextBlock(int user);
void ResetCurBlock(int user);
void SetCurBlock(int user);
void ResetAll(void);
void GameReady();
void delay(clock_t n);
int BlockGuideLine(int User);
void NextBlock(int User);
void IsEnd(int User);
void DownBlock(int user);
void RemoveBlock(int User);
void IsLinePull(int User, int RLine);
void EraseLine(int User, int RLine);
void DrawRank(int user);
void RenewRank(int user);
void ResetGame(int user);
void Preview(int user);
void MakeLine(int User, int num);

int main(void)
{
	CursorView(0);
	system("mode con cols=180 lines=60");

	DrawMab(1);
	DrawMab(2);
	
	DrawInformation(1);
	DrawInformation(2);

	ResetAll();
	//MakeLine(1, 5);
	GameReady();
}

void GameReady()
{
  		while(1){
			while(!kbhit()){
				clock_t current = clock();
				delay(10);
				if(Game1 == 'S'){
					if(NewBlockOn1){
						RemoveBlock(1);
						SetCurBlock(1);
						DrawBlock(1,'C');
						SetNextBlock(1);
						DrawBlock(1,'N');
						NewBlockOn1 = false;
					}
					if(current%Speed1 <= 30)
						DownBlock(1);
					DrawInformation(1);
				}
				else if(Game1 == 'E'){
					DrawRank(1);
					Game1 == 'Z';
				}
				if(Game2 == 'S'){
					if(NewBlockOn2){
						RemoveBlock(2);
						SetCurBlock(2);
						DrawBlock(2,'C');
						SetNextBlock(2);
						DrawBlock(2,'N');
						NewBlockOn2 = false;
					}
//					if(200<clock()%Speed2&&clock()%Speed2 < 210)
					if(current%Speed2 <= 30)
						DownBlock(2);
					DrawInformation(2);
				}
				else if(Game2 == 'E'){
					DrawRank(2);
					Game2 == 'Z';
				}
			}       
			check_key();
		}
}

void DownBlock(int user)
{
	if(user == 1)
	{
		CurY1++;
		ResetCurBlock(1);
		BlockGuideLine(1);
		DrawBlock(1,'B');
		DrawBlock(1,'C');
	}
	else if(user == 2)
	{
		CurY2++;
		ResetCurBlock(2);
		BlockGuideLine(2);
		DrawBlock(2,'B');
		DrawBlock(2,'C');
	}
}

void CursorView(char show) //화면의 커서를 보이거나 숨기기
{
 CONSOLE_CURSOR_INFO ConsoleCursor; // 콘솔커서 정보 구조체		//콘솔중 커서에 대한 정보를 저장하는 구조체이다.
 ConsoleCursor.bVisible = show; // SHOW 보임 , HIDE 안보임
 ConsoleCursor.dwSize = 1; // 커서 사이즈(세로길이)
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE) , &ConsoleCursor); // 설정		(어떤 콘솔에 대하여, 어떻게 할것인가?)
}

void gotoxy(int x, int y)///////////////////원하는 위치로 커서 이 동 
{
    COORD Pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void Color(int color_number)////////////////////////텍스트 색이나 택스트 글자색 지정 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color_number);
}

void F(int user, char mode, int num)
{ 
	int i;
	if(user == 1){
		if( mode == 'O'){
			Color(USER1_O_COLOR);
			for( i=0 ; i<num ; i++ )
				printf("■");
		}
		else if( mode == 'I'){ 
			Color(USER1_I_COLOR);
			for( i=0 ; i<num ; i++ )
				printf("  ");
		}
		else if( mode == 'B'){
			Color(USER1_B_COLOR);
			for( i=0 ; i<num ; i++ )
				printf("  ");
		}
	}
	
	else if(user == 2){
		if( mode == 'O'){
			Color(USER2_O_COLOR);
			for( i=0 ; i<num ; i++ )
				printf("■");
		}
		else if( mode == 'I'){
			Color(USER2_I_COLOR);
			for( i=0 ; i<num ; i++ )
				printf("  ");
		}
		else if( mode == 'B'){
			Color(USER2_B_COLOR);
			for( i=0 ; i<num ; i++ )
				printf("  ");
		}
	}
}

void DrawMab(int user)
{	
	int i=0;
	if(user == 1){
		gotoxy(USER1_X,USER1_Y+i);F(1,'O',23);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I',21);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I', 8);F(1,'O',12);F(1,'I', 1);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I', 8);F(1,'O', 1);F(1,'B',10);F(1,'O', 1);F(1,'I',1);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I', 8);F(1,'O', 1);;F(1,'B', 10);F(1,'O', 1);F(1,'I',1);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I', 1);F(1,'O', 6);F(1,'I', 1);F(1,'O', 1);F(1,'B',10);F(1,'O', 1);F(1,'I', 1);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I', 1);F(1,'O', 1);F(1,'B', 4);F(1,'O', 1);F(1,'I', 1);F(1,'O', 1);F(1,'B',10);F(1,'O', 1);F(1,'I', 1);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I', 1);F(1,'O', 1);F(1,'B', 4);F(1,'O', 1);F(1,'I', 1);F(1,'O', 1);F(1,'B',10);F(1,'O', 1);F(1,'I', 1);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I', 1);F(1,'O', 1);F(1,'B', 4);F(1,'O', 1);F(1,'I', 1);F(1,'O', 1);F(1,'B',10);F(1,'O', 1);F(1,'I', 1);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I', 1);F(1,'O', 1);F(1,'B', 4);F(1,'O', 1);F(1,'I', 1);F(1,'O', 1);F(1,'B',10);F(1,'O', 1);F(1,'I', 1);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I', 1);F(1,'O', 6);;F(1,'I', 1);F(1,'O', 1);F(1,'B',10);F(1,'O', 1);F(1,'I', 1);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I', 8);F(1,'O', 1);;F(1,'B', 10);F(1,'O', 1);F(1,'I',1);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I', 8);F(1,'O', 1);;F(1,'B', 10);F(1,'O', 1);F(1,'I',1);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I', 8);F(1,'O', 1);;F(1,'B', 10);F(1,'O', 1);F(1,'I',1);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I', 8);F(1,'O', 1);;F(1,'B', 10);F(1,'O', 1);F(1,'I',1);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I', 8);F(1,'O', 1);;F(1,'B', 10);F(1,'O', 1);F(1,'I',1);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I', 8);F(1,'O', 1);;F(1,'B', 10);F(1,'O', 1);F(1,'I',1);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I', 8);F(1,'O', 1);;F(1,'B', 10);F(1,'O', 1);F(1,'I',1);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I', 8);F(1,'O', 1);;F(1,'B', 10);F(1,'O', 1);F(1,'I',1);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I', 8);F(1,'O', 1);;F(1,'B', 10);F(1,'O', 1);F(1,'I',1);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I', 8);F(1,'O',12);F(1,'I', 1);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I',21);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I',21);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I',21);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I',21);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I',21);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I',21);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O', 1);F(1,'I',21);F(1,'O', 1);i++;
		gotoxy(USER1_X,USER1_Y+i);F(1,'O',23);i++;
	}
	if(user == 2)
	{
		gotoxy(USER2_X,USER2_Y+i);F(2,'O',23);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I',21);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I', 8);F(2,'O',12);F(2,'I', 1);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I', 8);F(2,'O', 1);F(2,'B',10);F(2,'O', 1);F(2,'I', 1);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I', 8);F(2,'O', 1);F(2,'B',10);F(2,'O', 1);F(2,'I', 1);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I', 1);F(2,'O', 6);F(2,'I', 1);F(2,'O', 1);F(2,'B',10);F(2,'O', 1);F(2,'I', 1);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I', 1);F(2,'O', 1);F(2,'B', 4);F(2,'O', 1);F(2,'I', 1);F(2,'O', 1);F(2,'B',10);F(2,'O', 1);F(2,'I', 1);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I', 1);F(2,'O', 1);F(2,'B', 4);F(2,'O', 1);F(2,'I', 1);F(2,'O', 1);F(2,'B',10);F(2,'O', 1);F(2,'I', 1);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I', 1);F(2,'O', 1);F(2,'B', 4);F(2,'O', 1);F(2,'I', 1);F(2,'O', 1);F(2,'B',10);F(2,'O', 1);F(2,'I', 1);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I', 1);F(2,'O', 1);F(2,'B', 4);F(2,'O', 1);F(2,'I', 1);F(2,'O', 1);F(2,'B',10);F(2,'O', 1);F(2,'I', 1);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I', 1);F(2,'O', 6);F(2,'I', 1);F(2,'O', 1);F(2,'B',10);F(2,'O', 1);F(2,'I', 1);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I', 8);F(2,'O', 1);F(2,'B',10);F(2,'O', 1);F(2,'I', 1);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I', 8);F(2,'O', 1);F(2,'B',10);F(2,'O', 1);F(2,'I', 1);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I', 8);F(2,'O', 1);F(2,'B',10);F(2,'O', 1);F(2,'I', 1);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I', 8);F(2,'O', 1);F(2,'B',10);F(2,'O', 1);F(2,'I', 1);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I', 8);F(2,'O', 1);F(2,'B',10);F(2,'O', 1);F(2,'I', 1);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I', 8);F(2,'O', 1);F(2,'B',10);F(2,'O', 1);F(2,'I', 1);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I', 8);F(2,'O', 1);F(2,'B',10);F(2,'O', 1);F(2,'I', 1);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I', 8);F(2,'O', 1);F(2,'B',10);F(2,'O', 1);F(2,'I', 1);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I', 8);F(2,'O', 1);F(2,'B',10);F(2,'O', 1);F(2,'I', 1);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I', 8);F(2,'O',12);F(2,'I', 1);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I',21);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I',21);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I',21);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I',21);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I',21);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I',21);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O', 1);F(2,'I',21);F(2,'O', 1);i++;
		gotoxy(USER2_X,USER2_Y+i);F(2,'O',23);i++;
	}
}

void DrawInformation(int user)
{
	int i=-9;
	if(user == 1)
	{
		if(Score1>Score2)
			Color(YELLOW);
		else
			Color(USER1_T_COLOR);
		gotoxy(USER1_X-3,USER1_Y+i);printf("**    **    ******    ********   *******      ****   ");i++;
		gotoxy(USER1_X-3,USER1_Y+i);printf("**    **   **    **   **         **    **    *  **   ");i++;
		gotoxy(USER1_X-3,USER1_Y+i);printf("**    **   ***        **         **    **       **   ");i++;
		gotoxy(USER1_X-3,USER1_Y+i);printf("**    **     ****     ********   ******         **   ");i++;
		gotoxy(USER1_X-3,USER1_Y+i);printf("**    **        ***   **         **   **        **   ");i++;
		gotoxy(USER1_X-3,USER1_Y+i);printf("********   **    **   **         **    **       **   ");i++;
		gotoxy(USER1_X-3,USER1_Y+i);printf(" ******     ******    ********   **     **   ********");i++;
		
		Color(WHITE);
		gotoxy(USER1_X+6,USER1_Y+4);printf("N E X T ");
		if(LevelUpEvent1>clock())
			Color(YELLOW);
		gotoxy(USER1_X+6,USER1_Y+22);printf("LEVEL: %7d",Level1);
		gotoxy(USER1_X+6,USER1_Y+24);printf(" GOAL: %7d",Goal1);
		gotoxy(USER1_X+6,USER1_Y+26);printf("SCORE: %7d",Score1);
	}
	else if(user == 2)
	{
		if(Score1<Score2)
			Color(YELLOW);
		else
			Color(USER2_T_COLOR);
		gotoxy(USER2_X-3,USER2_Y+i);printf("**    **    ******    ********   *******       ***** ");i++;
		gotoxy(USER2_X-3,USER2_Y+i);printf("**    **   **    **   **         **    **    **    **");i++;
		gotoxy(USER2_X-3,USER2_Y+i);printf("**    **   ***        **         **    **    **   ** ");i++;
		gotoxy(USER2_X-3,USER2_Y+i);printf("**    **     ****     ********   ******         **   ");i++;
		gotoxy(USER2_X-3,USER2_Y+i);printf("**    **        ***   **         **   **       **    ");i++;
		gotoxy(USER2_X-3,USER2_Y+i);printf("********   **    **   **         **    **     **     ");i++;
		gotoxy(USER2_X-3,USER2_Y+i);printf(" ******     ******    ********   **     **   ********");i++;
		
		Color(WHITE);
		gotoxy(USER2_X+6,USER2_Y+4);printf("N E X T ");
		if(LevelUpEvent2>clock())
			Color(YELLOW);
		gotoxy(USER2_X+6,USER2_Y+22);printf("LEVEL: %7d",Level2);
		gotoxy(USER2_X+6,USER2_Y+24);printf(" GOAL: %7d",Goal2);
		gotoxy(USER2_X+6,USER2_Y+26);printf("SCORE: %7d",Score2);
		
	}
}

void DrawBlock(int user, char mode) /// 전채블록,cur, next불록 전체 출력 
{
	int i,j;
	
	if(user == 1)
	{
		if(mode == 'C'){
			gotoxy(USER1_X+20,USER1_Y+20);
			Color(LIGHTRED);
			printf("■■■■■■■■■■■■");
			for( j=0 ; j<4 ; j++ )
			for( i=0 ; i<4 ; i++ )
				if(CurBlock1[i][j] != 0){
					SetBlock(USER1_X+20+CurX1*2+i*2,USER1_Y+3+CurY1+j, CurBlock1[i][j], CurShape1);
					SetBlock(USER1_X+20+CurX1*2+i*2,USER1_Y+20,YELLOW,1);
				}
		}	
		else if(mode == 'B')
			for( j=0 ; j<SERO ; j++ )
			for( i=0 ; i<GARO ; i++ )
			{
				SetBlock(USER1_X+20+i*2, USER1_Y+3+j, Block1[i][j][0], Block1[i][j][1]);
			}
		else if(mode == 'N')
			for( j=0 ; j<4 ; j++ )
			for( i=0 ; i<4 ; i++ )
			{
				SetBlock(USER1_X+6+i*2, USER1_Y+6+j, NextBlock1[i][j], NextShape1);
			}
	}
	else if(user == 2)
	{
		if(mode == 'C'){
			gotoxy(USER2_X+20,USER2_Y+20);
			Color(LIGHTBLUE);
			printf("■■■■■■■■■■■■");
			for( j=0 ; j<4 ; j++ )
			for( i=0 ; i<4 ; i++ )
				if(CurBlock2[i][j] != 0){
					SetBlock(USER2_X+20+CurX2*2+i*2,USER2_Y+3+CurY2+j, CurBlock2[i][j], CurShape2);
					SetBlock(USER2_X+20+CurX2*2+i*2,USER2_Y+20,YELLOW,1);
				}
		}
		else if(mode == 'B')
			for( j=0 ; j<SERO ; j++ )
			for( i=0 ; i<GARO ; i++ )
			{
				SetBlock(USER2_X+20+i*2, USER2_Y+3+j, Block2[i][j][0], Block2[i][j][1]);
			}
		else if(mode == 'N')
			for( j=0 ; j<4 ; j++ )
			for( i=0 ; i<4 ; i++ )
			{
				SetBlock(USER2_X+6+i*2, USER2_Y+6+j, NextBlock2[i][j], NextShape2);
			}
	}
}

void SetBlock(int X, int Y, int color, int shape)/// 전채블록,cur, next불록 실제 출력 
{
	gotoxy(X,Y);
	Color(color);
	switch(shape)
	{
		case 1:
			printf("■");
			break;
		case 2:
			printf("▩");
			break;
		case 3:
			printf("▥");
			break;
		case 4:
			printf("▤");
			break;
		case 5:
			printf("▣");
			break;
	}
}


void check_key(void)
{
	int i,j;
	int Bool_Tab = false;
	int Bool_Space = false;
	if(kbhit())
	{
	    int key=getch();
			switch(key)
		    {
		        case W:
		        	if(Game1 == 'S')
					{
				        CurTurn1 += 1;
				        ResetCurBlock(1);
				        for( i=0 ; i<4 ; i++ )
			   			for( j=0 ; j<4 ; j++ )
			    		    if(CurBlock1[i][j] != 0)
							{
			        		    if(CurX1+i<0)
			               			CurX1 = -i;
			               		else if(CurX1+i>9)
		                    		CurX1 = 9-i;
		                    	if(CurY1+j>16)
								{
									CurTurn1 -= 1;
		                			ResetCurBlock(1);
		                			break;
		                		}
				        		else if(Block1[CurX1+i][CurY1+j][0] != 0)
								{
		                			CurTurn1 -= 1;
		                			ResetCurBlock(1);
		                			break;
		                		}
		                	}
						DrawBlock(1,'B');
						DrawBlock(1,'C');
				        break;
				    }
			    case A:
			    	if(Game1 == 'S')
			    	{
				        CurX1 -= 1;
				        for( i=0 ; i<4 ; i++ )
			   			for( j=0 ; j<4 ; j++ )
			    		    if(CurBlock1[i][j] != 0){
			        		    if(CurX1+i<0)
			               			CurX1 = -i;
				        		else if(Block1[CurX1+i][CurY1+j][0] != 0){
		                			CurX1 +=1;
		                			return;
		                		}
		                	}
		                ResetCurBlock(1);
						DrawBlock(1,'B');
						DrawBlock(1,'C');
				        break;
				    }
			    case S:
			    	if(Game1 == 'S')
			    	{
				        CurY1 += 1;
				        ResetCurBlock(1);
				        BlockGuideLine(1);
						DrawBlock(1,'B');
						DrawBlock(1,'C');
				    	break;
			   		}
			    case D:
			    	if(Game1 == 'S')
			    	{
				        CurX1 += 1;
				        for( i=0 ; i<4 ; i++ )
		       	 		for( j=0 ; j<4 ; j++ )
		            		if(CurBlock1[i][j] != 0){
		                		if(CurX1+i>9)
		                    		CurX1 = 9-i;
		                		else if(Block1[CurX1+i][CurY1+j][0] != 0){
		                    		CurX1 -=1;
		                    		return;
		                    	}
		                    }
		                ResetCurBlock(1);
						DrawBlock(1,'B');
						DrawBlock(1,'C');
				        break;
				    }
			    case TAB :
			    	if(Game1 == 'S')
			    	{
				    	while(!Bool_Tab){
				        CurY1 += 1;
				        ResetCurBlock(1);
				        Bool_Tab = BlockGuideLine(1);
						DrawBlock(1,'B');
						DrawBlock(1,'C');
						delay(3);
						}
				    	break;
				    }
			    case UP:
			    	if(Game2 == 'S')
			    	{
				        CurTurn2 += 1;
						ResetCurBlock(2);
						for( i=0 ; i<4 ; i++ )
			   			for( j=0 ; j<4 ; j++ )
			    		    if(CurBlock2[i][j] != 0){
			        		    if(CurX2+i<0)
			               			CurX2 = -i;
			               		else if(CurX2+i>9)
		                    		CurX2 = 9-i;
		                    	if(CurY2+j>16){
									CurTurn2 -= 1;
		                			ResetCurBlock(2);
		                			break;
		                		}
				        		else if(Block2[CurX2+i][CurY2+j][0] != 0){
		                			CurTurn2 -= 1;
		                			ResetCurBlock(2);
		                			break;
		                		}
		                    }
						DrawBlock(2,'B');
						DrawBlock(2,'C');
			        	break;
			    	}
			    case LEFT:
			    	if(Game2 == 'S')
			    	{
				        CurX2 -= 1;
						for( i=0 ; i<4 ; i++ )
			   			for( j=0 ; j<4 ; j++ )
			    		    if(CurBlock2[i][j] != 0){
			        		    if(CurX2+i<0)
			               			CurX2 = -i;
				        		else if(Block2[CurX2+i][CurY2+j][0] != 0){
		                			CurX2 +=1;
		                			return;
		                		}
		                	}
		                ResetCurBlock(2);
						DrawBlock(2,'B');
						DrawBlock(2,'C');
				        break;
					}
			    case DOWN:
			    	if(Game2 == 'S')
			    	{
				        CurY2 += 1;   
						ResetCurBlock(2);
						BlockGuideLine(2);
						DrawBlock(2,'B');
						DrawBlock(2,'C');
				    	break;
				    }
			    case RIGHT:
			    	if(Game2 == 'S')
			    	{
				        CurX2 += 1;
						for( i=0 ; i<4 ; i++ )
		       	 		for( j=0 ; j<4 ; j++ )
		            		if(CurBlock2[i][j] != 0){
		                		if(CurX2+i>9)
		                    		CurX2 = 9-i;
		                		else if(Block2[CurX2+i][CurY2+j][0] != 0){
		                    		CurX2 -=1;
		                    		return;
		                    	}
		                    }
		                ResetCurBlock(2);
						DrawBlock(2,'B');
						DrawBlock(2,'C');
				    	break;
				    }
			    case SPACE:
			    	if(Game2 == 'S')
			    	{
				    	while(!Bool_Space){
				        CurY2 += 1;
				        ResetCurBlock(2);
				        Bool_Space = BlockGuideLine(2);
						DrawBlock(2,'B');
						DrawBlock(2,'C');
						delay(3);
						}
				    	break;
				case 'r':
					if(Game1 != 'S')
						ResetGame(1);	
					if(Game2 != 'S')
						ResetGame(2);
				    }
			}
	}
}


void BlockSeting(int arr[][4], int Sort, int Color, int Turn)///Next나 Cur블록에 블록 내용물을 집어넣는다. 
{
	int i,j;
	for( j=0 ; j<4 ; j++ )
    for( i=0 ; i<4 ; i++ )
            arr[i][j] = 0;
	switch(Sort)
	{
		case 1:
	        if		(Turn%2+1 == 1)	{	arr[2][0]=Color;	arr[2][1]=Color;	arr[2][2]=Color;	arr[2][3]=Color;	}
	        else if	(Turn%2+1 == 2)	{	arr[0][2]=Color;	arr[1][2]=Color;	arr[2][2]=Color;	arr[3][2]=Color;	}
			break;
	    case 2:
									{	arr[1][1]=Color;	arr[1][2]=Color;	arr[2][1]=Color;	arr[2][2]=Color;	}
	    	break;
	    case 3:
	        if		(Turn%4+1 == 1)	{	arr[1][1]=Color;	arr[2][1]=Color;	arr[2][2]=Color;	arr[2][3]=Color;	}
	        else if	(Turn%4+1 == 2)	{	arr[0][2]=Color;	arr[1][2]=Color;	arr[2][1]=Color;	arr[2][2]=Color;	}
	        else if	(Turn%4+1 == 3)	{	arr[1][0]=Color;	arr[1][1]=Color;	arr[1][2]=Color;	arr[2][2]=Color;	}
	        else if	(Turn%4+1 == 4)	{	arr[1][1]=Color;	arr[1][2]=Color;	arr[2][1]=Color;	arr[3][1]=Color;	} 
	        break;
	    case 4:
	        if		(Turn%4+1 == 1)	{	arr[1][1]=Color;	arr[1][2]=Color;	arr[1][3]=Color;	arr[2][1]=Color;	}
	        else if	(Turn%4+1 == 2)	{	arr[0][1]=Color;	arr[1][1]=Color;	arr[2][1]=Color;	arr[2][2]=Color;	}
	        else if	(Turn%4+1 == 3)	{	arr[1][2]=Color;	arr[2][0]=Color;	arr[2][1]=Color;	arr[2][2]=Color;	}
	        else if	(Turn%4+1 == 4)	{	arr[1][1]=Color;	arr[1][2]=Color;	arr[2][2]=Color;	arr[3][2]=Color;	}
	        break;
	    case 5:
	        if		(Turn%4+1 == 1)	{	arr[1][1]=Color;	arr[2][0]=Color;	arr[2][1]=Color;	arr[3][1]=Color;	}
	        else if	(Turn%4+1 == 2)	{	arr[2][0]=Color;	arr[2][1]=Color;	arr[2][2]=Color;	arr[3][1]=Color;	}
	        else if	(Turn%4+1 == 3)	{	arr[1][1]=Color;	arr[2][1]=Color;	arr[2][2]=Color;	arr[3][1]=Color;	}
	        else if	(Turn%4+1 == 4)	{	arr[1][1]=Color;	arr[2][0]=Color;	arr[2][1]=Color;	arr[2][2]=Color;	}
	        break;

	    case 6:
	        if		(Turn%2+1 == 1)	{	arr[0][1]=Color;	arr[1][1]=Color;	arr[1][2]=Color;	arr[2][2]=Color;	}
	        else if	(Turn%2+1 == 2)	{	arr[1][2]=Color;	arr[1][3]=Color;	arr[2][1]=Color;	arr[2][2]=Color;	}
	        break;

	    case 7:
	        if		(Turn%2+1 == 1)	{	arr[1][2]=Color;	arr[2][1]=Color;	arr[2][2]=Color;	arr[3][1]=Color;	}
	        else if	(Turn%2+1 == 2)	{	arr[1][1]=Color;	arr[1][2]=Color;	arr[2][2]=Color;	arr[2][3]=Color;	}
	        break;
	}
}

void SetNextBlock(int user)
{
	int Sort  = rand()%7+1;
	int Color = rand()%8+8;
	int turn  = rand()%4+1;
	int Shape = 1; //rand()%5+1;
	if(user == 1)
	{
		NextSort1  = Sort;
		NextColor1 = Color;
		NextTurn1  = turn;
		NextShape1 = Shape;
		BlockSeting(NextBlock1, NextSort1, NextColor1, NextTurn1);
	}
	else if( user == 2)
	{
		NextColor2 = Color;
		NextSort2  = Sort;
		NextTurn2  = turn;
		NextShape2 = Shape;
		BlockSeting(NextBlock2, NextSort2, NextColor2, NextTurn2);
	}
}

void ResetCurBlock(int user)
{
	if(user == 1)
		BlockSeting(CurBlock1, CurSort1, CurColor1, CurTurn1);
	else if(user == 2)
		BlockSeting(CurBlock2, CurSort2, CurColor2, CurTurn2);
}

void SetCurBlock(int user)
{
	int i,j;
	if(user == 1)
	{
		CurX1 = 3;
		CurY1 = 0;
		CurColor1 = NextColor1;
		CurSort1  = NextSort1;
		CurTurn1  = NextTurn1;
		CurShape1 = NextShape1;
		ResetCurBlock(1);
	}
	else if(user == 2)
	{
		CurX2 = 3;
		CurY2 = 0;
		CurColor2 = NextColor2;
		CurSort2  = NextSort2;
		CurTurn2  = NextTurn2;
		CurShape2 = NextShape2;
		ResetCurBlock(2);
	}
}

void ResetAll(void)
{
	int i,j;
	for( j=0 ; j<SERO ; j++ )
    for( i=0 ; i<GARO ; i++ )
    {
        Block1[i][j][0] = 0;
        Block1[i][j][1] = 1;
        Block2[i][j][0] = 0;
        Block2[i][j][1] = 1;
    }
	Game1 = 'S';
	Game2 = 'S';
	Speed1 = 1000;
	Speed2 = 1000;
	NewBlockOn1 = true;
	NewBlockOn2 = true;
		
	Score1=0;
	Score2=0;
	Level1=1;
	Level2=1;
	Goal1 =3;
	Goal2 =3;
	
	LevelUpEvent1 = 0;
	LevelUpEvent2 = 0;
	
	SetNextBlock(1);
	SetNextBlock(2);
}

void ResetGame(int user)
{
	int i,j;
	if(user == 1)
	{
		for( j=0 ; j<SERO ; j++ )
	    for( i=0 ; i<GARO ; i++ )
	    {
	        Block1[i][j][0] = 0;
	        Block1[i][j][1] = 1;
	    }
	    for( j=0 ; j<4 ; j++ )
	    for( i=0 ; i<4 ; i++ )
	    {
	        CurBlock1[i][j] = 0;
	        NextBlock1[i][j] = 0;
	    }
		Speed1 = 1000;
		NewBlockOn1 = true;	
		Score1=0;
		Level1=1;
		Goal1 =3;
		LevelUpEvent1 = 0;
		SetNextBlock(1);
		Game1 = 'S';
	}
	else if(user == 2)
	{
		for( j=0 ; j<SERO ; j++ )
	    for( i=0 ; i<GARO ; i++ )
	    {
	        Block2[i][j][0] = 0;
	        Block2[i][j][1] = 1;
	    }
	    for( j=0 ; j<4 ; j++ )
	    for( i=0 ; i<4 ; i++ )
	    {
	        CurBlock2[i][j] = 0;
	        NextBlock2[i][j] = 0;
	    }
		Speed2 = 1000;
		NewBlockOn2= true;	
		Score2=0;
		Level2=1;
		Goal2 =3;
		LevelUpEvent2 = 0;	
		SetNextBlock(2);
		Game2 = 'S';
	}
}

void delay(clock_t n)
{
	clock_t start = clock();
  	while(clock() - start < n)
  	;
}

int BlockGuideLine(int User)//나중에 스페이스로 쭉 낼릴때 쓰려고 boolean연산자 사 용 
{
	int i,j;
	if(User == 1){
	    for( i=0 ; i<4 ; i++ )
	    for( j=0 ; j<4 ; j++ )
	        if(CurBlock1[i][j] != 0){   
				if(CurY1+j>16){
	                NextBlock(1);
	                return true;
	            }
	            else if(Block1[CurX1+i][CurY1+j][0] != 0 ){
	                NextBlock(1);
	                return true;
	            }
	        }
	    return false;
	}
	else if(User == 2){
	    for( i=0 ; i<4 ; i++ )
	    for( j=0 ; j<4 ; j++ )
	        if(CurBlock2[i][j] != 0){    
	            if(CurY2+j>16){
	                NextBlock(2);
	                return true;
	            }
	            else if(Block2[CurX2+i][CurY2+j][0] != 0 ){
	                NextBlock(2);
	                return true;
	            }
	        }
	    return false;
	}
	return false;
}

void NextBlock(int User)
{
	int i,j;
	
    if(User == 1){
        CurY1 -= 1;
        for( i=0 ; i<4 ; i++ )
        for( j=0 ; j<4 ; j++ )
            if(CurBlock1[i][j] != 0){
                Block1[CurX1+i][CurY1+j][0] = CurColor1;
                Block1[CurX1+i][CurY1+j][1] = CurShape1;
            }
        NewBlockOn1 = true;
        Score1 += Level1*5;
        IsEnd(1);
        if(Game1 == 'E')
            return;
    }
    else if(User == 2){

        CurY2 -= 1;
        for( i=0 ; i<4 ; i++ )
        for( j=0 ; j<4 ; j++ )
            if(CurBlock2[i][j] != 0)
            	{
                Block2[CurX2+i][CurY2+j][0] = CurColor2;
                Block2[CurX2+i][CurY2+j][1] = CurShape2;
        		}
		NewBlockOn2 = true;
        Score2 += Level2*5;
        IsEnd(2);
        if(Game2 == 'E')
            return;
    }    
}

void IsEnd(int User)
{
	int i,j;
    if(User == 1){
        for( i=0 ; i<GARO ; i++  ){
            if(Block1[i][1][0] != 0){
                if(Game1 != 'E'){
                	RenewRank(1);
                	Game1 = 'E';
                	DrawInformation(1);
                    return;
                  }
            }
        }
    }
    else if(User == 2){
        for( i=0 ; i<GARO ; i++ ){
            if(Block2[i][1][0] != 0){
                if(Game2 != 'E'){
                	RenewRank(2);
                	Game2 = 'E';
                	DrawInformation(2);
                    return;
                }
            }
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RemoveBlock(int User)
{
    int i;
    if(User == 1)
        for( i=CurY1 ; i<CurY1+4 ; i++ )
        {
            IsLinePull(1, i);
        }
    else if(User == 2)
        for( i=CurY2 ; i<CurY2+4 ; i++ )
        {
            IsLinePull(2, i);
        }
}      
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IsLinePull(int User, int RLine)
{
	int i;
	
    if(User == 1){
            for( i=0 ; i<GARO ; i++ ){
                if(Block1[i][RLine][0] == 0)
                    return;
            }
            EraseLine(1,RLine);
            Goal1 -= 1;
            if(Goal1 == 0){

                Level1 ++;
                Goal1 = Level1+3;
                Score1 *= 2;
                
                if(Level1 < 6){
                	Speed1 -= SPEED_A;
                }
            	else if(Level1 <10){
            		MakeLine(1, 1);
            		Speed1 -= (int) SPEED_A/3;
				}
                else if(Level1 <15){
                	MakeLine(1, 2);
            		Speed1 -= (int) SPEED_A/5;
                }

                LevelUpEvent1 = clock() + 3000;
            }
    }
    else if(User == 2){
            for( i=0 ; i<GARO ; i++ ){
                if(Block2[i][RLine][0] == 0)
                    return;
            }
            EraseLine(2,RLine);
            Goal2 -= 1;    
            if(Goal2 == 0){

                Level2 ++;
                Goal2 = Level2+5;
                Score2 *= 2;
                
                if(Level2 < 6){
                	Speed2 -= SPEED_A;
                }
            	else if(Level2 <10){
            		MakeLine(2, 1);
            		Speed2 -= (int) SPEED_A/3;
				}
                else if(Level2 <15){
                	MakeLine(2, 2);
            		Speed2 -= (int) SPEED_A/5;
                }
                
                LevelUpEvent2 = clock() + 3000;
                
            }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void EraseLine(int User, int RLine)
{
	int i,j;
	
    if(User == 1)
    for( i=RLine ; i>=1 ; i--)
    for( j=0 ; j<GARO ; j++ ){
        Block1[j][i][0] = Block1[j][i-1][0];
        Block1[j][i][1] = Block1[j][i-1][1];
	}
    else if(User == 2)
        for( i=RLine ; i>=1 ; i--)
        for( j=0 ; j<GARO ; j++ ){
        	Block2[j][i][0] = Block2[j][i-1][0];
            Block2[j][i][1] = Block2[j][i-1][1];
        }
}

void DrawRank(int user)
{
	int i;
	if(user == 1)
	{
		gotoxy(USER1_X+23,USER1_Y+4);
		printf("RANK     SCORE");
		for( i=0 ; i<10 ; i++)
		{
			Color(LIGHTRED);
			if(Rank[i] == Score1)
				Color(YELLOW);
			gotoxy(USER1_X+23,USER1_Y+6+i);
			printf("%2d위  %8d",i+1,Rank[i]);
		}
	}
	else if(user == 2)
	{
		gotoxy(USER2_X+23,USER2_Y+4);
		printf("RANK     SCORE");
		for( i=0 ; i<10 ; i++)
		{
			Color(LIGHTBLUE);
			if(Rank[i] == Score2)
				Color(YELLOW);
			gotoxy(USER2_X+23,USER2_Y+6+i);
			printf("%2d위  %8d",i+1,Rank[i]);
		}
	}

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RenewRank(int User)
{
	int i;
    int temp;
    if(User == 1)
        Rank[10] = Score1;
    else if(User ==2)
        Rank[10] = Score2;
    for( i=10 ; i>0 ; i-- )
        if(Rank[i]>Rank[i-1]){
            temp = Rank[i-1];
            Rank[i-1] = Rank[i];
            Rank[i] = temp;
        }
		else{
        	break;
		}
	return;
}

void MakeLine(int User, int num)
{
	int i, j, k, temp;
	if(User == 1){
		for( k=0 ; k<num ; k++){
			temp = rand()%GARO;
		    for( i=1 ; i<SERO-1 ; i++)
		    for( j=0 ; j<GARO ; j++ ){
				Block1[j][i][0] = Block1[j][i+1][0];
				Block1[j][i][1] = Block1[j][i+1][1];
		    }
		    for( j=0 ; j<GARO ; j++ ){
		    		Block1[j][SERO-1][0] = LIGHTGRAY;
		   			Block1[j][SERO-1][1] = 1;
		   	}
		   	Block1[temp][SERO-1][0] = 0;
		   	Block1[temp][SERO-1][1] = 1;
	   	}
   }
   
   else if(User == 2){
		for( k=0 ; k<num ; k++){
			temp = rand()%GARO;
		    for( i=1 ; i<SERO-1 ; i++)
		    for( j=0 ; j<GARO ; j++ ){
				Block2[j][i][0] = Block2[j][i+1][0];
				Block2[j][i][1] = Block2[j][i+1][1];
		    }
		    for( j=0 ; j<GARO ; j++ ){
		    		Block2[j][SERO-1][0] = LIGHTGRAY;
		   			Block2[j][SERO-1][1] = 1;
		   	}
		   	Block1[temp][SERO-1][0] = 0;
		   	Block1[temp][SERO-1][1] = 1;
	   	}
   }
}
