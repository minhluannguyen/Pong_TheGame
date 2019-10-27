#include "pch.h"


Paddle::Paddle() {
	coorX = coorY = OriX = OriY = 0;
	size = 0;
}

Paddle::~Paddle()
{

}

Paddle::Paddle(int x, int y, int s) {
	coorX = OriX = x;
	coorY = OriY = y;
	size = s;
	gotoxy(x, y);
}

void Paddle::draw()
{
	int x = int(OriX);
	int y = int(OriY);
	gotoxy(x, y);
	for (int i = 1; i <= size; i++)
	{
		cout << " ";
		gotoxy(x, y + i);
	}
	x = int(coorX);
	y = int(coorY);
	gotoxy(x, y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	for (int i = 1; i <= size; i++)
	{
		cout << "|";
		gotoxy(x, y + i);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	OriX = x;
	OriY = y;
}

void Paddle::move(int state)
{
	if (coorY + state > 0 && coorY + state < height - 3)
		coorY += state;
}

void Paddle::reset()
{
	//Xoa dau vet trong truong hop 1 trong 2 nguoi choi thang
	int x = int(OriX);
	int y = int(OriY);
	gotoxy(x, y);
	for (int i = 1; i <= size; i++)
	{
		cout << " ";
		gotoxy(x, y + i);
	}
	
	coorY = OriY = (height / 2) - (size / 2);
}

void Paddle::selfControl(int vx, int X, int Y, int level)
{
	bool ok = false;
	if (vx > 0)
	{
		if (level == 1)
		{
			if (X >= 0.75*width)
				ok = true;
		}
		else
			if (level == 2)
			{
				if (X >= 0.6*width)
					ok = true;
			}
			else
				if (X >= 0.4*width)
					ok = true;
	}

	if (ok)
	{
		if (Y >= coorY + (size / 2))
			move(PADDLE_SPEED);
		else
			move(-PADDLE_SPEED);
	}
}

COORD Paddle::getCoord()
{
	COORD p;
	p.X = coorX;
	p.Y = coorY;
	return p;
}

int Paddle::getSize()
{
	return size;
}