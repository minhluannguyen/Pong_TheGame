#pragma once
#include "pch.h"
#include "Paddle.h"

class Ball
{
protected:
	float coorX, coorY;
	float OriX, OriY;
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

