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
	List();	//생성자
	void InsertBegining(char *Name, char *Brand, int Price);	//처음 삽입할때 사용하는 함수
	void InsertLast(char *Name, char *Brand, int Price);		//마지막 삽입할때 사용하는 함수
	void InsertPosition(char *Name, char *Brand, int Price, int index);	//해당하는 위치에 삽입하는 함수
	void DeleteProduct(char *Name);	//노드를 삭제하는 함수
	void UpdateProduct(char *ChangeName, char *Name, char *Brand, int Price); //해당 노드를 찾아서 정보를 수정하는 함수
	void SearchProduct(char *Name);	//해당 노드를 찾는 함수
	void SortedPrice();		//가격순으로 Soritng하는 함수
	void DisplayProduct();	//물품들을 출력하는 함수
	void ReserveProduct();	//물품들을 Reserver하는 함수
	~List();	//소멸자
};
/*생성자*/
List::List()
{
	head = NULL;
	tail = NULL;
	List::count = 0;
}
/*처음 위치에 삽입하는 함수*/
void List::InsertBegining(char *Name, char *Brand, int Price)
{
	Node* newNode = new Node;
	newNode->Name = new char[strlen(Name) + 1];
	strcpy(newNode->Name, Name);
	newNode->Brand = new char[strlen(Brand) + 1];
	strcpy(newNode->Brand, Brand);
	newNode->Price = Price; //새로 생성한 노드에 정보삽입

	//새로운 노드의 다음을 원래 head로 설정
	newNode->NextNode = head;
	//head가 비어있지 않다면 head와 새로운 노드를 연결
	if (head != NULL) {
		head->PrevNode = newNode;
	}
	//head를 새로운 Node로 설정
	head = newNode;
	//Count 증가
	List::count++;
	//head의 다음노드가 NULL일 경우 tail도 head를 가리킨다.
	if (head->NextNode == NULL) {
		tail = head;
	}
	//head와 tail을 연결
	head->PrevNode = tail;
	tail->NextNode = head;
}
/*마지막 위치에 삽입하는 함수*/
void List::InsertLast(char *Name, char *Brand, int Price)
{
	Node* newNode = new Node;
	newNode->Name = new char[strlen(Name) + 1];
	strcpy(newNode->Name, Name);
	newNode->Brand = new char[strlen(Brand) + 1];
	strcpy(newNode->Brand, Brand);
	newNode->Price = Price; //새로 생성한 노드에 정보삽입
	//새로운 노드의 이전노드를 테일로 설정 및 연결
	newNode->PrevNode = tail;
	//tail에 정보가 존재한다면 tail다음에 새로운 노드를 연결
	if (tail != NULL) {
		tail->NextNode = newNode;
	}
	//tail정보를 새로운 Node로 바꿔준다.
	tail = newNode;
	//카운트 증가
	List::count++;
	//tail에 이전노드가 비어있다면 head와 tail은 같은 곳을 가리킨다.
	if (tail->PrevNode == NULL) {
		head = tail;
	}
	//head와 tail정보를 수정
	head->PrevNode = tail;
	tail->NextNode = head;

}
/*해당하는 위치에 삽입하는 함수*/
void List::InsertPosition(char *Name, char *Brand, int Price, int index)
{
	Node* newNode = new Node;
	newNode->Name = new char[strlen(Name) + 1];
	strcpy(newNode->Name, Name);
	newNode->Brand = new char[strlen(Brand) + 1];
	strcpy(newNode->Brand, Brand);
	newNode->Price = Price; //새로 생성한 노드에 정보삽입
	/*Position이 처음일 경우*/
	/*InsetBeginning과 똑같이 진행하면 된다.*/
	if (index == 1) {
		
		newNode->NextNode = head;
		if (head != NULL) head->PrevNode = newNode;
		head = newNode; 
		if (head->NextNode == NULL) tail = head;
		head->PrevNode = tail;
		tail->NextNode = head;
	}
	/*Position이 마지막일 경우*/
	/*InsetLast와 똑같이 진행하면 된다.*/
	else if (index > 1 && index == count + 1) {
		
		newNode->PrevNode = tail;
		if (tail != NULL) tail->NextNode = newNode;
		tail = newNode;
		if (tail->PrevNode == NULL) head = tail;
		tail->NextNode = head;
		head->PrevNode = tail;
	}
	/*Position이 처음일 경우*/
	/*InsetBeginning과 같이 진행하면 된다.*/
	else if (index > count + 1)
	{
		cout << "현재정보보다 2개 이상 Position에는 InsertPosition이 불가능합니다." << endl;
	}
	/*Position이 중간일 경우*/
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
	//삽입된 것이기 때문에 Count증가
	List::count++;
}
/*이름으로 Node를 찾아서 삭제하는 함수*/
void List::DeleteProduct(char *Name)
{	
	Node *temp = head;
	int index;
	int overlap = 0;
	//해당 Node를 찾는 for문
	for (index = 1; index <= count; index++)
	{
		if (strcmp(temp->Name, Name) == 0) {
			overlap = 1; break;
		}
		else temp = temp->NextNode;
	}
	//이름을 찾았고, 삭제하려는 Node가 처음 위치인 경우
	//삭제하려는 Node의 전과 다음에 연결을 수정하고 delete로 메모리해제
	if (overlap == 1 && index == 1)
	{
		head = temp->NextNode;
		head->PrevNode = tail;
		cout << "**" << temp->Name << " " << "has been deleted from position " << index << "**";
		delete temp;
		List::count--;

	}
	//이름을 찾았고, 삭제하려는 Node의 위치가 마지막인 경우
	//삭제하려는 Node의 전과 다음에 연결을 수정하고 delete로 메모리해제
	else if (overlap == 1 && index > 1 && index == count)
	{
		tail = temp->PrevNode;
		tail->NextNode = head;
		cout << "**" << temp->Name << " " << "has been deleted from position " << index << "**";
		delete temp;
		List::count--;
	}
	//이름을 찾았고, 삭제하려는 Node가 중간 위치인 경우
	//삭제하려는 Node의 전과 다음에 연결을 수정하고 delete로 메모리해제
	else if (overlap == 1 && index > 1 && index < count) {
		temp->PrevNode->NextNode = temp->NextNode;
		temp->NextNode->PrevNode = temp->PrevNode;
		cout << "**" << temp->Name << " " << "has been deleted from position " << index << "**";
		delete temp;
		List::count--;
	}
	//예외처리
	else {
		cout << "삭제하려는 정보가 없습니다." << endl;
	}
	
}
/*이름으로 Node를 찾아서 정보를 변경하는 함수*/
void List::UpdateProduct(char *ChangeName, char *Name, char *Brand, int Price)
{
	Node *temp = head;
	int index;
	int overlap = 0;
	//해당 Node를 찾는 for문
	for (index = 1; index <= count; index++)
	{
		if (strcmp(temp->Name, ChangeName) == 0) {
			overlap = 1; break;
		}
		else temp = temp->NextNode;;
	}
	//Search해서 해당 Node를 찾았다면 정보를 수정해준다.
	if (overlap == 1)
	{
		temp->Name = new char[strlen(Name) + 1];
		temp->Brand = new char[strlen(Brand) + 1];
		strcpy(temp->Name, Name);
		strcpy(temp->Brand, Brand);
		temp->Price = Price;
	}
	//Search했는데 정보가 없다면 출력
	else cout << "업데이트할 정보가 없습니다." << endl;

}
/*이름으로 Node를 찾아서 정보를 출력하는 함수*/
void List::SearchProduct(char *Name)
{
	Node *temp = head;
	int index;
	int overlap = 0;
	//해당 Node를 찾는 for문//
	for (index = 1; index <= count; index++)
	{
		if (strcmp(temp->Name, Name) == 0) {
			overlap = 1; break;
		}
		else temp = temp->NextNode;
	}
	//Node를 찾았을 경우 정보들을 출력
	if (overlap == 1)
	{
		cout << "*At position: " << index << "*" << endl;
		cout << "Product name: " << temp->Name << endl;
		cout << "Product brand: " << temp->Brand << endl;
		cout << "Product price : " << temp->Price << endl;
	}
	//Node를 찾지 못했을 경우 출력
	else cout << "검색 하는 정보가 없습니다" << endl;
}
/*가격순으로 Sorting하는 함수*/
/*Node를 건드리지 않고 데이터 정보들을 수정*/
void List::SortedPrice()
{
	if (List::count == 0) {
		cout << "Sorting할 정보가 없습니다." << endl;
	}

	else {
		int index;
		//가격이 같을 경우 이름순으로 정렬하기 떄문에
		//이름순으로 먼저 정렬한다.
		for (index = 1; index < count; index++) {
			Node *temp = head;
			for (int j = 1; j < count; j++) {
				//해당 위치와 다음노드의 이름을 비교한다.
				if (strcmp(temp->Name ,temp->NextNode->Name) > 0) {
					//데이터를 수정하는 부분
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
		//이름순으로 정렬 되었기 때문에 가격순으로 정렬한다.
		for (index = 1; index < count; index++) {
				Node *temp = head;
			for (int j = 1; j < count; j++) { 
				//해당 Node와 다음 Node의 가격을 비교
				if (temp->Price > temp->NextNode->Price) {
					//데이터를 수정하는 부분
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
/*List를 출력하는 함수*/
void List::DisplayProduct()
{	
	//리스트 정보가 없는 경우
	if (count == 0) {
		cout << "정보가 없습니다." << endl;
	}
	else {
		Node* temp = head;
		//head부터 다음으로 넘기면서 List에 있는 Node 정보들을 출력
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
	//List에 하나밖에 없을 경우
	if (count < 2)
	{
		cout << "Reserve할 정보가 없거나 정보가 1개이기 때문에 Reserve하지 않아도 됩니다." << endl;
	}

	else
	{
		Node* temp = head;
		Node* temp2 = tail;
		//절반을 기준으로 head와 tail의 정보들을 바꿔준다
		//head를 1칸씩 Next하고 tail을 1칸씩 Prev하여 정보들을 바꿔준다.
		for (int i = 0; i < count / 2; i++)
		{
			char *tempName;
			char *tempBrand;
			int tempPrice;
			tempBrand = new char[strlen(temp->Brand) + 1];
			tempName = new char[strlen(temp->Name) + 1];
			//Data를 바꿔주는 부분
			strcpy(tempBrand, temp->Brand);
			strcpy(temp->Brand, temp2->Brand);
			strcpy(temp2->Brand, tempBrand);

			strcpy(tempName, temp->Name);
			strcpy(temp->Name, temp2->Name);
			strcpy(temp2->Name, tempName);

			tempPrice = temp->Price;
			temp->Price = temp2->Price;
			temp2->Price = tempPrice;

			//head는 Next
			//tail은 Prev
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

	//기능 부분을 출력
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
		//InputNumber 예외처리
		while (1)
		{	
			if (atoi(Input) != 0) break;

			else {
				cout << "Number를 숫자또는 1~10사이로 입력하세요. :";
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

			while (1)	//Pirce를 숫자로 입력받는 예외처리
			{
				if (atoi(price) != 0) break;
				else {
					cout << "price를 숫자로 다시 입력해 주세요. :";
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

			while (1)	//Pirce를 숫자로 입력받는 예외처리
			{
				if (atoi(price) != 0) break;
				else {
					cout << "price를 숫자로 다시 입력해 주세요. :";
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
					cout << "position을 숫자로 다시 입력해 주세요. :";
					cin.getline(price, sizeof(price));
				}

			}
			cout << "->Enter the product name: ";
			cin.getline(name, sizeof(name));
			cout << "->Enter the product brand: ";
			cin.getline(brand, sizeof(brand));
			cout << "->Enter the product price: ";
			cin.getline(price, sizeof(price));

			while (1)	//Pirce를 숫자로 입력받는 예외처리
			{
				if (atoi(price) != 0) break;
				else {
					cout << "price를 숫자로 다시 입력해 주세요. :";
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


			while (1)	//Pirce를 숫자로 입력받는 예외처리
			{
				if (atoi(price) != 0) break;
				else {
					cout << "price를 숫자로 다시 입력해 주세요. : ";
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