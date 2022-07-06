#include "LinkedList.h"
#include <iostream>
#include <string>
using namespace std;

LinkedList::LinkedList() : mySize(0), first(nullptr), last(nullptr)
{
}

LinkedList &LinkedList::operator=(const LinkedList &oriList)
{
	//清空链表
	removeAll();

	//开始拷贝链表
	this->mySize = oriList.mySize;
	if (oriList.mySize == 0)
	{
		this->first = nullptr;
		this->last = nullptr;
	}
	else
	{
		this->first = new Node(oriList.first->data);
		NodePtr current = this->first;
		NodePtr currentOri = oriList.first;

		while (currentOri->next != nullptr)
		{
			current->next = new Node(currentOri->next->data);
			current = current->next;
			currentOri = currentOri->next;
		}

		this->last = current;
	}

	return *this;
}

LinkedList::~LinkedList()
{
	removeAll();
}

void LinkedList::add(int index, ElementType dataVal)
{
	if (index > mySize)
	{
		cerr << "index (" << index << ") is larger than list size (" << mySize << ") !" << endl;
	}
	else
	{
		NodePtr newNode = new Node(dataVal);
		if (index == 0)
		{
			newNode->next = first;
			first = newNode;
		}
		else
		{
			NodePtr current = first;
			int cnt = 0;
			while (cnt < mySize - 1)
			{
				current = current->next;
				cnt++;
			}
			newNode->next = current->next;
			current->next = newNode;

			//恰好成了最后一个元素
			if (last->next == nullptr)
			{
				last = last->next;
			}
		}
		mySize++;
	}
}

void LinkedList::add(ElementType dataVal)
{
	NodePtr newNode = new Node(dataVal);
	if (first == nullptr)
	{
		first = newNode;
		last = newNode;
	}
	else
	{
		last->next = newNode;
		last = newNode;
	}
	mySize++;
}

ElementType LinkedList::get(int index) const
{
	if (index > mySize - 1)
	{
		cerr << "index (" << index << ") is larger than last index (" << mySize - 1 << ") !" << endl;
		return 0;
	}
	else
	{
		int cnt = 0;
		NodePtr current = first;
		while (cnt < index)
		{
			current = current->next;
			cnt++;
		}

		return current->data;
	}
}

ElementType LinkedList::getLast() const
{
	return first->data;
}

ElementType LinkedList::getFirst() const
{
	return last->data;
}

int LinkedList::getSize() const
{
	return mySize;
}

void LinkedList::remove(int index)
{
	if (index > mySize - 1)
	{
		cerr << "index (" << index << ") is larger than last index (" << mySize - 1 << ") !" << endl;
	}
	else
	{
		NodePtr delNode = nullptr;
		if (index == 0)
		{
			//只有一个元素
			if (first->next == nullptr)
			{
				delNode = first;
				first = nullptr;
				last = nullptr;
			}
			//不止一个元素
			else
			{
				delNode = first;
				first = first->next;
			}
		}
		else
		{
			NodePtr current = first;
			int cnt = 0;
			while (cnt < index - 1)
			{
				current = current->next;
				cnt++;
			}
			delNode = current->next;
			current->next = current->next->next;

			//删的恰好是最后一个元素
			if (delNode->next == nullptr)
			{
				last = current;
			}
		}
		delete delNode;
		mySize--;
	}
}

void LinkedList::removeAll()
{
	if (first != nullptr)
	{
		NodePtr delPtr = first;
		NodePtr current = delPtr->next;
		while (delPtr->next != nullptr)
		{
			delete delPtr;
			delPtr = current;
			current = current->next;
		}
		delete delPtr;

		first = nullptr;
		last = nullptr;
	}
}

void LinkedList::display(std::ostream &os, const char *seperator = "\t") const
{
	if (first == nullptr)
	{
		os << "Empty List." << seperator;
	}
	else
	{
		int cnt = 0;
		NodePtr current = first;
		while (cnt < mySize)
		{
			os << *current << seperator;
			current = current->next;
			cnt++;
		}
		os << endl;
	}
}

void LinkedList::set(int index, int dataVal)
{
	if (index > mySize - 1)
	{
		cerr << "index (" << index << ") is larger than last index (" << mySize - 1 << ") !" << endl;
	}
	else
	{
		int cnt = 0;
		NodePtr current = first;
		while (cnt < index)
		{
			cnt++;
			current = current->next;
		}
		current->data = dataVal;
	}
}

void LinkedList::reverse()
{
	if (mySize < 2)
	{
		// 只有一个元素或者空列表就啥都不做
	}
	else if (mySize == 2)
	{
		last->next = first;
		first = last;
		last = last->next;
	}
	else if (mySize > 2)
	{
		NodePtr n1, n2, n3;
		n1 = first;
		n2 = first->next;
		n3 = first->next->next;
		first->next = nullptr;
		last = first;

		// 总共n个元素，爬n-2次。在循环中，只把n2的后继挂接到n1上。最后退出循环的时候，n1指向倒数第二个元素，n2指向倒数第一个元素，在循环外将n2挂接到n1,可防止n3去寻找空指针的后继。

		int cnt = 0;
		while (cnt < mySize - 2)
		{
			cnt++;
			n2->next = n1;

			n1 = n2;
			n2 = n3;
			n3 = n3->next;
		}
		n2->next = n1;
		first = n2;
	}
}

std::ostream &operator<<(std::ostream &os, const Node &oriNode)
{
	// Node中存储的数据元素类型需要重载一下<<运算符，要不然输出的会是指针指向的地址
	os << oriNode.data;
	return os;
}

std::ostream &operator<<(std::ostream &os, const LinkedList &oriList)
{
	oriList.display(os);
	return os;
}
