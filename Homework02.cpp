#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string>
using namespace std;

void Homework02_Run()
{
	int numb;
	int sum = 0;
	printf("정수를 입력해주세요 :");
	cin >> numb;
	while (numb > 0)
	{
		sum += numb % 10;//나머지 더하기	ex) 1234 % 10 = (4)  -> 123 % 10 = (3) -> 12 % 10 = (2) -> 1 % 10 = (1)
		numb /= 10;		//나머지 끝자리제거		1234 / 10 = 123		123 / 10 =12	  12 / 10 = 1	-> 1 / 10 = 0
	}
	printf("%d\n", sum);
}