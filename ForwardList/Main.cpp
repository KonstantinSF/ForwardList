//ForwardList
#include<iostream>
#include<ctime>
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
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Element()
	{
		count--; //������� ���-�� ��������� ���� ��� �������� �����������
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

	}
	friend class ForwardList;
	friend class Iterator; 
	friend ForwardList operator+ (const ForwardList& left, const ForwardList& right); 
};
unsigned int Element::count = 0; //������������� ������ ���������� ������ �� ��������� ������!!!

class Iterator
{
	Element* Temp; 
public:
	Iterator(Element* Temp) : Temp(Temp)
	{
		cout << "ITConstructor:\t" << this << endl; 
	}
	~Iterator()
	{
		cout << "ITDestructor:\t" << this<< endl; 
	}
	Iterator& operator ++ ()
	{
		Temp = Temp->pNext; 
		return *this; 
	}
	bool operator == (const Iterator& other) const
	{
		return this->Temp == other.Temp; 
	}
	bool operator != (const Iterator& other) const
	{
		return this->Temp != other.Temp;
	}
	const int& operator *() const//���������� ��������� �������������
	{
		return Temp->Data; 
	}
	int& operator *() 
	{
		return Temp->Data;
	}
};

class ForwardList
{
	Element* Head;	//��������� �� ��������� ������� ������
	//������ �������� ������ ����� � ������
	unsigned int size; 
public:
	Iterator begin()
	{
		return Head; 
	}
	Iterator end()
	{
		return nullptr; 
	}

	ForwardList() :Head(nullptr), size(0)
	{
		//����������� �� ��������� ������� ������ ������.
		//���� ������ ��������� �� 0, �� ������ ����
#ifdef DEBUG
		cout << "LConstructor:\t" << this << endl;
#endif // DEBUG

	}
	/// CopyConstructor:///////
	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		cout << typeid(il.begin()).name() << endl; 
		for (int const* it = il.begin(); it != il.end(); it++)//it - ��� ��������
		{
			push_back(*it); 
		}
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other; //�� ������������ ����������� �������� �������� ������������
#ifdef DEBUG
		cout << "CopyConstructor:\t" << endl;
#endif // DEBUG

	}
	ForwardList(const ForwardList&& other) : ForwardList()
	{
		*this = std::move(other); //�-�� std::move �������� MoveAssignment
#ifdef DEBUG
		cout << "MoveConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~ForwardList()
	{
		while (Head) pop_front();
#ifdef DEBUG
		cout << "LDestructor:\t" << this << endl;
#endif // DEBUG

	}
	//////////////Operators: ////////////////
	ForwardList& operator = (const ForwardList& other)
	{
		if (this == &other)return *this; 
		while (Head) pop_front(); //������� ������ ������, ���� ������
		//deep copy
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data); 
		reverse();
		cout << "CopyAssignment:\t " <<this<< endl; 
		return *this; 
	}
	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other) return *this; 
		while (Head)pop_front();
		//Shallow copy:
		this->Head = other.Head; 
		this->size = other.size; 
		other.Head = nullptr; 
		other.size = 0; 
		cout << "MoveAssignment:\t" << this << endl; 
		return *this; 
	}
	//				Adding Elements:
	void push_front(int Data)//��������� ������� � ������ ������
	{
		////1) ������� ����� �������:
		//Element* New = new Element(Data);//��� �������� ��������� � ������� ������
		////2) �������������� ����� ������� � ������ ������:
		//New->pNext = Head;
		////3) ��������� ������ �� ����� �������:
		//Head = New;
		Head = new Element(Data, Head);
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
		if (Index == 0) return pop_front();
		if (Index > size)
		{
			cout << "Error: out of range. " << endl;
		}
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;
		Element* Erased = Temp->pNext;//������� erased ���������� �� ������ Temp->pNext; 
		Temp->pNext = Erased->pNext; //����� ���� ������ �� ���������
		delete Erased;
		size--;
	}
	void insert(int Index, int Data)
	{
		if (Index == 0) return push_front(Data); 
		//1. ������� ����� �������
		//Element* New = new Element(Data); 
		Element* Temp = Head; //������� ��������

		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;//2. ������� �� ������� ��������
		if (Temp->pNext)Temp = Temp->pNext; 
		//3. �������� ����� ������� � ������
		//New->pNext = Temp->pNext;//������ � ����� ��������
		//Temp->pNext=New; //��� ������
		Temp->pNext = new Element(Data, Temp->pNext); //������ ���� ��� ������ ������������
		size++;
	}
	//				Methods:
	void print()const
	{
		cout << "Head:\t" << Head << endl; 
		//Element* Temp = Head;	//Temp - ��� ��������.
		//�������� - ��� ���������, ��� ������ �������� 
		//����� �������� ������ � ��������� ��������� ������.
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext;	//������� �� ��������� �������
		//}
		for (Element*Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "���-�� ��������� ������:\t " << size << endl; 
		cout << "����� ���-�� ���������: " << Element::count << endl; 
	}
	void reverse()
	{
		ForwardList reverse; 
		while(Head)
		{
			reverse.push_front(Head->Data);//������ ������ ������� � ������, ��� ����������
			pop_front();//�� ����� ������ ������� � ������ 
		}
		this->Head = reverse.Head; 
		this->size = reverse.size; 
		reverse.Head = nullptr; 
	}
	friend ForwardList operator+ (const ForwardList& left, const ForwardList& right); 
};
ForwardList operator+ (const ForwardList& left, const ForwardList& right)
{
	
	ForwardList cat = left; //copyConstractor
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext) cat.push_back(Temp->Data); 
	return cat; 
}
//#define COUNT_CHECK
//#define RANGE_BASE_FOR_ARRAY
#define RANGE_BASE_FOR_LIST
//#define PREFORMANCE_CHECK
void main()
{
	setlocale(LC_ALL, "");
	//int n;
	//cout << "������� ������ ������: "; cin >> n;
	//ForwardList list;//������� ������ ����
	//for (int i = 0; i < n; i++)
	//{
	//	list.push_back(rand() % 100);
	//}
	//list.print();
	/*int index; 
	int value; 
	cout << "enter index erasing element: "; cin >> index; 
	cout << "enter meaning: "; cin >> value; 
	list.insert(index, value); 
	list.print(); */
	/*list.erase(index); 
	list.print(); */
	/*list.pop_back(); 
	list.print(); */
	/*list.reverse(); 
	list.print();*/

#ifdef COUNT_CHECK

	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);

	list1.print();
	list2.print();

	ForwardList list3 = list1 + list2;
	list3.print();

#endif // COUNT_CHECK
#ifdef RANGE_BASE_FOR_ARRAY
	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;
	for (int i : arr)
	{
		cout << i << "\t";
	}
	cout << endl;
#endif // RANGE_BASE_FOR_ARRAY
#ifdef RANGE_BASE_FOR_LIST
	ForwardList list = { 3,5,8,13,21 };
	list.print(); 
	for (int i : list)
	{
		cout << i << "\t"; 
	}
	cout << endl; 
#endif // RANGE_BASE_FOR_LIST
#ifdef PREFORMANCE_CHECK
	int n;
	cout << "������� ������ ������: "; cin >> n;
	ForwardList list;//������� ������ ����
	cout << "List created, loading data..." << endl;
	time_t start = time(NULL); //������� ������� ����� � ���
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	time_t end = time(NULL);
	cout << "Data load complete" << endl;
	cout << "Spend time: " << end - start << endl;
	list.print();
	cout << "Start copying" << endl;
	start = time(NULL);
	ForwardList list2 = list;
	cout << "End copying" << endl;
	end = time(NULL);
	cout << "Spend time: " << end - start << endl;
	list2.print();
#endif // PREFORMANCE_CHECK

}