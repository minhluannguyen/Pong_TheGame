﻿#include "pch.h"

int main()
{
	// An con tro trong console
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;
	ConCurInf.dwSize = 100;
	ConCurInf.bVisible = false;
	SetConsoleCursorInfo(hOut, &ConCurInf);
	//---------------------------------------------------------

	// Menu chinh
	mainMenu();	
}