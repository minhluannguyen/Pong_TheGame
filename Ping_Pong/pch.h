#ifndef PCH_H
#define PCH_H

#include <iostream>
using namespace std;
#include <windows.h>
#include <conio.h>

//Khoi tao cac bien lien quan toi toc do
#define START_BALL_SPEED 1
#define MAX_BALL_SPEED_X 3.5
#define PADDLE_SPEED 1

//Kich thuoc khung 
#define width 100
#define height 20

#include "Ball.h"
#include "Paddle.h"

void mainMenu();
void clearMenu(int startX, int startY);
void gotoxy(int column, int line);
void drawBoundary(int x, int y);

#endif //PCH_H
