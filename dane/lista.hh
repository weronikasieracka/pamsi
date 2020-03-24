#ifndef LISTA_HH
#define LISTA_HH
#include<iostream>
#include <cmath>
#include <iterator>
#include <list>
using namespace std;


template <typename T>
class element
{
    public:
    T value;
    element *next; // wskaźnik na następny element
    element(); //konstruktor
};


template <typename T>
element<T>::element()
{
    next = nullptr;

}
template <typename T>
   class Iterator
   {
       public:
       element<T> * itr;
       element<T> *begin();


   };
template <typename T>
 element<T> *Iterator<T>::begin()
 {
    return itr;
 }
template <typename T>
class List
{
    public:

        Iterator<T> it;
        element<T> *_begin; // wskaźnik na początek listy
        bool Empty();   //sprawdza czy lista jest pusta
        void pushBack( const T& newElement);
        void pushFront(const T& newElement);
        int list_size();
        void _insert(const T& newElement ,int index);
        void view_list();
        void remove(const T& element);
        Iterator<T>  begin ();
//        Iterator  end();
//        ConstIterator  cbegin () const;
//        ConstIterator  cend() const;
     T& operator [](int index);
        List();
        List(const List & Kopia);

};
template <typename T>
  T& List<T>::operator [](int index)
  {
      element<T> *tmp=_begin;
      for(int i=0; i<index; i++)
        tmp=tmp->next;

      return tmp->value;
  }

template <typename T>
List<T>::List(const List<T> & Kopia)
{
    _begin=Kopia._begin;
}
template <typename T>
Iterator<T> List<T>::begin ()
{
      return it.begin();
}
template <typename T>
List<T>::List() //tworzy listę z początkiem i końcem jako NULL
{
	_begin = nullptr;
}

#include "lista.hh"

template <typename T>
bool List<T>::Empty()
{
	if(_begin == NULL) //kiedy nie ma nic ani na początku to lista jest pusta
		return 1;
	else
		return 0;
}

template <typename T>
void List<T>::pushBack( const T& newElement)
{
    element<T> *new_ele = new element<T>;
    new_ele->value=newElement;
    if (Empty()) //sprawdzamy czy lista jest pusta
    {
        _begin=new_ele; //jeśli jest ustawiamy jako pierwszy element naszą zmienna
    }
    else
    {
        element<T> *temp = _begin;
        while (temp->next) //wędrujemy na koniec listy
        {
            temp = temp->next;
        }
    temp->next = new_ele;  // ostatni element wskazuje na nasz nowy
    new_ele->next = NULL;	 // ostatni nie wskazuje na nic
    }

}
template <typename T>
void List<T>::pushFront(const T& newElement)
{
    element<T> *new_ele = new element<T>;
    new_ele->value=newElement;
    new_ele->next= _begin;
    _begin = new_ele;
}
template <typename T>
int List<T>:: list_size()
{
int counter=0;
    if(_begin==NULL)
    {
    return counter;
    }
    else
    {
        element<T> *current=_begin;
        while (current != NULL)
        {
            counter++;
            current = current->next;
        }
    }
    return counter;
}






template <typename T>
void List<T>::_insert(const T& newElement ,int index)
{
    element<T> *new_ele = new element<T>;
    new_ele->value=newElement;
    element<T> *it = new element<T>;
    it=_begin;
    int counter =0; //licznik
    if (Empty()) //sprawdzamy czy lista jest pusta
    {
        pushFront(newElement);
    }
    else
    {
        if(index>=list_size())
        {
            pushBack(newElement);
        }
        else
        {
            while( it->next!=NULL)
        {
            counter++;
            if(counter==index)
            {
				new_ele->next = it->next;//ustawia wskaźnik, zeby wskazywal na nastepna rzecz
				it->next = new_ele;//poniej tamten zczyna wskazywac na nsz
                break;
            }

            it = it->next;

        }


        }

    }


}
template <typename T>
void List<T>::remove(const T& delelement)
{
    if (!Empty())
    {
        element<T> *current = new element<T>;
		element<T> *previous = new element<T>;
        element<T> *temp = new element<T>;

        current = _begin;
        if (current->value == delelement)
        {
			previous = _begin;
			_begin = _begin->next;

			delete previous;
		}
        while (current->next != NULL)
        {
            previous = current;
			current = current->next;
            if (current->value == delelement)
			{
				temp = current;
				previous->next = current->next;
				delete temp;
				break;
			}

        }

    }
    else
    {
    cout << "Nie mozna usunac, bo lista jest pusta"<<endl;
    }
}
template <typename T>
void List<T>::view_list()
{
    element<T> *it = _begin;
    while(it)
    {
     cout << it->value  <<endl;
     it=it->next;
    }
}


#endif
