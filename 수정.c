
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdbool.h>

#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_Y 20
#define TREE_BOTTOM_X 45

//새로운 장애물을 생성하는 함수
void DrawObstacle(int* treeX, int* birdX, bool* isBird)
{
    if (rand() % 2 == 0) //50% 확률로 bird 장애물 생성
    {
        *isBird = true;
        *birdX = TREE_BOTTOM_X;
        *treeX = 0;
    }
    else //50% 확률로 tree 장애물 생성
    {
        *isBird = false;
        *treeX = TREE_BOTTOM_X;
        *birdX = 0;
    }
}

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

//새 장애물 그리기
void DrawBird(int birdX, int birdY)
{
    GotoXY(birdX, birdY);
    printf("   /\\   ");
    printf(" /    \\ ");
    printf("/      \\");
    GotoXY(birdX, birdY + 1);
    printf(" <      >");
    GotoXY(birdX, birdY + 2);
    printf(" \\____/");
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


bool isCollision(const int treeX, const int dinoY, const bool isBird, const int birdX, const int birdY)
{
    if (isBird)
    {
        if (birdX <= 8 && birdX >= 4 &&
            dinoY - birdY <= 2 && dinoY - birdY >= 0)
        {
            return true;
        }
    }
    else
    {
        if (treeX <= 8 && treeX >= 4 &&
            dinoY > 8)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    SetConsoleView();

    while (true)        //(v2.0) 게임 루프
    {
        //게임 시작시 초기화
        bool isJumping = false;
        bool isBottom = true;
        const int gravity = 3;

        int dinoY = DINO_BOTTOM_Y;
        int treeX = TREE_BOTTOM_X;
        int birdX = 0;
        int birdY = 10;
        bool isBird = false;

        int score = 0;
        clock_t start, curr;    //점수 변수 초기화
        start = clock();        //시작시간 초기화

        while (true)    //한 판에 대한 루프
        {

            if (isCollision(treeX, dinoY, isBird, birdX, birdY))
                break;

            //z키가 눌렸고, 바닥이 아닐때 점프
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

            if (isBird)
            {
                birdX -= 2;
                if (birdX <= 0)
                {
                    DrawObstacle(&treeX, &birdX, &isBird);
                    birdY = 10;
                }
                else
                {
                    birdY -= 1;
                }

                DrawBird(birdX, birdY);
            }
            else
            {
                treeX -= 2;
                if (treeX <= 0)
                {
                    DrawObstacle(&treeX, &birdX, &isBird);
                }

                DrawTree(treeX);
            }

            if (dinoY <= 3)
            {
                isJumping = false;
            }

            DrawDino(dinoY);        //draw dino

            //(v2.0)
            curr = clock();
            if (((curr - start) / CLOCKS_PER_SEC) >= 1)
            {
                score++;    //스코어 UP
                start = clock();    //시작시간 초기화
            }
            Sleep(60);
            system("cls");    //clear


            GotoXY(22, 0);
            printf("Score : %d ", score);
        }

        //(v2.0) 게임 오버 메뉴
        DrawGameOver(score);
    }
    return 0;
}
