#include <iostream>
using namespace std;

template<typename T>
class Ptr {
private:
	T* p_Data;
	int* p_refCount;

public:
	Ptr() : p_Data(NULL), refCount(0) {};
	static Ptr Create() {
		
		int refCount = 0;
		cout << "ref cnt: " << refCount << " -> ";
		refCount = refCount + 1;
		cout << refCount << endl;
		return new Ptr(T, refCount);
	}
	Ptr<T>& operator = (const Ptr<T>& other) {
		if (this != &other) {
			if (reference->Release() == 0) {
				delete pointer;
				delete reference;
			}

			pointer = other.pointer;
			reference = other.reference;
			reference->AddRef();
		}
		return *this;
	}
	Ptr* operator -> () { return &p_Data; }
	~Ptr() { 
		while(1){
			if (p_refCount == 0) break;
			cout << "ref cnt: " << p_refCount << " -> ";
			delete p_Data;
			p_refCount--;
			cout << p_refCount << endl;
		}
		cout << "Deallocate the instance." << endl;
	}

};
class MyClass
{
private:
	int m_num;
	
public:
	MyClass() : m_num(0) {}
	void PrintNum(const char* name)
	{
		cout << name << ": " << m_num++ << endl;
	}

};

int main(void)
{
	Ptr<MyClass>::Create();
	Ptr<MyClass> mc1 = Ptr<MyClass>::Create();
	Ptr<MyClass> mc2 = Ptr<MyClass>::Create();
	mc1->PrintNum("mc1");
	mc1->PrintNum("mc1");
	mc1 = mc2;

	Ptr<MyClass> temp;
	temp = mc2;
	temp->PrintNum("mc2");
	{
		Ptr<MyClass> temp2 = mc2;
		temp2->PrintNum("mc2");
	}
	{
		Ptr<MyClass> temp2 = mc2;
		temp2->PrintNum("mc2");
	}

	return 0;
}