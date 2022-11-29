//ForwardList
#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;		//�������� ��������
	Element* pNext;	//����� ���������� ��������
	static unsigned int count; //���-�� ���������
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++; //������� ���-�� ���������
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--; //������� ���-�� ��������� ���� ��� �������� �����������
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};
unsigned int Element::count = 0; //������������� ������ ���������� ������ �� ��������� ������!!!

class ForwardList
{
	Element* Head;	//��������� �� ��������� ������� ������
	//������ �������� ������ ����� � ������
	unsigned int size; 
public:
	ForwardList() :Head(nullptr), size(0)
	{
		//����������� �� ��������� ������� ������ ������.
		//���� ������ ��������� �� 0, �� ������ ����
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//				Adding Elements:
	void push_front(int Data)//��������� ������� � ������ ������
	{
		//1) ������� ����� �������:
		Element* New = new Element(Data);//��� �������� ��������� � ������� ������
		//2) �������������� ����� ������� � ������ ������:
		New->pNext = Head;
		//3) ��������� ������ �� ����� �������:
		Head = New;
		size++; 
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data); 
		Element* New = new Element(Data); //������� ����� �������
		Element* Temp = Head; //������� ��������, ������� �� ������ �������� ������ pNext=nullptr; 
		while (Temp->pNext)Temp = Temp->pNext; //������ �������� ��������� �� ������ ������� 
		Temp->pNext = New; 
		size++;
	}
	//////Removing elements
	void pop_front()
	{
	//1. ��������� ����� ���������� ��������
		Element* erased = Head; 
		//2. ������ ������� �� ������
		Head = Head->pNext; 
		//3. ������� ������� �� ������
		delete erased; 
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr) return; 
		if (Head->pNext == nullptr) return pop_front(); 
		//1. ������� �� �������������� �������� ������, ����� ����� � ���� �����
		Element* Temp = Head; 
		while (Temp->pNext->pNext) Temp = Temp->pNext; 
		//2. ���� ������ ������� �� ������
		delete Temp->pNext; 
		//3.�������� ��������� �� ���� �������
		Temp->pNext = nullptr; 
		size--;
	}
	void erase(int Index)
	{
		Element* Temp = Head; 
		for (int i = 0; i < Index-1; i++) Temp = Temp->pNext;
		//if (Temp->pNext)Temp = Temp->pNext;
		Element* Erased = Temp->pNext->pNext; 
		Temp->pNext = Erased; 
		delete Erased; 
		size--; 
	}
	void insert(int Index, int Data)
	{
		if (Index == 0) return push_front(Data); 
		//1. ������� ����� �������
		Element* New = new Element(Data); 
		Element* Temp = Head; //������� ��������

		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;//2. ������� �� ������� ��������
		if (Temp->pNext)Temp = Temp->pNext; 
		//3. �������� ����� ������� � ������
		New->pNext = Temp->pNext;//������ � ����� ��������
		Temp->pNext=New; //��� ������
		size++;
	}
	//				Methods:
	void print()const
	{
		Element* Temp = Head;	//Temp - ��� ��������.
		//�������� - ��� ���������, ��� ������ �������� 
		//����� �������� ������ � ��������� ��������� ������.
		cout << "Head:\t" << Head << endl; 
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//������� �� ��������� �������
		}
		cout << "���-�� ��������� ������:\t " << size << endl; 
		cout << "����� ���-�� ���������: " << Element::count << endl; 
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "������� ������ ������: "; cin >> n;
	ForwardList list;//������� ������ ����
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	int index; 
	int value; 
	cout << "enter index erasing element: "; cin >> index; 
	//cout << "enter meaning: "; cin >> value; 
	/*list.insert(index, value); 
	list.print();*/ 
	list.erase(index); 
	list.print(); 
	/*list.pop_back(); 
	list.print(); */
	/*list.push_back(123); 
	list.print();*/
}