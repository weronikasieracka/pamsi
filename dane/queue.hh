#ifndef QUEUE_HH
#define QUEUE_HH
#include<iostream>
#include <cmath>
using namespace std;
#define SIZE 20
template<typename T>
class Queue
{
    public:
    T* tab; //do przechowywania danych
    int size;
    int front; //początek
    int end; //koniec
    int index(int i);

    void enqueue (const T& newElement);
    bool empty_Queue();
    bool full_Queue();
    void display();
    T dequeue ();
    Queue();
    Queue(const Queue & Kopia);
    ~Queue();
};


template <typename T>
Queue<T>::Queue(const Queue<T> & Kopia)
    {
     tab=Kopia.tab; //do przechowywania danych
     size=Kopia.size;
     front=Kopia.front; //początek
     end=Kopia.end; //koniec
    }
template <typename T>
Queue<T>::Queue()
{
	size=SIZE;
	front=0;
	end=0;
	tab = new T[size];
}
template <typename T>
Queue<T>::~Queue()
{
	delete[] tab; // zwolnienie zaalokowanej pamięci
}

template <typename T>
bool Queue<T>::empty_Queue()
{
	return end == front ;
}
template <typename T>

int Queue<T>::index(int i)
{
	return (i+1)%size;
}
template <typename T>
bool Queue<T>::full_Queue()
{
	return index(end) == front;
}
template <typename T>
T Queue<T>::dequeue()
{
	if(empty_Queue())
	{
        cout << "Kolejka jest pusta"<<endl;
        exit(EXIT_FAILURE);
	}
	else
	{
		T s = tab[front];
		front = index(front);
		return s;
	}
}
template <typename T>
void Queue<T>::enqueue(const T& newElement)
{
	if(full_Queue())
    {
        cout << "Kolejka jest pełna"<<endl;
        exit(EXIT_FAILURE);
    }
	else
	{
		tab[end]=newElement;
		end=index(end);
	}

}
template <typename T>
void Queue<T>::display()
{
    int i;
    if(empty_Queue())
	{
        cout << "Kolejka jest pusty"<<endl;
        exit(EXIT_FAILURE);
	}
    else
    {
        cout << "Elementy: ";
            for(i=front; i<end; i++)
            {
                cout << tab[i] << "\t";
            }
            cout<<endl;

    }

}
#endif
