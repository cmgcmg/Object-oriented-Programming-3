#include <iostream>
#include <cstring>
#include "AddrManager.h"

using namespace std;


int main()
{	//AddrManager Ŭ���� manage ����
	AddrManager manage;

	for (;;) {
		char Input[10];
		cout << "1. Show People    2. Show House    3. Change Name    4. Change Address    5. Quit" << endl;
		cout << "input: ";
		cin.getline(Input, sizeof(Input));
		while (1)
		{	//���� �Է��� 1~5�� �ƴҰ��
			if (atoi(Input) < 6 && atoi(Input) > 0) break;
			else
			{	//�ٽ� �Է¹޴´�.
				cout << "input���� 1~5���̿� ���ڷ� �ٽ� �Է����ּ���. : ";
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