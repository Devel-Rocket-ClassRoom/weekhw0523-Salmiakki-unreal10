#pragma once
#include <string>
#include "Utils.h"
#include "EnemySprites.h"

using namespace std;


string EnemyName[] = { "피카츄", "이브이" };
string EnemySprites[] = { sPikachu,sEevee };
enum EnemyType
{
    EEVEE,
    PIKACHU,
    ENEMY_COUNT
};
// ??? ???
int EnemyHP[ENEMY_COUNT] =
{
    15,     // Pikachu
    20,     // Eevee
};

int EnemyATK[ENEMY_COUNT] =
{
    1,      //피카츄 공격력
    1       //이브이 공격력
};
struct MazeEnemy
{
	string Name = "미싱노";
	string Sprite = " ";
	int HP = 1;
	int AtkMin = 0;
	int AtkMax = 2;
	int Reward = 1;

	MazeEnemy()
	{
		HP = GetRandomRange(15, 25);
		AtkMin = GetRandomRange(3, 7);
		AtkMax = GetRandomRange(8, 12);
		Reward = GetRandomRange(80, 120);
	}
	MazeEnemy(int index)
	{
		Name = EnemyName[index];
		Sprite = EnemySprites[index];
		HP = EnemyHP[index];
		AtkMin = GetRandomRange(EnemyATK[index], 7);
		AtkMax = GetRandomRange(8, 12);
		Reward = GetRandomRange(80, 120);
	}
};