#pragma once
#include "pch.h"
#include "Paddle.h"

class Ball
{
protected:
	//Toa do hien tai
	float coorX, coorY;
	//Toa do truoc do
	float OriX, OriY;
	//Toc do theo 2 phuong tung hoanh
	float vx, vy;
public:
	Ball();
	~Ball();
	Ball(int, int, int, int);
	void draw();
	void move();
	void reset();
	int checkImpactWall();
	int checkImpactPad(Paddle, Paddle);

	COORD getVelocity();
	COORD getCoord();
};

