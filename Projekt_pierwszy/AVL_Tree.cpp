#include<iostream>
#include "Draft.h"
#include <Windows.h>
#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;



int main()
{
	checkRemove();
	srand(time(NULL));
	int numberOfElements = 1000000;
	AVL_Tree test;
	DWORD start = GetTickCount();
	for (int i = 0; i < numberOfElements; i++)
	{
		test.insert(rand());
	} 
	DWORD stop = GetTickCount();
	cout << "Time for insert "<<numberOfElements<<" to the tree " << (long(stop) - long(start)) << " miliseconds."<<endl;
	
	DWORD startremove = GetTickCount();
	for (int i = 0; i < numberOfElements; i++)
	{
		test.remove(rand());
	}
	DWORD stopremove = GetTickCount();
	cout << "Time for remove " << numberOfElements << " from the tree " << (long(stopremove) - long(startremove)) << " miliseconds.";
	int waiter;

	cout << endl << endl;
	tenThousands_to_x_element_Tree(10000000);
	cin >> waiter;

}


