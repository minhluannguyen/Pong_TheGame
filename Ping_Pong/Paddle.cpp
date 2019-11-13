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
	//Ve thanh truot
	//Xoa thanh truot o vi tri cu
	int x = int(OriX);
	int y = int(OriY);
	gotoxy(x, y);
	for (int i = 1; i <= size; i++)
	{
		cout << " ";
		gotoxy(x, y + i);
	}

	//Ve thanh truot o vi tri moi
	x = int(coorX);
	y = int(coorY);
	gotoxy(x, y);
	//Thanh truot mau xanh la
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	for (int i = 1; i <= size; i++)
	{
		cout << "|";
		gotoxy(x, y + i);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	//Cap nhat lai vi tri
	OriX = x;
	OriY = y;
}

void Paddle::move(int state)
{
	//Cap nhat toa do thanh truot moi khi nguoi choi cho
	//di chuyen, tranh truong hop cham voi tuong
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
	//Dua thanh truot ve vi tri ban dau
	coorY = OriY = (height / 2) - (size / 2);
}

void Paddle::selfControl(int vx, int X, int Y, int level)
{
	//Ham cho thanh truot tu chay neu chon che do choi voi may
	bool ok = false;
	//Neu bong dang chay ve huong thanh truot cua may
	//Tuy theo level ma thanh truot bat dau di chuyen
	if (vx > 0)
	{
		if (level == 1) //Easy
		{
			if (X >= 0.75*width) //Bong cach thanh truot 1/4 width
				ok = true;
		}
		else
			if (level == 2) //Medium
			{
				if (X >= 0.6*width) //Bong cach thanh truot 40% width
					ok = true;
			}
			else
				if (X >= 0.4*width) //Bong cach thanh truot 60% width
					ok = true;
	}

	//Neu bong da vao tam ngam cua thanh truot thi
	//cho thanh truot bat dau di chuyen
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
	//Tra ve toa do cua thanh truot
	COORD p;
	p.X = coorX;
	p.Y = coorY;
	return p;
}

int Paddle::getSize()
{
	//Tra ve do dai thanh truot
	return size;
}