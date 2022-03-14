#pragma once

template < typename T>
class PrtNode
{
private :
	T item; // A data item
	PrtNode<T>* next; // Pointer to next node
	double Priority; // an indication of the priority of the Fighters
public :
	PrtNode();
	PrtNode( const T & r_Item);	//passing by const ref.
	PrtNode( const T & r_Item, PrtNode<T>* nextNodePtr);
	void setItem( const T & r_Item);
	void setNext(PrtNode<T>* nextNodePtr);
	void setPriority (const double P);
	T getItem() const ;
	PrtNode<T>* getNext() const ;
	double getPriority () const;
}; // end Node


template < typename T>
PrtNode<T>::PrtNode() 
{
	next = nullptr;
} 

template < typename T>
PrtNode<T>::PrtNode( const T& r_Item)
{
	item = r_Item;
	next = nullptr;
} 

template < typename T>
PrtNode<T>::PrtNode( const T& r_Item, PrtNode<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}
template < typename T>
void PrtNode<T>::setItem( const T& r_Item)
{
	item = r_Item;
} 

template < typename T>
void PrtNode<T>::setNext(PrtNode<T>* nextNodePtr)
{
	next = nextNodePtr;
} 
template < typename T>
void PrtNode<T>::setPriority (const double P)
{
	Priority = P;
}
template < typename T>
T PrtNode<T>::getItem() const
{
	return item;
} 

template < typename T>
PrtNode<T>* PrtNode<T>::getNext() const
{
	return next;
} 

template < typename T>
double PrtNode<T>::getPriority() const
{
	return Priority;
}

