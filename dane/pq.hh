#ifndef PQ_HH
#define PQ_HH
#include<iostream>
#include <cmath>
using namespace std;

template<typename T>
class Ele
{
    public:
    Ele *next;
    int priority;
    T data;
};
template<typename T>
class PriorityQueue
{
    private:

    public:
     Ele<T> *first;
    void enqueue(const T& newElement ,int priority);
    void dequeue();
    void view_dQ();
    PriorityQueue();
    ~PriorityQueue();
    PriorityQueue(const PriorityQueue &kopia );

};

template <typename T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue& kopia )
{
    first=kopia.first;
}
template <typename T>
PriorityQueue<T>::PriorityQueue() //Konstruktor = tworzymy pustą kolejke
{
    first = NULL;
}
template <typename T>
PriorityQueue<T>::~PriorityQueue() //Destruktor=usówa kolejke
{
  while(first)
{
  dequeue();
}
}

template <typename T>
void PriorityQueue<T>::enqueue(const T& newElement ,int priority)
{
    Ele<T> *f, *e;
    f = new Ele<T>;
    //inicjujemy pola nowego elementu
    f->priority = priority;
    f->data = newElement;
    if (first==NULL || priority < first->priority)
    {
        f->next=first;
        first=f;
    }
    else            //jeśli element ma najwyższy priorytet
    {
        e=first; //element wstawiamy na początek listy
        while (e->next != NULL && e->next->priority <= priority) //szukamy na liście pierwszego elementu o niższym priorytecie
        {
            e = e->next;
        }
        //nowy element wstawiamy przed element ( e→next )
        f->next = e->next;
        e->next = f;

    }

}
template <typename T>
void PriorityQueue<T>::dequeue()
{
    if(first==NULL)
    {
        cout << "Kolejka priorytetowa jest pusta"<<endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        Ele<T> * p = first;
        cout<<"Usunięty element to: "<<p->data<<endl;
        first = first->next; //odłączamy pierwszy element
        delete p;

    }

}
template <typename T>
void PriorityQueue<T>::view_dQ()
{
    Ele<T> *ptr;
    ptr = first;
    if(first==NULL)
    {
        cout << "Kolejka priorytetowa jest pusta"<<endl;
        exit(EXIT_FAILURE);
    }
    else
    {

        while(ptr != NULL)
        {
            cout<<"Prorytet elementu: "<<ptr->priority<<" "<<"Wartość elementu:"<<ptr->data<<endl;
            ptr = ptr->next;
        }

    }


}
#endif
