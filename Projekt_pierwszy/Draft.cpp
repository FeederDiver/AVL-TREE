#include<iostream>
#include "Draft.h"
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <Windows.h>
using namespace std;

void AVL_Tree::makeEmpty(Node* localNode)
{
	if (localNode == NULL) return;
	else
	{
		makeEmpty(localNode->get_right());
		makeEmpty(localNode->get_left());
		delete localNode;
	}

}

Node* AVL_Tree::insert(int value, Node* localNode)
{
	if (localNode == NULL)
	{
		localNode = new Node;
		localNode->set_value(value);
		localNode->set_right(NULL);
		localNode->set_left(NULL);
		localNode->set_height(0);
	}
	else if (value < localNode->get_value())
	{
		localNode->set_left(insert(value, localNode->get_left()));
		if (currentNodeHeight(localNode->get_left()) - currentNodeHeight(localNode->get_right()) == 2)
		{
			if (value < localNode->get_left()->get_value())
				localNode = rightRotate(localNode);
			else
				localNode = leftRightRotate(localNode);
		}
	}
	else if (value > localNode->get_value())
	{
		localNode->set_right(insert(value, localNode->get_right()));
		if (currentNodeHeight(localNode->get_right()) - currentNodeHeight(localNode->get_left()) == 2)
		{
			if (value > localNode->get_right()->get_value())
				localNode = leftRotate(localNode);
			else
				localNode = rightLeftRotate(localNode);
		}
	}
	localNode->set_height(1 + fmax(currentNodeHeight(localNode->get_left()), currentNodeHeight(localNode->get_right())));
	return localNode;

}
Node* AVL_Tree::rightRotate(Node* localNode)
{

	Node* temproraryNode= localNode->get_left();
	if (temproraryNode == NULL) 
	{
		localNode = leftRotate(localNode);
		temproraryNode = localNode->get_left();
	}
	localNode->set_left(temproraryNode->get_right());
	localNode->set_height(fmax(currentNodeHeight(localNode->get_right()), currentNodeHeight(localNode->get_left())) + 1);
	temproraryNode->set_right(localNode);
	temproraryNode->set_height(fmax(currentNodeHeight(temproraryNode->get_right()), currentNodeHeight(temproraryNode->get_left())) + 1);
	return temproraryNode;
}

Node* AVL_Tree::leftRotate(Node* localNode)
{
	Node* temproraryNode = localNode->get_right();
	if (temproraryNode == NULL)
	{
		localNode = rightRotate(localNode);
		temproraryNode = localNode->get_right();
	}
	localNode->set_right(temproraryNode->get_left());
	localNode->set_height(fmax(currentNodeHeight(localNode->get_right()), currentNodeHeight(localNode->get_left())) + 1);
	temproraryNode->set_left(localNode);
	temproraryNode->set_height(fmax(currentNodeHeight(temproraryNode->get_right()), currentNodeHeight(temproraryNode->get_left())) + 1);
	return temproraryNode;
}

Node* AVL_Tree::rightLeftRotate(Node* localNode)
{
	localNode->set_right(rightRotate(localNode->get_right()));
	localNode = leftRotate(localNode);
	return localNode;
}

Node* AVL_Tree::leftRightRotate(Node* localNode)
{
	localNode->set_left(leftRotate(localNode->get_left()));
	localNode = rightRotate(localNode);
	return localNode;
}

int AVL_Tree::currentNodeHeight(Node* localNode)
{
	return (localNode == NULL ? -1 : localNode->get_height());
}

void AVL_Tree::privInOrder(Node* localNode)
{
	if (localNode == NULL)
		return;
	else
	{
		privInOrder(localNode->get_left());
		cout << localNode->get_value() << " ";
		privInOrder(localNode->get_right());
	}
}

void AVL_Tree::privPreOrder(Node* localNode)
{
	if (localNode == NULL)
		return;
	else
	{
		cout << localNode->get_value() << " ";
		privPreOrder(localNode->get_left());
		privPreOrder(localNode->get_right());
	}
}

void AVL_Tree::privPostOrder(Node* localNode)
{
	if (localNode == NULL)
		return;
	else
	{
		privPostOrder(localNode->get_left());
		privPostOrder(localNode->get_right());
		cout << localNode->get_value() << " ";
	}
}


Node* AVL_Tree::remove(int value, Node* localNode)
{
	Node* temproraryNode;
	if (localNode == NULL) return NULL;
	else if (value < localNode->get_value()) localNode->set_left(remove(value, localNode->get_left()));
	else if (value > localNode->get_value()) localNode->set_right(remove(value, localNode->get_right()));
	// When we have 2 children of removed node we need to remove ( rewrite ) one of it: 
	else if (localNode->get_right() && localNode->get_left())
	{
		if (currentNodeHeight(localNode->get_right()) - currentNodeHeight(localNode->get_left())>0)
		{
			temproraryNode = getMin(localNode->get_right());
			localNode->set_value(temproraryNode->get_value());
			localNode->set_right(remove(localNode->get_value(), localNode->get_right()));
		}
		else
		{
			temproraryNode = getMax(localNode->get_left());
			localNode->set_value(temproraryNode->get_value());
			localNode->set_left(remove(localNode->get_value(), localNode->get_left()));
		}
	}
	//Otherwise, or after that we can use the 'basic' version:
	else
	{
		if (localNode->get_left() == NULL)
			localNode = localNode->get_right();
		else if (localNode->get_right() == NULL)
			localNode = localNode->get_left();
	}
	if (localNode == NULL)
		return localNode;
	localNode->set_height(fmax(currentNodeHeight(localNode->get_left()), currentNodeHeight(localNode->get_right())) + 1);
	if (currentNodeHeight(localNode->get_left()) - currentNodeHeight(localNode->get_right()) == 2)
	{
		if (currentNodeHeight(localNode->get_left()->get_left()) -
			currentNodeHeight(localNode->get_left()->get_right()) == 1)
			localNode = rightRotate(localNode);
		else
			localNode = leftRightRotate(localNode);
	}
	else if (currentNodeHeight(localNode->get_right()) - currentNodeHeight(localNode->get_left()) == 2)
	{
		if (currentNodeHeight(localNode->get_right()->get_right()) -
			currentNodeHeight(localNode->get_right()->get_left()) == 1)
			localNode = leftRotate(localNode);
		else
		{
			localNode = rightLeftRotate(localNode);
		}
	}
	localNode->set_right(checkBalance(localNode->get_right()));
	localNode->set_left(checkBalance(localNode->get_left()));
	localNode->set_height(fmax(currentNodeHeight(localNode->get_left()), currentNodeHeight(localNode->get_right())) + 1);
	return localNode;
}

Node* AVL_Tree::getMin(Node* localNode)
{
	if (localNode == NULL)
		return NULL;
	else if (localNode->get_left() == NULL)
		return localNode;
	else
		return getMin(localNode->get_left());
}

Node* AVL_Tree::getMax(Node* localNode)
{
	if (localNode == NULL)
		return NULL;
	else if (localNode->get_right() == NULL)
		return localNode;
	else
		return getMin(localNode->get_right());
}

Node* AVL_Tree::checkBalance(Node* localNode)
{
	if (localNode != NULL && localNode->get_left() != NULL)
	{
		if (currentNodeHeight(localNode->get_left()) - currentNodeHeight(localNode->get_right()) == 2)
		{
			if (currentNodeHeight(localNode->get_left()->get_left()) -
				currentNodeHeight(localNode->get_left()->get_right()) == 1)
				localNode = rightRotate(localNode);
			else
				localNode = leftRightRotate(localNode);
		}
	}
	else if (localNode != NULL && localNode->get_right() != NULL)
	{
		if (currentNodeHeight(localNode->get_right()) - currentNodeHeight(localNode->get_left()) == 2)
		{
			if (currentNodeHeight(localNode->get_right()->get_right()) -
				currentNodeHeight(localNode->get_right()->get_left()) == 1)
				localNode = leftRotate(localNode);
			else
				localNode = rightLeftRotate(localNode);
		}
	}
	return localNode;
}



void checkRemove()
{
	AVL_Tree test;
	test.insert(53);
	test.insert(41);
	test.insert(140);
	test.insert(123);
	test.insert(142);
	test.insert(28);
	test.insert(58);
	test.insert(148);
	test.remove(28);
	test.remove(41);
	test.remove(53);
}

void tenThousands_to_x_element_Tree(int x)
{
	AVL_Tree test;
	for (int i = 0; i < x; i++)
	{
		test.insert(rand());
	}
	DWORD start = GetTickCount();
	for (int i = x; i < x + 10000; i++)
	{

		test.insert(i);
	}
	DWORD stop = GetTickCount();
	cout << "Time for insert 100 000 elements to " << x << " element Tree " << (long(stop) - long(start)) << " miliseconds." << endl;

	DWORD startremove = GetTickCount();
	for (int i = 0; i < 10000; i++)
	{
		test.remove(rand());
	}
	DWORD stopremove = GetTickCount();
	cout << "Time for insert 100 000 elements to " << x << " element Tree " << (long(stopremove) - long(startremove)) << " miliseconds." << endl;
	int waiter;
	cin >> waiter;
}
