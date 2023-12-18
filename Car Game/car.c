#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

// ANSI escape codes for cursor positioning
#define gotoxy(x, y) printf("\033[%d;%dH", (y), (x))

int enemyY[3];
int enemyX[3];
int enemyFlag[3];

char car[4][4] = {{' ', '|', '|', ' '},
                  {'|', '|', '|', '|'},
                  {' ', '|', '|', ' '},
                  {'|', '|', '|', '|'}};

int carPos = WIN_WIDTH / 2;
int score = 0;

void drawBorder()
{
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            gotoxy(0 + j, i);
            printf("|");
            gotoxy(WIN_WIDTH - j, i);
            printf("|");
        }
    }

    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        gotoxy(SCREEN_WIDTH, i);
        printf("|");
    }
}

void updateScore()
{
    gotoxy(WIN_WIDTH + 7, 5);
    printf("Score: %d\n", score);
}

void genEnemy(int ind)
{
    enemyX[ind] = 17 + rand() % (33);
}

void drawCar()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gotoxy(j + carPos, i + 22);
            printf("%c", car[i][j]);
        }
    }
}

void drawEnemy(int ind)
{
    if (enemyFlag[ind] == 1)
    {
        gotoxy(enemyX[ind], enemyY[ind]);
        printf("**");
        gotoxy(enemyX[ind], enemyY[ind] + 1);
        printf(" ** ");
        gotoxy(enemyX[ind], enemyY[ind] + 2);
        printf("**");
        gotoxy(enemyX[ind], enemyY[ind] + 3);
        printf(" ** ");
    }
}

int collision()
{
    if (enemyY[0] + 4 >= 23)
    {
        if (enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9)
        {
            return 1;
        }
    }
    return 0;
}

void gameover()
{
    system("cls");
    printf("\n");
    printf("\t\t--------------------------\n");
    printf("\t\t-------- Game Over -------\n");
    printf("\t\t--------------------------\n\n");
    printf("\t\tPress any key to go back to the menu.");
    getch();
}

void eraseCar()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gotoxy(j + carPos, i + 22);
            printf(" ");
        }
    }
}

void eraseEnemy(int ind)
{
    if (enemyFlag[ind] == 1)
    {
        gotoxy(enemyX[ind], enemyY[ind]);
        printf("    ");
        gotoxy(enemyX[ind], enemyY[ind] + 1);
        printf("    ");
        gotoxy(enemyX[ind], enemyY[ind] + 2);
        printf("    ");
        gotoxy(enemyX[ind], enemyY[ind] + 3);
        printf("    ");
    }
}

void resetEnemy(int ind)
{
    eraseEnemy(ind);
    enemyY[ind] = 1;
    genEnemy(ind);
}

void play()
{
    carPos = -1 + WIN_WIDTH / 2;
    score = 0;
    enemyFlag[0] = 1;
    enemyFlag[1] = 0;
    enemyY[0] = enemyY[1] = 1;

    system("cls");
    drawBorder();
    updateScore();
    genEnemy(0);
    genEnemy(1);

    gotoxy(WIN_WIDTH + 7, 2);
    printf("Car Game");
    gotoxy(WIN_WIDTH + 6, 4);
    printf("----------");
    gotoxy(WIN_WIDTH + 6, 6);
    printf("----------");
    gotoxy(WIN_WIDTH + 7, 12);
    printf("Control ");
    gotoxy(WIN_WIDTH + 7, 13);
    printf("-------- ");
    gotoxy(WIN_WIDTH + 2, 14);
    printf(" A Key - Left");
    gotoxy(WIN_WIDTH + 2, 15);
    printf(" D Key - Right");

    gotoxy(18, 5);
    printf("Press any key to start");
    getch();
    gotoxy(18, 5);
    printf("                      ");

    while (1)
    {
        if (kbhit())
        {
            char ch = getch();
            if (ch == 'a' || ch == 'A')
            {
                if (carPos > 18)
                    carPos -= 4;
            }
            if (ch == 'd' || ch == 'D')
            {
                if (carPos < 50)
                    carPos += 4;
            }
            if (ch == 27)
            {
                break;
            }
        }

        drawCar();
        drawEnemy(0);
        drawEnemy(1);

        if (collision() == 1)
        {
            gameover();
            return;
        }

        Sleep(50);
        eraseCar();
        eraseEnemy(0);
        eraseEnemy(1);

        if (enemyY[0] == 10)
            if (enemyFlag[1] == 0)
                enemyFlag[1] = 1;

        if (enemyFlag[0] == 1)
            enemyY[0] += 1;

        if (enemyFlag[1] == 1)
            enemyY[1] += 1;

        if (enemyY[0] > SCREEN_HEIGHT - 4)
        {
            resetEnemy(0);
            score++;
            updateScore();
        }
        if (enemyY[1] > SCREEN_HEIGHT - 4)
        {
            resetEnemy(1);
            score++;
            updateScore();
        }
    }
}

int main()
{
    srand((unsigned)time(NULL));

    do
    {
        system("cls");
        gotoxy(10, 5);
        printf(" -------------------------- ");
        gotoxy(10, 6);
        printf(" |        Car Game        | ");
        gotoxy(10, 7);
        printf(" --------------------------");

        gotoxy(10, 9);
        printf("1. Start Game");
        gotoxy(10, 10);
        printf("2. Instructions");
        gotoxy(10, 11);
        printf("3. Quit");

        gotoxy(10, 13);
        printf("Select option: ");
        char op = getche();

        if (op == '1')
            play();
        else if (op == '2')
            printf("'a' for left \n'd' for right ");
        else if (op == '3')
            exit(0);

    } while (1);

    return 0;
}
