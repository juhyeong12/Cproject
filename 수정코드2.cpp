
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdbool.h>

#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_Y 20
#define TREE_BOTTOM_X 45
#define BIRD_BOTTOM_Y 10


void SetConsoleView()
{
	system("mode con:cols=100 lines=25");
	system("title Google Dinosaurs. By BlockDMask.");
}


void GotoXY(int x, int y)
{
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}


int GetKeyDown()
{
	if (_kbhit() != 0)
	{
		return _getch();
	}
	return 0;
}


void DrawDino(int dinoY)
{
	GotoXY(0, dinoY);
	static bool legFlag = true;
	printf("        $$$$$$$ \n");
	printf("       $$ $$$$$$\n");
	printf("       $$$$$$$$$\n");
	printf("$      $$$      \n");
	printf("$$     $$$$$$$  \n");
	printf("$$$   $$$$$     \n");
	printf(" $$  $$$$$$$$$$ \n");
	printf(" $$$$$$$$$$$    \n");
	printf("  $$$$$$$$$$    \n");
	printf("    $$$$$$$$    \n");
	printf("     $$$$$$     \n");
	if (legFlag)
	{
		printf("     $    $$$    \n");
		printf("     $$          ");
		legFlag = false;
	}
	else
	{
		printf("     $$$  $     \n");
		printf("          $$    ");
		legFlag = true;
	}
}

void DrawTree(int treeX)
{
	GotoXY(treeX, TREE_BOTTOM_Y);
	printf("$$$$");
	GotoXY(treeX, TREE_BOTTOM_Y + 1);
	printf(" $$ ");
	GotoXY(treeX, TREE_BOTTOM_Y + 2);
	printf(" $$ ");
	GotoXY(treeX, TREE_BOTTOM_Y + 3);
	printf(" $$ ");
	GotoXY(treeX, TREE_BOTTOM_Y + 4);
	printf(" $$ ");
}

void DrawBird(int birdX)
{
	GotoXY(birdX, BIRD_BOTTOM_Y);
	printf("  $$$$$   ");
	GotoXY(birdX, BIRD_BOTTOM_Y + 1);
	printf(" ($$   $$) ");
}

void DrawObstacle(int obstacleType, int obstacleX)
{
	if (obstacleType == 1)
	{
		DrawTree(obstacleX);
	}
	else if (obstacleType == 2)
	{
		DrawBird(obstacleX);
	}
}

void DrawGameOver(const int score)
{
	system("cls");
	int x = 18;
	int y = 8;
	GotoXY(x, y);
	printf("===========================");
	GotoXY(x, y + 1);
	printf("======G A M E O V E R======");
	GotoXY(x, y + 2);
	printf("===========================");
	GotoXY(x, y + 5);
	printf("SCORE : %d", score);

	printf("\n\n\n\n\n\n\n\n\n");
	system("pause");
}


bool isCollision(const int obstacleType, const int obstacleX, const int dinoY)
{
	if (obstacleType == 1)
	{
		if (obstacleX <= 8 && obstacleX >= 4 &&
			dinoY > 8)
		{
			return true;
		}
	}
	else if (obstacleType == 2)
	{
		if (obstacleX <= 8 && obstacleX >= 2 &&
			dinoY >= BIRD_BOTTOM_Y && dinoY < BIRD_BOTTOM_Y + 2)
		{
			return true;
		}
	}
	return false;
}

int main()
{
	SetConsoleView();

	while (true)		//(v2.0) ���� ����
	{
		//���� ���۽� �ʱ�ȭ
		bool isJumping = false;
		bool isBottom = true;
		const int gravity = 3;

		int dinoY = DINO_BOTTOM_Y;
		int obstacleX = TREE_BOTTOM_X;
		int obstacleType = 0;

		int score = 0;
		clock_t start, curr;	//���� ���� �ʱ�ȭ
		start = clock();		//���۽ð� �ʱ�ȭ

		while (true)	//�� �ǿ� ���� ����
		{
			if (isCollision(obstacleType, obstacleX, dinoY))
				break;

			//zŰ�� ���Ȱ�, �ٴ��� �ƴҶ� ����
			if (GetKeyDown() == 'z' && isBottom)
			{
				isJumping = true;
				isBottom = false;
			}

			if (isJumping)
			{
				dinoY -= gravity;
			}
			else
			{
				dinoY += gravity;
			}

			if (dinoY >= DINO_BOTTOM_Y)
			{
				dinoY = DINO_BOTTOM_Y;
				isBottom = true;
			}

			obstacleX -= 2;
			if (obstacleX <= 0)
			{
				obstacleType = rand() % 2 + 1;
				obstacleX = TREE_BOTTOM_X;
			}

			if (dinoY <= 3)
			{
				isJumping = false;
			}

			DrawDino(dinoY);		//draw dino
			DrawObstacle(obstacleType, obstacleX);		//draw obstacle

			//(v2.0)
			curr = clock();
			if (((curr - start) / CLOCKS_PER_SEC) >= 1)
			{
				score++;	//���ھ� UP
				start = clock();	//���۽ð� �ʱ�ȭ
			}
			Sleep(60);
			system("cls");	//clear

			GotoXY(22, 0);
			printf("Score : %d ", score);
		}

		//(v2.0) ���� ���� �޴�
		DrawGameOver(score);
	}
	return 0;
}