#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string>
#include "Homework04.h"
#include "Homework05.h"

using namespace std;


void Homework04_Run()
{
	int Seed = (unsigned int)time(0);
	srand(Seed);
	//시작 금액 10000
	int InitialMoney = 10000;
	int Money = InitialMoney;
	//시작 금액 10000
	/*한판에 무조건 최소 100 배팅해야 함.만약 소지금액이 100 이하일 경우 게임 종료.
	딜러는 A~K까지의 트럼프 카드 중 2장을 중복없이 선택하고 조커 카드가 추가된다.
	플레이어는 딜러의 카드 중 한장을 선택한다.
	만약 플레이어가 조커를 뽑있다면 플레이어의 승리.배팅 금액의 2배를 받는다.
	플레이어가 조커를 뽑지 못했다면 다음 게임을 시작하거나 배팅 금액의 2배를 추가로 지불하고 한번 더 선택할 수 있다.*/
	

	string CardNames[] = { "A", "J", "Q", "K", "JOKER" };

	while (Money > 99)
	{
		printf("\n딜러의 카드 : [?] [?] [?]\n");
		bool Pick[3] = { false, false, false }; // 플레이어가 선택한 카드
		int DealerHand[3] = { 0, }; // 딜러의 카드 3장
		printf("현재 소지금액 : [%d]\n", Money);
		int bet = 0;
		bet = Bet(Money); // 베팅 금액 입력 받기
		Money -= bet;
		int Array[6] = { 0,1,2,3,4,5 }; // 0~5까지의 숫자 //0:빈 칸, 1:A, 2:J, 3:Q, 4:K, 5:JOKER
		int JokerIndex = rand() % 3; // 조커 위치 랜덤
		for (int i = 0; i < 3; i++)
		{
			while (DealerHand[i] == 0 || DealerHand[i] == 5)
			{
				int RandomIndex = rand() % 6; // 0~5 숫자를 랜덤으로 뽑기
				DealerHand[i] = Array[RandomIndex]; // 딜러의 카드로 선택
				//printf("%d, ", DealerHand[i]);
				Array[RandomIndex] = 0; // 중복 방지 
			}

		}
		DealerHand[JokerIndex] = 5; // 딜러의 카드 중 하나에 조커 배치
		int NextGame = 0;
		int Input = 0;
		bool Round2 = false;
		while (true)
		{
			printf("1) 2) 3) 카드 중 하나를 선택해주세요 :");
			cin >> Input;
			if (Pick[Input-1] == false)
			{
				switch (Input)
				{
				case 1:
					Pick[0] = true;
					break;
				case 2:
					Pick[1] = true;
					break;
				case 3:
					Pick[2] = true;
					break;
				}
				printf("\n딜러의 카드 : [%s] [%s] [%s]\n",
					Pick[0] ?
					CardNames[DealerHand[0] - 1].c_str() : "?",
					Pick[1] ?
					CardNames[DealerHand[1] - 1].c_str() : "?",
					Pick[2] ?
					CardNames[DealerHand[2] - 1].c_str() : "?");
			}
			else
			{
				printf("이미 선택한 카드입니다. 다른 카드를 선택해주세요.\n");
				continue;
			}
			if (DealerHand[Input - 1] == 5) // 플레이어가 조커를 뽑았을 때
			{
				Money += 2*bet;
				printf("축하합니다! 조커를 뽑았습니다! [%d]원을 획득했습니다!\n\n", bet);
				break;
			}
			else if  (Round2)
			{
				printf("조커가 아니였습니다...[%d]원을 잃었습니다.\n\n", bet);
				
				break;
			}
			printf("1) 다음 게임 2)묻고 더블로\n");
			cin >> NextGame;
			switch (NextGame)
			{
			case 1:
				printf("다음 게임을 시작합니다.\n");
				break;
			case 2:
				printf("배팅금의 2배를 추가 지불합니다.\n");
				Round2 = true;
				Money -= 2*bet;
				bet += 2*bet;			// 배팅 금액의 2배를 추가로 지불
				printf("현재 소지금액 : [%d]\n", Money);
				continue;
			}
			break;
			
		}
		
	}
	printf("소지 금액이 100 이하입니다. 게임이 종료됩니다.\n");

	
}
