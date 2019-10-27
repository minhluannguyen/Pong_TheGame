#include "pch.h"
#include "Ball.h"


Ball::Ball()
{
	coorX = coorY = OriX = OriY = 0;
	vx = vy = 0;
}


Ball::~Ball()
{
}

Ball::Ball(int x, int y, int veloX, int veloY)
{
	coorX = OriX = x;
	coorY = OriY = y;
	vx = veloX;
	vy = veloY;
	gotoxy(x, y);
}

void Ball::draw()
{
	//Ve bong o thoi diem hien tai
	//Xoa vi tri cu
	int x = int(OriX);
	int y = int(OriY);
	gotoxy(x, y);
	cout << ' ';
	
	//Cap nhat vi tri cu sau khi xoa
	OriX = coorX;
	OriY = coorY;

	//In vi tri moi voi mau do
	x = int(coorX);
	y = int(coorY);
	gotoxy(x, y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << "o";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
}

void Ball::reset()
{
	//Hieu chinh lai vi tri khi moi bat dau game hoac co nguoi choi thang
	int x = int(OriX);
	int y = int(OriY);
	gotoxy(x, y);
	cout << ' ';

	//Trai bong xuat hien giua khung hinh
	coorX = OriX = width / 2;
	coorY = OriY = height / 2;
	//Hieu chinh toc do ban dau
	//Bong di chuyen ngang voi toc do ban dau cho truoc (duong ve ben trai, am ve ben phai)
	if (rand() % 2 + 0)
		vx = START_BALL_SPEED;
	else
		vx = -START_BALL_SPEED;
	//Bong di chuyen doc (do nay) cho truoc va khong doi (duong di xuong, am di len)
	if (rand() % 2 + 0)
		vy = 1;
	else
		vy = -1;	
}

void Ball::move()
{
	//Khong cho bong vuot qua toc do ngang cho truoc
	if (vx > MAX_BALL_SPEED_X)
		vx = MAX_BALL_SPEED_X;
	if (vx < -MAX_BALL_SPEED_X)
		vx = -MAX_BALL_SPEED_X;

	//Thay doi toi toa do moi
	coorX = coorX + vx;
	coorY = coorY + vy;
}

int Ball::checkImpactWall()
{
	//Kiem tra va cham voi tuong
	//Cham tuong duoi
	if (coorY + vy >= height + 1)
	{
		//Doi theo huong doc nguoc lai
		vy = -vy;
		coorY = height;
	}
	//Cham tuong tren
	if (coorY + vy < 1)
	{
		//Doi theo huong doc nguoc lai
		vy = -vy;
		coorY = 1;
	}
	//Cham bien nguoi choi 2
	if (coorX + vx > width)
	{
		//Bong dinh vao tuong
		coorX = width;
		draw();
		return 1;
	}
	//Cham bien nguoi choi 1
	if (coorX + vx < 1)
	{
		//Bong dinh vao tuong
		coorX = 1;
		draw();
		return 2;
	}
	return 3;
}

int Ball::checkImpactPad(Paddle p1, Paddle p2)
{
	int size = p1.getSize();
	float desX = coorX + vx;
	float desY = coorY + vy;
	if (desX > p2.getCoord().X - fabs(vx) && desX <= p2.getCoord().X && desY >= p2.getCoord().Y && desY <= p2.getCoord().Y + size)
	{
		coorX = p2.getCoord().X;
		//coorY += vy;
		//vx += float(coorX - p1.getCoord().X) / 3;
		vx = vx + vx * 0.1;
		vx = -vx;
		draw();
		return 2;
	}
	if (desX < p1.getCoord().X + fabs(vx) && desX >= p1.getCoord().X && desY >= p1.getCoord().Y && desY <= p1.getCoord().Y + size)
	{
		coorX = p1.getCoord().X;
		//coorY += vy;
		vx = vx + vx * 0.1;
		vx = -vx;
		draw();
		return 1;
	}
	return -1;
}

COORD Ball::getVelocity()
{
	COORD Velo;
	Velo.X = vx;
	Velo.Y = vy;
	return Velo;
}

COORD Ball::getCoord()
{
	COORD p;
	p.X = coorX;
	p.Y = coorY;
	return p;
}