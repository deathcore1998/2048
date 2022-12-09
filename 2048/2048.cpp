﻿#include "Game2048.h"

int main()
{
	system("title Game 2048");
	setlocale(LC_ALL, "RU");
	srand(time(NULL));

	Game2048 mygame;

	char commandexecution;

	while (1)
	{
		commandexecution = _getch();
		switch (commandexecution)
		{
		case 0x4B:
			mygame.PushLeft();
			break;

		case 0x48:
			mygame.PushUp();
			break;

		case 0x4D:
			mygame.PushRight();
			break;

		case 0x50:
			mygame.PushDown();
			break;
		case 'b':
			mygame.CancelPush();
			break;
		case 'n':
			mygame.StartGame();
			break;
		}
	}
}