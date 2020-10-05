#include <iostream>
#include <string.h>
#pragma warning(disable:4996)
using namespace std;

class Node {
public:
	char *Name;
	char *Brand;
	int Price;
	Node* NextNode;
	Node* PrevNode;
};

class List
{
private:	
	int count;
	Node* head;
	Node* tail;

public:
	List();	//������
	void InsertBegining(char *Name, char *Brand, int Price);	//ó�� �����Ҷ� ����ϴ� �Լ�
	void InsertLast(char *Name, char *Brand, int Price);		//������ �����Ҷ� ����ϴ� �Լ�
	void InsertPosition(char *Name, char *Brand, int Price, int index);	//�ش��ϴ� ��ġ�� �����ϴ� �Լ�
	void DeleteProduct(char *Name);	//��带 �����ϴ� �Լ�
	void UpdateProduct(char *ChangeName, char *Name, char *Brand, int Price); //�ش� ��带 ã�Ƽ� ������ �����ϴ� �Լ�
	void SearchProduct(char *Name);	//�ش� ��带 ã�� �Լ�
	void SortedPrice();		//���ݼ����� Soritng�ϴ� �Լ�
	void DisplayProduct();	//��ǰ���� ����ϴ� �Լ�
	void ReserveProduct();	//��ǰ���� Reserver�ϴ� �Լ�
	~List();	//�Ҹ���
};
/*������*/
List::List()
{
	head = NULL;
	tail = NULL;
	List::count = 0;
}
/*ó�� ��ġ�� �����ϴ� �Լ�*/
void List::InsertBegining(char *Name, char *Brand, int Price)
{
	Node* newNode = new Node;
	newNode->Name = new char[strlen(Name) + 1];
	strcpy(newNode->Name, Name);
	newNode->Brand = new char[strlen(Brand) + 1];
	strcpy(newNode->Brand, Brand);
	newNode->Price = Price; //���� ������ ��忡 ��������

	//���ο� ����� ������ ���� head�� ����
	newNode->NextNode = head;
	//head�� ������� �ʴٸ� head�� ���ο� ��带 ����
	if (head != NULL) {
		head->PrevNode = newNode;
	}
	//head�� ���ο� Node�� ����
	head = newNode;
	//Count ����
	List::count++;
	//head�� ������尡 NULL�� ��� tail�� head�� ����Ų��.
	if (head->NextNode == NULL) {
		tail = head;
	}
	//head�� tail�� ����
	head->PrevNode = tail;
	tail->NextNode = head;
}
/*������ ��ġ�� �����ϴ� �Լ�*/
void List::InsertLast(char *Name, char *Brand, int Price)
{
	Node* newNode = new Node;
	newNode->Name = new char[strlen(Name) + 1];
	strcpy(newNode->Name, Name);
	newNode->Brand = new char[strlen(Brand) + 1];
	strcpy(newNode->Brand, Brand);
	newNode->Price = Price; //���� ������ ��忡 ��������
	//���ο� ����� ������带 ���Ϸ� ���� �� ����
	newNode->PrevNode = tail;
	//tail�� ������ �����Ѵٸ� tail������ ���ο� ��带 ����
	if (tail != NULL) {
		tail->NextNode = newNode;
	}
	//tail������ ���ο� Node�� �ٲ��ش�.
	tail = newNode;
	//ī��Ʈ ����
	List::count++;
	//tail�� ������尡 ����ִٸ� head�� tail�� ���� ���� ����Ų��.
	if (tail->PrevNode == NULL) {
		head = tail;
	}
	//head�� tail������ ����
	head->PrevNode = tail;
	tail->NextNode = head;

}
/*�ش��ϴ� ��ġ�� �����ϴ� �Լ�*/
void List::InsertPosition(char *Name, char *Brand, int Price, int index)
{
	Node* newNode = new Node;
	newNode->Name = new char[strlen(Name) + 1];
	strcpy(newNode->Name, Name);
	newNode->Brand = new char[strlen(Brand) + 1];
	strcpy(newNode->Brand, Brand);
	newNode->Price = Price; //���� ������ ��忡 ��������
	/*Position�� ó���� ���*/
	/*InsetBeginning�� �Ȱ��� �����ϸ� �ȴ�.*/
	if (index == 1) {
		
		newNode->NextNode = head;
		if (head != NULL) head->PrevNode = newNode;
		head = newNode; 
		if (head->NextNode == NULL) tail = head;
		head->PrevNode = tail;
		tail->NextNode = head;
	}
	/*Position�� �������� ���*/
	/*InsetLast�� �Ȱ��� �����ϸ� �ȴ�.*/
	else if (index > 1 && index == count + 1) {
		
		newNode->PrevNode = tail;
		if (tail != NULL) tail->NextNode = newNode;
		tail = newNode;
		if (tail->PrevNode == NULL) head = tail;
		tail->NextNode = head;
		head->PrevNode = tail;
	}
	/*Position�� ó���� ���*/
	/*InsetBeginning�� ���� �����ϸ� �ȴ�.*/
	else if (index > count + 1)
	{
		cout << "������������ 2�� �̻� Position���� InsertPosition�� �Ұ����մϴ�." << endl;
	}
	/*Position�� �߰��� ���*/
	else {
		
		Node *temp = head;
	
		for (int i = 1; i < count; i++)
		{
			temp = temp->NextNode;
		}
		newNode->PrevNode = temp->PrevNode;
		newNode->NextNode = temp;
		temp->PrevNode->NextNode = newNode;
		temp->PrevNode = newNode;

	}
	//���Ե� ���̱� ������ Count����
	List::count++;
}
/*�̸����� Node�� ã�Ƽ� �����ϴ� �Լ�*/
void List::DeleteProduct(char *Name)
{	
	Node *temp = head;
	int index;
	int overlap = 0;
	//�ش� Node�� ã�� for��
	for (index = 1; index <= count; index++)
	{
		if (strcmp(temp->Name, Name) == 0) {
			overlap = 1; break;
		}
		else temp = temp->NextNode;
	}
	//�̸��� ã�Ұ�, �����Ϸ��� Node�� ó�� ��ġ�� ���
	//�����Ϸ��� Node�� ���� ������ ������ �����ϰ� delete�� �޸�����
	if (overlap == 1 && index == 1)
	{
		head = temp->NextNode;
		head->PrevNode = tail;
		cout << "**" << temp->Name << " " << "has been deleted from position " << index << "**";
		delete temp;
		List::count--;

	}
	//�̸��� ã�Ұ�, �����Ϸ��� Node�� ��ġ�� �������� ���
	//�����Ϸ��� Node�� ���� ������ ������ �����ϰ� delete�� �޸�����
	else if (overlap == 1 && index > 1 && index == count)
	{
		tail = temp->PrevNode;
		tail->NextNode = head;
		cout << "**" << temp->Name << " " << "has been deleted from position " << index << "**";
		delete temp;
		List::count--;
	}
	//�̸��� ã�Ұ�, �����Ϸ��� Node�� �߰� ��ġ�� ���
	//�����Ϸ��� Node�� ���� ������ ������ �����ϰ� delete�� �޸�����
	else if (overlap == 1 && index > 1 && index < count) {
		temp->PrevNode->NextNode = temp->NextNode;
		temp->NextNode->PrevNode = temp->PrevNode;
		cout << "**" << temp->Name << " " << "has been deleted from position " << index << "**";
		delete temp;
		List::count--;
	}
	//����ó��
	else {
		cout << "�����Ϸ��� ������ �����ϴ�." << endl;
	}
	
}
/*�̸����� Node�� ã�Ƽ� ������ �����ϴ� �Լ�*/
void List::UpdateProduct(char *ChangeName, char *Name, char *Brand, int Price)
{
	Node *temp = head;
	int index;
	int overlap = 0;
	//�ش� Node�� ã�� for��
	for (index = 1; index <= count; index++)
	{
		if (strcmp(temp->Name, ChangeName) == 0) {
			overlap = 1; break;
		}
		else temp = temp->NextNode;;
	}
	//Search�ؼ� �ش� Node�� ã�Ҵٸ� ������ �������ش�.
	if (overlap == 1)
	{
		temp->Name = new char[strlen(Name) + 1];
		temp->Brand = new char[strlen(Brand) + 1];
		strcpy(temp->Name, Name);
		strcpy(temp->Brand, Brand);
		temp->Price = Price;
	}
	//Search�ߴµ� ������ ���ٸ� ���
	else cout << "������Ʈ�� ������ �����ϴ�." << endl;

}
/*�̸����� Node�� ã�Ƽ� ������ ����ϴ� �Լ�*/
void List::SearchProduct(char *Name)
{
	Node *temp = head;
	int index;
	int overlap = 0;
	//�ش� Node�� ã�� for��//
	for (index = 1; index <= count; index++)
	{
		if (strcmp(temp->Name, Name) == 0) {
			overlap = 1; break;
		}
		else temp = temp->NextNode;
	}
	//Node�� ã���� ��� �������� ���
	if (overlap == 1)
	{
		cout << "*At position: " << index << "*" << endl;
		cout << "Product name: " << temp->Name << endl;
		cout << "Product brand: " << temp->Brand << endl;
		cout << "Product price : " << temp->Price << endl;
	}
	//Node�� ã�� ������ ��� ���
	else cout << "�˻� �ϴ� ������ �����ϴ�" << endl;
}
/*���ݼ����� Sorting�ϴ� �Լ�*/
/*Node�� �ǵ帮�� �ʰ� ������ �������� ����*/
void List::SortedPrice()
{
	if (List::count == 0) {
		cout << "Sorting�� ������ �����ϴ�." << endl;
	}

	else {
		int index;
		//������ ���� ��� �̸������� �����ϱ� ������
		//�̸������� ���� �����Ѵ�.
		for (index = 1; index < count; index++) {
			Node *temp = head;
			for (int j = 1; j < count; j++) {
				//�ش� ��ġ�� ��������� �̸��� ���Ѵ�.
				if (strcmp(temp->Name ,temp->NextNode->Name) > 0) {
					//�����͸� �����ϴ� �κ�
					char *tempBrand;
					tempBrand = new char[strlen(temp->Brand) + 1];
					char *tempName;
					tempName = new char[strlen(temp->Name) + 1];
					int tempPrice;

					strcpy(tempBrand, temp->Brand);
					strcpy(temp->Brand, temp->NextNode->Brand);
					strcpy(temp->NextNode->Brand, tempBrand);

					strcpy(tempName, temp->Name);
					strcpy(temp->Name, temp->NextNode->Name);
					strcpy(temp->NextNode->Name, tempName);

					tempPrice = temp->Price;
					temp->Price = temp->NextNode->Price;
					temp->NextNode->Price = tempPrice;

					temp = temp->NextNode;

				}
				else temp = temp->NextNode;
			}
		}
		//�̸������� ���� �Ǿ��� ������ ���ݼ����� �����Ѵ�.
		for (index = 1; index < count; index++) {
				Node *temp = head;
			for (int j = 1; j < count; j++) { 
				//�ش� Node�� ���� Node�� ������ ��
				if (temp->Price > temp->NextNode->Price) {
					//�����͸� �����ϴ� �κ�
					char *tempBrand;
					tempBrand = new char[strlen(temp->Brand) + 1];
					char *tempName;
					tempName = new char[strlen(temp->Name) + 1];
					int tempPrice;

					strcpy(tempBrand,temp->Brand);
					strcpy(temp->Brand, temp->NextNode->Brand);
					strcpy(temp->NextNode->Brand, tempBrand);

					strcpy(tempName, temp->Name);
					strcpy(temp->Name, temp->NextNode->Name);
					strcpy(temp->NextNode->Name, tempName);

					tempPrice = temp->Price;
					temp->Price = temp->NextNode->Price;
					temp->NextNode->Price = tempPrice;

					temp = temp->NextNode;
					
				}
				else temp = temp->NextNode;
			}
		}
	}
	
}
/*List�� ����ϴ� �Լ�*/
void List::DisplayProduct()
{	
	//����Ʈ ������ ���� ���
	if (count == 0) {
		cout << "������ �����ϴ�." << endl;
	}
	else {
		Node* temp = head;
		//head���� �������� �ѱ�鼭 List�� �ִ� Node �������� ���
		for (int i = 1; i <= List::count; i++)
		{
			
			cout << "product name: " << temp->Name << endl;
			cout << "brand name: " << temp->Brand << endl;
			cout << "price: " << temp->Price << endl;
			temp = temp->NextNode;
		}
	}
}

void List::ReserveProduct()
{	
	//List�� �ϳ��ۿ� ���� ���
	if (count < 2)
	{
		cout << "Reserve�� ������ ���ų� ������ 1���̱� ������ Reserve���� �ʾƵ� �˴ϴ�." << endl;
	}

	else
	{
		Node* temp = head;
		Node* temp2 = tail;
		//������ �������� head�� tail�� �������� �ٲ��ش�
		//head�� 1ĭ�� Next�ϰ� tail�� 1ĭ�� Prev�Ͽ� �������� �ٲ��ش�.
		for (int i = 0; i < count / 2; i++)
		{
			char *tempName;
			char *tempBrand;
			int tempPrice;
			tempBrand = new char[strlen(temp->Brand) + 1];
			tempName = new char[strlen(temp->Name) + 1];
			//Data�� �ٲ��ִ� �κ�
			strcpy(tempBrand, temp->Brand);
			strcpy(temp->Brand, temp2->Brand);
			strcpy(temp2->Brand, tempBrand);

			strcpy(tempName, temp->Name);
			strcpy(temp->Name, temp2->Name);
			strcpy(temp2->Name, tempName);

			tempPrice = temp->Price;
			temp->Price = temp2->Price;
			temp2->Price = tempPrice;

			//head�� Next
			//tail�� Prev
			temp = temp->NextNode;
			temp2 = temp2->PrevNode;

		}

		cout << "**The product list has been reserved**" << endl;
	}
}

List::~List()
{	
	Node* temp = tail;
	if (count != 0)
	{
		delete temp;
		temp->PrevNode;
		count--;
	}
}

int main() {
	
	char Input[128] = { 0 };
	char name[128] = { 0 };
	char brand[128] = { 0 };
	char price[128] = { 0 };
	char changename[128] = { 0 };
	char sequence[128] = { 0 };

	//��� �κ��� ���
	cout << "******************************************" << endl;
	cout << "S T A R T " << endl;
	cout << "******************************************" << endl;
	cout << "1.Insert product at beginning" << endl;
	cout << "2.Insert product at last" << endl;
	cout << "3.Insert product at position" << endl;
	cout << "4.Delete Product" << endl;
	cout << "5.Update Product" << endl;
	cout << "6.Search product" << endl;
	cout << "7.Sort by price in ascending order" << endl;
	cout << "8.Display product list" << endl;
	cout << "9.Reverse product list" << endl;
	cout << "10.Exit" << endl;

	List Management;
	

	while (1) {
		cout << endl;
		cout << "Enter your number: ";
		cin.getline(Input, sizeof(Input));
		//InputNumber ����ó��
		while (1)
		{	
			if (atoi(Input) != 0) break;

			else {
				cout << "Number�� ���ڶǴ� 1~10���̷� �Է��ϼ���. :";
				cin.getline(Input, sizeof(Input));
			}
		}
		/*1.Insert product at beginning*/
		if (atoi(Input) == 1)
		{
			cout << "<Insert product at beginning>" << endl;
			cout << "->Enter the product name: ";
			cin.getline(name, sizeof(name));
			cout << "->Enter the product brand: ";
			cin.getline(brand, sizeof(brand));
			cout << "->Enter the product price: ";
			cin.getline(price, sizeof(price));

			while (1)	//Pirce�� ���ڷ� �Է¹޴� ����ó��
			{
				if (atoi(price) != 0) break;
				else {
					cout << "price�� ���ڷ� �ٽ� �Է��� �ּ���. :";
					cin.getline(price, sizeof(price));
				}
			}
			Management.InsertBegining(name, brand, atoi(price));

		}
		/*2.Insert product at Last*/
		else if (atoi(Input) == 2)
		{
			cout << "<Insert product at last>" << endl;
			cout << "->Enter the product name: ";
			cin.getline(name, sizeof(name));
			cout << "->Enter the product brand: ";
			cin.getline(brand, sizeof(brand));
			cout << "->Enter the product price: ";
			cin.getline(price, sizeof(price));

			while (1)	//Pirce�� ���ڷ� �Է¹޴� ����ó��
			{
				if (atoi(price) != 0) break;
				else {
					cout << "price�� ���ڷ� �ٽ� �Է��� �ּ���. :";
					cin.getline(price, sizeof(price));
				}
			}
			Management.InsertLast(name, brand, atoi(price));
		}
		/*3.Insert product at Position*/
		else if (atoi(Input) == 3)
		{
			cout << "<Insert product at position>" << endl;
			cout << ">Enter the position of product inserted: ";
			cin.getline(sequence, sizeof(sequence));
			while (1)
			{
				if (atoi(sequence) != 0) break;
				else {
					cout << "position�� ���ڷ� �ٽ� �Է��� �ּ���. :";
					cin.getline(price, sizeof(price));
				}

			}
			cout << "->Enter the product name: ";
			cin.getline(name, sizeof(name));
			cout << "->Enter the product brand: ";
			cin.getline(brand, sizeof(brand));
			cout << "->Enter the product price: ";
			cin.getline(price, sizeof(price));

			while (1)	//Pirce�� ���ڷ� �Է¹޴� ����ó��
			{
				if (atoi(price) != 0) break;
				else {
					cout << "price�� ���ڷ� �ٽ� �Է��� �ּ���. :";
					cin.getline(price, sizeof(price));
				}
			}
			Management.InsertPosition(name, brand, atoi(price), atoi(sequence));
		}
		/*4.Delete Product*/
		else if (atoi(Input) == 4)
		{
			cout << "<Delete product>" << endl;
			cout << "->Enter the product name you want to delete: ";
			cin.getline(name, sizeof(name));
			Management.DeleteProduct(name);
		}
		/*5.Update Product*/
		else if (atoi(Input) == 5)
		{
			cout << "<Update product>" << endl;
			cout << ">Enter the product name: ";
			cin.getline(changename, sizeof(changename));
			cout << ">Enter the new product name: ";
			cin.getline(name, sizeof(name));
			cout << ">Enter the new brand: ";
			cin.getline(brand, sizeof(brand));
			cout << ">Enter the new price: ";
			cin.getline(price, sizeof(price));


			while (1)	//Pirce�� ���ڷ� �Է¹޴� ����ó��
			{
				if (atoi(price) != 0) break;
				else {
					cout << "price�� ���ڷ� �ٽ� �Է��� �ּ���. : ";
					cin.getline(price, sizeof(price));
				}
			}

			Management.UpdateProduct(changename, name, brand, atoi(price));
		}
		/*6.Search Product*/
		else if (atoi(Input) == 6)
		{
			cout << "<Search product>" << endl;
			cout << "->Enter the product name: ";
			cin.getline(name, sizeof(name));
			Management.SearchProduct(name);

		}
		/*7.Sort by price in ascending order */
		else if (atoi(Input) == 7)
		{
			cout << "<Sort by price in ascending order>" << endl;
			Management.SortedPrice();
			
		}
		/*8. Display product listr*/
		else if (atoi(Input) == 8)
		{
			cout << "Display product list" << endl;
			Management.DisplayProduct();

		}
		/*9.Reserve product list */
		else if (atoi(Input) == 9)
		{
			cout << "<Reserve product list" << endl;
			Management.ReserveProduct();
		}
		/*10. Quit */
		else if (atoi(Input) == 10)
		{
			break;
		}
		
	}

	return 0;
}