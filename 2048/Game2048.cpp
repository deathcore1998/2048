#include "Game2048.h"

Game2048::Game2048() { StartGame(); }

void Game2048::StartGame()
{
	score = 0;
	tempscore = 0;
	gamefield = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	RandomFilling();
	RandomFilling();
	earlygamefield = gamefield;

	string topwall = "\t ___________________________";
	string topbot = " \t|______|______|______|______|";
	string wall = " \t|      |      |      |      |";
	printf("\n%s\n", topwall.c_str());

	for (int i = 0; i < 16; i += 4)
	{
		printf("%s\n \t", wall.c_str());
		for (int j = 0; j < 4; j++)
		{
			if (gamefield[i + j] == 4 or gamefield[i + j] == 2)
			{
				printf("|   \x1B[31m%-3d\033[0m", gamefield[i + j]);
			}
			else
			{
				printf("|   %-3d", gamefield[i + j]);
			}
		}
		printf("|\n%s\n", topbot.c_str());
	}

	setCursorPosition(51, 2);
	printf("Текущий счет: %d      ", score);

	setCursorPosition(51, 5);
	printf("Команды управления игрой:");

	setCursorPosition(51, 7);
	printf("<- Cмещение всех блоков влево");

	setCursorPosition(51, 8);
	printf("\x18 Cмещение всех блоков вверх");

	setCursorPosition(51, 9);
	printf("-> Cмещение всех блоков вправо");

	setCursorPosition(51, 10);
	printf("\x19 Cмещение всех блоков вниз");

	setCursorPosition(51, 12);
	printf("'b' - Отмена одного хода");

	setCursorPosition(51, 13);
	printf("'n' - Начать игру сначала");

	Storagegamefield();
}

void Game2048::RandomFilling()
{
	countforrandom = 0;
	for (int i = 0; i < 16; ++i)
	{
		if (gamefield[i] == 0)
		{
			arrayforindexrandom[++countforrandom - 1] = i;
		}
	}
	if (countforrandom == 0) { return; }

	else
	{
		gamefield[arrayforindexrandom[rand() % countforrandom]] = myrand[rand() % 10];
	}
}

void Game2048::СheckEndGame()
{
	countforrandom = 0;
	for (int i = 0; i < 16; ++i)
	{
		if (gamefield[i] == 0)
		{
			arrayforindexrandom[++countforrandom - 1] = i;
		}
	}

	if (countforrandom == 0)
	{
		for (int i = 0; i <= 8; i += 4)
		{
			for (int j = 0; j < 4; j++)
			{
				if (j != 3)
				{
					if (gamefield[i + j] == gamefield[i + 1 + j] or gamefield[i + j] == gamefield[i + 4 + j])
					{
						return;
					}
				}
				else
				{
					if (gamefield[i + j] == gamefield[i + 4 + j])
					{
						return;
					}
				}
			}
		}
		for (int i = 12; i < 14; i++)
		{
			if (gamefield[i] == gamefield[i + 1])
			{
				return;
			}
		}
		printf("\t\t\t\t\x1B[31mИгра окончена!\033[0m\n");
	}
}

void Game2048::ShowGameField()
{
	for (int i = 0; i < 16; i += 4)
	{
		for (int j = 0; j < 4; j++)
		{
			setCursorPosition(9 + j * 7, 3 + (i / 4) * 3);
			gamefield[i + j] = abs(gamefield[i + j]);

			if (gamefield[i + j] == 0)
			{
				printf("   %-3d", gamefield[i + j]);
				continue;
			}
			if (gamefield[i + j] == 2 or gamefield[i + j] == 4 or gamefield[i + j] == 8)
			{
				printf("   \x1B[31m%-3d\033[0m", gamefield[i + j]);
				continue;
			}
			if (gamefield[i + j] == 16 or gamefield[i + j] == 32 or gamefield[i + j] == 64)
			{
				printf("  \x1B[32m%-4d\033[0m", gamefield[i + j]);
				continue;
			}
			if (gamefield[i + j] == 128 or gamefield[i + j] == 256 or gamefield[i + j] == 512)
			{
				printf("  \x1B[33m%-4d\033[0m", gamefield[i + j]);
				continue;
			}
			if (gamefield[i + j] == 1024 or gamefield[i + j] == 2048 or gamefield[i + j] == 4096)
			{
				printf(" \x1B[34m%-5d\033[0m", gamefield[i + j]);
				continue;
			}
			if (gamefield[i + j] == 8192 or gamefield[i + j] == 16384 or gamefield[i + j] == 32768)
			{
				printf(" \x1B[35m%-5d\033[0m", gamefield[i + j]);
				continue;
			}
			else
			{
				printf("|\x1B[36m%-5d\033[0m", gamefield[i + j]);
			}
		}
	}
	setCursorPosition(65, 2);
	printf("%d", score);

	setCursorPosition(76, 13);
}

void Game2048::PushLeft()
{
	Storagegamefield();
	for (int i = 0; i < 16; i += 4)
	{
		int temp = 0;
		for (int j = i; j < 3 + i; j++)
		{
			MovePush(j, j + 1);

			if (j == 2 + i && temp != 2)
			{
				temp++;
				j = i - 1;
			}
		}
	}
	CheckMoveFunction();
}

void Game2048::PushRight()
{
	Storagegamefield();
	for (int i = 0; i < 16; i += 4)
	{
		int temp = 0;
		for (int j = 3 + i; j > i; j--)
		{
			MovePush(j, j - 1);

			if (j == 1 + i && temp != 2)
			{
				temp++;
				j = 3 + i + 1;
			}
		}
	}
	CheckMoveFunction();
}

void Game2048::PushUp()
{
	Storagegamefield();
	for (int i = 0; i < 4; i++)
	{
		int temp = 0;
		for (int j = i; j <= 8 + i; j += 4)
		{
			MovePush(j, j + 4);

			if (j == 8 + i && temp != 2)
			{
				temp++;
				j = i - 4;
			}
		}
	}
	CheckMoveFunction();
}

void Game2048::PushDown()
{
	Storagegamefield();
	for (int i = 0; i < 4; i++)
	{
		int temp = 0;
		for (int j = 12 + i; j >= 4; j -= 4)
		{
			MovePush(j, j - 4);

			if (j == 4 + i && temp != 2)
			{
				temp++;
				j = 12 + i + 4;
			}
		}
	}
	CheckMoveFunction();
}

void Game2048::MovePush(int index1, int index2)
{
	if (gamefield[index1] == gamefield[index2] && gamefield[index1] > 0)
	{
		score += gamefield[index1] * 2;
		gamefield[index1] = -(gamefield[index2] * 2);
		gamefield[index2] = 0;
		checkmove = true;
	}
	if (gamefield[index1] == 0 && gamefield[index2] != 0)
	{
		swap(gamefield[index1], gamefield[index2]);
		checkmove = true;
	}
}

void Game2048::CancelPush()
{
	setCursorPosition(30, 0);
	printf("                                 ");
	gamefield = earlygamefield;
	score = earlyscore;

	ShowGameField();
}

void Game2048::Storagegamefield()
{
	tempgamefield = gamefield;
	tempscore = score;
}

void Game2048::CheckMoveFunction()
{
	if (checkmove)
	{
		earlygamefield = tempgamefield;
		earlyscore = tempscore;
		RandomFilling();
		checkmove = false;
	}
	else
	{
		СheckEndGame();
	}
	ShowGameField();
}

void Game2048::setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}