#pragma once
#include "Generic_DS/Node.h"
#include <iostream>

template <class T>
class PriorityQ
{
private :

	Node<T>* backPtr;
	Node<T>* frontPtr;
public :
	PriorityQ<T>()
	{
		backPtr = nullptr;
		frontPtr = nullptr;
	}

	bool isEmpty() const 
	{
		if(frontPtr == nullptr)
			return true;
		else
			return false;
	}

	bool enqueue(const T& newEntry)
	{
		Node<T> * ptr = frontPtr;
		Node<T>* newNodePtr = new Node<T>(newEntry);
		// Insert the new node
		if (isEmpty())
		{
			frontPtr = newNodePtr; // The queue is empty
			newNodePtr -> setNext(nullptr);
			return true;
		}

		else if (newEntry < frontPtr -> getItem())
		{
			newNodePtr -> setNext(frontPtr);
			frontPtr = newNodePtr;
			return true;
		}

		else if (frontPtr -> getNext() == nullptr && newEntry > frontPtr -> getItem() )
		{
			frontPtr -> setNext(newNodePtr);
			newNodePtr -> setNext(nullptr);
			return true;
		}

		else 
		{
			while (ptr-> getNext())
			{
				if (ptr->getNext() -> getItem() > newEntry )
				{
					newNodePtr -> setNext(ptr ->getNext());
					ptr ->setNext (newNodePtr);
					return true;
				}
				ptr = ptr ->getNext();
			}

		}

		ptr ->setNext(newNodePtr);
		newNodePtr->setNext(nullptr);
		return true;
	}

	bool dequeue(T& frntEntry)
	{
		if(isEmpty())
			return false;

		Node<T>* nodeToDeletePtr = frontPtr;
		frntEntry = frontPtr->getItem();
		frontPtr = frontPtr->getNext();
		// Queue is not empty; remove front

		// Free memory reserved by the dequeued node
		delete nodeToDeletePtr;
		return true;
	}
	bool peekFront(T& frntEntry)  const
	{
		if(isEmpty())
			return false;

		frntEntry = frontPtr->getItem();
		return true;
	}

	//toArray function to be used ONLY when drawing the queue items
	const T* toArray(int& count) //returns array of T (array of items)
	{
		//IMPORTANT:
		//toArray function to be used ONLY when drawing the queue items

		count=0;

		if(!frontPtr)
			return nullptr;
		//counting the no. of items in the Queue
		Node<T>* p = frontPtr;
		while(p)
		{
			count++;
			p = p->getNext();
		}


		T* Arr= new T[count];
		p = frontPtr;
		for(int i=0; i<count;i++)
		{
			Arr[i] = p->getItem();
			p = p->getNext();
		}
		return Arr;
		//IMPORTANT:
		//toArray function to be used ONLY when drawing the queue items

	}

	~PriorityQ<T>()
	{
		T x;
		while (!isEmpty())
		{
			dequeue(x);
		}
	}
};





