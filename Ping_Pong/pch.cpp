#include "pch.h"

void gotoxy(int x, int y)
{
	//Ham dua con tro toi toa do cho truoc
	//x la ngang, y la doc
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord	);
}

void drawBoundary(int x, int y)
{
	//Ham ve khung hinh chu nhat co dien tich x*y
	// beginx va beginy la toa do tren trai cua hinh chu nhat
	int beginx = 0, beginy = 0;
	gotoxy(beginx, beginy);
	for (int i = 1; i <= x + 2; i++)
		cout << "#";
	gotoxy(beginx, beginy);
	for (int i = 1; i <= y + 1; i++)
	{
		gotoxy(beginx, beginy + i);
		cout << "#";
	}
	gotoxy(beginx + x + 1, beginy);
	for (int i = 1; i <= y + 1; i++)
	{
		gotoxy(beginx + x + 1, beginy + i);
		cout << "#";
	}
	gotoxy(beginx, beginy + y + 1);
	for (int i = 1; i <= x + 2; i++)
		cout << "#";
}

void PlayerWin(int id, int mode)
{
	//Khi bong cham bien cua 1 trong 2 nguoi choi
	//id la nguoi choi thang, mode la che do choi
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	//In ra thong bao va doi nguoi dung an SPACE

	gotoxy(width / 2 - 10, height / 2);
	if (mode == 2 && id == 2)
		cout << "Computer win!";
	else
		cout << "Player " << id << " win!";

	gotoxy(width / 2 - 10, height / 2 + 1);
	cout << "Press space to continue...";

	cin.sync();
	char c = _getch();
	do
	{
		c = _getch();
		if (c == 27)
			return;
	} while (c != ' ');
	cin.sync();
	//Xoa thong bao
	gotoxy(width / 2 - 10, height / 2);
	cout << "               ";
	gotoxy(width / 2 - 10, height / 2 + 1);
	cout << "                            ";
}

void printScore(int P1Score, int P2Score, int mode)
{
	//Ham in va cap nhat diem nguoi choi
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(width / 3, height + 2);
	cout << "Player 1: " << P1Score;
	gotoxy(2 * width / 3, height + 2);
	if (mode == 1)
		cout << "Player 2: " << P2Score;
	else
		cout << "Computer: " << P2Score;
}

bool winCondition(int P1Score, int P2Score, int mode, int topScore)
{
	//Ham kiem tra 1 trong 2 da dat diem toi da chua
	//P1Score va P2Score la diem cua 2 nguoi choi
	//mode la che do (1 la 2 nguoi choi, 2 la choi voi may)
	//topScore la diem toi da
	//Cho chu mau vang
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	//Neu nguoi choi 1 thang thi in ra thong bao tuy theo che do choi
	if (P1Score == topScore)
	{
		if (mode == 1)
		{
			gotoxy(width / 2 - 27, height / 2 - 2);
			cout << "Player 1 won! ESC to exit, Space to play again.";
		}
		else
		{
			gotoxy(width / 2 - 27, height / 2 - 2);
			cout << "You won! ESC to exit, Space to play again.";
		}
		return true;
	}
	//Neu nguoi choi 2 hoac may thang thi in ra thong bao tuy theo che do choi
	if (P2Score == topScore)
	{
		if (mode == 1)
		{
			gotoxy(width / 2 - 27, height / 2 - 2);
			cout << "Player 2 won! ESC to exit, Space to play again.";
		}
		else
		{
			gotoxy(width / 2 - 27, height / 2 - 2);
			cout << "Computer won! ESC to exit, Space to play again.";
		}
		return true;
	}
	return false;
}

void Game(int mode, int level, int topScore)
{
	//Ham game, mode la che do choi (1 la 2 nguoi, 2 la dau voi may)
	//level la do kho khi dau voi may
	//topScore la diem toi da
	system("cls");
	//Diem ban dau 2 ben la 0
	int P1Score = 0;
	int P2Score = 0;
	//Bien theo doi coi game da bat dau hay chua, mac dinh la chua
	bool started = false;
	//Toc do delay cua game
	int speed = 75;

	//Thiet lap khong gian choi game
	//Ve khung
	drawBoundary(width, height);
	//Ghi diem moi nguoi choi
	printScore(P1Score, P2Score, mode);

	//Cac doi tuong chinh cua game
	//Bong
	Ball B;
	B.reset();
	//2 thanh truot va vi tri bat dau
	Paddle P1(6, height / 2 - 2, 5);
	Paddle P2(width - 5, height / 2 - 2, 5);

	// In ra huong dan choi
	gotoxy(width / 2 - 27, height / 2 + 1);
	cout << "Press space to start. Press ESC while playing to exit.";
	gotoxy(width / 2 - 27, height / 2 + 2);
	cout << "Use W, S and arrow keys to move your paddle.";
	gotoxy(width / 2 - 27, height / 2 + 3);
	cout << "First player get to " << topScore <<" win";

	while (true)
	{
		//Kiem tra da an phim ESC de thoat
		if (GetAsyncKeyState(VK_ESCAPE))
			break;

		//Kiem tra nguoi dung da an SPACE va san sang choi chua
		if (started)
		{
			cin.clear();
			// Nguoi choi 1 di chuyen bang 2 phia W va S
			if (GetAsyncKeyState(0x57)) //Virtual code W
				P1.move(-PADDLE_SPEED);
			if (GetAsyncKeyState(0x53)) //Virtual code S
				P1.move(PADDLE_SPEED);
			// Nguoi choi 2 di chuyen neu o mode 1, o mode 2 la computer
			if (mode != 2)
			{
				if (GetAsyncKeyState(VK_UP))
					P2.move(-PADDLE_SPEED);
				if (GetAsyncKeyState(VK_DOWN))
					P2.move(PADDLE_SPEED);
			}

			//May tu dieu khien paddle
			if (mode == 2)
				P2.selfControl(B.getVelocity().X, B.getCoord().X, B.getCoord().Y, level);

			//Kiem tra va cham tuong
			int checkW = B.checkImpactWall();
			//Kiem tra va cham Paddle
			int checkP = B.checkImpactPad(P1, P2);

			//Cac truong hop va cham
			if (!(checkW == 3 || checkP == 1 || checkP == 2))
			{
				//Nguoi choi 1 thang
				if (checkW == 1)
				{
					PlayerWin(1, mode);
					P1Score++;
				}
				//Nguoi choi 2 hoac may thang
				if (checkW == 2)
				{
					PlayerWin(2, mode);
					P2Score++;
				}
				//In diem ra man hinh (1 la Human Vs Human, 2 la Human Vs Computer)
				printScore(P1Score, P2Score, mode);
				// Kiem tra da dat toi diem gioi han chua
				if (winCondition(P1Score, P2Score, mode, topScore))
				{
					//Tra diem ca 2 ve 0
					P1Score = 0;
					P2Score = 0;
					started = false;

					//Cho nguoi dung an SPACE
					cin.sync();
					char c = 'c';
					do
					{
						c = _getch();
						if (c == 27)
							return;
					} while (c != ' ');

				}
				//Tra lai mau chu trang
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

				//Hieu chinh bong va thanh truot ve vi tri ban dau
				B.reset();
				P1.reset();
				P2.reset();

			}

			//Ve cac Paddle va bong o vi tri hien tai
			P1.draw();
			P2.draw();
			B.move();
			B.draw();
			//In diem ra man hinh (1 la Human Vs Human, 2 la Human Vs Computer)
			printScore(P1Score, P2Score, mode);
			//Delay
			Sleep(speed);
		}
		else
		{
			//Kiem tra nguoi dung da an nut SPACE chua
			if (GetAsyncKeyState(VK_SPACE))
			{
				//Neu da an thi cho game bat dau, xoa huong dan choi
				
				started = true;
				gotoxy(width / 2 - 27, height / 2 - 2);
				cout << "                                                   ";
				gotoxy(width / 2 - 27, height / 2 + 1);
				cout << "                                                       ";
				gotoxy(width / 2 - 27, height / 2 + 2);
				cout << "                                             ";
				gotoxy(width / 2 - 27, height / 2 + 3);
				cout << "                           ";
			}
		}
	} 
}

int compLevel()
{
	//Menu chon do kho dau voi may
	clearMenu(42, 14);
	gotoxy(45, 14);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << "Easy" << endl;
	gotoxy(45, 15);
	cout << "Medium" << endl;
	gotoxy(45, 16);
	cout << "Hard";
	gotoxy(45, 17);
	cout << "Back to Main menu";

	//Cac thao tac voi mui ten trong menu
	int Oi = 14;
	int i = 14;
	int KB_code = 1;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	while (KB_code != 13)
	{
		gotoxy(42, i);
		cout << "->";
		if (_kbhit())
		{
			KB_code = _getch();
			switch (KB_code)
			{
			case 72:
				if (i > 14)
				{
					i--;
				}
				break;
			case 80:
				if (i < 17)
				{
					i++;
				}
				break;
			}
			gotoxy(42, Oi);
			cout << "  ";
			Oi = i;
		}
	}

	//Tra ve 3 muc do de kho trung binh va quay ve menu chinh
	switch (i)
	{
	case 14:
		return 1;
		break;
	case 15:
		return 2;
		break;
	case 16:
		return 3;
		break;
	}
	return -1;
}

void scoreSetting(int &topScore)
{
	//Menu thay doi diem toi da
	//Xoa menu cu
	clearMenu(42, 14);
	//In menu thay doi diem
	gotoxy(45, 14);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << "Score limit: " << topScore << "." << endl;
	gotoxy(45, 15);
	cout << "3" << endl;
	gotoxy(45, 16);
	cout << "5";
	gotoxy(45, 17);
	cout << "7";
	gotoxy(45, 18);
	cout << "Back to Main menu";

	//Cac thao tac cua mui ten chon trong menu
	int Oi = 15;
	int i = 15;
	int KB_code = 1;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	while (KB_code != 13)
	{
		gotoxy(42, i);
		cout << "->";
		if (_kbhit())
		{
			KB_code = _getch();
			switch (KB_code)
			{
			case 72:
				if (i > 15)
				{
					i--;
				}
				break;
			case 80:
				if (i < 18)
				{
					i++;
				}
				break;
			}
			gotoxy(42, Oi);
			cout << "  ";
			Oi = i;
		}
	}

	//3 lua chon diem khac nhau
	switch (i)
	{
	case 15:
		topScore = 3;
		break;
	case 16:
		topScore = 5;
		break;
	case 17:
		topScore = 7;
		break;
	}
}

void clearMenu(int startX, int startY)
{
	//Xoa menu
	gotoxy(startX, startY);
	for (int i = 1; i <= 6; i++)
	{
		for (int j = 1; j <= 30; j++)
			cout << " ";
		gotoxy(startX, startY + i);
	}
}

void titlePong(int canleTrai, int xuongDong)
{
	gotoxy(canleTrai, xuongDong);
	//Doi thanh mau xanh la (Green)
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout << " #########         ######       ##       #       ####### " << endl; gotoxy(canleTrai, xuongDong + 1);
	cout << " ##      ##       ##     #      ###      #      ##       " << endl; gotoxy(canleTrai, xuongDong + 2);
	cout << " ##       ##     ##       #     # ##     #     ##        " << endl; gotoxy(canleTrai, xuongDong + 3);
	cout << " ##      ##     ##         #    #  ##    #    ##         " << endl; gotoxy(canleTrai, xuongDong + 4);
	cout << " ########       ##         #    #   ##   #    ##     ####" << endl; gotoxy(canleTrai, xuongDong + 5);
	cout << " ##             ##         #    #    ##  #    ##      ## " << endl; gotoxy(canleTrai, xuongDong + 6);
	cout << " ##              ##       #     #     ## #     ##     ## " << endl; gotoxy(canleTrai, xuongDong + 7);
	cout << " ##               ##     #      #      ###      ##    ## " << endl; gotoxy(canleTrai, xuongDong + 8);
	cout << " ##                ######       #       ##       ####### " << endl;
}

void mainMenu()
{
	int i = 14;
	// Diem toi da mac dinh la 5
	int topScore = 5;
	while (i != 17)
	{
		//Xoa man hinh
		system("cls");

		//In tieu de game
		titlePong(30, 2);

		//In ra menu chinh
		gotoxy(45, 14);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		cout << "Human vs. Human" << endl;
		gotoxy(45, 15);
		cout << "Human vs. Computer" << endl;
		gotoxy(45, 16);
		cout << "Win condition: First to " << topScore << ".";
		gotoxy(45, 17);
		cout << "Exit game.";

		// Mui ten lua chon trong menu
		// Oi la gia tri i cu dung de xoa mui ten khi thay doi dong
		int Oi = 14;
		// KB_code la cac phim lua chon
		int KB_code = 1;
		//Mui ten mau trang
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		while (KB_code != 13)// 13 la Enter, khi da chon 1 muc thi ngung thao tac mui ten
		{
			// In mui ten o vi tri hien tai
			gotoxy(42, i);
			cout << "->";
			//Kiem tra nguoi dung co an nut nao hay chua
			if (_kbhit())
			{
				//Neu co thi luu lai
				KB_code = _getch();
				switch (KB_code)
				{
				case 72: //Truong hop mui ten di len (up)
					if (i > 14)
					{
						i--;
					}
					break;

				case 80: //Truong hop mui ten di xuong (down)
					if (i < 17)
					{
						i++;
					}
					break;
				}
				//Xoa mui ten cu
				gotoxy(42, Oi);
				cout << "  ";
				Oi = i;
			}			
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		int level;
		//Cac lua chon
		switch (i)
		{
		case 14: // Vao game 2 nguoi choi voi nhau
			Game(1, -1, topScore);
			break;
		case 15: // Vao game 1 nguoi choi voi may
			level = compLevel();
			if (level != -1)
				Game(2, level, topScore);
			break;
		case 16: // Dieu chinh diem de chien thang
			scoreSetting(topScore);
			break;
		case 17: //Thoat
			system("cls");
			return;
			break;
		}
	}
}