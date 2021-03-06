//이 게임은 동아리과제를 위해서 만들어졌습니다.개발자는 곽건,이치우,이원재는 도움을 주었습니다.
//
#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h> 

//이것은 비쥬얼스튜디오로 작성됬습니다.알아서 고치시기를 
int board[52][52] = { 0 };//정답을 저장하는 게임의 본질
int showboard[52][52] = { 0 };//보여주기 위한 배열
int cnt = 0;//폭탄개수세는 변수다.
int bomb = 0;//폭탄의 개수 그 자체다.
int inr, inc;
int boardsize = 0;//판의 크기를 저장한다.


void inputbomb();//폭탄의 개수를 입력받는 함수
void resetshowboard();//showboard를 초기화하는 함수
void bombplace();//폭탄을 랜덤으로 설치하는 함수
void printshowboard();//showboard를 누르지 보여지지 않은 상태인 -1로 초기화하는 함수
void boxis_0();//누른곳이 0을 처리하는 함수
void boxis_num();//누른곳이 숫자면을 처리하는 함수
void input();//좌표를 입력받는  함수
int gameclear();//게임이 완료되었는지 확인하는 함수
int boxis_bomb();//누른곳이 폭탄이라면을 처리하는 함수
void resetboard();//board를 리셋하는 함수
void searchconnectedzero();//연결된 0을 찾아 출력하는 함수
void show(int inr, int inc);//파라미터로 넘긴 좌표의 값을 출력하는 함수
void inputboardsize();//보드의 크기를 입력하는 함수
void showall();//이스터에그를 위한 정답공개기



int main()
{
	char trash;
	int op;
	srand(time(NULL));//랜덤표 만들기  
	printf("지뢰찾기:\n현재 이 게임은 개발중에 있습니다.\n각 숫자는 8방향 안 블럭에 있는 폭탄의 개수를 나타냅니다.\n처음에 판의 크기와 폭탄의 개수를 입력하면 게임이 시작됩니다.\n");
	printf("\n1.게임시작\n2.종료\n"), scanf_s("%d", &op);
	if (op == 2)
	{
		exit(1);
	}
	
	system("cls");

	newgame:;//새로운게임시작시 필요한 goto포인트

	inputboardsize();//보드의 크기를 입력받고,
	inputbomb();//폭탄의 개수도 입력받고,
	resetshowboard();//쇼보드를 리셋하고
	resetboard();//보드를 리셋하고
	bombplace();//폭탄을 설치한다.
	

	while (1)
	{
		printf("\n\n\n\n\n");
		printshowboard();//쇼보드를 출력한다.
		input();//좌표를 입력받는다.

		if (board[inr][inc] == 0)//누른곳이 0이라면
		{
			boxis_0();//0을 누른처리를 하고,
			searchconnectedzero();//인접0을 처리해 보여준다.
		}
		else if (board[inr][inc] >= 1000)//폭탄을 밟으면
		{
			if (boxis_bomb() == 1)//이거는 다시시작누른거
			{
				goto newgame;
			}
			else//이거는 게임끝
			{
				break;
			}
		}
		else//숫자를 누른것을 나타낸다.
		{
			boxis_num();//숫자를 누른것에 대해서 처리를 해준다.
		}

		if (gameclear() == 1)//게임을 클리어했으면
		{
			break;//나간다.//게임클리어에대한 처리는 함수안에 있다.
		}
		system("cls");//한번 입력을 할때마다 콘솔창을 다시 불러와 정보 업데이트를 한다  
	}

}


void inputbomb()//폭탄의 개수를 입력받는 함수
{
	printf("폭탄의 개수를 입력하세요:"); scanf_s("%d", &bomb);
	if (bomb>boardsize*boardsize || bomb<1)//폭탄의 수가 보드의 제곱이면 안되고,1보다 작아도 안된다
	{
		printf("잘못입력했습니다.");
		inputbomb();//잘못입력하면 재귀로 처리
	}
}


void resetshowboard()//showboard의 값을 -1로 초기화 시켜주는 함수 
{
	for (int i = 0; i<boardsize+1; i++)
	{
		for (int j = 0; j<boardsize+1; j++)
		{
			showboard[i][j] = -1;//이중으로 돌면서 -1로 초기화한다.
		}
	}
}

void bombplace()//이 몸이 처리한 버그라고 해두지//이원재의 도움
{
	for (int i = 0; i<bomb; i++)//폭탄을 설치한 곳의 팔방에 1씩 더해준다. 판 만들기  
	{
		int a, b;
		do//핵심인데,같은곳을 안나오게 처리를 했다.
		{
			a = rand() % boardsize + 1;
			b = rand() % boardsize + 1;
		} while (board[a][b] >= 1000);


		board[a - 1][b - 1] += 1;//8방향을 더하는 부분
		board[a - 1][b] += 1;
		board[a - 1][b + 1] += 1;

		board[a][b - 1] += 1;
		board[a][b] += 1000;
		board[a][b + 1] += 1;

		board[a + 1][b - 1] += 1;
		board[a + 1][b] += 1;
		board[a + 1][b + 1] += 1;

	}
}

void printshowboard()//showboard를 출력하는 부분이다.
{
	int row = 1, col = 1;
	printf("\t\t\t\t");
	for (row = 1; row <= boardsize; row++)//여기는 열번호 출력부
	{
		printf("%d\t", row);
	}
	printf("\n\n\n");//다음줄로 넘기고
	for (int i = 1; i<boardsize+1; i++)//쇼보드 출력부 행을 돈다
	{
		printf("\t\t\t");
		printf("%d\t",i);//열번호 출력
		for (int j = 1; j<boardsize+1; j++)//열을돈다.
		{
			if (showboard[i][j] == -1)//한번도 안간곳은 블럭으로
			{
				printf("▩\t");
			}
			else
			{
				printf("%d\t", showboard[i][j]);//누른곳은 이거
			}
		}
		printf("\n\n\n");
	}
}

void boxis_0()//누른곳이 0이라면 주변 8방향을 보여준다.
{
	showboard[inr - 1][inc - 1] = board[inr - 1][inc - 1];
	showboard[inr - 1][inc] = board[inr - 1][inc];
	showboard[inr - 1][inc + 1] = board[inr - 1][inc + 1];

	showboard[inr][inc - 1] = board[inr][inc - 1];
	showboard[inr][inc] = board[inr][inc];
	showboard[inr][inc + 1] = board[inr][inc + 1];

	showboard[inr + 1][inc - 1] = board[inr + 1][inc - 1];
	showboard[inr + 1][inc] = board[inr + 1][inc];
	showboard[inr + 1][inc + 1] = board[inr + 1][inc + 1];
}

void boxis_num()//입력한 곳이 그냥 숫자라면
{
	showboard[inr][inc] = board[inr][inc];
}

int gameclear()//게임클리어
{
	cnt = 0;
	for (int i = 1; i<boardsize+1; i++)//게임클리어
	{
		for (int j = 1; j<boardsize+1; j++)
		{
			if (0 <= showboard[i][j] && showboard[i][j]<7)
			{
				cnt++;//폭탄이 아니면서 눌린곳을 센다 
			}
		}
	}
	if (cnt == (boardsize*boardsize - bomb))//게임클리어확인 만약 전체칸-폭탄수가 cnt 라면 께임이 끝난다. 
	{
		system("cls");
		printf("깼습니다!\n\n\n");
		return 1;//깻으면 1을 리턴한다.
	}
}

int boxis_bomb()//폭탄 밟음을 처리
{
	char in;
	printf("폭탄 밟음!");
	getchar();
	printf("\n다시 하시겠습니까?Y/N"); scanf_s("%c", &in);
	if (in == 'y' || in == 'Y')
	{
		system("cls");
		return 1;
	}
}

void input()//좌표입력함수
{
	printf("행번호:"), scanf_s("%d", &inr);
	printf("열번호:"), scanf_s("%d", &inc);
	if ((inr <= 0 || inr >= boardsize+1) || (inc <= 0 && inc >= boardsize+1))
	{
		if (inr == 2002&&inc==1208)//이스터에그다
		{
			showall();//정답을 보여주는 함수다.
			printf("이거는 이스터에그입니다.\n개발자:곽건,이치우,이원재(도움)\n즐거운 게임하세요!!\n");
		}
		if (inr == 2002 && inc == 1025)//이스터에그다
		{
			showall();
		}
		printf("다시입력하세요!\n");//입력을 이상하게 했을시에 다시 입력을 받는곳   
		input();//재귀로 재입력
	}
}

void resetboard()//보드리셋함수
{
	for (int i = 0; i<boardsize+2; i++)
	{
		for (int j = 0; j<boardsize+2; j++)
		{
			board[i][j] = 0;//다 0으로 초기화 한다.
		}
	}
}



void searchconnectedzero()//인접한0을 나타내준다.
{
	int notgoodway=100;//별로 좋은 방법이 아니다.
	while (notgoodway--)//그냥 100번 돌면서 0과 이어진부분을 나타낸다.
	{
		for (int i = 1; i < boardsize+1; i++)
		{
			for (int j = 1; j < boardsize+1; j++)
			{
				if (showboard[i][j]==0)
				{
					show(i, j);
				}
			}
		}
	}
}

void show(int inr,int inc)//보여주는 함수다.
{

	showboard[inr - 1][inc - 1] = board[inr - 1][inc - 1];
	showboard[inr - 1][inc] = board[inr - 1][inc];
	showboard[inr - 1][inc + 1] = board[inr - 1][inc + 1];

	showboard[inr][inc - 1] = board[inr][inc - 1];
	showboard[inr][inc] = board[inr][inc];
	showboard[inr][inc + 1] = board[inr][inc + 1];

	showboard[inr + 1][inc - 1] = board[inr + 1][inc - 1];
	showboard[inr + 1][inc] = board[inr + 1][inc];
	showboard[inr + 1][inc + 1] = board[inr + 1][inc + 1];
}

void inputboardsize()//보드사이즈를 입력받는 함수다.
{
	printf("판의 크기를 입력하세요a*a:"), scanf_s("%d", &boardsize);
	if (boardsize > 50||boardsize<6)//50보다 커도 안되고(오버플로우)혹은 6보다 작으면 안된다.(그냥 6은 되야할거같아서)
	{
		printf("판의 크기가 너무 크거나 작습니다.다시 입력하세요!\n");
		inputboardsize();//재귀로 재 입력
	}
}

void showall()//정답을 보여주는 함수다.이스터에그용이다.
{
	printf("정답:\n");//여기서 부터  테스트시 정답을 알려주기 위함 
	for (int i = 1; i<boardsize + 1; i++)
	{
		printf("\t\t\t");
		for (int j = 1; j<boardsize + 1; j++)
		{
			printf("\t%d", board[i][j]);
		}
		printf("\n\n");
	}
	printf("\n\n\n");//여기까지 
}
//주석 다 달았다ㅋ










