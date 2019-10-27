#ifndef PCH_H
#define PCH_H

#include <iostream>
using namespace std;
#include <windows.h>
#include <conio.h>
#include <time.h>

#define START_BALL_SPEED 1
#define MAX_BALL_SPEED_X 4
#define MAX_BALL_SPEED_Y 2
#define PADDLE_SPEED 1

#define width 100
#define height 20

#include "Ball.h"
#include "Paddle.h"

void mainMenu();
void clearMenu(int startX, int startY);
void gotoxy(int column, int line);
void drawBoundary(int x, int y);
float random_between_two_float(float min, float max);

#endif //PCH_H
