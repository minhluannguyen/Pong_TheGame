#pragma once

#include "pch.h"
#include "Ball.h"

class Paddle
{
protected:
	float coorX, coorY;
	float OriX, OriY;
	int size;
public:
	Paddle();
	~Paddle();
	Paddle(int, int, int);
	void draw();
	void move(int);
	void reset();
	void selfControl(int, int, int, int);
	COORD getCoord();
	int getSize();

	void gotoXY(HANDLE, COORD);

};