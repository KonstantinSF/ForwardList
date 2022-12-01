//ForwardList
#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;		//Значение элемента
	Element* pNext;	//Адрес следующего элемента
	static unsigned int count; //кол-во элементов
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++; //считаем кол-во элементов
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--; //считаем кол-во элементов если оно меняется уменьшается
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
	friend ForwardList operator+ (const ForwardList& left, const ForwardList& right); 
};
unsigned int Element::count = 0; //инициализация статич переменной только за пределами класса!!!

class ForwardList
{
	Element* Head;	//Указатель на начальный элемент списка
	//Голова является точкой входа в список
	unsigned int size; 
public:
	ForwardList() :Head(nullptr), size(0)
	{
		//Конструктор по умолчанию создает пустой список.
		//Если Голова указывает на 0, то список пуст
		cout << "LConstructor:\t" << this << endl;
	}
	/// CopyConstructor:///////
	
	ForwardList(const ForwardList& other) :ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other; //из конструктора копирования вызываем оператор присваивания
		cout << "CopyConstructor:\t" << endl; 
	}
	ForwardList(const ForwardList&& other) : ForwardList()
	{
		*this = std::move(other); //Ф-ия std::move вызывает MoveAssignment
		cout << "MoveConstructor:\t" <<this<< endl; 
	}
	~ForwardList()
	{
		while (Head) pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	//////////////Operators: ////////////////
	ForwardList& operator = (const ForwardList& other)
	{
		if (this == &other)return *this; 
		while (Head) pop_front(); //удаляем старый список, этот список
		//deep copy
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data); 
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
	void push_front(int Data)//добавляет элемент в начало списка
	{
		////1) Создаем новый элемент:
		//Element* New = new Element(Data);//все элементы находятся в динамич памяти
		////2) Пристыковываем новый элемент к началу списка:
		//New->pNext = Head;
		////3) Переводим Голову на новый элемент:
		//Head = New;
		Head = new Element(Data, Head);
		size++; 
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data); 
		Element* New = new Element(Data); //создаем новый элемент
		Element* Temp = Head; //создаем итератор, доходим до послед элемента списка pNext=nullptr; 
		while (Temp->pNext)Temp = Temp->pNext; //теперь итератор указывает на послед элемент 
		Temp->pNext = New; 
		size++;
	}
	//////Removing elements
	void pop_front()
	{
	//1. Сохраняем адрес удаляемого элемента
		Element* erased = Head; 
		//2. Исключ элемент из списка
		Head = Head->pNext; 
		//3. Удаляем элемент из памяти
		delete erased; 
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr) return; 
		if (Head->pNext == nullptr) return pop_front(); 
		//1. Доходим до предпоследнего элемента списка, чтобы взять с него адрес
		Element* Temp = Head; 
		while (Temp->pNext->pNext) Temp = Temp->pNext; 
		//2. Удал послед элемент из памяти
		delete Temp->pNext; 
		//3.Зануяемь указатель на след элемент
		Temp->pNext = nullptr; 
		size--;
	}
	void erase(int Index)
	{
		Element* Temp = Head; 
		for (int i = 0; i < Index-1; i++) Temp = Temp->pNext;
		Element* Erased = Temp->pNext; 
		Temp->pNext = Erased->pNext; 
		delete Erased; 
		size--; 
	}
	void insert(int Index, int Data)
	{
		if (Index == 0) return push_front(Data); 
		//1. Создаем новый элемент
		//Element* New = new Element(Data); 
		Element* Temp = Head; //создаем итератор

		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;//2. доходим до нужного элемента
		if (Temp->pNext)Temp = Temp->pNext; 
		//3. включаем новый элемент в список
		//New->pNext = Temp->pNext;//ссылка в новом элементе
		//Temp->pNext=New; //это голова
		Temp->pNext = new Element(Data, Temp->pNext); //делаем тоже при помощи конструктора
		size++;
	}
	//				Methods:
	void print()const
	{
		cout << "Head:\t" << Head << endl; 
		//Element* Temp = Head;	//Temp - это итератор.
		//Итератор - это указатель, при помощи которого 
		//можно получить доступ к элементам структуры данных.
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext;	//Переход на следующий элемент
		//}
		for (Element*Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "кол-во элементов списка:\t " << size << endl; 
		cout << "общее кол-во элементов: " << Element::count << endl; 
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
void main()
{
	setlocale(LC_ALL, "");
	//int n;
	//cout << "Введите размер списка: "; cin >> n;
	//ForwardList list;//создали объект Лист
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
	/*list.push_back(123); 
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
	for (int i : list)
	{
		cout << i << "\t"; 
	}
	cout << endl; 
#endif // RANGE_BASE_FOR_LIST

}