#include <iostream>
#include <cstring>
#include <fstream>
#pragma warning (disable:4996)
#pragma warning (disable:4101)
using namespace std;

//Singly Linked List
class List
{
private:
	class Node {
	public:
		char *Word;		
		int size;		
		Node* nextNode;	
	};

	int count;
	Node* head = new Node;

public:
	List();
	~List();

	void add(char *Word, int size);	//리스트에 정보를 추가하는 함수
	void set(char *Word, int size);	//리스트를 추가하는 함수
	char *getWord(int index);		//리스트로 부터 단어 정보를 얻어오는 함수
	int getSize(int index);			//리스트로 부터 Size를 얻어오는 함수
};
//List 생성자
List::List() {
	head->nextNode = NULL;
	List::count = 0;
}
//List 소멸자
List::~List() {

	Node* temp = head;
	int i = 0;
	if (i != count)
	{
		delete temp;	//메모리 헤제
		temp->nextNode;
		count++;
	}
}
//List에 추가하는 함수
void List::add(char *data, int size) {
	Node* newNode = new Node;
	newNode->Word = new char[strlen(data) + 1];
	strcpy(newNode->Word, data);
	newNode->size = size;
	newNode->nextNode = NULL;
	//헤드의 다음노드가 비어있다면 새로운 노드를 삽입
	if (head->nextNode == NULL) {
		head->nextNode = newNode;
	}
	//리스트의 마지막을 찾아서 마지막 뒤에 새로운 노드를 삽입
	else {
		Node* temp = head;
		while (temp->nextNode != NULL) {
			temp = temp->nextNode;
		}
		temp->nextNode = newNode;
	}

	List::count++;//리스트에 삽입했으므로 Count는 증가
}
//List에 Set하는 함수
void List::set(char *Word, int size)
{
	Node *temp = head;
	for (int i = 0; i < count; i++) {
		temp = temp->nextNode;
		if (strcmp(temp->Word, Word) == 0) { break; }
		else continue;
	}
	temp->size = size;
}
//List에서 들어있는 정보의 Size를 얻어오는 함수
int List::getSize(int index) {
	Node* temp = head;
	for (int i = 0; i < index; i++) {
		temp = temp->nextNode;
	}
	return temp->size;
}
//List에 들어있는 정보의 단어를 얻어오는 함수
char* List::getWord(int index) {
	Node* temp = head;
	for (int i = 0; i < index; i++) {
		temp = temp->nextNode;
	}
	return temp->Word;
}
//메모장에서 불러온 인자들을 가지고 리스트에 삽입 및 처리하는 함수
void my_tok(char arr[], List &list, char *Standard);

int main()
{
	char arr[100] = { 0 };
	List Blueberry;	//블루베리 List
	List Banana;	//바나나 List
	List Grape;		//포도 List
	List Melon;		//멜론 List
	List Kiwi;		//키위 List

	//input.txt로부터 한줄을 읽어 온다//
	ifstream read;
	read.open("input.txt");
	if (read.fail()) {
		cout << "파일을 불러올 수 없습니다. " << endl;
	}

	else {
		read.getline(arr, sizeof(arr));
	}

	cout << arr << endl;
	my_tok(arr, Blueberry, "Blueberry");
	my_tok(arr, Banana, "Banana");
	my_tok(arr, Grape, "Grape");
	my_tok(arr, Melon, "Melon");
	my_tok(arr, Kiwi, "Kiwi");

	

	return 0;
}

void my_tok(char arr[], List &list, char *Standard)
{
	char cpyarr[100] = { 0 };
	char *Banana;
	char *Blueberry;
	char *Kiwi;
	char *Melon;
	char *Grape;

	//Count 변수
	int BananaCount = 0;
	int BlueberryCount = 0;
	int KiwiCount = 0;
	int MelonCount = 0;
	int GrapeCount = 0;
	int NodeCount = 0;

	char *temp;
	char *next;
	strcpy(cpyarr, arr); // 모든 정보들이 들어있다.

	temp = strtok(cpyarr, " "); // 한번짜르고

	while (1) {	//찾아야 되는 값의 제일 처음부분

		if (temp == NULL) break;

		if (strcmp(temp, Standard) == 0) { //기준 값을 찾으면 

			temp = strtok(NULL, " "); //다음것을 확인

			if (temp == NULL) break;	// 다음 값이 NULL 일경우
			
			else {	//다음 값이 NULL이 아닐 경우
				//Count가 0이고, Banana일 경우
				if (BananaCount == 0 && strcmp(temp, "Banana") == 0) {
					BananaCount = BananaCount + 1;
					list.add(temp, BananaCount);
					NodeCount = NodeCount + 1;
					temp = strtok(NULL, " ");
				}
				//Count가 0이고, Blueberry일 경우
				else if (BlueberryCount == 0 && strcmp(temp, "Blueberry") == 0) {
					BlueberryCount = BlueberryCount + 1;
					list.add(temp, BlueberryCount);
					NodeCount = NodeCount + 1;
					temp = strtok(NULL, " ");
				}
				//Count가 0이고, Kiwi일 경우
				else if (KiwiCount == 0 && strcmp(temp, "Kiwi") == 0) {
					KiwiCount = KiwiCount + 1;
					list.add(temp, KiwiCount);
					NodeCount = NodeCount + 1;
					temp = strtok(NULL, " ");
				}
				//Count가 0이고, Melon일 경우
				else if (MelonCount == 0 && strcmp(temp, "Melon") == 0) {
					MelonCount = MelonCount + 1;
					list.add(temp, MelonCount);
					NodeCount = NodeCount + 1;
					temp = strtok(NULL, " ");
				}
				//Count가 0이고, Grape일 경우
				else if (GrapeCount == 0 && strcmp(temp, "Grape") == 0) {
					GrapeCount = GrapeCount + 1;
					list.add(temp, GrapeCount);
					NodeCount = NodeCount + 1;
					temp = strtok(NULL, " ");
				}
				//Count가 0이 아니고, Banana일 경우
				else if (BananaCount != 0 && strcmp(temp, "Banana") == 0) {
					BananaCount = BananaCount + 1;
					list.set(temp, BananaCount);
					temp = strtok(NULL, " ");
				}
				//Count가 0이 아니고, Blueberry일 경우
				else if (BlueberryCount != 0 && strcmp(temp, "Blueberry") == 0) {
					BlueberryCount = BlueberryCount + 1;
					list.set(temp, BlueberryCount);
					temp = strtok(NULL, " ");
				}
				//Count가 0이 아니고, Kiwi일 경우
				else if (KiwiCount != 0 && strcmp(temp, "Kiwi") == 0) {
					KiwiCount = KiwiCount + 1;
					list.set(temp, KiwiCount);
					temp = strtok(NULL, " ");
				}
				//Count가 0이 아니고, Melon일 경우
				else if (MelonCount != 0 && strcmp(temp, "Melon") == 0) {
					MelonCount = MelonCount + 1;
					list.set(temp, MelonCount);
					temp = strtok(NULL, " ");
				}
				//Count가 0이 아니고, Grape일 경우
				else if (GrapeCount != 0 && strcmp(temp, "Grape") == 0) {
					GrapeCount = GrapeCount + 1;
					list.set(temp, GrapeCount);
					temp = strtok(NULL, " ");
				}

			}

		}
		//다음 인자를 받아온다.
		else temp = strtok(NULL, " ");
	}

	//리스트 정보들을 출력하는 부분
	cout << Standard << ": ";
	for (int i = 1; i <= NodeCount; i++) {
		if(i==NodeCount) cout << list.getWord(i) << "(" << list.getSize(i) << ")" << endl;
		else cout << list.getWord(i) << "(" << list.getSize(i) << "),";
	}

}