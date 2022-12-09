#pragma once
#include <iostream>
#include <array>
#include <ctime>
#include <conio.h>
#include <Windows.h>

using namespace std;

class Game2048
{
private:
	array<int, 16> gamefield;
	int score;

	int earlyscore = 0;
	int tempscore;

	array<int, 16> earlygamefield;
	array<int, 16> tempgamefield;

	const int myrand[10]{ 2,2,2,2,2,2,2,2,2,4 };
	int countforrandom = 0;
	int arrayforindexrandom[16];

	bool checkmove = false;

public:

	Game2048();

	void StartGame();

	void RandomFilling();

	void ShowGameField();

	void PushLeft();

	void PushRight();

	void PushUp();

	void PushDown();

	void CheckMoveFunction();

	void MovePush(int index1, int index2);

	void CancelPush();

	void Storagegamefield();

	void ÑheckEndGame();

	void setCursorPosition(int x, int y);
};
