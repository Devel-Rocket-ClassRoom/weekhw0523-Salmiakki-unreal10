#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string>
#include "Homework03.h"
using namespace std;

int Bet(int currentMoney)
{
	int MyBet = 0;
	
	while (MyBet < 100 || MyBet > currentMoney)						// 최소 베팅 금액은 100
	{
		printf("베팅 금액을 입력해주세요 :");
		cin >> MyBet;
		if (MyBet < 100)
		{
			printf("최소 베팅 금액은 100입니다. 다시 입력해주세요.\n");
		}
		else if (MyBet > currentMoney)
		{
			printf("소지 금액을 초과할 수 없습니다. 다시 입력해주세요.\n");
		}
	}
	printf("베팅 금액 : [%d]\n", MyBet);
	return MyBet;
	
}

int Spin()
{
	int Multiplier = 0; // 배율값
	int Num1=rand() % 10; // 0~9까지의 숫자 중 하나가 랜덤으로 나옴
	int Num2=rand() % 10; // 0~9까지의 숫자 중 하나가 랜덤으로 나옴
	int Num3=rand() % 10; // 0~9까지의 숫자 중 하나가 랜덤으로 나옴
	printf("\n결과 : [%d] [%d] [%d]\n\n", Num1, Num2, Num3);
	if (Num1 == Num2 && Num2 == Num3) // 세 숫자가 모두 같을 때
	{
		Multiplier = 50; // 50배
		if (Num1 == 7) // 세 숫자가 모두 7일 때
		{
			Multiplier = 10000; // 10000배
			printf("***축하합니다! 777이 나왔습니다! 10000배를 획득했습니다!***\n");
		}
		else
		{
			printf("축하합니다! 같은 숫자 3개가 나왔습니다! 50배를 획득했습니다!\n");
		}
	}
	return Multiplier;
}

void Homework03_Run()
{
	int Seed = (unsigned int)time(0);
	srand(Seed);
	//시작 금액 10000
	int InitialMoney = 10000;
	int Money = InitialMoney;
	/*한판에 무조건  최소 100 배팅해야 함.만약 소지금액이 100 이하일 경우 게임 종료.
		같은 숫자 3개가 나오면 50배로 돌려 받는다.
		만약 777이면 10000배 받음*/

	while (Money > 99) 
	{
		printf("현재 소지금액 : [%d]\n", Money);
		int Prize = 0;
		int bet = 0;
		bet = Bet(Money); // 베팅 금액 입력 받기
		Prize = bet*Spin(); // 슬롯머신 돌리기
		if (Prize > 0) // 상금이 있을 때
		{
			Money += Prize; // 상금 추가
			Money -= bet;
			printf("축하합니다! %d원을 획득했습니다!\n", Prize);
		}
		else // 상금이 없을 때
		{
			Money -= bet; // 베팅 금액 차감
			printf("아쉽습니다! %d원을 잃었습니다.\n", bet);
		}
		
		

	}
	printf("게임종료\n\n\n\n");

}
