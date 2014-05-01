#include <iostream>
#include <vector>
using namespace std;

class Element      /// Класс узла дерева
{
public:
	Element();
	Element(int value);

public:
	int               data;
	Element*          parent;
	vector<Element*>  childVector;  ///Массив "детей" узла дерева

};
Element::Element()
{
	data = 0;
	parent = nullptr;
}

Element::Element(int value)
{
	data = value;
}



class Tree          /// Класс "дерево"
{
public:
	Tree();
	~Tree();
	void     Add_Element(int Number, int Value);  /// Метод добавления узла к дереву	
	void     Print_Tree()   const;
	int      Get_Data(int Number) const;

private:
	void     Print_Direct(Element* El) const;
	void     Print_Reverse(Element* El) const;
	void     Print_Symmetrical(Element* El) const;
	void     Delete_Tree(Element* El);
	Element* Find_Element(Element* El, int Number) const;

private:
	Element* Root;  /// указатель на корень дерева
};

//! Реализация методов Класса "Дерево"

Tree::Tree()
{
	Root = new Element;
}


Element* Tree::Find_Element(Element* El, int Number) const
{
	Element* temp = nullptr;
	if (Number)
		Number--;
	if (!Number) return El;
	else
	{
		for (int itr = 0; itr < El->childVector.size(); itr++)
		{
			if (temp) break;
			temp = Find_Element(El->childVector[itr], Number);
		}
	}
	return temp;
}

void Tree::Add_Element(int Number, int Value)
{
	if (Number < 0) return;
	if (!Number) Root->data = Value;
	else
	{
		Element* leaf = new Element(Value);

		leaf->parent = Find_Element(Root, Number);
		leaf->parent->childVector.push_back(leaf);
	}
	return;
}

int Tree::Get_Data(int Number) const
{
	Element* leaf = Find_Element(Root, Number);
	return leaf->data;
}

void Tree::Print_Direct(Element* El) const
{
	cout << El->data << endl;
	for (int itr = 0; itr < El->childVector.size(); itr++)
	{
		Print_Direct(El->childVector[itr]);
	}
	return;
}

void Tree::Print_Reverse(Element* El) const
{
	for (int itr = 0; itr < El->childVector.size(); itr++)
	{
		Print_Reverse(El->childVector[itr]);
	}
	cout << El->data << endl;
	return;
}

void Tree::Print_Symmetrical(Element* El) const
{

	for (int itr = 0; itr < El->childVector.size(); itr++)
	{
		Print_Symmetrical(El->childVector[itr]);
		if (!itr)
			cout << El->data << endl;
	}
	if (!(El->childVector.size()))
		cout << El->data << endl;
	return;
}
void Tree::Print_Tree() const
{
	cout << "---------Direct  Bypass-----------" << endl;
	Print_Direct(Root);
	cout << "---------Reverse  Bypass-----------" << endl;
	Print_Reverse(Root);
	cout << "---------Symmetrical  Bypass-----------" << endl;
	Print_Symmetrical(Root);
	return;
}

void Tree::Delete_Tree(Element* El)
{
	for (int itr = 0; itr < El->childVector.size(); itr++)
	{
		Delete_Tree(El->childVector[itr]);
		delete El->childVector[itr];
	}
	return;
}

Tree::~Tree()
{
	Delete_Tree(Root);
	delete Root;
}


int main()
{
	Tree treee;    //! Объект класса "дерево"
	unsigned int Number, ElNum;
	int Value;
	cout << "Enter number of points: ";
	cin >> ElNum;
	for (int itr = 0; itr < ElNum; itr++)
	{
		cin >> Number >> Value;
		treee.Add_Element(Number, Value);
	}

	treee.Print_Tree();  //! вывод дерева на экран
	system("pause");
	return 0;
}