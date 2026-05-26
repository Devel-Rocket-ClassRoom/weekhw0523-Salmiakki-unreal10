#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string>
using namespace std;

char GetInput()
{
    char input;
    cin >> input;
    return input;
}

int BattleManager(int attackPoints, int targetHP, bool isPlayer, string enemyName)
{
	int CriticalChance = 10; // 치명타 확률 (10%)
    int ChangedHP = 0;
    int RawDamage = attackPoints+rand()%15;
	int Damage = rand() % 100 <= CriticalChance ? RawDamage * 2 : RawDamage; // 치명타 여부 결정
	printf("%s의 공격! %d 데미지!", isPlayer ? "플레이어" : enemyName.c_str(), Damage);
    printf("%s\n", Damage > RawDamage ? "급소에 맞았다!":"");
	ChangedHP = targetHP - Damage;
	ChangedHP = ChangedHP < 0 ? 0 : ChangedHP;
	printf("%s의 남은 HP: [%d]\n\n", isPlayer ? enemyName.c_str() : "플레이어", ChangedHP);
    return ChangedHP;
}

int BattleScene(int currentHP)
{
	int PlayerHP = currentHP;   //플레이어 체력
	int PlayerATK = 1;          //플레이어 공격력
    string sPikachu = (
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⠿⠛⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠀⠀⠀⠀⠀⡸⠁⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⡀⢀⠀⠀⠀⠀⠀⠀⢀⠔⠋⠁⠀⠀\n"
        "⠀⠀⠀⠀⠀⠀⠀⢀⠇⠀⠀⢰⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⠤⠒⠊⠉⠉⠁⣽⣿⣿⡿⠋⠀⠀⠀⠀⣠⠖⠁⠀⠀⠈⠀⠀\n"
        "⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⢀⠇⢀⣀⣀⣀⣀⣀⠀⠀⠀⢀⡠⠔⠊⠁⠀⠀⠀⠀⠀⠀⢠⣿⡿⠋⠁⠀⠀⠀⣠⠞⠁⠀⠀⠀⠀⠀⡄⠀\n"
        "⠀⠀⠀⠀⠀⠀⠀⢸⣀⠴⠋⠉⠁⠀⠀⠀⠀⠀⠉⠙⠖⠉⠀⠀⠀⠀⠀⠀⠀⠀⣀⠴⠛⠁⠀⠀⠀⠀⣠⠞⠁⠀⠀⠀⠀⠀⠀⠀⢠⠀\n"
        "⠀⠀⠀⠀⠀⠀⢀⠞⠁⠀⠀⠀⠀⠀⠀⣾⢙⣶⡄⠀⠀⠰⢤⣠⡤⠤⠔⠒⠂⠉⠀⠀⠀⠀⠀⠀⣠⠞⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠀\n"
        "⠀⠀⠀⠀⠀⠀⣮⣞⣹⠀⠀⠀⠀⠀⠀⠙⠿⠿⠃⠀⠀⠀⠀⠈⢳⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠜⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠼⠃\n"
        "⠀⠀⠀⠀⠀⢰⠛⠿⠁⣈⣀⣀⣀⣤⠀⠀⠀⢠⠖⠒⠲⡄⠀⠀⠀⡆⠀⠀⠀⠀⠀⠀⠀⢰⠧⠤⠔⠂⠐⠈⠈⠀⠀⠀⣠⠔⠊⠁⠀⠀\n"
        "⠀⠀⠀⠀⢠⡟⣇⠀⠉⢿⣿⣿⣿⣿⠀⠀⠀⢯⡐⠲⣠⡇⠀⠀⠀⢳⠀⠀⠀⠀⠀⠀⠀⠘⡄⠀⠀⠀⠀⠀⠀⣠⠔⠋⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠀⠸⣦⡟⠀⠀⠈⢿⠟⠛⢻⠀⠀⠀⠀⠙⠚⠋⠀⠀⠀⠀⠀⢇⠀⠀⠀⠀⠀⠀⠀⠘⡄⠀⠀⠀⠔⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠀⠀⠹⣄⠀⠀⠀⠀⠳⣄⡼⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⡀⠈⢆⠀⠀⠀⠀⠀⠀⠀⠹⡀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠀⢀⣀⠬⠷⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡴⠚⠃⠢⢄⠀⠈⢣⡀⠀⠀⠀⠀⠀⢀⡽⠀⠀⢸⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⣤⠔⠊⠁⠀⠀⠀⠈⠳⠀⠀⣀⠀⠀⠀⠀⠀⠀⠀⢿⠁⠀⠀⠀⠈⠀⠀⠘⡿⢆⠀⠀⣠⠔⠉⠀⠀⣀⠜⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠐⡏⠸⠀⠀⠀⠀⠀⠀⠀⢢⠀⠈⠳⢄⣀⠀⠀⠀⠀⠈⢧⡀⠀⠀⠀⣀⡀⠀⠀⠀⠱⡈⠣⡀⠀⢠⠚⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⠻⠦⢤⣀⠀⠀⠀⠀⠀⠀⢣⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠛⠤⠼⠛⠁⠀⠀⠀⠀⠘⣆⠙⢶⣿⣷⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠀⠀⠉⠉⠙⠒⠒⠒⠒⢣⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠿⠳⣾⣿⣿⡿⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⡉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣾⠿⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡴⠋⡘⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠱⡀⠀⠀⠀⣀⡤⠔⠲⣶⣆⣀⡀⠀⠐⠤⠤⠔⠒⠉⠀⣰⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠒⠤⣥⠤⢴⠚⠉⠀⠀⠀⠈⠉⠒⠂⠤⠤⢤⡤⠞⢻⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣾⡿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢧⣀⣸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢋⡁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠻⢿⠃⠀\n"
        );
    string sEevee = (
        "⠀⠀⠀⠀⠀⠀⠀⣀⣼⠙⣦⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠀⠀⠀⣠⡯⠙⣦⢻⣧⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠀⠀⠀⣿⠀⣴⣿⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣠⡤⣤⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠀⠀⢰⣿⢳⣿⣿⣸⡇⠀⠀⠀⠀⠀⠀⣴⡶⣾⢋⣛⢀⣿⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠀⠀⢸⣿⢸⣿⠸⡏⠀⠀⠀⠀⣠⣼⠻⢯⣵⣾⣿⡏⣿⠋⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠀⠀⠈⣿⣿⡯⢿⡷⢶⣀⣠⣶⡟⣁⣼⣿⣿⣿⣏⣹⠋⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠀⣠⣾⠿⠊⠑⠀⢇⡈⠻⣿⢧⡴⣿⣿⣿⠿⣽⡞⠁⢀⣀⣀⣠⣴⣶⠀⠀\n"
        "⠀⠀⠀⡼⢿⠇⠀⠀⠀⠀⠀⠀⠀⠀⢰⣟⣻⣾⡿⠛⣟⣾⡿⠏⠉⠛⡠⣤⡟⠀⠀\n"
        "⠀⠀⠀⣷⡖⣦⠀⠀⠀⠀⠀⠀⠀⠀⠘⢻⣿⠁⠀⣰⣿⠏⠁⠀⠀⠐⠂⠛⣧⠀⠀\n"
        "⠀⠀⣤⡿⣿⣿⠀⠀⠀⠀⢸⣏⣳⠀⢠⠾⣿⣀⣼⠿⣄⠀⢀⡀⠀⠀⠀⠀⢻⣧⠀\n"
        "⠀⠀⢻⣧⡌⣭⠗⠀⠀⠀⢸⣿⣿⠂⣆⣼⠉⠻⣿⡃⠘⠴⠛⠯⠻⣧⡀⠀⣌⢽⡆\n"
        "⠀⣠⡾⠝⠷⣶⣏⣵⠶⠋⣀⡰⢲⣯⡿⠇⠀⡀⠸⢷⠀⠀⠀⠀⠀⠘⣇⠞⠉⢹⡇\n"
        "⢸⠁⠀⠀⠠⠘⠋⠙⠛⠛⠛⠛⠛⠛⣄⠀⠀⢀⣺⡿⢤⡀⠀⠀⠀⠀⠀⣀⣴⣿⡇\n"
        "⠘⢷⣷⠠⠀⠀⠀⠀⠀⠀⠀⠈⢱⠀⢸⡇⠠⣿⣿⣇⠀⠉⠓⠒⠒⠒⣋⢩⣽⠏⠀\n"
        "⠀⠈⠻⢾⣧⡄⠀⠀⠀⡀⠀⢠⡘⢀⣿⣤⠟⠋⠉⣿⣷⠀⠀⣴⠒⣞⣡⣽⠃⠀⠀\n"
        "⠀⠀⠀⠈⢻⣷⣠⡆⢀⠹⣴⣾⡟⠿⢿⣻⡆⠀⠀⠀⣿⣤⣤⡶⠾⠞⠛⠀⠀⠀⠀\n"
        "⠀⠀⠀⠀⢀⣽⣿⠙⠻⣾⣿⣻⡗⠀⢿⣿⠟⠀⠀⣴⠟⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⢰⣿⡏⣦⢠⣴⢿⡿⠏⠁⠀⣸⣷⣤⣷⣶⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠀⠉⠛⠛⠻⠟⠈⢻⣶⣾⡾⠏⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        );

    string EnemyName[] = { "피카츄", "이브이" };
    string EnemySprites[] = { sPikachu,sEevee };
    enum EnemyType
    {
        EEVEE,
        PIKACHU,
        ENEMY_COUNT
    };
    // ??? ???
    int HP[ENEMY_COUNT] =
    {
        15,     // Pikachu
        20,     // Eevee
    };

    int ATK[ENEMY_COUNT] =
    {
        1,      //피카츄 공격력
        1       //이브이 공격력
    };
    int enemy = rand() % ENEMY_COUNT;
	int EnemyHP = HP[enemy];
    printf("\n\n\n야생의 %s 가 나타났다!\n", EnemyName[enemy].c_str());
    printf("\n%s\n", EnemySprites[enemy].c_str());
    printf("%s  HP:[%d]\n", EnemyName[enemy].c_str(), HP[enemy]);
	while (true)
    {
        EnemyHP = BattleManager(PlayerATK, EnemyHP, true, EnemyName[enemy]);
        if (EnemyHP <= 0)
        {
            printf("%s를 쓰러트렸다!\n", EnemyName[enemy].c_str());
            break;
		}
        PlayerHP = BattleManager(ATK[enemy], PlayerHP, false, EnemyName[enemy]);
        if (PlayerHP <= 0)
        {
            printf("플레이어는 눈 앞이 깜깜해졌다!\n");
            break;
		}
    }
    return PlayerHP;
}

int Bonfire(int currentHP)
{
    int PlayerHP = currentHP;
    int Heal = 10;
    if (PlayerHP < 100)
    {
        PlayerHP += Heal;
        if (PlayerHP > 100)
        {
            Heal -= PlayerHP - 100;
            PlayerHP = 100;
        }
        printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀        ⠀⢀⡴⠢⣀⠀⠀⠀       \n");
        printf("    ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠒⠔⠋⠀⠀⠀      \n");
        printf("   ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠤⠴⠒⠖⠖⠶⠢⠤⣀⠀⠀⠀⠀⠀⠀⠀     \n");
        printf("   ⠀⠀⠠⠖⢆⡀⠀⠀⣠⠔⣇⠲⣀⢀⠂⣀⠒⣊⢴⣹⠠⣄⠀⠀⠀⡠⢄   \n");
        printf("   ⠀⠀⠈⠂⠋⠀⠀⢸⠀⠀⠽⣷⣮⣷⢿⣮⣷⣽⡾⠏⠀⠀⡆⠀⠀⠁⠈    \n");
        printf("   ⠀⠀⠀⠀⠀⠀⠀⠸⡀⠀⣸⡧⡀⡤⣀⠠⣀⠠⣼⣟⢀⢠⠇⠀⠀⠀⠀    \n");
        printf("   ⡤⡀⠀⠀⠀⠀⠀⠀⠨⡇⢹⡕⠶⠶⠴⠶⠴⠶⣮⡏⢸⠁⠀⠀⠀⠀⠀    \n");
        printf("   ⠑⠁⠀⠀⠀⠀⢀⡠⠞⠁⠀⠙⠳⠾⠶⠷⠾⠞⠋⠀⠈⠳⣄⠀⠀⠀⠀    \n");
        printf("   ⠀⠀⠀⠀⠀⢰⠋⠀⣀⣤⣤⣤⣶⣶⣶⣶⣶⣦⣤⣤⣤⣀⠈⠓⡄⠀⠀    \n");
        printf("   ⠀⠀⠀⠀⠀⢸⠀⠘⠛⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠂⡅⠀⠀    \n");
        printf("   ⠀⠀⠀⠀⠀⢸⠀⠀⠀⢀⣾⣿⣷⣶⣿⣿⣿⣿⣷⣾⣶⡾⢷⡆⡄⠀⠀    \n");
        printf("   ⠀⠀⠀⠀⠀⢸⠀⠀⢀⣾⣿⣿⣿⣯⣿⣿⣿⠟⠉⠙⢿⣿⣿⡇⠇⠀⠀    \n");
        printf("   ⠀⠀⠀⠀⠀⢸⠀⠀⢸⣿⣿⣯⣿⣿⣿⣻⣧⡠⢤⢤⣬⣿⣿⡇⡃⠀⠀    \n");
        printf("   ⠀⠀⠀⠀⠀⢸⠀⠀⢾⣯⣽⡿⣽⣿⣟⣿⢿⣦⣥⣼⡿⣿⣹⡇⡃⠀⠀    \n");
        printf("   ⠀⠀⠀⠀⠀⢸⠀⠀⢯⡿⡏⠁⠀⢹⣟⡾⡿⣽⣻⣽⣻⢿⡽⡇⡅⠀⠀    \n");
        printf("   ⠀⠀⠀⠀⠀⢸⠀⠀⡟⡟⣷⣤⣤⣿⢫⣷⠛⣧⡟⣶⣿⣯⡟⡇⡆⠀⠀    \n");
        printf("   ⠀⠀⠀⠀⠀⢸⠀⠀⣽⡷⣍⢯⣝⢮⡽⢬⡛⣶⢹⣭⢆⡾⣹⠇⡆⠀⠀    \n");
        printf("   ⠀⠀⠀⠀⠀⢸⠀⠀⢾⡘⢿⠚⡌⢇⢏⢣⢃⠗⡛⡜⢎⡹⢏⡇⠆⠀⠀    \n");
        printf("   ⠀⠀⠀⠀⠀⢾⡀⠀⣞⢡⢎⠩⡘⠌⡌⢢⠉⡌⡙⠬⡆⠩⠌⣆⡃⠀⠀    \n");
        printf("   ⠀⠀⠀⠀⠀⠈⠋⠤⣈⢀⡂⠡⠌⠰⢈⠂⠌⡐⠁⢂⡐⣡⠼⠚⠁⠀⠀   \n");
        printf("   ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠑⠒⠒⠒⠒⠒⠒⠛⠉⠉⠀⠀⠀⠀⠀⠀     \n");
        printf("\n[마을이다! 체력을 %d 회복했다!]\n\n", Heal);
    }
    return PlayerHP;
}

//void OneDtoTwoD(int** (Array), int SizeY, int SizeX)
//{
//    int a = 0;
//    int NewArray[200] = { 0, };
//    for (int j = 0; j < SizeY * SizeX; j++)
//    {
//        for (int i = 0; i < SizeX ; i++)
//        {
//            //printf("%d ", Array[j][i]);
//           NewArray[a] = Array[j][i];
//            a++;
//        }
//    }
//    for (int Element : NewArray)
//    {
//        printf("%d \n", Element);
//    }
//}

void TwoDtoOneD(int(* arr)[20], int Height)       // Maze는 첫번째 요소(int 20개 짜리 배열)의 주소를 가리키는 포인터, int(*arr)[20]으로 타입을 맞춘다 arr = &Maze[0]
{
	int NewArray[200] = { 0, };
    int count = 0;
    for (int i = 0; i <Height; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            NewArray[count] = (arr)[i][j];
			count++;
        }
    }
    for (int Element : NewArray)
    {
        printf("%d ", Element);
	}
}

void Homework05_Run()
{
    int Seed = (unsigned int)time(0);
    srand(Seed);

	const int EncounterRate = 30;       //적 조우 확률
	int PlayerHP = 100;             //플레이어 체력
    // ??? ???
    const int MazeRows = 10;
    const int MazeCols = 20;

    // ??? ???
    int Maze[MazeRows][MazeCols] =
    {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,2,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,1,0,1},
        {1,1,1,1,0,1,0,1,1,0,1,0,1,1,0,1,0,1,0,1},
        {1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1},
        {1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
        {1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1},
        {1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1},
        {1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,3,1},
        {1,0,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    int playerx = 1; // ??????? x ???
    int playery = 1; // ??????? y ???
    int Initialx = playerx; // ???????? x ???
    int Initialy = playery; // ???????? x ???
    int Endx = 0; // ???????? x ???
    int Endy = 0; // ???????? y ???
    // ??? ???
    TwoDtoOneD(Maze, 10);
    
    
    while (true)
    {
        
        system("cls");
        Maze[Initialy][Initialx] = 2;
        //printf("%d\n", Maze[1][1]);

        for (int i = 0; i < MazeRows; i++)
        {
            for (int j = 0; j < MazeCols; j++)
            {
                switch (Maze[i][j])
                {
                case 1:
                    printf("# "); // ??
                    break;
                case 0:
                    printf(". "); // ??
                    break;
                case 2:
                    printf("S "); // ??????
                    break;
                case 3:
                    printf("E "); // ??????
                    Endy = i;
                    Endx = j;
                    break;
                case 4:
                    printf("P "); // ?????
                    playery = i;
                    playerx = j;
                    break;
                }
            }
            printf("\n");
        }
        //Maze[playery][playerx] = 4; // ???? ???
        printf("[%d, %d] HP : [%d]\n", playerx, playery,PlayerHP);

        if (Maze[Endy][Endx] == 4)
        {
            printf("축하합니다! 게임을 클리어했습니다!\n");
            break; // ???? ????
        }

        int newx = playerx;
        int newy = playery;

        switch (GetInput())
        {
        case 'w': case'W': // ???? ???
            newy--;
            break;
        case 's': case'S': // ????? ???
            newy++;
            break;
        case 'a': case'A': // ???????? ???
            newx--;
            break;
        case 'd': case 'D': // ?????????? ???
            newx++;
            break;
        }
        printf("진행을 위해 아무키나 눌러주세요");
        int temp = getchar();

        system("cls");
        // ????? ????? ???? ???? ???? ??? ???????
        if (Maze[newy][newx] != 1 && Maze[newy][newx] != 2)
        {
            temp = Maze[newy][newx];

            Maze[newy][newx] = 4; // ??? ??? ???
            Maze[playery][playerx] = 0; // ???? ??? ????
            if (temp == 0)
            {
				if (rand() % 100 < EncounterRate)       //EncounterRAte보다 작은 수가 나오면 전투발생
                {
                    PlayerHP = BattleScene(PlayerHP);
                    printf("진행을 위해 아무키나 눌러주세요");
                    int temp = getchar();

				}
                else if (rand() % 200 < EncounterRate+20)
                {
                    PlayerHP = Bonfire(PlayerHP);
                    printf("진행을 위해 아무키나 눌러주세요");
                    int temp = getchar();

                }
                
            }     
        }
        if (PlayerHP <= 0)
        {
            printf("게임오버!\n");
            break;
        }

    }
}