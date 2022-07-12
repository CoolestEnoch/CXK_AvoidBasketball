#ifndef __LinkedList_H__
#define __LinkedList_H__

#include <iostream>
#include <string>

typedef int ElementType;

class Node
{
public:
	ElementType data;
	Node *next;

	Node(ElementType value)
	{
		data = value;
		next = nullptr;
	}
};

std::ostream &operator<<(std::ostream &os, const Node &oriNode);

class LinkedList
{
private:
	typedef Node *NodePtr;

	int mySize;

	NodePtr first;
	NodePtr last;

public:
	LinkedList();
	LinkedList &operator=(const LinkedList &oriList);
	~LinkedList();

	// 数据操作函数
	void add(ElementType dataVal);
	void add(int index, ElementType dataVal);
	ElementType get(int index) const;
	ElementType getLast() const;
	ElementType getFirst() const;
	int getSize() const;
	void remove(int index);
	void removeAll();
	void display(std::ostream &os, const char* seperator) const;//等效<<运算符
	void set(int index, ElementType dataVal);
	void reverse();
};

std::ostream &operator<<(std::ostream &os, const LinkedList &oriList);

#endif
