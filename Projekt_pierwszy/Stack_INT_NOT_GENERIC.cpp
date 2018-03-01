#include <iostream>
#include <exception>

using namespace std;

template<class myType>
class Element
{
	private:
		myType top;
		Element *previous;
	public:
		int getTop() { return top;  }
		Element* getPrev() { return previous ;}

		Element(int value, Element* prev)
		{
			top = value;
			previous = prev;
		}

};
template<class StockType>
class myStock
{
	private: 
		Element<StockType> *head;
		int size = 0;
	public:

		void push(StockType value)
		{
			Element <StockType>* pointer = head;
			head = new Element<StockType>(value, pointer);
			size++;
		}

		void peek()
		{
			cout << head->getTop(); 
		}

		void pop()
		{
			if (size == 0)
			{
				cout << "Stack is empty";
			}
			else
			{
				head = new Element<StockType>(head->getPrev()->getTop(), head->getPrev()->getPrev());
				size--;
			}
		}
};

int main()
{	
	myStock <long> a;
	a.push(5);
	a.peek();
	a.push(7);
	a.peek();
	a.push(12);
	a.pop();
	a.push(10);
	a.push(12);
}