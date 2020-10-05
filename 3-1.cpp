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

	void add(char *Word, int size);	//����Ʈ�� ������ �߰��ϴ� �Լ�
	void set(char *Word, int size);	//����Ʈ�� �߰��ϴ� �Լ�
	char *getWord(int index);		//����Ʈ�� ���� �ܾ� ������ ������ �Լ�
	int getSize(int index);			//����Ʈ�� ���� Size�� ������ �Լ�
};
//List ������
List::List() {
	head->nextNode = NULL;
	List::count = 0;
}
//List �Ҹ���
List::~List() {

	Node* temp = head;
	int i = 0;
	if (i != count)
	{
		delete temp;	//�޸� ����
		temp->nextNode;
		count++;
	}
}
//List�� �߰��ϴ� �Լ�
void List::add(char *data, int size) {
	Node* newNode = new Node;
	newNode->Word = new char[strlen(data) + 1];
	strcpy(newNode->Word, data);
	newNode->size = size;
	newNode->nextNode = NULL;
	//����� ������尡 ����ִٸ� ���ο� ��带 ����
	if (head->nextNode == NULL) {
		head->nextNode = newNode;
	}
	//����Ʈ�� �������� ã�Ƽ� ������ �ڿ� ���ο� ��带 ����
	else {
		Node* temp = head;
		while (temp->nextNode != NULL) {
			temp = temp->nextNode;
		}
		temp->nextNode = newNode;
	}

	List::count++;//����Ʈ�� ���������Ƿ� Count�� ����
}
//List�� Set�ϴ� �Լ�
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
//List���� ����ִ� ������ Size�� ������ �Լ�
int List::getSize(int index) {
	Node* temp = head;
	for (int i = 0; i < index; i++) {
		temp = temp->nextNode;
	}
	return temp->size;
}
//List�� ����ִ� ������ �ܾ ������ �Լ�
char* List::getWord(int index) {
	Node* temp = head;
	for (int i = 0; i < index; i++) {
		temp = temp->nextNode;
	}
	return temp->Word;
}
//�޸��忡�� �ҷ��� ���ڵ��� ������ ����Ʈ�� ���� �� ó���ϴ� �Լ�
void my_tok(char arr[], List &list, char *Standard);

int main()
{
	char arr[100] = { 0 };
	List Blueberry;	//��纣�� List
	List Banana;	//�ٳ��� List
	List Grape;		//���� List
	List Melon;		//��� List
	List Kiwi;		//Ű�� List

	//input.txt�κ��� ������ �о� �´�//
	ifstream read;
	read.open("input.txt");
	if (read.fail()) {
		cout << "������ �ҷ��� �� �����ϴ�. " << endl;
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

	//Count ����
	int BananaCount = 0;
	int BlueberryCount = 0;
	int KiwiCount = 0;
	int MelonCount = 0;
	int GrapeCount = 0;
	int NodeCount = 0;

	char *temp;
	char *next;
	strcpy(cpyarr, arr); // ��� �������� ����ִ�.

	temp = strtok(cpyarr, " "); // �ѹ�¥����

	while (1) {	//ã�ƾ� �Ǵ� ���� ���� ó���κ�

		if (temp == NULL) break;

		if (strcmp(temp, Standard) == 0) { //���� ���� ã���� 

			temp = strtok(NULL, " "); //�������� Ȯ��

			if (temp == NULL) break;	// ���� ���� NULL �ϰ��
			
			else {	//���� ���� NULL�� �ƴ� ���
				//Count�� 0�̰�, Banana�� ���
				if (BananaCount == 0 && strcmp(temp, "Banana") == 0) {
					BananaCount = BananaCount + 1;
					list.add(temp, BananaCount);
					NodeCount = NodeCount + 1;
					temp = strtok(NULL, " ");
				}
				//Count�� 0�̰�, Blueberry�� ���
				else if (BlueberryCount == 0 && strcmp(temp, "Blueberry") == 0) {
					BlueberryCount = BlueberryCount + 1;
					list.add(temp, BlueberryCount);
					NodeCount = NodeCount + 1;
					temp = strtok(NULL, " ");
				}
				//Count�� 0�̰�, Kiwi�� ���
				else if (KiwiCount == 0 && strcmp(temp, "Kiwi") == 0) {
					KiwiCount = KiwiCount + 1;
					list.add(temp, KiwiCount);
					NodeCount = NodeCount + 1;
					temp = strtok(NULL, " ");
				}
				//Count�� 0�̰�, Melon�� ���
				else if (MelonCount == 0 && strcmp(temp, "Melon") == 0) {
					MelonCount = MelonCount + 1;
					list.add(temp, MelonCount);
					NodeCount = NodeCount + 1;
					temp = strtok(NULL, " ");
				}
				//Count�� 0�̰�, Grape�� ���
				else if (GrapeCount == 0 && strcmp(temp, "Grape") == 0) {
					GrapeCount = GrapeCount + 1;
					list.add(temp, GrapeCount);
					NodeCount = NodeCount + 1;
					temp = strtok(NULL, " ");
				}
				//Count�� 0�� �ƴϰ�, Banana�� ���
				else if (BananaCount != 0 && strcmp(temp, "Banana") == 0) {
					BananaCount = BananaCount + 1;
					list.set(temp, BananaCount);
					temp = strtok(NULL, " ");
				}
				//Count�� 0�� �ƴϰ�, Blueberry�� ���
				else if (BlueberryCount != 0 && strcmp(temp, "Blueberry") == 0) {
					BlueberryCount = BlueberryCount + 1;
					list.set(temp, BlueberryCount);
					temp = strtok(NULL, " ");
				}
				//Count�� 0�� �ƴϰ�, Kiwi�� ���
				else if (KiwiCount != 0 && strcmp(temp, "Kiwi") == 0) {
					KiwiCount = KiwiCount + 1;
					list.set(temp, KiwiCount);
					temp = strtok(NULL, " ");
				}
				//Count�� 0�� �ƴϰ�, Melon�� ���
				else if (MelonCount != 0 && strcmp(temp, "Melon") == 0) {
					MelonCount = MelonCount + 1;
					list.set(temp, MelonCount);
					temp = strtok(NULL, " ");
				}
				//Count�� 0�� �ƴϰ�, Grape�� ���
				else if (GrapeCount != 0 && strcmp(temp, "Grape") == 0) {
					GrapeCount = GrapeCount + 1;
					list.set(temp, GrapeCount);
					temp = strtok(NULL, " ");
				}

			}

		}
		//���� ���ڸ� �޾ƿ´�.
		else temp = strtok(NULL, " ");
	}

	//����Ʈ �������� ����ϴ� �κ�
	cout << Standard << ": ";
	for (int i = 1; i <= NodeCount; i++) {
		if(i==NodeCount) cout << list.getWord(i) << "(" << list.getSize(i) << ")" << endl;
		else cout << list.getWord(i) << "(" << list.getSize(i) << "),";
	}

}