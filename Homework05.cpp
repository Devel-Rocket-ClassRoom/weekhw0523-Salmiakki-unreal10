#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <string>
#include "Homework05.h"
#include "Enemy.h"
#include "Player.h"
using namespace std;

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 맵파일 열기
string OpenMapData()
{
    string FilePath = ".\\Data\\MapData.txt";	// .은 현재 워킹 폴더 (기본적으로 파일이 실행되는 곳)
    std::ifstream InputFile(FilePath);	//입력용 파일 스트림 만들기
    // - 파일을 불러와서 저장은 이름과 돈을 출력하기
    string Output="0";
    if (InputFile.is_open())
    {
        string FileTxt
        {
            (std::istreambuf_iterator<char>(InputFile)),
            (std::istreambuf_iterator<char>())
        };

        const string Content = FileTxt;
        Output = Content;
    }
    else
    {
        // 파일이 없거나 다른 이유로 열리지 않았다.
        printf("파일을 열 수 없습니다.\n");
    }
    return Output;
}
// 맵데이터 불러오기
Map* LoadMapData(string Content)
{
    Map* LeMaze = new Map;
    size_t Pos = Content.find(',');
    size_t temp = 0;
    string Word = Content.substr(temp, Pos - temp);
    //printf("파일 내용: \n%d\n",atoi(Word.c_str()));

    temp = Pos + 1;
    Pos = Content.find('\n', Pos + 1);
    int Width = atoi(Word.c_str());
    Word = Content.substr(temp, Pos - temp);
    int Height = atoi(Word.c_str());
    LeMaze->MapStructure = new int[Height * Width];
    LeMaze->Width = Width;
    LeMaze->Height = Height;

    for (int i = 0; i < Height; i++)
    {
        for (int j = 0; j < Width; j++)
        {
            bool LineShift = j > Width - 2 ? true : false;
            temp = Pos + 1;
            Pos = Content.find(LineShift ?
                '\n' :
                ',',
                Pos + 1);
            Word = Content.substr(temp, Pos - temp);
            LeMaze->MapStructure[i * Width + j] = atoi(Word.c_str());
            printf("%d,", LeMaze->MapStructure[i * Width + j]);
            LineShift = false;
        }
        printf("\n");

    }
    return LeMaze;
}

void CleanUpMapData(Map* MazeData)
{
    if (MazeData->MapStructure)
    {
        delete[] MazeData->MapStructure;
        MazeData->MapStructure = nullptr;
    }
    MazeData->Width = 0;
    MazeData->Height = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 키 입력 받기
char GetInput()
{
    char input;
    cin >> input;
    return input;
}
// 화면 넘기기
void Proceed()
{
    printf("진행을 위해 아무키나 눌러주세요");
    int temp = getchar();
}

Position FindPlayer(Map& Maze, bool Spawn)
{
    Position PlayerLoc(0, 0);
    for (int i = 0; i < Maze.Height; i++)
    {
        for (int j = 0; j < Maze.Width + 1; j++)
        {
            if (Spawn == true)
            {
                if (Maze.MapStructure[i * Maze.Width + j] == 2)
                {
                    PlayerLoc.X = j;
                    PlayerLoc.Y = i;
                }
            }
            else
            {
                if(Maze.MapStructure[i * Maze.Width + j] == 4 )
                {
                    PlayerLoc.X = j;
                    PlayerLoc.Y = i;
                }
            }
        }
    }
    Maze.MapStructure[PlayerLoc.Y * Maze.Width + PlayerLoc.X] = 4;
    return PlayerLoc;
}

// 월드 출력
void PrintWorld(Map& Maze, int& EndX, int& EndY)
{
    for (int i = 0; i < Maze.Height; i++)
    {
        for (int j = 0; j < Maze.Width + 1; j++)
        {
            switch (Maze.MapStructure[i * Maze.Width + j])
            {
            case 1:
                printf("# ");
                break;
            case 0:
                printf(". ");
                break;
            case 2:
                printf("S ");
                break;
            case 3:
                printf("E ");
                EndY = i;
                EndX = j;
                break;
            case 4:
                printf("P ");
                break;
            }
        }
        printf("\n");
    }
}

// 이동 키 체크
void CheckMovement(char Input, int& newx, int& newy)
{
    switch (Input)
    {
    case 'w': case'W':
        newy--;
        break;
    case 's': case'S':
        newy++;
        break;
    case 'a': case'A':
        newx--;
        break;
    case 'd': case 'D':
        newx++;
        break;
    }
}

// 전투 처리
int BattleManager(int attackPoints, int targetHP, bool isPlayer, string enemyName)
{
	int CriticalChance = 10; // 치명타 확률 (10%)
    int ChangedHP = 0;
    int RawDamage = attackPoints+rand()%5;
	int Damage = rand() % 100 <= CriticalChance ? RawDamage * 2 : RawDamage; // 치명타 여부 결정
	printf("%s의 공격! %d 데미지!", isPlayer ? "플레이어" : enemyName.c_str(), Damage);
    printf("%s\n", Damage > RawDamage ? "급소에 맞았다!":"");
	ChangedHP = targetHP - Damage;
	ChangedHP = ChangedHP < 0 ? 0 : ChangedHP;
	printf("%s의 남은 HP: [%d]\n\n", isPlayer ? enemyName.c_str() : "플레이어", ChangedHP);
    return ChangedHP;
}
// 전투 화면
int BattleScene(int currentHP)
{
	int PlayerHP = currentHP;   //플레이어 체력
	int PlayerATK = 1;          //플레이어 공격력

    MazeEnemy EnemyInBattle=MazeEnemy(rand() % ENEMY_COUNT);

	int EnemyHP = EnemyInBattle.HP;

    printf("\n\n\n야생의 %s 가 나타났다!\n", EnemyInBattle.Name.c_str());
    printf("\n%s\n", EnemyInBattle.Sprite.c_str());
    printf("%s  HP:[%d]\n", EnemyInBattle.Name.c_str(), EnemyInBattle.HP);
	while (true)
    {
        EnemyHP = BattleManager(PlayerATK, EnemyHP, true, EnemyInBattle.Name);
        if (EnemyHP <= 0)
        {
            printf("%s를 쓰러트렸다!\n", EnemyInBattle.Name.c_str());
            break;
		}
        PlayerHP = BattleManager(EnemyInBattle.AtkMin, PlayerHP, false, EnemyInBattle.Name);
        if (PlayerHP <= 0)
        {
            printf("플레이어는 눈 앞이 깜깜해졌다!\n");
            break;
		}
    }
    return PlayerHP;
}

int Bonefire(Character character, int currentHP)
{
    int PlayerHP = currentHP;
    int Heal = 10;
    if (currentHP < character.MaxHP)
    {
        PlayerHP += Heal;
        if (PlayerHP > character.MaxHP)
        {
            Heal -= PlayerHP - character.MaxHP;
            PlayerHP = character.MaxHP;
        }
        
        printf("\n[마을이다! 체력을 %d 회복했다!]\n\n", Heal);
    }
    return PlayerHP;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 게임 실행
void Homework05_Run()
{
    
    int Seed = (unsigned int)time(0);
    srand(Seed);

	const int EncounterRate = 30;       // 적 조우 확률
    Character c_Player;                 // 플레이어 인스턴스 생성

    Map Maze = *(LoadMapData(OpenMapData()));
    Position Player=FindPlayer(Maze, true);
    Position End(-1, -1);
    const int MazeHeight = Maze.Height;
    const int MazeWidth = Maze.Width;
    
    
    
    while (true)    // 메인 루프
    {
        
        system("cls");
        //Maze.MapStructure[1*MazeWidth+1] = 2;
        // 맵 생성
        PrintWorld(Maze, End.X, End.Y);
        Player = FindPlayer(Maze, false);


        printf("[%d, %d] HP : [%d]\n", Player.X, Player.Y,c_Player.HP);

        if (Maze.MapStructure[End.Y* MazeWidth +End.X] == 4)
        {
            printf("축하합니다! 게임을 클리어했습니다!\n");
            break; 
        }

        Position NewPlayer(Player.X, Player.Y);

        CheckMovement(GetInput(), NewPlayer.X, NewPlayer.Y);
        Proceed();

        system("cls");
        if (Maze.MapStructure[NewPlayer.Y * MazeWidth + NewPlayer.X] != 1 && Maze.MapStructure[NewPlayer.Y * MazeWidth + NewPlayer.X] != 2)
        {
            int temp = Maze.MapStructure[NewPlayer.Y * MazeWidth + NewPlayer.X];

            Maze.MapStructure[NewPlayer.Y * MazeWidth + NewPlayer.X] = 4;
            Maze.MapStructure[Player.Y * MazeWidth + Player.X] = 0;
            if (temp == 0)
            {
				if (rand() % 100 < EncounterRate)       //EncounterRAte보다 작은 수가 나오면 전투발생
                {
                    c_Player.HP = BattleScene(c_Player.HP);
                    Proceed();

				}
                else if ((rand() % 200 < EncounterRate+20)&&(c_Player.HP !=100))
                {
                    c_Player.HP = Bonefire(c_Player,c_Player.HP);
                    Proceed();

                }
                
            }     
        }
        if (c_Player.HP <= 0)
        {
            printf("게임오버!\n");
            break;
        }

    }
}

