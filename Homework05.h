#pragma once
char GetInput();
int BattleScene(int currentHP);
void Homework05_Run();

struct Map {
	int Width = 1;
	int Height = 1;
	int* MapStructure = nullptr;

	Map() = default;
};