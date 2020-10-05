#include <iostream>
#include <cstring>
#include "AddrManager.h"

using namespace std;


int main()
{	//AddrManager 클래스 manage 생성
	AddrManager manage;

	for (;;) {
		char Input[10];
		cout << "1. Show People    2. Show House    3. Change Name    4. Change Address    5. Quit" << endl;
		cout << "input: ";
		cin.getline(Input, sizeof(Input));
		while (1)
		{	//숫자 입력이 1~5가 아닐경우
			if (atoi(Input) < 6 && atoi(Input) > 0) break;
			else
			{	//다시 입력받는다.
				cout << "input값을 1~5사이에 숫자로 다시 입력해주세요. : ";
				cin.getline(Input, sizeof(Input));
			}
		}
		/*1. Show People*/
		if (atoi(Input) == 1)
		{
			manage.ShowPeople();
		}
		/*2. Show House*/
		else if (atoi(Input) == 2)
		{
			manage.ShowHouse();
		}
		/*3 Change Name*/
		else if (atoi(Input) == 3)
		{
			manage.ChangeName();
		}
		/*4. Change Address*/
		else if (atoi(Input) == 4)
		{
			manage.ChangeAddress();
		}
		/*5. Quit*/
		else if (atoi(Input) == 5)
		{
			break;
		}
	

	}

	return 0;
}