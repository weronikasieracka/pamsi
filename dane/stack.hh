#ifndef STACK_HH
#define STACK_HH
#include<iostream>
#include <cmath>
using namespace std;
#define SIZE 20

template<typename T>
class Stack
{
    int value=SIZE;
    T *tab;  //do przechowywania danych
    int capacity; //size
    T begin; //pierwszy element
    T end;
    void Bigger();
    public:
    void push(const T& newElement);
    int size();
    bool isFull();
    bool isEmpty();
    T pop();
    T view();
    Stack(); //konstruktor
    ~Stack(); //destruktor
    Stack(const Stack &s);
};
template<typename T>
Stack<T>::Stack()
{
    tab = new T[value];
    capacity=value;
    begin=-1;
    end=-1;
}
template<typename T>
Stack<T>::~Stack()
{
    delete[] tab;	//zwalniamy pamięć
}
template<typename T>
Stack<T>::Stack(const Stack &s)
{
    if (s->begin != s->end)
    {
        T *pom;
        pom = s->end;
        end = new T;
        end.capacity = pom.capacity;
        end.next = new T;
        begin = end;
        while (pom.next != nullptr)
        {
            pom = pom->mext;
            begin.next = new T;
            begin = begin.next;
            begin.capacity = pom.capacity;
            begin.next=NULL;
        }
    }
    else
    {
        begin=end=NULL;
    }

}

template<typename T>
int Stack<T>::size()
{
    return begin+1;
}
template<typename T>
bool Stack<T>::isFull()
{
    return size()==capacity;
}
template<typename T>
bool Stack<T>::isEmpty()
{
    return size()==0;
}
template<typename T>
void Stack<T>::push(const T& newElement)
{
    if(isFull())	//jeśli kończy się miejsce
    {
        Bigger();	//stos się powiększa
        tab[++begin] = newElement;	//umieszczamy element na stosie
    }
    else
    {
        tab[++begin] = newElement;	//umieszczamy element na stosie
    }

}
template <typename T>
void Stack<T>::Bigger()
{
    T *next = new T[value+10];         //nowa tablica jest o 10 el. większa

	for(int i=0;i<value;++i)

		next[i] = tab[i];	//kopiujemy starą tablicę do nowej


	delete []tab;	//starą tablicę możemy skasować


	tab = next;		//teraz tab pokazuje na nową, większą tablicę

	value += 10;		//trzeba zapisać o ile powiększyliśmy tablicę

}
template <typename T>
T Stack<T>::pop()
{
    if(!isEmpty())
    {
        return tab[begin--];
    }
    else
    {
        cout << "Stos jest pusty"<<endl;
        exit(EXIT_FAILURE);
    }

}
template <typename T>
T Stack<T>::view()
{
    if(!isEmpty())
    {
        return tab[begin];
    }
    else
    {
        cout << "Stos jest pusty"<<endl;
        exit(EXIT_FAILURE);
    }

}

#endif
